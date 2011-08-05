#ifndef VM_PIPEEND_H
#define VM_PIPEEND_H

#include "vm_pipe.h"
#include "vm_types.h"

class VMPipeEnd {
public:
	virtual void write(Uint8 b)=0;
	virtual Uint8 read()=0;

	VMMemoryArray read(VMType t);

	VMMemoryArray read(size_t size);
	virtual void write(const VMMemoryArray &a);
};

class VMPipeEndIO: public VMPipeEnd {
public:
	virtual ~VMPipeEndIO();

	void write(Uint8 b);
	Uint8 read();
};

class VMPipeEndAPI: public VMPipeEnd {
public:
	virtual ~VMPipeEndAPI();

	void write(Uint8 b);
	Uint8 read();
};

class VMPipeEndQueue: public VMPipeEnd {
	VMPipe *pipe;
	bool first;
public:
	VMPipeEndQueue(VMPipe *p, bool pfirst);
	virtual ~VMPipeEndQueue();

	void write(Uint8 b);
	Uint8 read();
};

#endif
