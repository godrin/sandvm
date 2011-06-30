#ifndef VM_TYPES
#define VM_TYPES

#include <stddef.h>

class Uint64 {
	unsigned char data[8];

public:
	Uint64();
	size_t asSizeT();
	void add(const Uint64 &other);
};

class Uint8 {
	typedef unsigned int __type;
	__type i;

public:
	Uint8();
	Uint8(size_t p);
	size_t asSizeT();
	void add(const Uint8 &other);
	void sub(const Uint8 &other);
	void mul(const Uint8 &other);
	void div(const Uint8 &other);
	void mod(const Uint8 &other);
	bool isZero() const;
	void dec();
	void inc();
	bool lessThan(const Uint8 &other);
	bool equals(const Uint8 &other);

	void setBit(size_t which,bool val);
};



class Uint32 {
	typedef unsigned int __type;
	__type i;

public:
	Uint32();
	Uint32(size_t p);
	size_t asSizeT();
	void add(const Uint32 &other);
	void sub(const Uint32 &other);
	void mul(const Uint32 &other);
	void div(const Uint32 &other);
	void mod(const Uint32 &other);
	bool isZero() const;
	void dec();
	void inc();
	bool lessThan(const Uint32 &other);
	bool equals(const Uint32 &other);
	Uint8 get(size_t index);
};



#endif
