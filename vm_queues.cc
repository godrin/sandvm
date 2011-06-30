#include "vm_queues.h"

VMQueue::VMQueue(size_t pSize) :
		size(pSize), buffer(new VMMemoryData[size]), writePtr(0), readPtr(0) {

}

void VMQueue::push(VMMemoryData c) {

}
VMMemoryData VMQueue::pop() {

}

VMQueues::VMQueues(size_t count) :
		queues(count) {

}
VMQueue *VMQueues::getQueue(size_t index) {
	return queues[index];
}
