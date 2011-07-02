#include "vm_ops.h"
#include "vm_memory.h"
#include "vm_loader.h"

#include <string>

VMLoader::VMLoader(VMMemory *m, std::istream &istream) :
		stream(istream), memory(m), ptr(0) {

}

void VMLoader::load() {
	char code;

	while (!stream.eof()) {
		stream >> code;

		switch (code) {
		case 'x':
			readInstruction();
			break;
		case 'b':
			readByte();
			break;
		case 's':
			readString();
			break;
		case 'i':
			readUint32();
			break;
		case 'u':
			readUint8();
			break;
		}
	}
}

VMOps getOp(const std::string &s) {

	if (s == "DAT")
		return DAT;
	if (s == "MOVE")
		return MOVE;
	if (s == "ADD")
		return ADD;
	if (s == "SUB")
		return SUB;
	if (s == "MUL")
		return MUL;
	if (s == "DIV")
		return DIV;
	if (s == "MOD")
		return MOD;
	if (s == "JMP")
		return JMP;
	if (s == "JMZ")
		return JMZ;
	if (s == "JMN")
		return JMN;
	if (s == "SPL")
		return SPL;
	if (s == "SLT")
		return SLT;
	if (s == "CMP")
		return CMP;
	if (s == "NOP")
		return NOP;
	return NOP;
}

void VMLoader::readInstruction() {
	std::string s;
	stream >> s;
	memory->set(ptr++, getOp(s));

}
void VMLoader::readUint32() {
	Uint32::__type i;
	stream >> i;
	Uint32 x(i);
	for (int c = 0; c < 4; c++) {
		memory->set(ptr++, x.get(c));
	}
}
void VMLoader::readUint8() {
	Uint32::__type i;
	stream >> i;
	Uint8 x(i);
	memory->set(ptr++, x);
}
void VMLoader::readString() {
	Uint32::__type _len;
	stream >> _len;
	char *buffer = new char[_len];

	stream.get();
	stream.read(buffer, _len);
	stream.get();

	for (int c = 0; c < _len; c++) {
		memory->set(ptr++, buffer[c]);
	}
}

void VMLoader::readByte() {
	char c;
	stream >> c;
	memory->set(ptr++, c);
}
