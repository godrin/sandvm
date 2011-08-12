#ifndef VM_NET_H
#define VM_NET_H

class VMNetNodeID {

};

class VMNetChannel {
	void write(std::string buffer);
	std::string read(size_t atMost);
};

class VMNet {

};

#endif
