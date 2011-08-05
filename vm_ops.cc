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
	case PUSHQ:
		return "PUSHQ";
	case POPQ:
		return "POPQ";
	case PUSHP:
		return "PUSHP";
	case POPP:
		return "POPP";
	case PUSHS:
		return "PUSHS";
	case POPS:
		return "POPS";
	case JOIN:
		return "JOIN";
	case THREADP:
		return "THREADP";
	case ASSERT:
		return "ASSERT";
	case DEBUGOUT:
		return "DEBUGOUT";
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
	if (s == "PUSHQ")
		return PUSHQ;
	if (s == "POPQ")
		return POPQ;
	if (s == "PUSHS")
		return PUSHS;
	if (s == "POPS")
		return POPS;
	if (s == "PUSHP")
		return PUSHP;
	if (s == "POPP")
		return POPP;
	if (s == "JOIN")
		return JOIN;
	if (s == "THREADP")
		return THREADP;
	if (s == "ASSERT")
		return ASSERT;
	if (s == "DEBGOUT")
		return DEBUGOUT;
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
	case SPL:
		return 2;
	case JMP:
	case JMZ:
	case JMN:
	case SLT:
	case JOIN:
		return 1;
	case CMP:
		return 2;
	case NOP:
		return 0;
	case PUSHQ:
	case POPQ:
	case PUSHS:
	case POPS:
	case PUSHP:
	case POPP:
	case THREADP:
	case ASSERT:
		return 2;
		return 2;
	case DEBUGOUT:
		return 1;

	}
	return 0;
}
