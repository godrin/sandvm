#include "vm_loader.h"
#include "vm_memory.h"
#include "vm_vm.h"
#include "vm_defines.h"
#include "vm_sim.h"



int main() {
	std::ifstream f("test.txt");
	VMMemory *m = new VMMemory(2000,"Memory");

	VMLoader l(m, f);
	l.load();
	VMVm vm;


	vm.setThreads(new VMThreads(VM_THREAD_COUNT_PER_VM));
	vm.setMemory(m);
	vm.setQueues(new VMQueues(VM_QUEUE_COUNT));

	VMThread *thread = new VMThread();
	thread->setMemory(vm.getMemory());
	thread->setRegisters(new VMRegisters(VM_REGISTER_COUNT,"Registers"));
	thread->setIP(0);
	vm.getThreads()->addThread(thread);

	for (int i = 0; i < 20; i++)
		runOp(vm.getThreads()->getNextThread());


	return 0;
}
