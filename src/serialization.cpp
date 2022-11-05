#include "jbt/serialization.hpp"
#include <iostream>

namespace jbt {

	void read_bool(std::istream& input, bool& result) {
		input.read(reinterpret_cast<char*>(&result), sizeof(bool));
	}

	void read_string(std::istream& input, std::string& result) {
		uint16_t size;

		// read size
		read_ushort(input, size);
		result.resize(static_cast<size_t>(size));

		// read data
		input.read(result.data(), size * sizeof(char));
	}

	void read_byte(std::istream& input, int8_t& result) {
		input.read(reinterpret_cast<char*>(&result), sizeof(int8_t));
	}
	void read_ubyte(std::istream& input, uint8_t& result) {
		input.read(reinterpret_cast<char*>(&result), sizeof(uint8_t));
	}
	void read_short(std::istream& input, int16_t& result) {
		input.read(reinterpret_cast<char*>(&result), sizeof(int16_t));
	}
	void read_ushort(std::istream& input, uint16_t& result) {
		input.read(reinterpret_cast<char*>(&result), sizeof(uint16_t));
	}
	void read_int(std::istream& input, int32_t& result) {
		input.read(reinterpret_cast<char*>(&result), sizeof(int32_t));
	}
	void read_uint(std::istream& input, uint32_t& result) {
		input.read(reinterpret_cast<char*>(&result), sizeof(uint32_t));
	}
	void read_long(std::istream& input, int64_t& result) {
		input.read(reinterpret_cast<char*>(&result), sizeof(int64_t));
	}
	void read_ulong(std::istream& input, uint64_t& result) {
		input.read(reinterpret_cast<char*>(&result), sizeof(uint64_t));
	}
	void read_float(std::istream& input, float& result) {
		input.read(reinterpret_cast<char*>(&result), sizeof(float));
	}
	void read_double(std::istream& input, double& result) {
		input.read(reinterpret_cast<char*>(&result), sizeof(double));
	}

	void write_bool(std::ostream& output, const bool& value) {
		output.write(reinterpret_cast<const char*>(&value), sizeof(bool));
	}

	void write_string(std::ostream& output, const std::string& value) {
		size_t size = value.size();
		assert(size <= 65535 && "String size is too big. Maximum size is 65535");
		
		// write string size
		write_ushort(output, static_cast<uint16_t>(size));

		// write string data
		output.write(value.c_str(), size * sizeof(char));
	}

	void write_byte(std::ostream& output, const int8_t& value) {
		output.write(reinterpret_cast<const char*>(&value), sizeof(int8_t));
	}

	void write_ubyte(std::ostream& output, const uint8_t& value) {
		output.write(reinterpret_cast<const char*>(&value), sizeof(uint8_t));
	}

	void write_short(std::ostream& output, const int16_t& value) {
		output.write(reinterpret_cast<const char*>(&value), sizeof(int16_t));
	}

	void write_ushort(std::ostream& output, const uint16_t& value) {
		output.write(reinterpret_cast<const char*>(&value), sizeof(uint16_t));
	}

	void write_int(std::ostream& output, const int32_t& value) {
		output.write(reinterpret_cast<const char*>(&value), sizeof(int32_t));
	}

	void write_uint(std::ostream& output, const uint32_t& value) {
		output.write(reinterpret_cast<const char*>(&value), sizeof(uint32_t));
	}

	void write_long(std::ostream& output, const int64_t& value) {
		output.write(reinterpret_cast<const char*>(&value), sizeof(int64_t));
	}

	void write_ulong(std::ostream& output, const uint64_t& value) {
		output.write(reinterpret_cast<const char*>(&value), sizeof(uint64_t));
	}

	void write_float(std::ostream& output, const float& value) {
		output.write(reinterpret_cast<const char*>(&value), sizeof(float));
	}

	void write_double(std::ostream& output, const double& value) {
		output.write(reinterpret_cast<const char*>(&value), sizeof(double));
	}

}

