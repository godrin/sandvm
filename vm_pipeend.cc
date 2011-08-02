#include "vm_pipeend.h"
#include "vm_queues.h"
#include <iostream>

VMPipeEndQueue::VMPipeEndQueue(VMPipe *p, bool pfirst) :
		pipe(p), first(pfirst) {

}
VMPipeEndQueue::~VMPipeEndQueue() {

}

void VMPipeEndQueue::write(Uint8 b) {
	pipe->write(b, first);
}
Uint8 VMPipeEndQueue::read() {
	return pipe->read(first);
}

VMPipeEndIO::~VMPipeEndIO() {

}

void VMPipeEndIO::write(Uint8 b) {
	//std::cout << "IO:" << ((int) b) << std::endl;
	std::cout<<(char)b;
}
Uint8 VMPipeEndIO::read() {
	throw VMQueueEmpty(QUEUE_TYPE_PIPE, 0);
}

VMPipeEndAPI::~VMPipeEndAPI() {

}

void VMPipeEndAPI::write(Uint8 b) {

}
Uint8 VMPipeEndAPI::read() {

}
