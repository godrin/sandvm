#ifndef VM_THREAD_H
#define VM_THREAD_H

#include "vm_instruction.h"

class VMVm;

class VMThread {
	VMMemory *memory;
	VMRegisters *registers;
	VMVm *vm;
	size_t ip;
	VMInstruction currentInstruction;
	bool alive;
	bool zeroFlag;

public:
	VMThread();
	~VMThread();

	void setMemory(VMMemory *m);
	void setRegisters(VMRegisters *regs);
	void setIP(size_t pip);
	size_t getIP();
	VMInstruction *getCurrentInstruction();
	VMRegisters *getRegisters();
	VMMemory *getMemory();
	void fork(size_t pip);

	void die();

	void setZero(bool f);
	bool getZeroFlag() const;

	bool isAlive() const;

};

#endif
