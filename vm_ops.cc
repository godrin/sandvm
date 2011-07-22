#include "vm_ops.h"
#include "vm_tools.h"

std::string toString(VMOps op) {
	switch (op) {
	case DAT:
		return "DAT";
	case MOVE:
		return "MOVE";
	case ADD:
		return "ADD";
	case SUB:
		return "SUB";
	case MUL:
		return "MUL";
	case DIV:
		return "DIV";
	case MOD:
		return "MOD";
	case JMP:
		return "JMP";
	case JMZ:
		return "JMZ";
	case JMN:
		return "JMN";
	case SPL:
		return "SPL";
	case SLT:
		return "SLT";
	case CMP:
		return "CMP";
	case NOP:
		return "NOP";
	case PUSH:
		return "PUSH";
	case POP:
		return "POP";

	}
	return "UNKNOWN";
}

VMOps getOp(const std::string &x) {
	std::string s = toUpper(x);
	if (s == "DAT" || s == "STOP")
		return DAT;
	if (s == "MOVE" || s == "MOV")
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
	if (s == "JMZ" || s == "JZ")
		return JMZ;
	if (s == "JMN" || s == "JNZ")
		return JMN;
	if (s == "SPL")
		return SPL;
	if (s == "SLT")
		return SLT;
	if (s == "CMP")
		return CMP;
	if (s == "NOP")
		return NOP;
	if (s == "PUSH")
		return PUSH;
	if (s == "POP")
		return POP;
	return INV;
}

size_t opSize(VMOps op) {
	switch (op) {
	case DAT:
		return 0;
	case MOVE:
	case ADD:
	case SUB:
	case MUL:
	case DIV:
	case MOD:
		return 2;
	case JMP:
	case JMZ:
	case JMN:
	case SPL:
	case SLT:
		return 1;
	case CMP:
		return 2;
	case NOP:
		return 0;
	case PUSH:
		return 2;
	case POP:
		return 2;

	}
	return 0;
}
