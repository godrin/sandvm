#include "vm_memory.h"
#include "vm_log.h"

#define LOGLEVEL 2

VMMemory::VMMemory(size_t pSize, std::string pTypename) :
		cells(pSize), type(pTypename) {
}

VMMemory::~VMMemory() {
}

void VMMemory::set(VMMemoryData index, VMMemoryData data) {
	logger(LOGLEVEL) << " " << type << " set cell " << index << " to " << data
			<< vmlog::endl;
	cells[index % cells.size()] = data;
}

VMMemoryData VMMemory::get(VMMemoryData index) {
	VMMemoryData data = cells[index % cells.size()];
	logger(LOGLEVEL) << " " << type << " get cell " << index << " which is "
			<< data << vmlog::endl;
	return data;
}

VMMemory *VMMemory::clone() {
	VMMemory *c = new VMMemory(cells.size(), "Memory");
	for (size_t i = 0; i < cells.size(); i++) {
		c->set(i, get(i));
	}
	return c;
}

void VMMemory::set(VMMemoryAddress addr, VMMemoryArray data) {
	std::copy(data.begin(), data.end(),
			std::inserter(data, cells.begin() + addr));
}

VMMemoryArray VMMemory::getArray(size_t p, VMType t) {

	VMMemoryArray r;
	Uint32 size;
	if (t == STRING) {
		size = getUint32(p);
		size += 4;

	} else {

		switch (t) {
		case BYTE:
			size = 1;
			break;
		case WORD:
			size = 2;
			break;
		case DWORD:
		case ADDRESS:
			size = 4;
			break;
		case FLOAT:
			size = 4;
			break;
		default:
			throw int();
		}
	}
	std::copy(cells.begin() + p, cells.begin() + p + size,
			std::back_inserter(r));
	return r;
}

Uint32 VMMemory::getValue(size_t p, VMType t) {
	switch (t) {
	case BYTE:
		return getUint8(p);
	case WORD:
		return getUint16(p);
	case DWORD:
	case ADDRESS:
		return getUint32(p);
	default:
		throw int();
	}
}

Uint8 VMMemory::getUint8(size_t p) {
	return toUint8(cells, p);
}
Uint16 VMMemory::getUint16(size_t p) {
	return toUint16(cells, p);
}
Uint32 VMMemory::getUint32(size_t p) {
	return toUint32(cells, p);
}
std::string VMMemory::getStdString(size_t p) {
	return toStdString(cells, p);
}

VMMemoryArray toArray(Uint8 b) {
	VMMemoryArray d;
	d.push_back(b);
	return d;
}
VMMemoryArray toArray(Uint16 b) {
	VMMemoryArray d;
	d.push_back(b & 0xFF);
	d.push_back((b >> 8) & 0xFF);
	return d;
}
VMMemoryArray toArray(Uint32 b) {
	VMMemoryArray d;
	d.push_back(b & 0xFF);
	d.push_back((b >> 8) & 0xFF);
	d.push_back((b >> 16) & 0xFF);
	d.push_back((b >> 24) & 0xFF);
	return d;
}

VMMemoryArray toArray(size_t p, VMType t) {
	switch (t) {
	case BYTE:
		return toArray((Uint8) p);
	case WORD:
		return toArray((Uint16) p);
	case DWORD:
	case ADDRESS:
		return toArray((Uint32) p);
	default:
		throw int();
	}
}
VMMemoryArray toArray(std::string b) {
	size_t l = b.length();
	VMMemoryArray a;
	if (l < 65336 - 4) {
		// ok
		VMMemoryArray c = toArray(((Uint32) l));
		std::copy(c.begin(), c.end(), std::back_inserter(a));
		std::copy(b.begin(), b.end(), std::back_inserter(a));

	} else {
		throw int();
	}
	return a;
}

Uint8 toUint8(const VMMemoryArray &a, size_t p) {
	if (a.size() >= p + 1) {
		// ok
		return a[p];
	} else {
		throw int();
	}
}
Uint16 toUint16(const VMMemoryArray &a, size_t p) {
	if (a.size() >= p + 2) {
		return a[p] | (a[p + 1] << 8);
	} else {
		throw int();
	}
}
Uint32 toUint32Internal(const VMMemoryArray &a, size_t p) {
	return a[p] | (a[p + 1] << 8) | (a[p + 2] << 16) | (a[p + 3] << 24);
}

Uint32 toUint32(const VMMemoryArray &a, size_t p) {
	if (a.size() >= 4 + p) {
		return toUint32Internal(a, p);
	} else {
		throw int();
	}
}
Uint32 toValue(const VMMemoryArray &a, VMType t, size_t p) {
	switch (t) {
	case BYTE:
		return toUint8(a, p);
	case WORD:
		return toUint16(a, p);
	case DWORD:
	case ADDRESS:
		return toUint32(a, p);
	default:
		throw int();
	}
}

std::string toStdString(const VMMemoryArray &a, size_t p) {
	if (a.size() < 4 + p)
		throw int();
	Uint32 l = toUint32Internal(a, p);
	if (a.size() == 4 + l + p) {
		std::string x;
		std::copy(a.begin() + 4 + p, a.end(), std::back_inserter(x));
		return x;
	} else {
		throw int();
	}
}
