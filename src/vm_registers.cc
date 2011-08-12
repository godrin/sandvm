#include "vm_registers.h"

VMRegisters::VMRegisters(size_t regCount, std::string pName) :
		vals(regCount), name(pName) {

}

Uint32 VMRegisters::get(size_t pos) {
	return vals[pos % vals.size()];
}
void VMRegisters::set(size_t pos, Uint32 val) {
	vals[pos % vals.size()] = val;
}

VMRegisters *VMRegisters::clone() {
	VMRegisters *x = new VMRegisters(0, name);
	std::copy(vals.begin(), vals.end(), std::back_inserter(x->vals));
	return x;
}
