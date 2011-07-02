#ifndef VM_LOADER_H
#define VM_LOADER_H

#include <fstream>

class VMMemory;

class VMLoader {
	std::istream &stream;
	VMMemory *memory;
	size_t ptr;
public:
	VMLoader(VMMemory *m, std::istream &istream);

	void load();
private:
	void readInstruction();
	void readUint8();
	void readUint32();
	void readString();
	void readByte();
};

#endif
