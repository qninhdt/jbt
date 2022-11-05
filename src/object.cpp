#include "jbt/object.hpp"
#include "jbt/tag.hpp"

#define OBJECT_GETTER_SETTER_IMPL(name_, type)                       \
	void object::set_##name_(std::string& name, const type& value) { \
		tags.insert({ name, new name_##_tag(value) });               \
	};

namespace jbt {

	OBJECT_GETTER_SETTER_IMPL(bool, bool)
	//OBJECT_GETTER_SETTER_IMPL(string, std::string)
	//OBJECT_GETTER_SETTER_IMPL(byte, int8_t)
	//OBJECT_GETTER_SETTER_IMPL(ubyte, uint8_t)
	//OBJECT_GETTER_SETTER_IMPL(short, int16_t)
	//OBJECT_GETTER_SETTER_IMPL(ushort, uint16_t)
	//OBJECT_GETTER_SETTER_IMPL(int, int32_t)
	//OBJECT_GETTER_SETTER_IMPL(uint, uint32_t)
	//OBJECT_GETTER_SETTER_IMPL(long, int64_t)
	//OBJECT_GETTER_SETTER_IMPL(ulong, uint64_t)

}