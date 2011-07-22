#ifndef VM_VM_H
#define VM_VM_H

#include "vm_memory.h"
#include "vm_queues.h"
#include "vm_threads.h"

class VMVm {
	VMMemory *memory;
	VMThreads *threads;

public:
	VMVm();
	VMMemory *getMemory();
	VMThreads *getThreads();

	void setMemory(VMMemory *p);
	void setThreads(VMThreads *p);
};

#endif
