#include "vm_log.h"

#include <map>

static int logLevel = 3;
static std::map<int, LogStream*> streams;
namespace vmlog {
tendl endl;
}

LogStream::LogStream(int l) :
		level(l) {

}

int LogStream::getLevel() const {
	return level;
}

void setLogLevel(int l) {
	logLevel = l;
}

LogStream& logger(int level) {
	if (!streams[level])
		streams[level] = new LogStream(level);
	return *streams[level];
}

LogStream &operator<<(LogStream &o, int i) {
	if (o.getLevel() < logLevel)
		std::cout << i;
	return o;
}
LogStream &operator<<(LogStream &o, unsigned int i) {
	if (o.getLevel() < logLevel)
		std::cout << i;
	return o;
}

LogStream &operator<<(LogStream &o, size_t i) {
	if (o.getLevel() < logLevel)
		std::cout << i;
	return o;

}
LogStream &operator<<(LogStream &o, const std::string &i) {
	if (o.getLevel() < logLevel)
		std::cout << i;
	return o;

}

LogStream &operator<<(LogStream &o, const vmlog::tendl&i) {
	if (o.getLevel() < logLevel)
		std::cout << std::endl;

	return o;
}
