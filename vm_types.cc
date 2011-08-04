#include "vm_types.h"

// Uint64

Uint64::Uint64() {
	for (size_t x = 0; x < 8; x++)
		data[x] = 0;
}
size_t Uint64::asSizeT() {
	size_t s = 0;
	for (size_t x = 0; x < 8; x++) {
		s = (s << 8) | data[x];
	}
}

void Uint64::add(const Uint64 &other) {
	unsigned int t;
	unsigned int fromLast = 0;
	for (size_t x = 7; x >= 0; x--) {
		t = ((unsigned int) data[x]) + ((unsigned int) other.data[x])
				+ fromLast;

		fromLast = (t & 0x100) ? 1 : 0;
		data[x] = (t & 0xFF);
	}
}

// Uint32C

Uint8C::Uint8C() :
		i(0) {

}

Uint8C::__type Uint8C::value() {
	return i;
}

Uint8C::Uint8C(size_t p) {
	i = p;
}

size_t Uint8C::asSizeT() {
	return i;
}
void Uint8C::add(const Uint8C &other) {
	i += other.i;
}
void Uint8C::sub(const Uint8C &other) {
	i -= other.i;
}
void Uint8C::mul(const Uint8C &other) {
	i *= other.i;
}
void Uint8C::div(const Uint8C &other) {
	i /= other.i;
}
void Uint8C::mod(const Uint8C &other) {
	i %= other.i;
}
bool Uint8C::isZero() const {
	return i == 0;
}

void Uint8C::dec() {
	i--;
}
void Uint8C::inc() {
	i++;
}

bool Uint8C::lessThan(const Uint8C &other) {
	return i < other.i;
}
bool Uint8C::equals(const Uint8C &other) {
	return i == other.i;
}

void Uint8C::setBit(size_t which, bool val) {
	unsigned char b = 1;
	for (; which > 0; which--)
		b <<= 1;
	if (val)
		i |= b;
	else
		i = i & (0xFF ^ b);
}

// Uint32C

Uint32C::Uint32C() :
		i(0) {

}

Uint32C::Uint32C(size_t p) {
	i = p;
}

Uint32C::Uint32C(__type p) :
		i(p) {

}

size_t Uint32C::asSizeT() {
	return i;
}
void Uint32C::add(const Uint32C &other) {
	i += other.i;
}
void Uint32C::sub(const Uint32C &other) {
	i -= other.i;
}
void Uint32C::mul(const Uint32C &other) {
	i *= other.i;
}
void Uint32C::div(const Uint32C &other) {
	i /= other.i;
}
void Uint32C::mod(const Uint32C &other) {
	i %= other.i;
}
bool Uint32C::isZero() const {
	return i == 0;
}

void Uint32C::dec() {
	i--;
}
void Uint32C::inc() {
	i++;
}

bool Uint32C::lessThan(const Uint32C &other) {
	return i < other.i;
}
bool Uint32C::equals(const Uint32C &other) {
	return i == other.i;
}

Uint8C Uint32C::get(size_t index) {
	__type x = i;
	for (int i = 0; i < index; i++) {
		x = x >> 8;
	}
	return x & 0xFF;
}

