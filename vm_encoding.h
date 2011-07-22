#ifndef VM_ENCODING_H
#define VM_ENCODING_H

#include "vm_types.h"

class VMMemory;
class VMInstruction;

class VMEncodingException {
	size_t where;
public:
	VMEncodingException(size_t pwhere);
	size_t pos();
};

class VMEncoding {
public:
	// returns size of encoding
	size_t encode(VMMemory *memory, size_t pos, VMInstruction *instruction);
	size_t decode(VMMemory *memory, size_t pos, VMInstruction *instruction);

};

#endif
