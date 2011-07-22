#include "vm_instruction.h"
#include "vm_ops.h"

VMArg *VMInstruction::getArg0() {
	return &arg0;
}
VMArg *VMInstruction::getArg1() {
	return &arg1;
}

VMOps VMInstruction::getOp() {
	return op;
}

VMInstruction ins(VMOps op, VMArg a) {
	VMInstruction i;
	i.setOp(op);
	i.setArg0(a);
	return i;
}
VMInstruction ins(VMOps op, VMArg a, VMArg b) {
	VMInstruction i;
	i.setOp(op);
	i.setArg0(a);
	i.setArg1(b);
	return i;

}

void VMInstruction::setOp(VMOps p) {
	op = p;
}
void VMInstruction::setArg0(VMArg a) {
	arg0 = a;
}
void VMInstruction::setArg1(VMArg b) {
	arg1 = b;
}

VMType VMInstruction::getType() {
	return type;
}
void VMInstruction::setType(VMType ptype) {
	type = ptype;
}

std::string VMInstruction::toString() {
	std::string s = "<Op";
	s += ::toString(getOp());
	s += ".";
	switch (type) {
	case BYTE:
		s += "b";
		break;
	case WORD:
		s += "w";
		break;
	case DWORD:
		s += "d";
		break;
	}

	s += " ";
	size_t arity = opSize(getOp());
	if (arity > 0) {
		s += " arg0:";
		s += arg0.toString(getType());
	}
	if (arity > 1) {
		s += " arg1:";
		s += arg1.toString(getType());
	}
	return s + ">";
}

size_t VMInstruction::getLen() {
	return len;
}
void VMInstruction::setLen(size_t l) {
	len = l;
}
