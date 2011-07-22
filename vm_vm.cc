#include "vm_vm.h"

VMVm::VMVm() :
		memory(0), threads(0) {

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
