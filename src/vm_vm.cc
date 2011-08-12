#include "vm_vm.h"
#include "vm_pipe.h"
#include "vm_pipeend.h"
#include "api/vm_api.h"

VMVm::VMVm() :
		memory(0), threads(0) {
	api = new VMApi(this);
}
VMMemory *VMVm::getMemory() {
	return memory;
}
VMThreads *VMVm::getThreads() {
	return threads;
}

void VMVm::setMemory(VMMemory *p) {
	memory = p;
}

void VMVm::setThreads(VMThreads *p) {
	threads = p;
}

VMConfig *VMVm::getConfig() {
	return &config;
}

VMPipeEnd *VMVm::getIOPipe() {
	return new VMPipeEndIO();
}
VMPipeEnd *VMVm::getAPIPipe() {
	return new VMPipeEndAPI();
}

VMPipeEnd *VMVm::getThreadPipe(size_t from, size_t to) {
	if (from == to)
		return 0;

	std::pair<size_t, size_t> index;
	bool first;

	if (from < to) {
		index = std::make_pair(from, to);
		first = true;
	} else {
		index = std::make_pair(to, from);
		first = false;
	}

	if (threadPipes[index] == 0) {
		threadPipes[index] = new VMPipe(config.getQueueSize());
	}
	return threadPipes[index]->getPipeEnd(first);
}

void VMVm::threadDeleted(size_t id) {
	std::cout << "Thread deleted:" << id << std::endl;
}

VMApi *VMVm::getApi() {
	return api;
}
