#ifndef VM_MEMORY
#define VM_MEMORY

#include <iostream>
#include <vector>
#include <stddef.h>

#include "vm_types.h"


class VMMemory {
	VMMemoryArray cells;
	std::string type;

public:
	VMMemory(size_t psize, std::string pTypename);
	~VMMemory();

	void set(VMMemoryData index, VMMemoryData data);
	void set(VMMemoryAddress addr, VMMemoryArray data);
	VMMemoryData get(VMMemoryData index);

	VMMemory *clone();

	Uint8 getUint8(size_t p);
	Uint16 getUint16(size_t p);
	Uint32 getUint32(size_t p);
	std::string getStdString(size_t p);

	VMMemoryArray getArray(size_t p, VMType t);
	Uint32 getValue(size_t p, VMType t);

};


VMMemoryArray toArray(Uint8 b);
VMMemoryArray toArray(Uint16 b);
VMMemoryArray toArray(Uint32 b);
VMMemoryArray toArray(std::string b);
VMMemoryArray toArray(size_t p, VMType t);

Uint8 toUint8(const VMMemoryArray &a, size_t p = 0);
Uint16 toUint16(const VMMemoryArray &a, size_t p = 0);
Uint32 toUint32(const VMMemoryArray &a, size_t p = 0);
std::string toStdString(const VMMemoryArray &a, size_t p = 0);
Uint32 toValue(const VMMemoryArray &a, VMType t, size_t p = 0);

#endif

