#ifndef VM_ARG_H
#define VM_ARG_H

#include "vm_types.h"
#include "vm_memory.h"

/*
 *
 * "R" - existant => register - not => address
 * "*" - existant => indirect - not => direct
 */

class VMArg {
	VMMemoryData value;
	bool mRegister;
	bool indirect;
public:
	bool isRegister();
	bool isAddress();

	bool isIndirect();
	bool isDirect();
	VMMemoryData getValue();

	void setValue(VMMemoryData data);
	void setRegister(bool reg);
	void setDirect(bool d);
};

VMArg reg(VMMemoryData d);
VMArg ireg(VMMemoryData d);
VMArg val(VMMemoryData d);
VMArg mem(VMMemoryData d);

#endif

