#include "vm_arg.h"
#include <sstream>

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

VMMemoryData VMArg::getValue(VMType type) {
	switch (type) {
	case DWORD:
		return dword;
	case WORD:
		return word;
	case BYTE:
		return byte;
	}
	throw int();
}

void VMArg::setValue(VMMemoryData data, VMType type) {
	switch (type) {
	case DWORD:
		dword = data.asSizeT();
		break;
	case WORD:
		word = data.asSizeT();
		break;
	case BYTE:
		byte = data.asSizeT();
		break;
	default:
		throw int();
	}
}
void VMArg::setRegister(bool reg) {
	mRegister = reg;
}
void VMArg::setDirect(bool d) {
	indirect = !d;
}

Uint8 VMArg::getUint8() {
	return byte;
}
Uint16 VMArg::getUint16() {
	return word;
}
Uint32 VMArg::getUint32() {
	return dword;
}
void VMArg::set(Uint8 v) {
	byte = v;
}
void VMArg::set(Uint16 v) {
	word = v;
}
void VMArg::set(Uint32 v) {
	dword = v;
}

std::string VMArg::toString(VMType t) {
	std::ostringstream os;

	if (indirect)
		os << "*";
	if (isRegister())
		os << "R";
	os << (int) getValue(t).asSizeT();

	return os.str();
}
