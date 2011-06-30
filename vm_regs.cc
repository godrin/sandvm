#include "vm_regs.h"

template<class T>
VMRegisters<T>::VMRegisters(size_t pCount) :
		count(pCount), content(new T[pCount]) {

}

template<class T>
VMRegisters<T>::~VMRegisters() {
	delete[] content;
}

template<class T>
T VMRegisters<T>::get(size_t index) {
	return content[(index >= count) ? (index % count) : index];
}
template<class T>
void VMRegisters<T>::set(size_t index, const T &value) {
	content[(index >= count) ? (index % count) : index];
}

template<class T>
VMRegisters<T> *VMRegisters<T>::clone() {
	VMRegisters<T> rs = new VMRegisters<T>(count);
	for (size_t i = 0; i < count; i++) {
		rs.set(i, get(i));
	}
}
