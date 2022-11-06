#ifndef JBT_INTERNAL
#define JBT_INTERNAL

#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

namespace jbt {

	class tag;

	using tag_map = std::map<std::string, tag*>;
	using tag_list = std::vector<tag*>;

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
