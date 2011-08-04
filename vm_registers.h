#ifndef VM_REGISTERS_H
#define VM_REGISTERS_H

#include "vm_types.h"
#include <vector>
#include <string>

class VMRegisters {
	std::vector<Uint32> vals;
	std::string name;
public:
	VMRegisters(size_t regCount, std::string pName);

	Uint32 get(size_t pos);
	void set(size_t pos,Uint32 val);

	VMRegisters *clone();
};

#endif
