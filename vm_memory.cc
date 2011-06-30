#include "vm_memory.h"

VMMemoryData VMMemoryCell::get() {
	return data;
}
void VMMemoryCell::set(VMMemoryData pdata) {
	data = pdata;
}

VMMemory::VMMemory(size_t pSize) :
		size(pSize), cells(new VMMemoryCell[pSize]) {
}

VMMemory::~VMMemory() {
	delete[] cells;
}

void VMMemory::set(VMMemoryData index, VMMemoryData data) {
	std::cout << " set cell " << index.asSizeT() << " to " << data.asSizeT()
			<< std::endl;
	cells[index.asSizeT() % size].set(data);
}

VMMemoryData VMMemory::get(VMMemoryData index) {
	return cells[index.asSizeT() % size].get();
}

VMMemory *VMMemory::clone() {
	VMMemory *c = new VMMemory(size);
	for (size_t i = 0; i < size; i++) {
		c->set(i, get(i));
	}
}
