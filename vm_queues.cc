#include "vm_queues.h"
#include "vm_log.h"
#include "vm_config.h"

#define LOGLEVEL 1

VMQueue::VMQueue(size_t pSize, VMQueueMode pmode, size_t pid) :
		size(pSize), buffer(new Uint8[size]), writePtr(1), readPtr(0), mode(
				pmode), queueEnd(0), id(pid) {

}

VMQueue *VMQueue::clone(size_t pid) {
	VMQueue *q = new VMQueue(size, mode, pid);
	for (size_t x = 0; x < size; x++) {
		q->buffer[x] = buffer[x];
	}
	q->writePtr = writePtr;
	q->readPtr = readPtr;

	return q;
}

VMQueueType VMQueue::getQueueType() {
	if (mode == QUEUE_MODE_STACK)
		return QUEUE_TYPE_STACK;
	return QUEUE_TYPE_QUEUE;
}

void VMQueue::write(Uint8 c) {
	if (mode == QUEUE_MODE_OUT) {
		if (queueEnd)
			queueEnd->push(c);
		else
			std::cout << "out:" << c << "(" << ((int) c) << ")" << std::endl;
	} else if (mode == QUEUE_MODE_BOTH || mode == QUEUE_MODE_IN
			|| mode == QUEUE_MODE_STACK) {
		if (writePtr != readPtr) {
			buffer[writePtr++] = c;
			writePtr %= size;
		} else {
			throw VMQueueOverflow(getQueueType(), id);
		}
	}
}
Uint8 VMQueue::read() {
	if (mode == QUEUE_MODE_OUT) {
		throw VMQueueWrongUse(getQueueType(), id);
	} else if (mode == QUEUE_MODE_BOTH || mode == QUEUE_MODE_IN) {
		size_t next = (readPtr + 1) % size;
		if (writePtr != next) {
			readPtr = next;
			return buffer[readPtr];
		} else {
			throw VMQueueEmpty(getQueueType(), id);
		}
	} else if (mode == QUEUE_MODE_STACK) {
		size_t next = (writePtr - 1) % size;
		if (next != readPtr) {
			writePtr = next;
			return buffer[writePtr];
		} else {
			throw VMQueueEmpty(getQueueType(), id);
		}
	}
}

VMQueues::VMQueues(size_t count) :
		queues(count) {
}
VMQueues::VMQueues(VMConfig *config) :
		queues(config->getQueueCount()), stacks(config->getStackCount()), pipes(
				config->getPipeCount()) {

	for (size_t i = 0; i < config->getQueueCount(); i++)
		queues[i] = new VMQueue(config->getQueueSize(), QUEUE_MODE_BOTH, i);
	for (size_t i = 0; i < config->getStackCount(); i++)
		stacks[i] = new VMQueue(config->getQueueSize(), QUEUE_MODE_STACK, i);

}
VMPipeEnd *VMQueues::getQueue(size_t index, VMQueueType type) {
	VMPipeEnd *q = getQueueUnchecked(index, type);
	if (q == 0)
		throw VMQueueUndefined(type, index);
	return q;
}

VMPipeEnd *VMQueues::getQueueUnchecked(size_t index, VMQueueType type) {

	switch (type) {
	case QUEUE_TYPE_QUEUE:
		return queues[index % queues.size()];
	case QUEUE_TYPE_STACK:
		return stacks[index % stacks.size()];
	case QUEUE_TYPE_PIPE:
		return pipes[index % pipes.size()];
	}
}

void VMQueues::setQueue(size_t index, VMQueue *queue) {
	queues[index] = queue;
}

size_t getWritePipe(size_t index, VMConfig *config) {
	return 3 + config->getQueueCount() + config->getStackCount() + index * 2;
}
size_t getReadPipe(size_t index, VMConfig *config) {
	return getWritePipe(index, config) + 1;
}

VMQueues *VMQueues::clone(size_t threadIndex, VMConfig *config) {
	VMQueues *q = new VMQueues(config);

	return q;
}

void VMQueues::setPipe(size_t index, VMPipeEnd *q) {
	pipes[index % pipes.size()] = q;
}

VMQueueException::VMQueueException(VMQueueType t, size_t id) :
		queueType(t), queueId(id) {

}

size_t VMQueueException::getQueueId() {
	return queueId;
}
VMQueueType VMQueueException::getType() {
	return queueType;
}
