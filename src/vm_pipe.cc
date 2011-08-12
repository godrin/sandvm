#include "vm_pipe.h"
#include "vm_queues.h"

VMPipe::VMPipe(size_t queueLength) :
		q0(new VMQueue(queueLength, QUEUE_MODE_BOTH,0)), q1(
				new VMQueue(queueLength, QUEUE_MODE_BOTH,0)) {

}

void VMPipe::write(Uint8 c, bool first) {
	if (first)
		q0->write(c);
	else
		q1->write(c);
}
Uint8 VMPipe::read(bool first) {
	if (first)
		return q1->read();
	else
		return q0->read();
}

VMPipeEnd *VMPipe::getPipeEnd(bool first) {
	return new VMPipeEndQueue(this, first);
}

