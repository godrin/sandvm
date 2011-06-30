#include "vm_vm.h"

VMVm::VMVm() :
		memory(0), queues(0), threads(0) {

}
VMMemory *VMVm::getMemory() {
	return memory;
}
VMQueues *VMVm::getQueues() {
	return queues;
}
VMThreads *VMVm::getThreads() {
	return threads;
}

void VMVm::setMemory(VMMemory *p) {
	memory = p;
}
void VMVm::setQueues(VMQueues *p) {
	queues = p;
}
void VMVm::setThreads(VMThreads *p) {
	threads = p;
}
