#include "vm_vm.h"
#include "vm_thread.h"
#include "vm_log.h"

#include <iostream>
#include <string>

#define LOGLEVEL 5

VMComputingField simgetdirect(VMThread *thread, VMArg *arg, VMType type) {
	VMComputingField data;

	if (arg->isRegister()) {
		logger(LOGLEVEL) << " from register in :" << arg->getValue(type)
				<< vmlog::endl;
		data = thread->getRegisters()->get(arg->getValue(type));
	} else
		data = arg->getValue(type);
	return data;
}

// R10 => get value out of 10th register
// *R10 => get address out of 10th register and look up in memory
// 10 => get value of out memory-position 10
// *10 => get address from mem-position 10 and look up in memory
VMMemoryArray simget(VMThread *thread, VMArg *arg, VMType type) {

	VMMemoryArray data;

	if (arg->isIndirect()) {
		VMComputingField addr = simgetdirect(thread, arg, ADDRESS); // direct
		logger(LOGLEVEL) << " indirect resolve from:" << addr << vmlog::endl;
		data = thread->getMemory()->getArray(addr, type);
	} else {
		data = toArray(simgetdirect(thread, arg, type), type); // direct
	}
	return data;
}

Uint32 simgetVal(VMThread *thread, VMArg *arg, VMType type) {
	Uint32 data;

	if (arg->isIndirect()) {
		VMComputingField addr = simgetdirect(thread, arg, ADDRESS); // direct
		logger(LOGLEVEL) << " indirect resolve from:" << addr << vmlog::endl;
		data = thread->getMemory()->getValue(addr, type);
	} else {
		data = simgetdirect(thread, arg, type);
	}
	return data;
}

// R10 => put value in register 10
// *R10 => get address from register 10 and store in memory location
// 10 => put value into memory position 10
// *10 => lookup address at memory position 10 and store in looked up memory location
void simput(VMThread *thread, VMArg *arg, VMMemoryArray data, VMType t) {
	VMMemoryAddress addr;
	if (arg->isIndirect()) {
		addr = simgetdirect(thread, arg, t);
		thread->getMemory()->set(addr, data);
	} else {
		addr = arg->getValue(t);
		if (arg->isRegister()) {
			thread->getRegisters()->set(addr, toValue(data, t, 0));
		} else if (arg->isAddress())
			thread->getMemory()->set(addr, data);
	}
}

VMQueueType queueType(VMOps op) {
	switch (op) {
	case POPP:
	case PUSHP:
		return QUEUE_TYPE_PIPE;
	case POPS:
	case PUSHS:
		return QUEUE_TYPE_STACK;
	case POPQ:
	case PUSHQ:
		return QUEUE_TYPE_QUEUE;
	}
	throw int();
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
	try {
		switch (i->getOp()) {
		case DAT:
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
			// FIXME: Support FLOATS
			size_t data = simgetVal(thread, arg1, type);
			switch (i->getOp()) {
			case ADD:
				data += simgetVal(thread, arg0, type);
				break;
			case SUB:
				data -= simgetVal(thread, arg0, type);
				break;
			case MUL:
				data *= simgetVal(thread, arg0, type);
				break;
			case DIV:
				data /= simgetVal(thread, arg0, type);
				break;
			case MOD:
				data %= simgetVal(thread, arg0, type);
				break;
			}
			simput(thread, arg1, toArray(data, type), type);
			thread->setZero(data == 0);
		}
			break;
		case JMP:
			nextIP = simgetVal(thread, arg0, type);
			break;
		case JMZ:
			if (thread->getZeroFlag())
				nextIP = simgetVal(thread, arg0, type);
			break;
		case JMN:
			if (!thread->getZeroFlag())
				nextIP = simgetVal(thread, arg0, type);
			break;
		case SPL:
			simput(thread, arg1,
					toArray(thread->fork(simgetVal(thread, arg0, type)), type),
					type);
			break;
		case SLT:
			thread->setZero(
					simgetVal(thread, arg0, type)
							<= (simgetVal(thread, arg1, type)));
			break;
		case CMP: {
			VMComputingField value0 = simgetVal(thread, arg0, type);
			VMComputingField value1 = simgetVal(thread, arg1, type);
			logger(LOGLEVEL) << "value0:" << value0 << " value1:" << value1
					<< vmlog::endl;
			thread->setZero(value0 == value1);
		}
			break;
		case NOP:
			logger(LOGLEVEL) << "NOP at" << thread->getIP() << vmlog::endl;
			break;
		case PUSHQ:
		case PUSHS:
		case PUSHP: {
			VMMemoryAddress addr = simgetVal(thread, arg1, type);
			VMMemoryArray val = simget(thread, arg0, type);
			VMPipeEnd *q = thread->getQueues()->getQueue(addr,
					queueType(i->getOp()));
			q->write(val);
		}
			break;
		case POPQ:
		case POPS:
		case POPP: {
			VMMemoryAddress addr = simgetVal(thread, arg0, type);
			logger(LOGLEVEL) << "pop a value from queue val:" << addr
					<< vmlog::endl;
			VMPipeEnd *pipeEnd=thread->getQueues()->getQueue(addr,
					queueType(i->getOp()));

			VMMemoryArray val = pipeEnd->read(type);
			simput(thread, arg1, val, type);
		}
			break;
		case JOIN: {

			VMMemoryAddress addr = simgetVal(thread, arg0, type);
			logger(LOGLEVEL) << "joining to thread " << addr
					<< " to thread " << thread->getId() << vmlog::endl;

			if (thread->getVM()->getThreads()->getThread(addr)) {
				nextIP = thread->getIP(); // stay here
			}

		}
			break;
		case THREADP: {
			throw int(); // not implemented

			VMMemoryAddress threadId = simgetVal(thread, arg0, type);
			VMMemoryAddress pipeId = simgetVal(thread, arg1, type);

			thread->getQueues()->setPipe(
					pipeId,
					thread->getVM()->getThreadPipe(thread->getId(),
							threadId));
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
	catch(VMQueueException e) {
		std::cout << "QueueException:" << typeid(e).name() << std::endl;
		// TODO: add exception handling
		thread->die();
	}
}

void sim() {
	VMVm vm;
	vm.getMemory();

}
