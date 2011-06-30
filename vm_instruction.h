#ifndef VM_INSTRUCTION_H
#define VM_INSTRUCTION_H

#include "vm_ops.h"
#include "vm_arg.h"

#include <vector>

class VMInstruction {
	VMOps op;
	VMArg arg0,arg1;

public:
	VMOps getOp();

	VMArg *getArg0();
	VMArg *getArg1();

	void set(VMMemory *memory,size_t ip);

	void setOp(VMOps op);
	void setArg0(VMArg a);
	void setArg1(VMArg a);

	void putAt(VMMemory *memory,size_t pos);
};

VMInstruction ins(VMOps op,VMArg a);
VMInstruction ins(VMOps op,VMArg a,VMArg b);

#endif
