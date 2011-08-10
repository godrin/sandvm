#include "vm_api_file.h"

int main(int argc, char *argv[]) {
	VMApi api(0);
	VMApiModule *mod = new VMFileAccess();
	mod->init(&api);

	api.write("file", "write", std::string("filename.txt"), (Uint32) 0,
			std::string("testtext"));

	return 0;
}
