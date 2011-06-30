#ifndef VM_OPS_H
#define VM_OPS_H

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
	NOP
	//LDP,
	//STP
};


#endif

