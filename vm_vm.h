#ifndef VM_VM_H
#define VM_VM_H

#include "vm_memory.h"
#include "vm_queues.h"
#include "vm_threads.h"

class VMVm {
	VMMemory *memory;
	VMQueues *queues;
	VMThreads *threads;

public:
	VMVm();
	VMMemory *getMemory();
	VMQueues *getQueues();
	VMThreads *getThreads();

	void setMemory(VMMemory *p);
	void setQueues(VMQueues *p);
	void setThreads(VMThreads *p);
};

#endif
