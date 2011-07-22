#include "vm_vm.h"
#include "vm_sim.h"
#include "vm_threads.h"
#include "vm_defines.h"
#include "vm_encoding.h"

#include <iostream>

int main() {
	VMVm vm;
	vm.setThreads(new VMThreads(VM_THREAD_COUNT_PER_VM));
	vm.setMemory(new VMMemory(VM_MEMORY_SIZE,"Memory"));
	vm.setQueues(new VMQueues(VM_QUEUE_COUNT));
	vm.getMemory()->set(0, NOP);
	vm.getMemory()->set(10,11);
	VMEncoding encoding;
	VMInstruction i=ins(JMP, mem(10));
	encoding.encode(vm.getMemory(),4,&i);

	VMThread *thread = new VMThread();
	thread->setMemory(vm.getMemory());
	thread->setRegisters(new VMRegisters(VM_REGISTER_COUNT,"Registers"));
	thread->setIP(0);
	vm.getThreads()->addThread(thread);

	for (int i = 0; i < 20; i++)
		runOp(vm.getThreads()->getNextThread());

	return 0;
}
