#ifndef JBT_SERIALIZER_H
#define JBT_SERIALIZER_H

#include "jbt/internal.hpp"

namespace jbt {

	class serializer {

	public:
		static void read_bool(std::istream& input, bool& result);
		static void read_string(std::istream& input, std::string& result);
		static void read_byte(std::istream& input, int8_t& result);
		static void read_ubyte(std::istream& input, uint8_t& result);
		static void read_short(std::istream& input, int16_t& result);
		static void read_ushort(std::istream& input, uint16_t& result);
		static void read_int(std::istream& input, int32_t& result);
		static void read_uint(std::istream& input, uint32_t& result);
		static void read_long(std::istream& input, int64_t& result);
		static void read_ulong(std::istream& input, uint64_t& result);
		static void read_float(std::istream& input, float& result);
		static void read_double(std::istream& input, double& result);
		static void read_object(std::istream& input, object_t& result);
		static void read_list(std::istream& input, list_t& result);
		static void read_tag(std::istream& input, tag& result);
		static void read_tag_type(std::istream& input, tag_type& result);

		static void write_bool(std::ostream& output, const bool& value);
		static void write_string(std::ostream& output, const std::string& value);
		static void write_byte(std::ostream& output, const int8_t& value);
		static void write_ubyte(std::ostream& output, const uint8_t& value);
		static void write_short(std::ostream& output, const int16_t& value);
		static void write_ushort(std::ostream& output, const uint16_t& value);
		static void write_int(std::ostream& output, const int32_t& value);
		static void write_uint(std::ostream& output, const uint32_t& value);
		static void write_long(std::ostream& output, const int64_t& value);
		static void write_ulong(std::ostream& output, const uint64_t& value);
		static void write_float(std::ostream& output, const float& value);
		static void write_double(std::ostream& output, const double& value);
		static void write_object(std::ostream& output, const object_t& value);
		static void write_list(std::ostream& output, const list_t& value);
		static void write_tag(std::ostream& output, const tag& value);
		static void write_tag_type(std::ostream& output, const tag_type& value);
	};
}

#endif // !JBT_SERIALIZER_H
