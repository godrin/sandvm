#ifndef VM_VM_H
#define VM_VM_H

#include "vm_memory.h"
#include "vm_queues.h"
#include "vm_threads.h"
#include "vm_config.h"

#include <map>

class VMPipe;
class VMPipeEnd;
class VMApi;

class VMVm {
	VMMemory *memory;
	VMThreads *threads;

	VMConfig config;
	VMApi *api;

	// pipes between threads
	std::map<std::pair<size_t, size_t>,VMPipe*> threadPipes;

public:
	VMVm();
	VMMemory *getMemory();
	VMThreads *getThreads();

	void setMemory(VMMemory *p);
	void setThreads(VMThreads *p);

	VMConfig *getConfig();

	VMPipeEnd *getThreadPipe(size_t from, size_t to);
	VMPipeEnd *getIOPipe();
	VMPipeEnd *getAPIPipe();

	void threadDeleted(size_t id);

	VMApi *getApi();
};

#endif
