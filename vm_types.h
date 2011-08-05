#ifndef VM_TYPES
#define VM_TYPES

#include <stddef.h>
#include <vector>
#include <string>

enum VMType {
	BYTE, WORD, DWORD, ADDRESS, FLOAT, STRING, // limited to 65536-4 bytes

	INVALID_TYPE
};

std::string toString(VMType t);

class Uint64 {
	unsigned char data[8];

public:
	Uint64();
	size_t asSizeT();
	void add(const Uint64 &other);
};

typedef unsigned char Uint8;
typedef unsigned short int Uint16;
typedef unsigned int Uint32;

class Uint8C {
public:
	typedef Uint8 __type;
private:
	__type i;

public:
	Uint8C();
	Uint8C(size_t p);
	size_t asSizeT();
	__type value();
	void add(const Uint8C &other);
	void sub(const Uint8C &other);
	void mul(const Uint8C &other);
	void div(const Uint8C &other);
	void mod(const Uint8C &other);
	bool isZero() const;
	void dec();
	void inc();
	bool lessThan(const Uint8C &other);
	bool equals(const Uint8C &other);

	void setBit(size_t which, bool val);
};

class Uint32C {
public:
	typedef unsigned int __type;
private:
	__type i;

public:
	Uint32C();
	Uint32C(size_t p);
	Uint32C(__type p);
	size_t asSizeT();
	void add(const Uint32C &other);
	void sub(const Uint32C &other);
	void mul(const Uint32C &other);
	void div(const Uint32C &other);
	void mod(const Uint32C &other);
	bool isZero() const;
	void dec();
	void inc();
	bool lessThan(const Uint32C &other);
	bool equals(const Uint32C &other);
	Uint8C get(size_t index);
};

typedef Uint8 VMMemoryData;

typedef std::vector<Uint8> VMMemoryArray;
typedef Uint32 VMMemoryAddress;
typedef Uint32 VMComputingField;

class VMExceptionWrongType {
	VMType type;
public:
	VMExceptionWrongType(VMType t) :
			type(t) {
	}
	std::string what() {
		std::string x = "WrongType Used ";
		return x + toString(type);
	}
}
;

#endif
