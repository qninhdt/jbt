#include "jbt/tag.hpp"
#include "jbt/serialization.hpp"

#define PRIMATIVE_TAG_CLASS_IMPL(name, type, enum_type)  \
	                                                     \
	name##_tag::name##_tag()                             \
		: name##_tag(0) {}                               \
	                                                     \
	name##_tag::name##_tag(const type& value)            \
		: tag(tag_type::##enum_type)                     \
		, value(value) {}                                \
	                                                     \
	name##_tag::name##_tag(type&& value)                 \
		: tag(tag_type::##enum_type)                     \
		, value(std::move(value)) {}                     \
	                                                     \
	void name##_tag::read(std::istream& input) {         \
		read_##name(input, value);                       \
	}                                                    \
	                                                     \
	void name##_tag::write(std::ostream& output) const { \
		write_##name(output, value);                     \
	}                                                    \
	type name##_tag::get_value() const {                 \
		return value;                                    \
	}

#define OBJECT_TAG_GETTER_SETTER_IMPL(name_, type, enum_type)                   \
	type object_tag::get_##name_(const std::string& name) const {               \
		tag* tag = get_tag(name);                                               \
		assert(tag->get_type() == tag_type::##enum_type && "Wrong tag type");   \
		return static_cast<name_##_tag*>(tag)->get_value();                     \
	}                                                                           \
	void object_tag::set_##name_(const std::string& name, const type& value) {  \
		set_tag(name, new name_##_tag(value));                                  \
	}

#define LIST_TAG_GETTER_SETTER_IMPL(name, type, enum_type)                      \
	type list_tag::get_##name(const uint32_t& index) const {                    \
		tag* tag = get_tag(index);                                              \
		assert(tag->get_type() == tag_type::##enum_type && "Wrong tag type");   \
		return static_cast<name##_tag*>(tag)->get_value();                      \
	}                                                                           \
	void list_tag::set_##name(const uint32_t& index, const type& value) {       \
		set_tag(index, new name##_tag(value));                                  \
	}                                                                           \
	void list_tag::add_##name(const type& value) {                              \
		add_tag(new name##_tag(value));                                         \
	}

namespace jbt {

	tag::tag(const tag_type& type)
		:type(type) {}

	tag::tag(tag_type&& type)
		:type(std::move(type)) {}

	tag_type tag::get_type() const {
		return type;
	}

	string_tag::string_tag(): string_tag("") {};
	string_tag::string_tag(const std::string& value): tag(tag_type::STRING), value(value) {};
	string_tag::string_tag(std::string&& value): tag(tag_type::STRING), value(value) {};

	void string_tag::read(std::istream& input) {
		read_string(input, value);
	}

	void string_tag::write(std::ostream& output) const {
		write_string(output, value);
	}

	std::string string_tag::get_value() const {
		return value;
	}

	object_tag::object_tag(): tag(tag_type::OBJECT) {}

	void object_tag::read(std::istream& input) {
		read_tag_map(input, tags);
	}

	void object_tag::write(std::ostream& output) const {
		write_tag_map(output, tags);
	}

	tag* object_tag::get_tag(const std::string& name) const {
		auto it = tags.find(name);
		assert(it != tags.end() && "Tag not found");
		return it->second;
	}

	void object_tag::set_tag(const std::string& name, tag* tag) {
		assert(name.size() <= 255 && "Maximum name length is 255");
		assert(!name.empty() && "Empty name is not allowed");
		assert(tag != nullptr && "Null tag is not allowed");
		tags[name] = tag;
	}

	std::string object_tag::get_string(const std::string& name) {
		tag* tag = get_tag(name);
		assert(tag->get_type() == tag_type::STRING && "Wrong tag type");
		return static_cast<string_tag*>(tag)->get_value();
	}

	void object_tag::set_string(const std::string& name, const std::string value) {
		assert(value.size() <= 65535 && "Maximum length of string is 65535");
		set_tag(name, new string_tag(value));
	}

	object_tag* object_tag::get_object(const std::string& name) {
		tag* tag = get_tag(name);
		assert(tag->get_type() == tag_type::OBJECT && "Wrong tag type");
		return static_cast<object_tag*>(tag);
	}

	void object_tag::set_object(const std::string& name, object_tag* value) {
		set_tag(name, value);
	}

	list_tag* object_tag::get_list(const std::string& name) {
		tag* tag = get_tag(name);
		assert(tag->get_type() == tag_type::OBJECT && "Wrong tag type");
		return static_cast<list_tag*>(tag);
	}

	void object_tag::set_string(const std::string& name, list_tag* value) {
		set_tag(name, value);
	}

	OBJECT_TAG_GETTER_SETTER_IMPL(bool, bool, BOOL)
	OBJECT_TAG_GETTER_SETTER_IMPL(byte, int8_t, BYTE)
	OBJECT_TAG_GETTER_SETTER_IMPL(ubyte, uint8_t, UBYTE)
	OBJECT_TAG_GETTER_SETTER_IMPL(short, int16_t, SHORT)
	OBJECT_TAG_GETTER_SETTER_IMPL(ushort, uint16_t, USHORT)
	OBJECT_TAG_GETTER_SETTER_IMPL(int, int32_t, INT)
	OBJECT_TAG_GETTER_SETTER_IMPL(uint, uint32_t, UINT)
	OBJECT_TAG_GETTER_SETTER_IMPL(long, int64_t, LONG)
	OBJECT_TAG_GETTER_SETTER_IMPL(ulong, uint64_t, ULONG)

