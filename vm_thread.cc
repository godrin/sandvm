#include "vm_thread.h"
#include "vm_vm.h"

VMThread::VMThread() {
	memory = 0;
	alive = true;
}

VMThread::~VMThread() {
	delete registers;
}

void VMThread::setMemory(VMMemory *m) {
	memory = m;
}
void VMThread::setRegisters(VMRegisters *regs) {
	registers = regs;
}
void VMThread::setIP(size_t pip) {
	ip = pip;
	currentInstruction.set(getMemory(), ip);
}
size_t VMThread::getIP() {
	return ip;
}

VMInstruction *VMThread::getCurrentInstruction() {
	return &currentInstruction;
}

void VMThread::die() {
	alive = false;
}

VMRegisters *VMThread::getRegisters() {
	return registers;
}
VMMemory *VMThread::getMemory() {
	return memory;
}

void VMThread::setZero(bool flag) {
	zeroFlag = flag;
}
bool VMThread::getZeroFlag() const {
	return zeroFlag;
}

void VMThread::fork(size_t pip) {
	VMThread *t = new VMThread();
	t->setMemory(getMemory());
	t->setRegisters(getRegisters()->clone());
	t->setIP(pip);
	vm->getThreads()->addThread(t);
}

bool VMThread::isAlive() const {
	return alive;
}
