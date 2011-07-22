#ifndef VM_QUEUES_H
#define VM_QUEUES_H

#include <vector>

#include "vm_memory.h"

class VMQueueEnd {
public:
	virtual VMMemoryData push(VMMemoryData data)=0;
};

class VMQueueOverflow {

};
class VMQueueWrongUse {

};
class VMQueueEmpty {

};

class VMQueue {
public:
	enum Mode {
		IN, OUT, BOTH, STACK
	};
private:
	size_t size;
	VMMemoryData *buffer;
	size_t writePtr, readPtr;
	Mode mode;
	VMQueueEnd *queueEnd;

public:
	VMQueue(size_t pSize, Mode pmode);
	void push(VMMemoryData c);
	VMMemoryData pop();

};

class VMQueues {
	std::vector<VMQueue*> queues;

public:
	VMQueues(size_t count);
	VMQueue *getQueue(size_t index);
	void setQueue(size_t index, VMQueue *queue);

};

#endif
