#ifndef VM_CONFIG_H
#define VM_CONFIG_H

#include <string>

class VMConfig {
	size_t stackCount, queueCount, threadCount, registerCount, memorySize,
			queueSize, pipeCount;
public:

	VMConfig();
	void setStackCount(size_t c);
	size_t getStackCount();
	void setQueueCount(size_t c);
	size_t getQueueCount();
	void setThreadCount(size_t c);
	size_t getThreadCount();

	void setRegisterCount(size_t c);
	size_t getRegisterCount();
	void setMemorySize(size_t c);
	size_t getMemorySize();

	void setQueueSize(size_t c);
	size_t getQueueSize();
	void setPipeCount(size_t c);
	size_t getPipeCount();
};

#endif
