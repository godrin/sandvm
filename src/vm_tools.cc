#include "vm_tools.h"

std::string toUpper(const std::string &s) {
	std::string x(s);
	for (size_t i = 0; i < x.length(); i++) {
		if (x[i] >= 'a' && x[i] <= 'z') {
			x[i] = x[i] + ('A' - 'a');
		}
	}
	return x;
}
