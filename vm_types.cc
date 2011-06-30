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

// Uint32

Uint8::Uint8() :
		i(0) {

}

Uint8::Uint8(size_t p) {
	i = p;
}

size_t Uint8::asSizeT() {
	return i;
}
void Uint8::add(const Uint8 &other) {
	i += other.i;
}
void Uint8::sub(const Uint8 &other) {
	i -= other.i;
}
void Uint8::mul(const Uint8 &other) {
	i *= other.i;
}
void Uint8::div(const Uint8 &other) {
	i /= other.i;
}
void Uint8::mod(const Uint8 &other) {
	i %= other.i;
}
bool Uint8::isZero() const {
	return i == 0;
}

void Uint8::dec() {
	i--;
}
void Uint8::inc() {
	i++;
}

bool Uint8::lessThan(const Uint8 &other) {
	return i < other.i;
}
bool Uint8::equals(const Uint8 &other) {
	return i == other.i;
}

void Uint8::setBit(size_t which, bool val) {
	unsigned char b = 1;
	for (; which > 0; which--)
		b <<= 1;
	if (val)
		i |= b;
	else
		i = i & (0xFF ^ b);
}

// Uint32

Uint32::Uint32() :
		i(0) {

}

Uint32::Uint32(size_t p) {
	i = p;
}

size_t Uint32::asSizeT() {
	return i;
}
void Uint32::add(const Uint32 &other) {
	i += other.i;
}
void Uint32::sub(const Uint32 &other) {
	i -= other.i;
}
void Uint32::mul(const Uint32 &other) {
	i *= other.i;
}
void Uint32::div(const Uint32 &other) {
	i /= other.i;
}
void Uint32::mod(const Uint32 &other) {
	i %= other.i;
}
bool Uint32::isZero() const {
	return i == 0;
}

void Uint32::dec() {
	i--;
}
void Uint32::inc() {
	i++;
}

bool Uint32::lessThan(const Uint32 &other) {
	return i < other.i;
}
bool Uint32::equals(const Uint32 &other) {
	return i == other.i;
}

Uint8 Uint32::get(size_t index) {
	__type x = i;
	for (int i = 0; i < index; i++) {
		x = x >> 8;
	}
	return x & 0xFF;
}
