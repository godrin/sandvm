#include "vm_vm.h"
#include "vm_sim.h"
#include "vm_threads.h"

#include "vm_defines.h"

int main() {
	VMVm vm;
	std::cout << "1" << std::endl;
	vm.setThreads(new VMThreads(VM_THREAD_COUNT_PER_VM));
	vm.setMemory(new VMMemory(VM_MEMORY_SIZE));
	vm.setQueues(new VMQueues(VM_QUEUE_COUNT));
	vm.getMemory()->set(0, NOP);
	vm.getMemory()->set(10,11);
	ins(JMP, mem(10)).putAt(vm.getMemory(), 4);

	VMThread *thread = new VMThread();
	thread->setMemory(vm.getMemory());
	thread->setRegisters(new VMRegisters(VM_REGISTER_COUNT));
	thread->setIP(0);
	vm.getThreads()->addThread(thread);

	for (int i = 0; i < 20; i++)
		runOp(vm.getThreads()->getNextThread());

	return 0;
}
