#include "vm_vm.h"
#include "vm_thread.h"

#include <iostream>
#include <string>

VMMemoryData simgetdirect(VMThread *thread, VMArg *arg) {
	VMMemoryData data;

	if (arg->isRegister()) {
		std::cout << " from register in :" << arg->getValue().asSizeT()
				<< std::endl;
		data = thread->getRegisters()->get(arg->getValue());
	} else
		data = arg->getValue();
	return data;
}

// R10 => get value out of 10th register
// *R10 => get address out of 10th register and look up in memory
// 10 => get value of out memory-position 10
// *10 => get address from mem-position 10 and look up in memory
VMMemoryData simget(VMThread *thread, VMArg *arg) {

	VMMemoryData data = simgetdirect(thread, arg);

	if (arg->isIndirect()) {
		std::cout << " indirect resolve from:" << data.asSizeT() << std::endl;
		data = thread->getMemory()->get(data);
	}
	return data;
}

// R10 => put value in register 10
// *R10 => get address from register 10 and store in memory location
// 10 => put value into memory position 10
// *10 => lookup address at memory position 10 and store in looked up memory location
void simput(VMThread *thread, VMArg *arg, VMMemoryData data) {
	VMMemoryData addr;
	if (arg->isIndirect()) {
		addr = simgetdirect(thread, arg);
		thread->getMemory()->set(addr, data);
	} else {
		addr = arg->getValue();
		if (arg->isRegister()) {
			thread->getRegisters()->set(addr, data);
		} else if (arg->isAddress())
			thread->getMemory()->set(addr, data);
	}
}

void runOp(VMThread *thread) {
	if (!thread) {
		std::cerr << "thread is null!" << std::endl;
		return;
	}

	VMInstruction *i = thread->getCurrentInstruction();
	VMArg *arg0 = i->getArg0(), *arg1 = i->getArg1();
	VMRegisters *regs = thread->getRegisters();
	VMMemory *memory = thread->getMemory();
	size_t nextIP = std::string::npos;

	std::cout << "AT:" << thread->getIP() << std::endl;

	switch (i->getOp()) {
	case DAT:
		std::cout << "DAT" << std::endl;
		thread->die();
		break;
	case MOVE:
		simput(thread, arg0, simget(thread, arg1));
		break;
	case ADD:
	case SUB:
	case MUL:
	case DIV:
	case MOD: {
		VMMemoryData data = simget(thread, arg1);
		switch (i->getOp()) {
		case ADD:
			data.add(simget(thread, arg0));
			break;
		case SUB:
			data.sub(simget(thread, arg0));
			break;
		case MUL:
			data.mul(simget(thread, arg0));
			break;
		case DIV:
			data.div(simget(thread, arg0));
			break;
		case MOD:
			data.mod(simget(thread, arg0));
			break;
		}
		simput(thread, arg1, data);
		thread->setZero(data.isZero());
	}
		break;
	case JMP:
		nextIP = simget(thread, arg0).asSizeT();
		break;
	case JMZ:
		if (thread->getZeroFlag())
			nextIP = simget(thread, arg0).asSizeT();
		break;
	case JMN:
		if (!thread->getZeroFlag())
			nextIP = simget(thread, arg0).asSizeT();
		break;
	case SPL:
		thread->fork(simget(thread, arg0).asSizeT());
		break;
	case SLT:
		thread->setZero(simget(thread, arg0).lessThan(simget(thread, arg1)));
		break;
	case CMP:
		thread->setZero((simget(thread, arg0).equals(simget(thread, arg1))));
		break;
	case NOP:
		std::cout << "NOP at" << thread->getIP() << std::endl;
		break;
	default:
		std::cout << "UNKNOWN" << std::endl;
	}
	if (nextIP == std::string::npos)
		nextIP = thread->getIP() + 4;
	thread->setIP(nextIP);

}

void sim() {
	VMVm vm;
	vm.getMemory();

}
