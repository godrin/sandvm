#include "vm_threads.h"
#include "vm_log.h"

#define LOGLEVEL 5

#define INC(val) (((val)+1)%maxCount)
#define DEC(val) ((val)>0?((val)-1):maxCount-1)

VMThreads::VMThreads(size_t pMaxCount) :
		maxCount(pMaxCount), currentIndex(0) {
	threads = new VMThread*[maxCount];
	for (size_t i = 0; i < maxCount; i++)
		threads[i] = 0;
	logger(LOGLEVEL) << "VMThreads::VMThreads" << vmlog::endl;

}
VMThreads::~VMThreads() {
	logger(LOGLEVEL) << "VMThreads::~VMThreads" << vmlog::endl;
	for (int i = 0; i < maxCount; i++) {
		if (threads[i])
			delete threads[i];
	}
	delete[] threads;
}
VMThread *VMThreads::getNextThread() {
	if (maxCount == 0)
		return 0;
	int startIndex = INC(currentIndex);
	int workingIndex = startIndex;
	do {
		if (threads[workingIndex]) {
			if (!threads[workingIndex]->isAlive()) {
				delete threads[workingIndex];
				threads[workingIndex] = 0;
			} else {
				currentIndex = workingIndex;
				return threads[workingIndex];
			}
		}
		workingIndex = INC(workingIndex);
	} while (workingIndex != startIndex);
	return 0;
}
void VMThreads::rmThread(VMThread *thread) {
	for (int i = 0; i < maxCount; i++) {
		if (threads[i] == thread) {
			threads[i] = 0;
			delete thread;
		}
	}
}
size_t VMThreads::addThread(VMThread *thread) {
	if (maxCount > 0) {

		for (int i = DEC(currentIndex); i != currentIndex; i = DEC(i)) {
			logger(LOGLEVEL) << "i:" << i << " currentIndex:" << currentIndex
					<< vmlog::endl;
			if (threads[i] == 0) {
				threads[i] = thread;
				return i + 1;
			}
		}
	}
	delete thread;
	return 0;
}

VMThread *VMThreads::getThread(size_t index) {
	if (index == 0)
		return 0;
	return threads[index - 1];
}
