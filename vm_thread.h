#ifndef VM_THREAD_H
#define VM_THREAD_H

#include "vm_instruction.h"
#include "vm_registers.h"

class VMVm;
class VMEncoding;
class VMQueues;

class VMThread {
	VMMemory *memory;
	VMRegisters *registers;
	VMVm *vm;
	size_t ip;
	VMInstruction currentInstruction;
	bool alive;
	bool zeroFlag;
	VMEncoding *encoder;
	VMQueues *queues;

	size_t id;
	size_t parentId;

public:
	VMThread();
	~VMThread();

	void setId(size_t pid);
	size_t getId();

	void setParentId(size_t p);
	size_t getParentId();

	void setEncoder(VMEncoding *pEncoding);
	void setMemory(VMMemory *m);
	void setRegisters(VMRegisters *regs);
	void setIP(size_t pip);
	size_t getIP();
	VMInstruction *getCurrentInstruction();
	VMRegisters *getRegisters();
	VMMemory *getMemory();
	VMVm *getVM();
	void setVM(VMVm *pvm);
	// returns threadid (which is normally >0 or 0 is nil)
	size_t fork(size_t pip);

	void die();

	void setZero(bool f);
	bool getZeroFlag() const;

	bool isAlive() const;

	VMQueues *getQueues();
	void setQueues(VMQueues *p);
private:
	void checkQueues();

};

#endif