	list_tag::list_tag(): tag(tag_type::LIST) {}

	tag* list_tag::get_tag(const uint32_t& index) const {
		assert(index < tags.size() && "Out of bounds");
		return tags[index];
	}
	
	void list_tag::set_tag(const uint32_t& index, tag* value) {
		assert(index < tags.size() && "Out of bounds");
		assert(value != nullptr && "Null tag is not allowed");
		tags[index] = value;
	}
	
	uint32_t list_tag::size() const {
		return tags.size();
	}

	void list_tag::reserve(const uint32_t& size) {
		tags.reserve(size);
	}

	void list_tag::resize(const uint32_t& size) {
		tags.resize(size);
	}

	void list_tag::read(std::istream& input) {
		read_tag_list(input, tags);
	}

	void list_tag::write(std::ostream& output) const {
		write_tag_list(output, tags);
	}

	object_tag* list_tag::get_object(const uint32_t& index) const {
		tag* tag = get_tag(index);
		assert(tag->get_type() == tag_type::OBJECT && "Wrong tag type");
		return static_cast<object_tag*>(tag);
	}

	void list_tag::set_object(const uint32_t& index, object_tag* value) {
		set_tag(index, value);
	}

	std::string list_tag::get_string(const uint32_t& index) const {
		tag* tag = get_tag(index);
		assert(tag->get_type() == tag_type::STRING && "Wrong tag type");
		return static_cast<string_tag*>(tag)->get_value();
	}

	void list_tag::set_string(const uint32_t& index, const std::string& value) {
		assert(value.size() <= 65535 && "Maximum length of string is 65535");
		set_tag(index, new string_tag(value));
	}

	list_tag* list_tag::get_list(const uint32_t& index) const {
		tag* tag = get_tag(index);
		assert(tag->get_type() == tag_type::STRING && "Wrong tag type");
		return static_cast<list_tag*>(tag);
	}

	void list_tag::set_list(const uint32_t& index, list_tag* value) {
		set_tag(index, value);
	}

	void list_tag::add_tag(tag* value) {
		assert(value != nullptr && "Null tag is not allowed");
		tags.push_back(value);
	}

	void list_tag::add_object(object_tag* value) {
		add_tag(value);
	}

	void list_tag::add_string(const std::string& value) {
		assert(value.size() <= 65535 && "Maximum length of string is 65535");
		add_tag(new string_tag(value));
	}

	void list_tag::add_list(list_tag* value) {
		add_tag(value);
	}

	LIST_TAG_GETTER_SETTER_IMPL(bool, bool, BOOL)
	LIST_TAG_GETTER_SETTER_IMPL(byte, int8_t, BYTE)
	LIST_TAG_GETTER_SETTER_IMPL(ubyte, uint8_t, UBYTE)
	LIST_TAG_GETTER_SETTER_IMPL(short, int16_t, SHORT)
	LIST_TAG_GETTER_SETTER_IMPL(ushort, uint16_t, USHORT)
	LIST_TAG_GETTER_SETTER_IMPL(int, int32_t, INT)
	LIST_TAG_GETTER_SETTER_IMPL(uint, uint32_t, UINT)
	LIST_TAG_GETTER_SETTER_IMPL(long, int64_t, LONG)
	LIST_TAG_GETTER_SETTER_IMPL(ulong, uint64_t, ULONG)

	list_tag::~list_tag() {
		for (auto& a_tag : tags) {
			if (a_tag != nullptr) {
				delete a_tag;
			}
		}
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
	PRIMATIVE_TAG_CLASS_IMPL(float, float, FLOAT)
	PRIMATIVE_TAG_CLASS_IMPL(double, double, DOUBLE)

	tag* create_empty_tag(const tag_type& type) {
		switch (type) {
		case jbt::tag_type::NONE:
			assert(false && "None type tag is not allowed");
			return nullptr;
		case jbt::tag_type::BOOL:
			return new bool_tag();
		case jbt::tag_type::LIST:
			return new list_tag();
		case jbt::tag_type::STRING:
			return new string_tag();
		case jbt::tag_type::OBJECT:
			return new object_tag();
		case jbt::tag_type::BYTE:
			return new byte_tag();
		case jbt::tag_type::UBYTE:
			return new ubyte_tag();
		case jbt::tag_type::SHORT:
			return new short_tag();
		case jbt::tag_type::USHORT:
			return new ushort_tag();
		case jbt::tag_type::INT:
			return new int_tag();
		case jbt::tag_type::UINT:
			return new uint_tag();
		case jbt::tag_type::LONG:
			return new long_tag();
		case jbt::tag_type::ULONG:
			return new ulong_tag();
		case jbt::tag_type::FLOAT:
			return new float_tag();
		case jbt::tag_type::DOUBLE:
			return new double_tag();
		default:
			assert(false && "Tag type is not found");
			return nullptr;
		}
	}
}