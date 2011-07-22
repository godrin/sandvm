#ifndef VM_ASM_H
#define VM_ASM_H

#include <fstream>

class VMMemory;
class VMEncoding;

namespace Asm2 {
void parse(std::istream &stream, VMMemory *memory, size_t start,
		VMEncoding *encoder);
}
#endif
