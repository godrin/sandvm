#include "vm_memory.h"
#include "vm_vm.h"
#include "vm_defines.h"
#include "vm_sim.h"
#include "vm_asm.h"
#include "vm_encoding.h"
#include "vm_queues.h"

int main(int argc, char *argv[]) {
	VMMemory *m = new VMMemory(2000, "Memory");

	std::string filename;
	if (argc > 1)
		filename = argv[1];
	else
		filename = "test.asm";

	std::ifstream f(filename.c_str());

	VMEncoding encoder;

	Asm2::parse(f, m, 0, &encoder);

	VMVm vm;

	VMThreads *threads = new VMThreads(VM_THREAD_COUNT_PER_VM);
	vm.setThreads(threads);
	vm.setMemory(m);

	VMThread *thread = new VMThread();
	thread->setMemory(vm.getMemory());
	thread->setRegisters(new VMRegisters(VM_REGISTER_COUNT, "Registers"));
	thread->setIP(0);
	thread->setVM(&vm);
	thread->setQueues(new VMQueues(VM_QUEUE_COUNT));
	thread->getQueues()->setQueue(0, new VMQueue(10, VMQueue::OUT));
	thread->getQueues()->setQueue(1, new VMQueue(10, VMQueue::BOTH));
	thread->getQueues()->setQueue(2, new VMQueue(10, VMQueue::STACK));
	vm.getThreads()->addThread(thread);

	for (int i = 0; i < 8000; i++) {
		std::cout << "STEP " << i << std::endl;
		thread = vm.getThreads()->getNextThread();
		if (!thread)
			break;
		runOp(thread);
	}

	return 0;
}
