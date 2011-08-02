#ifndef VM_OPS_H
#define VM_OPS_H

#include <string>

enum VMOps {
	DAT,
	MOVE,
    ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	JMP,
	JMZ, // jump,if zflag
	JMN, // jump,if not zflag
	SPL, // split off thread
	SLT, // less than -> zflag=>true
	CMP, //equal -> zflag=>true
	NOP,
	INV, // INVALID
	PUSHQ, // queue
	POPQ,
	PUSHS, // stack
	POPS,
	PUSHP, // pipe
	POPP,
	JOIN,
	THREADP,
	//LDP,
	//STP
	INVALID_OP
};

std::string toString(VMOps op);

size_t opSize(VMOps op);
VMOps getOp(const std::string &s);


#endif

