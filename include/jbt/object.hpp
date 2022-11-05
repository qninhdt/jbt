#ifndef JBT_OBJECT_H
#define JBT_OBJECT_H

#include <unordered_map>
#include "jbt/internal.hpp"

#define OBJECT_GETTER_SETTER(name_, type)                    \
	type get_##name_(const std::string& name);               \
	void set_##name_(std::string& name, const type& value); 

namespace jbt {

	class base_tag;

	class object {

	public:
		
		object();

		OBJECT_GETTER_SETTER(bool, bool)
		OBJECT_GETTER_SETTER(string, std::string)
		OBJECT_GETTER_SETTER(byte, int8_t)
		OBJECT_GETTER_SETTER(ubyte, uint8_t)
		OBJECT_GETTER_SETTER(short, int16_t)
		OBJECT_GETTER_SETTER(ushort, uint16_t)
		OBJECT_GETTER_SETTER(int, int32_t)
		OBJECT_GETTER_SETTER(uint, uint32_t)
		OBJECT_GETTER_SETTER(long, int64_t)
		OBJECT_GETTER_SETTER(ulong, uint64_t)
		
	private:
		std::unordered_map<std::string, base_tag*> tags;

	};

}

#endif // !JBT_OBJECT_H
