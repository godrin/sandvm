#include "vm_ops.h"

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

	}
	return "UNKNOWN";
}
