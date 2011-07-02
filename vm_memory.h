#ifndef VM_MEMORY
#define VM_MEMORY

#include <iostream>
#include <vector>
#include <stddef.h>

#include "vm_types.h"

typedef Uint8 VMMemoryData;

class VMMemoryCell {
	VMMemoryData data;
public:
	VMMemoryData get();
	void set(VMMemoryData data);
};

class VMMemory {
	VMMemoryCell *cells;
	size_t size;
	std::string type;

public:
	VMMemory(size_t psize,std::string pTypename);
	~VMMemory();

	void set(VMMemoryData index, VMMemoryData data);
	VMMemoryData get(VMMemoryData index);

	VMMemory *clone();

};

typedef VMMemory VMRegisters;

#endif

