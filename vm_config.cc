#include "vm_config.h"
#include "vm_defines.h"

VMConfig::VMConfig() {
	threadCount = VM_THREAD_COUNT_PER_VM;
	stackCount = 10;
	queueCount = VM_QUEUE_COUNT;
	memorySize = 2000;
	registerCount = VM_REGISTER_COUNT;
	queueSize = VM_QUEUE_SIZE;
	pipeCount = VM_THREAD_COUNT_PER_VM + 3;
}

void VMConfig::setStackCount(size_t c) {
	stackCount = c;
}
size_t VMConfig::getStackCount() {
	return stackCount;
}
void VMConfig::setQueueCount(size_t c) {
	queueCount = c;
}
size_t VMConfig::getQueueCount() {
	return queueCount;
}
void VMConfig::setThreadCount(size_t c) {
	threadCount = c;
}
size_t VMConfig::getThreadCount() {
	return threadCount;
}

void VMConfig::setRegisterCount(size_t c) {

	registerCount = c;
}
size_t VMConfig::getRegisterCount() {
	return registerCount;
}
void VMConfig::setMemorySize(size_t c) {
	memorySize = c;
}
size_t VMConfig::getMemorySize() {
	return memorySize;
}

void VMConfig::setQueueSize(size_t c) {
	if (c == 0)
		throw int();
	queueSize = c;
}
size_t VMConfig::getQueueSize() {
	return queueSize;
}

void VMConfig::setPipeCount(size_t c) {
	pipeCount = c;
}
size_t VMConfig::getPipeCount() {
	return pipeCount;
}
