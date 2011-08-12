#ifndef VM_PIPE_H
#define VM_PIPE_H

#include "vm_types.h"

class VMPipeEnd;
class VMQueue;

class VMPipe {
	VMQueue *q0, *q1;

public:
	VMPipe(size_t queueLength);

	void write(Uint8 c,bool first);
	Uint8 read(bool first);

	VMPipeEnd *getPipeEnd(bool first);
};

#endif
