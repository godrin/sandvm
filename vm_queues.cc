#include "vm_queues.h"
#include "vm_log.h"

#define LOGLEVEL 1

VMQueue::VMQueue(size_t pSize, Mode pmode) :
		size(pSize), buffer(new VMMemoryData[size]), writePtr(1), readPtr(0), mode(
				pmode), queueEnd(0) {

}

void VMQueue::push(VMMemoryData c) {
	if (mode == OUT) {
		if (queueEnd)
			queueEnd->push(c);
		else
			std::cout << "out:" << c.value() << "(" << ((int) c.value()) << ")"
					<< std::endl;
	} else if (mode == BOTH || mode == IN || mode == STACK) {
		if (writePtr != readPtr) {
			buffer[writePtr++] = c;
			writePtr %= size;
		} else {
			throw VMQueueOverflow();
		}
	}
}
VMMemoryData VMQueue::pop() {
	if (mode == OUT) {
		throw VMQueueWrongUse();
	} else if (mode == BOTH || mode == IN) {
		size_t next = (readPtr + 1) % size;
		if (writePtr != next) {
			readPtr = next;
			return buffer[readPtr];
		} else {
			throw VMQueueEmpty();
		}
	} else if (mode == STACK) {
		size_t next = (writePtr - 1) % size;
		if (next != readPtr) {
			writePtr = next;
			return buffer[writePtr];
		} else {
			throw VMQueueEmpty();
		}
	}
}

VMQueues::VMQueues(size_t count) :
		queues(count) {

}
VMQueue *VMQueues::getQueue(size_t index) {
	if (!queues[index]) {
		logger(LOGLEVEL) << "VMQueues::getQueue(" << index << ") is null!"
				<< vmlog::endl;

		throw int();
	}
	return queues[index];
}

void VMQueues::setQueue(size_t index, VMQueue *queue) {
	queues[index] = queue;
}

