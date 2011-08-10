#ifndef VM_API_FILE_H
#define VM_API_FILE_H

#include "vm_api.h"

class VMFileAccess: public VMApiModule {
public:
	std::string readBuffer(std::string fileName, Uint32 start, Uint32 len);
	Uint32 writeBuffer(std::string fileName, Uint32 start, std::string buffer);
	virtual void init(VMApi *api);
	virtual std::string getName();
};

#endif
