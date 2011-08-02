#include "vm_memory.h"
#include "vm_vm.h"
#include "vm_sim.h"
#include "vm_asm.h"
#include "vm_encoding.h"
#include "vm_queues.h"
#include "vm_log.h"

int main(int argc, char *argv[]) {
	VMMemory *m = new VMMemory(2000, "Memory");

	setLogLevel(0);

	std::string filename;
	if (argc > 1)
		filename = argv[1];
	else
		filename = "test.asm";

	std::cout << "Running " << filename << std::endl;

	std::ifstream f(filename.c_str());

	VMEncoding encoder;

	VMVm vm;
	Asm2::parse(f, m, 0, &encoder, vm.getConfig());

	VMThreads *threads = new VMThreads(vm.getConfig()->getThreadCount());
	vm.setThreads(threads);
	vm.setMemory(m);

	VMThread *thread = new VMThread();
	thread->setMemory(vm.getMemory());
	thread->setRegisters(
			new VMRegisters(vm.getConfig()->getRegisterCount(), "Registers"));
	thread->setIP(0);
	thread->setVM(&vm);
	thread->setQueues(new VMQueues(vm.getConfig()));
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
