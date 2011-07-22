#include "vm_vm.h"
#include "vm_thread.h"
#include "vm_log.h"

#include <iostream>
#include <string>

#define LOGLEVEL 1

VMMemoryData simgetdirect(VMThread *thread, VMArg *arg, VMType type) {
	VMMemoryData data;

	if (arg->isRegister()) {
		logger(LOGLEVEL) << " from register in :"
				<< arg->getValue(type).asSizeT() << vmlog::endl;
		data = thread->getRegisters()->get(arg->getValue(type));
	} else
		data = arg->getValue(type);
	return data;
}

// R10 => get value out of 10th register
// *R10 => get address out of 10th register and look up in memory
// 10 => get value of out memory-position 10
// *10 => get address from mem-position 10 and look up in memory
VMMemoryData simget(VMThread *thread, VMArg *arg, VMType type) {

	VMMemoryData data = simgetdirect(thread, arg, type);

	if (arg->isIndirect()) {
		logger(LOGLEVEL) << " indirect resolve from:" << data.asSizeT()
				<< vmlog::endl;
		data = thread->getMemory()->get(data);
	}
	return data;
}

// R10 => put value in register 10
// *R10 => get address from register 10 and store in memory location
// 10 => put value into memory position 10
// *10 => lookup address at memory position 10 and store in looked up memory location
void simput(VMThread *thread, VMArg *arg, VMMemoryData data, VMType t) {
	VMMemoryData addr;
	if (arg->isIndirect()) {
		addr = simgetdirect(thread, arg, t);
		thread->getMemory()->set(addr, data);
	} else {
		addr = arg->getValue(t);
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
	logger(LOGLEVEL) << "Run op at " << thread->getIP() << vmlog::endl;
	VMInstruction *i = thread->getCurrentInstruction();
	logger(LOGLEVEL) << "I:" << i->toString() << vmlog::endl;

	VMArg *arg0 = i->getArg0(), *arg1 = i->getArg1();
	VMRegisters *regs = thread->getRegisters();
	VMMemory *memory = thread->getMemory();
	size_t nextIP = thread->getIP() + i->getLen();
	VMType type = i->getType();

	logger(LOGLEVEL) << toString(i->getOp()) << "-start" << vmlog::endl;

	// always from-> to
	// e.g. MOV a,b - take from a and write on b

	switch (i->getOp()) {
	case DAT:
		std::cout << "DIIIIIEEEEE" << std::endl;
		thread->die();
		return; // back out - because thread is dead anyway
	case MOVE:
		simput(thread, arg1, simget(thread, arg0, type), type);
		break;
	case ADD:
	case SUB:
	case MUL:
	case DIV:
	case MOD: {
		VMMemoryData data = simget(thread, arg1, type);
		switch (i->getOp()) {
		case ADD:
			data.add(simget(thread, arg0, type));
			break;
		case SUB:
			data.sub(simget(thread, arg0, type));
			break;
		case MUL:
			data.mul(simget(thread, arg0, type));
			break;
		case DIV:
			data.div(simget(thread, arg0, type));
			break;
		case MOD:
			data.mod(simget(thread, arg0, type));
			break;
		}
		simput(thread, arg1, data, type);
		thread->setZero(data.isZero());
	}
		break;
	case JMP:
		nextIP = simget(thread, arg0, type).asSizeT();
		break;
	case JMZ:
		if (thread->getZeroFlag())
			nextIP = simget(thread, arg0, type).asSizeT();
		break;
	case JMN:
		if (!thread->getZeroFlag())
			nextIP = simget(thread, arg0, type).asSizeT();
		break;
	case SPL:
		thread->fork(simget(thread, arg0, type).asSizeT());
		break;
	case SLT:
		thread->setZero(
				simget(thread, arg0, type).lessThan(
						simget(thread, arg1, type)));
		break;
	case CMP: {
		VMMemoryData value0 = simget(thread, arg0, type);
		VMMemoryData value1 = simget(thread, arg1, type);
		logger(LOGLEVEL) << "value0:" << value0.value() << " value1:"
				<< value1.value() << vmlog::endl;
		thread->setZero((value0.equals(value1)));
	}
		break;
	case NOP:
		logger(LOGLEVEL) << "NOP at" << thread->getIP() << vmlog::endl;
		break;
	case PUSH: {
		VMMemoryData addr = simget(thread, arg1, type);
		VMMemoryData val = simget(thread, arg0, type);
		logger(LOGLEVEL) << "Push a value to a queue val:" << val.value()
				<< " to queue " << addr.value() << vmlog::endl;
		thread->getQueues()->getQueue(addr.value())->push(val);
	}
		break;
	case POP: {
		VMMemoryData addr = simget(thread, arg0, type);
		logger(LOGLEVEL) << "pop a value from queue val:" << addr.value()
				<< vmlog::endl;
		VMMemoryData val = thread->getQueues()->getQueue(addr.value())->pop();
		simput(thread, arg1, val, type);
	}
		break;
	default:
		logger(LOGLEVEL) << "UNKNOWN" << vmlog::endl;
	}
	logger(LOGLEVEL) << toString(i->getOp()) << "-end" << vmlog::endl;
	if (nextIP == std::string::npos)
		nextIP = thread->getIP() + 4;
	thread->setIP(nextIP);

}

void sim() {
	VMVm vm;
	vm.getMemory();

}
