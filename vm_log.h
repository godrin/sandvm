#ifndef VM_LOG_H
#define VM_LOG_H

#include <iostream>
#include <string>

class LogStream {
private:
	int level;
public:
	LogStream(int l);

	int getLevel() const;
};

namespace vmlog {
struct tendl {

};
extern tendl endl;
}

LogStream &logger(int level);
void setLogLevel(int l);

LogStream &operator<<(LogStream &o, int i);
LogStream &operator<<(LogStream &o, unsigned int i);
LogStream &operator<<(LogStream &o, size_t i);
LogStream &operator<<(LogStream &o, const std::string &i);
LogStream &operator<<(LogStream &o, const vmlog::tendl&i);

#endif
