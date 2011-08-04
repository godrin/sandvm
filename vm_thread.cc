#include "vm_thread.h"
#include "vm_vm.h"
#include "vm_encoding.h"
#include "vm_log.h"

#define LOGLEVEL 2

VMThread::VMThread() {
	memory = 0;
	registers = 0;
	vm = 0;
	queues = 0;
	alive = true;
	encoder = 0;
	logger(LOGLEVEL) << " nu thread" << vmlog::endl;
	id = 0;
}

VMThread::~VMThread() {
	if (vm)
		vm->threadDeleted(id);
	logger(LOGLEVEL) << " ~VMThread" << vmlog::endl;
	logger(LOGLEVEL) << "registers[0]=" << registers->get(0)
			<< vmlog::endl;
	delete registers;
	delete queues;
	logger(LOGLEVEL) << " ~VMThread" << vmlog::endl;
}

void VMThread::setMemory(VMMemory *m) {
	memory = m;
}
void VMThread::setRegisters(VMRegisters *regs) {
	registers = regs;
}
void VMThread::setIP(size_t pip) {
	ip = pip;
	encoder->decode(memory, ip, &currentInstruction);
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

size_t VMThread::fork(size_t pip) {
	VMThread *t = new VMThread();
	t->setMemory(getMemory());
	t->setRegisters(getRegisters()->clone());
	t->setIP(pip);
	t->setEncoder(encoder);
	t->setQueues(queues->clone(id, getVM()->getConfig()));

	t->getQueues()->setPipe(VMQueues::IO, getVM()->getIOPipe());
	t->getQueues()->setPipe(VMQueues::API, getVM()->getAPIPipe());

	size_t threadId = vm->getThreads()->addThread(t);

	return threadId;
}

bool VMThread::isAlive() const {
	return alive;
}

void VMThread::setEncoder(VMEncoding *pEncoding) {
	encoder = pEncoding;
}
VMVm *VMThread::getVM() {
	return vm;
}

void VMThread::setVM(VMVm *pvm) {
	vm = pvm;

	checkQueues();
}

VMQueues *VMThread::getQueues() {
	return queues;
}
void VMThread::setQueues(VMQueues *p) {
	queues = p;

	checkQueues();
}

void VMThread::setId(size_t pid) {
	id = pid;
}
size_t VMThread::getId() {
	return id;
}

void VMThread::checkQueues() {
	if (queues && vm) {
		if (!queues->getQueueUnchecked(0, QUEUE_TYPE_PIPE)) {
			queues->setPipe(VMQueues::IO,vm->getIOPipe());
			queues->setPipe(VMQueues::API,vm->getAPIPipe());
		}
	}
}
