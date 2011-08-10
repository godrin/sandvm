#include "vm_api.h"

Uint32 iunmarshal(std::string s, size_t pos) {
	Uint32 x = (((Uint32) s[pos]) << 24) | (((Uint32) s[pos + 1]) << 16)
			| (((Uint32) s[pos + 2]) << 8) | (((Uint32) s[pos + 3]));
	return x;
}

template<>
Uint32 unmarshal(const std::string &s, size_t &pos) {
	if (s[pos] == 'i') {
		pos++;

		Uint32 i = iunmarshal(s, pos);
		pos += 4;
		return i;
	} else {
		std::cout << "unmarshal failed for Uint32:" << s.substr(pos,std::string::npos) << " at pos:" << pos
				<< std::endl;
		throw int();
	}
}

template<>
std::string unmarshal(const std::string &s, size_t &pos) {
	if (s[pos] == 's') {
		pos++;
		Uint32 len = iunmarshal(s, pos);
		pos += 4;
		size_t o = pos;
		pos += len;

		return s.substr(o, len);

	} else
		throw int();
}

std::string imarshal(Uint32 i) {
	char x[4] = { (i >> 24) & 0xFF, (i >> 16) & 0xFF, (i >> 8) & 0xFF, (i)
			& 0xFF };

	std::string s(x, 4);
	if (s.length() != 4)
		throw int();
	return s;

}
template<>
std::string marshal(Uint32 i) {
	return "i" + imarshal(i);
}

template<>
std::string marshal(std::string x) {
	return "s" + imarshal((Uint32) x.length()) + x;
}

