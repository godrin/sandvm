#include "vm_memory.h"

VMMemoryData VMMemoryCell::get() {
	return data;
}
void VMMemoryCell::set(VMMemoryData pdata) {
	data = pdata;
}

VMMemory::VMMemory(size_t pSize, std::string pTypename) :
		size(pSize), cells(new VMMemoryCell[pSize]), type(pTypename) {
}

VMMemory::~VMMemory() {
	delete[] cells;
}

void VMMemory::set(VMMemoryData index, VMMemoryData data) {
	std::cout << " " << type << " set cell " << index.asSizeT() << " to "
			<< data.asSizeT() << std::endl;
	cells[index.asSizeT() % size].set(data);
}

VMMemoryData VMMemory::get(VMMemoryData index) {
	VMMemoryData data=cells[index.asSizeT() % size].get();
	std::cout << " " << type << " get cell " << index.asSizeT() << " which is "
			<< data.asSizeT() << std::endl;
	return data;
}

VMMemory *VMMemory::clone() {
	VMMemory *c = new VMMemory(size,"Memory");
	for (size_t i = 0; i < size; i++) {
		c->set(i, get(i));
	}
}
