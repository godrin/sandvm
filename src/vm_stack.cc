#include "vm_stack.h"

VMStack::VMStack(size_t psize) :
		data(new VMMemoryData[psize]), size(psize), p(0) {

}
VMStack::~VMStack() {
	delete[] data;
}
void VMStack::push(VMMemoryData pData) throw (VMOverflowError){
	if (p < size) {
		data[p++] = pData;
	} else {
		throw VMOverflowError();
	}

}
VMMemoryData VMStack::pop() throw (VMUnderflowError){
	if (p > 0) {
		return data[p--];
	}
	throw VMUnderflowError();
}
