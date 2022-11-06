#include "jbt/serialization.hpp"
#include "jbt/tag.hpp"
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

	void read_tag_type(std::istream& input, tag_type& result) {
		uint8_t id;
		read_ubyte(input, id);
		result = static_cast<tag_type>(id);
	}

	void read_tag_map(std::istream& input, tag_map& result) {
		uint16_t size;
		read_ushort(input, size);

		for (int i = 1; i <= size; ++i) {
			// read name
			uint8_t name_size;
			read_ubyte(input, name_size);

			std::string name;
			name.resize(name_size);

			input.read(name.data(), name_size);

			// read tag type
			tag_type type;
			read_tag_type(input, type);

			// read tag payload
			tag* a_tag = create_empty_tag(type);
			a_tag->read(input);

			result[name] = a_tag;
		}
	}

	void read_tag_list(std::istream& input, tag_list& result) {
		uint32_t size;
		read_uint(input, size);

		result.resize(size);

		for (int i = 0; i < size; ++i) {
			tag_type type;
			read_tag_type(input, type);

			tag* a_tag = create_empty_tag(type);
			a_tag->read(input);
		}
	}

	void write_bool(std::ostream& output, const bool& value) {
		output.write(reinterpret_cast<const char*>(&value), sizeof(bool));
	}

	void write_string(std::ostream& output, const std::string& value) {
		size_t size = value.size();
		
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

	void write_tag_type(std::ostream& output, const tag_type& value) {
		write_ubyte(output, static_cast<uint8_t>(value));
	}

	void write_tag_map(std::ostream& output, const tag_map& value) {
		const size_t size = value.size();
		assert(size <= 65535 && "Maximum number of tags in an object is 65535");

		write_ushort(output, static_cast<uint16_t>(size));

		for (const auto& [name, a_tag] : value) {
			assert(a_tag != nullptr, "Null tag is not allowed");

			// write name
			uint8_t name_size = static_cast<uint8_t>(name.size());

			write_ubyte(output, name_size);
			output.write(name.c_str(), name_size);

			// write tag type
			write_tag_type(output, a_tag->get_type());

			// write tag payload
			a_tag->write(output);
		}
	}

	void write_tag_list(std::ostream& output, const tag_list& value) {
		write_uint(output, value.size());

		for (const auto& a_tag : value) {
			write_tag_type(output, a_tag->get_type());
			a_tag->write(output);
		}
	}
}

