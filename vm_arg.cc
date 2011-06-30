#include "vm_arg.h"

bool VMArg::isRegister() {
	return mRegister;
}
bool VMArg::isAddress() {
	return !isRegister();
}

bool VMArg::isIndirect() {
	return indirect;
}
bool VMArg::isDirect() {
	return !indirect;
}

VMMemoryData VMArg::getValue() {
	return value;
}

void VMArg::setValue(VMMemoryData data) {
	value = data;
}
void VMArg::setRegister(bool reg) {
	mRegister = reg;
}
void VMArg::setDirect(bool d) {
	indirect = !d;
}

VMArg reg(VMMemoryData d) {
	VMArg a;
	a.setValue(d);
	a.setRegister(true);
	a.setDirect(true);
	return a;
}

VMArg ireg(VMMemoryData d) {
	VMArg a;
	a.setValue(d);
	a.setRegister(true);
	a.setDirect(false);
	return a;
}
VMArg val(VMMemoryData d) {
	VMArg a;
	a.setValue(d);
	a.setRegister(false);
	a.setDirect(true);
	return a;
}
VMArg mem(VMMemoryData d) {
	VMArg a;
	a.setValue(d);
	a.setRegister(false);
	a.setDirect(false);
	return a;
}
