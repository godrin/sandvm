#include "vm_api_file.h"

std::string VMFileAccess::readBuffer(std::string fileName, Uint32 start,
		Uint32 len) {
	return "oook";
}
Uint32 VMFileAccess::writeBuffer(std::string fileName, Uint32 start,
		std::string buffer) {
	std::cout << "Written '" << buffer << "' to file " << fileName << " at pos:"
			<< start << std::endl;
	return 0;
}
void VMFileAccess::init(VMApi *api) {
	api->reg(this, "read", &VMFileAccess::readBuffer);
	api->reg(this, "write", &VMFileAccess::writeBuffer);
}

std::string VMFileAccess::getName() {
	return "file";
}

