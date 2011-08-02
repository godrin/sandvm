#ifndef VM_THREADS_H
#define VM_THREADS_H

#include "vm_thread.h"

class VMThreads {
	size_t maxCount;
	VMThread** threads;
	size_t currentIndex;
public:
	VMThreads(size_t pMaxCount);
	~VMThreads();
	VMThread *getNextThread();
	void rmThread(VMThread *thread);
	// 0  == nil
	// >0 threadid
	size_t addThread(VMThread *thread);
	// index+1 !
	VMThread *getThread(size_t index);
};

#endif
