#ifndef VM_ARG_H
#define VM_ARG_H

#include "vm_types.h"
#include "vm_memory.h"

#include <string>

/*
 *
 * "R" - existant => register - not => address
 * "*" - existant => indirect - not => direct
 */

class VMArg {
	//VMMemoryData value;
	bool mRegister;
	bool indirect;
	union {
		Uint8 byte;
		Uint16 word;
		Uint32 dword;
	};
	std::string data;
public:
	bool isRegister();
	bool isAddress();

	bool isIndirect();
	bool isDirect();
	VMMemoryData getValue(VMType t);
	Uint8 getUint8();
	Uint16 getUint16();
	Uint32 getUint32();
	const std::string &getString();
	void set(Uint8 v);
	void set(Uint16 v);
	void set(Uint32 v);
	void set(const std::string &s);

	void setValue(VMMemoryData data, VMType t);
	void setRegister(bool reg);
	void setDirect(bool d);

	std::string toString(VMType t);
};

#endif

