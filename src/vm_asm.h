#ifndef VM_ASM_H
#define VM_ASM_H

#include <fstream>

class VMMemory;
class VMEncoding;
class VMConfig;

namespace Asm2 {
void parse(std::istream &stream, VMMemory *memory, size_t start,
		VMEncoding *encoder,VMConfig *config);
}
#endif
