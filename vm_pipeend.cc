#include "vm_pipeend.h"
#include "vm_queues.h"
#include <iostream>

VMMemoryArray VMPipeEnd::read(size_t size) {
	VMMemoryArray x;
	for (size_t i = 0; i < size; i++)
		x.push_back(read());
	return x;
}
void VMPipeEnd::write(const VMMemoryArray &a) {
	for (VMMemoryArray::const_iterator i = a.begin(); i != a.end(); i++) {
		write(*i);
	}
}

VMMemoryArray VMPipeEnd::read(VMType t) {
	if (t == STRING) {
		Uint32 a = toUint32(read(DWORD));
		return read(a);
	} else {
		size_t l;
		switch (t) {
		case BYTE:
			l = 1;
			break;
		case WORD:
			l = 2;
			break;
		case DWORD:
		case ADDRESS:
			l = 4;
			break;
		default:
			throw int();
		}
		return read(l);
	}
}

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
	std::cout << (char) b;
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
