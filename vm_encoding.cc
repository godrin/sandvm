#include "vm_encoding.h"
#include "vm_instruction.h"
#include "vm_log.h"

#define LOGLEVEL 5

VMEncodingException::VMEncodingException(size_t pwhere) :
		where(pwhere) {

}
size_t VMEncodingException::pos() {
	return where;
}

Uint8 getFlags(VMInstruction *instruction) {
	bool aDirect = instruction->getArg0()->isDirect();
	bool bDirect = instruction->getArg1()->isDirect();
	bool aRegister = instruction->getArg0()->isRegister();
	bool bRegister = instruction->getArg1()->isRegister();
	Uint8 type = instruction->getType();
	Uint8 result;
	if (type < INVALID_TYPE) {
		result = type;
	} else
		throw new int();

	if (aDirect)
		result |= 0x10;
	if (bDirect)
		result |= 0x20;
	if (aRegister)
		result |= 0x40;
	if (bRegister)
		result |= 0x80;
	return result;
}

void setFlags(Uint8 flags, VMInstruction *instruction) {
	Uint8 type = flags & 0xF;
	if (type < INVALID_TYPE) {
		instruction->setType((VMType) type);
	} else {
		throw new int();
	}
	bool aDirect = flags & 0x10;
	bool bDirect = flags & 0x20;
	bool aRegister = flags & 0x40;
	bool bRegister = flags & 0x80;
	instruction->getArg0()->setDirect(aDirect);
	instruction->getArg1()->setDirect(bDirect);
	instruction->getArg0()->setRegister(aRegister);
	instruction->getArg1()->setRegister(bRegister);
}

size_t encodeArg(VMMemory *memory, size_t pos, VMArg *arg, VMType type) {
	size_t len = 0;
	logger(LOGLEVEL) << "encode arg at:" << pos << " value:"
			<< arg->getValue(type) << vmlog::endl;
	switch (type) {
	case BYTE: {
		Uint8 byte = arg->getUint8();
		if (memory)
			memory->set(pos++, byte);
		len++;
	}
		break;
	case WORD: {
		Uint16 word = arg->getUint16();
		if (memory)
			memory->set(pos++, word & 0xFF);
		len++;
		if (memory)
			memory->set(pos++, (word >> 8) & 0xFF);
		len++;
	}
		break;
	case DWORD: {

		Uint32 word = arg->getUint32();
		if (memory)
			memory->set(pos++, word & 0xFF);
		len++;
		if (memory)
			memory->set(pos++, (word >> 8) & 0xFF);
		len++;
		if (memory)
			memory->set(pos++, (word >> 16) & 0xFF);
		len++;
		if (memory)
			memory->set(pos++, (word >> 24) & 0xFF);
		len++;
	}
		break;
	}
	return len;

}

size_t VMEncoding::encode(VMMemory *memory, size_t start,
		VMInstruction *instruction) {
	size_t pos = start;
	size_t len = 0;

	logger(LOGLEVEL) << "encoding:" << toString(instruction->getOp())
			<< vmlog::endl;

	VMOps op = instruction->getOp();
	if (memory)
		memory->set(pos++, op);
	len++;

	Uint8 flags = getFlags(instruction);
	if (memory)
		memory->set(pos++, flags);
	len++;

	size_t parameterCount = opSize(op);
	if (parameterCount > 0) {

		VMArg *arg = instruction->getArg0();
		size_t add = encodeArg(memory, pos, arg, instruction->getType());
		pos += add;
		len += add;

	}
	if (parameterCount > 1) {
		VMArg *arg = instruction->getArg1();
		size_t add = encodeArg(memory, pos, arg, instruction->getType());
		pos += add;
		len += add;

	}

	return len;
}
size_t decodeArg(VMArg *arg, VMType type, VMMemory *memory, size_t pos) {
	size_t len = 0;
	if (type == DWORD) {
		Uint32 v = (((Uint32) memory->get(pos + 3)) << 24)
				| (((Uint32) memory->get(pos + 2)) << 16)
				| (((Uint32) memory->get(pos + 1)) << 8)
				| (((Uint32) memory->get(pos)));
		arg->set(v);
		len = 4;

	} else if (type == WORD) {
		Uint16 v = (((Uint16) memory->get(pos + 1)) << 8)
				| (((Uint16) memory->get(pos)));
		arg->set(v);
		len = 2;
	} else if (type == BYTE) {
		Uint8 v = ((Uint8) memory->get(pos));
		arg->set(v);
		len = 1;
	}
	return len;
}

size_t VMEncoding::decode(VMMemory *memory, size_t start,
		VMInstruction *instruction) {
	size_t pos = start;
	size_t len = 0;

	Uint8 v = memory->get(pos);
	if (v >= INVALID_OP)
		throw VMEncodingException(start);
	instruction->setOp((VMOps) v);

	pos++, len++;
	Uint8 flags = memory->get(pos);
	setFlags(flags, instruction);
	pos++, len++;
	size_t arity = opSize(instruction->getOp());
	if (arity > 0) {
		size_t s = decodeArg(instruction->getArg0(), instruction->getType(),
				memory, pos);
		pos += s;
		len += s;
	}
	if (arity > 1) {
		size_t s = decodeArg(instruction->getArg1(), instruction->getType(),
				memory, pos);
		pos += s;
		len += s;
	}
	logger(LOGLEVEL) << "setLen:" << len << vmlog::endl;
	instruction->setLen(len);

	return len;
}
