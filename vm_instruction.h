#ifndef VM_INSTRUCTION_H
#define VM_INSTRUCTION_H

#include "vm_ops.h"
#include "vm_arg.h"

#include <vector>
#include <string>


class VMInstruction {
	VMOps op;
	VMArg arg0, arg1;
	VMType type;
	size_t len;

public:
	VMOps getOp();
	VMType getType();
	void setType(VMType type);

	VMArg *getArg0();
	VMArg *getArg1();

	void setOp(VMOps op);
	void setArg0(VMArg a);
	void setArg1(VMArg a);

	std::string toString();
	size_t getLen();
	void setLen(size_t l);
};

VMInstruction ins(VMOps op, VMArg a);
VMInstruction ins(VMOps op, VMArg a, VMArg b);

#endif
