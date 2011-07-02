#ifndef VM_STACK_H
#define VM_STACK_H

#include "vm_memory.h"

class VMOverflowError {

};
class VMUnderflowError {

};

class VMStack {
	VMMemoryData *data;
	size_t size;
	size_t p;
public:
	VMStack(size_t psize);
	~VMStack();
	void push(VMMemoryData p) throw (VMOverflowError);
	VMMemoryData pop() throw (VMUnderflowError);

};

#endif
