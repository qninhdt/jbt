#ifndef JBT_SERIALIZATION_H
#define JBT_SERIALIZATION_H

#include "jbt/internal.hpp"

namespace jbt {

	void read_bool(std::istream& input, bool& result);
	void read_string(std::istream& input, std::string& result);
	void read_byte(std::istream& input, int8_t& result);
	void read_ubyte(std::istream& input, uint8_t& result);
	void read_short(std::istream& input, int16_t& result);
	void read_ushort(std::istream& input, uint16_t& result);
	void read_int(std::istream& input, int32_t& result);
	void read_uint(std::istream& input, uint32_t& result);
	void read_long(std::istream& input, int64_t& result);
	void read_ulong(std::istream& input, uint64_t& result);
	void read_float(std::istream& input, float& result);
	void read_double(std::istream& input, double& result);

	void write_bool(std::ostream& output, const bool& value);
	void write_string(std::ostream& output, const std::string& value);
	void write_byte(std::ostream& output, const int8_t& value);
	void write_ubyte(std::ostream& output, const uint8_t& value);
	void write_short(std::ostream& output, const int16_t& value);
	void write_ushort(std::ostream& output, const uint16_t& value);
	void write_int(std::ostream& output, const int32_t& value);
	void write_uint(std::ostream& output, const uint32_t& value);
	void write_long(std::ostream& output, const int64_t& value);
	void write_ulong(std::ostream& output, const uint64_t& value);
	void write_float(std::ostream& output, const float& value);
	void write_double(std::ostream& output, const double& value);

}

#endif // !JBT_SERIALIZATION_H
