#ifndef JBT_INTERNAL
#define JBT_INTERNAL

#include <cassert>
#include <fstream>

namespace jbt {
	enum class tag_type : uint8_t {
		NONE,
		BOOL,
		LIST,
		STRING,
		OBJECT,
		BYTE,
		UBYTE,
		SHORT,
		USHORT,
		INT,
		UINT,
		LONG,
		ULONG,
		FLOAT,
		DOUBLE
	};
}

#endif // !JBT_INTERNAL
