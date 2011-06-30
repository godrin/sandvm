#ifndef VM_QUEUES_H
#define VM_QUEUES_H

#include <vector>

#include "vm_memory.h"

class VMQueue {
	size_t size;
	VMMemoryData *buffer;
	size_t writePtr, readPtr;

public:
	VMQueue(size_t pSize);
	void push(VMMemoryData c);
	VMMemoryData pop();
};

class VMQueues {
	std::vector<VMQueue*> queues;

public:
	VMQueues(size_t count);
	VMQueue *getQueue(size_t index);

};

#endif
