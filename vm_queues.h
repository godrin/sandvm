#ifndef VM_QUEUES_H
#define VM_QUEUES_H

#include <vector>

#include "vm_memory.h"
#include "vm_pipeend.h"

class VMConfig;
class VMVm;
class VMPipeEnd;

class VMQueueEnd {
public:
	virtual VMMemoryData push(VMMemoryData data)=0;
};

enum VMQueueMode {
	QUEUE_MODE_IN, QUEUE_MODE_OUT, QUEUE_MODE_BOTH, QUEUE_MODE_STACK
};

enum VMQueueType {
	QUEUE_TYPE_STACK, QUEUE_TYPE_QUEUE, QUEUE_TYPE_PIPE
};

class VMQueue: public VMPipeEnd {
public:

private:
	size_t size;
	Uint8 *buffer;
	size_t writePtr, readPtr;
	VMQueueMode mode;
	VMQueueEnd *queueEnd;
	size_t id;

public:
	VMQueue(size_t pSize, VMQueueMode pmode, size_t pid);
	void write(Uint8 c);
	Uint8 read();

	VMQueue *clone(size_t pid);

	VMQueueType getQueueType();

	virtual void write(const VMMemoryArray &a);

};

class VMQueues {
	std::vector<VMQueue*> queues;
	std::vector<VMQueue*> stacks;
	std::vector<VMPipeEnd*> pipes;
	VMVm *vm;

public:

	static const int IO = 0;
	static const int API = 1;

	VMQueues(size_t count);
	VMQueues(VMConfig *config);
	VMPipeEnd *getQueue(size_t index, VMQueueType type);
	VMPipeEnd *getQueueUnchecked(size_t index, VMQueueType type);
	void setQueue(size_t index, VMQueue *queue);
	void setPipe(size_t index, VMPipeEnd *pipeEnd);

	VMQueues *clone(size_t threadIndex, VMConfig *config);

};

class VMQueueException {
public:
	VMQueueException(VMQueueType t, size_t id);

	size_t getQueueId();
	VMQueueType getType();
private:
	VMQueueType queueType;
	size_t queueId;

};

class VMQueueOverflow: public VMQueueException {
public:
	VMQueueOverflow(VMQueueType t, size_t id) :
			VMQueueException(t, id) {
	}
};
class VMQueueWrongUse: public VMQueueException {
public:
	VMQueueWrongUse(VMQueueType t, size_t id) :
			VMQueueException(t, id) {
	}

};
class VMQueueEmpty: public VMQueueException {
public:
	VMQueueEmpty(VMQueueType t, size_t id) :
			VMQueueException(t, id) {
	}

};

class VMQueueUndefined: public VMQueueException {
public:
	VMQueueUndefined(VMQueueType t, size_t id) :
			VMQueueException(t, id) {
	}

};

#endif
