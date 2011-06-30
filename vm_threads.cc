#include "vm_threads.h"

#define INC(val) (((val)+1)%maxCount)
#define DEC(val) ((val)>0?((val)-1):maxCount-1)

VMThreads::VMThreads(size_t pMaxCount) :
		maxCount(pMaxCount) {
	threads = new VMThread*[maxCount];

}
VMThreads::~VMThreads() {
	for (int i = 0; i < maxCount; i++) {
		if (threads[i])
			delete threads[i];
	}
	delete[] threads;
}
VMThread *VMThreads::getNextThread() {
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
bool VMThreads::addThread(VMThread *thread) {
	for (int i = DEC(currentIndex); i != currentIndex; i = DEC(i)) {
		if (threads[i] == 0) {
			threads[i] = thread;
			return true;
		}
	}
	delete thread;
	return false;
}
