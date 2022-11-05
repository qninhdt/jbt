#include "jbt/tag.hpp"
#include "jbt/serialization.hpp"

#define PRIMATIVE_TAG_CLASS_IMPL(name, type, enum_type)  \
                                                         \
	name##_tag::name##_tag()                             \
		: name##_tag(0) {}                               \
                                                         \
	name##_tag::name##_tag(const type& value)            \
		: base_tag(tag_type::##enum_type)                \
		, value(value) {}                                \
                                                         \
	name##_tag::name##_tag(type&& value)                 \
		: base_tag(tag_type::##enum_type)                \
		, value(std::move(value)) {}                     \
                                                         \
	void name##_tag::read(std::istream& input) {         \
		read_##name(input, value);                       \
	}                                                    \
                                                         \
	void name##_tag::write(std::ostream& output) const { \
		write_##name(output, value);                     \
	}
	

namespace jbt {

	base_tag::base_tag(const tag_type& type)
		:type(type) {}

	base_tag::base_tag(tag_type&& type)
		:type(std::move(type)) {}

	tag_type base_tag::get_type() const {
		return type;
	}

	PRIMATIVE_TAG_CLASS_IMPL(bool, bool, BOOL)
	PRIMATIVE_TAG_CLASS_IMPL(byte, int8_t, BYTE)
	PRIMATIVE_TAG_CLASS_IMPL(ubyte, uint8_t, UBYTE)
	PRIMATIVE_TAG_CLASS_IMPL(short, int16_t, SHORT)
	PRIMATIVE_TAG_CLASS_IMPL(ushort, uint16_t, USHORT)
	PRIMATIVE_TAG_CLASS_IMPL(int, int32_t, INT)
	PRIMATIVE_TAG_CLASS_IMPL(uint, uint32_t, UINT)
	PRIMATIVE_TAG_CLASS_IMPL(long, int64_t, LONG)
	PRIMATIVE_TAG_CLASS_IMPL(ulong, uint64_t, ULONG)
}