#ifndef JBT_TAG_H
#define JBT_TAG_H

#include <map>
#include <vector>
#include "jbt/internal.hpp"

#define OBJECT_TAG_GETTER_SETTER(name_, type)                     \
	type get_##name_(const std::string& name) const;              \
	void set_##name_(const std::string& name, const type& value);

#define LIST_TAG_GETTER_SETTER(name_, type)                      \
	type get_##name_(const uint32_t& index) const;               \
	void set_##name_(const uint32_t& index, const type& value);  \
	void add_##name_(const type& value);


#define PRIMATIVE_TAG_CLASS(name, type)         \
	class name##_tag: public tag {              \
	public:                                     \
	    name##_tag();                           \
	    name##_tag(const type& value);          \
	    name##_tag(type&& value);               \
	    void read(std::istream& input);         \
	    void write(std::ostream& output) const; \
		type get_value() const;                 \
	private:                                    \
		type value;                             \
	};

namespace jbt {

	class tag {
	public:
		virtual void read(std::istream& input) = 0;
		virtual void write(std::ostream& output) const = 0;
		tag_type get_type() const;

		tag(const tag_type& type);
		tag(tag_type&& type);

	protected:
		tag_type type;
	};

	class string_tag : public tag {
	public:
		string_tag();
		string_tag(const std::string& value);
		string_tag(std::string&& value);
		void read(std::istream& input);
		void write(std::ostream& output) const;
		std::string get_value() const;
	private:
		std::string value;
	};

	class list_tag;
	class object_tag : public tag {

	public:

		object_tag();

		void read(std::istream& input);
		void write(std::ostream& output) const;

		tag* get_tag(const std::string& name) const;
		void set_tag(const std::string& name, tag* tag);

		object_tag* get_object(const std::string& name);
		void set_object(const std::string& name, object_tag* value);

		std::string get_string(const std::string& name);
		void set_string(const std::string& name, const std::string value);

		list_tag* get_list(const std::string& name);
		void set_string(const std::string& name, list_tag* value);

		OBJECT_TAG_GETTER_SETTER(bool, bool)
		OBJECT_TAG_GETTER_SETTER(byte, int8_t)
		OBJECT_TAG_GETTER_SETTER(ubyte, uint8_t)
		OBJECT_TAG_GETTER_SETTER(short, int16_t)
		OBJECT_TAG_GETTER_SETTER(ushort, uint16_t)
		OBJECT_TAG_GETTER_SETTER(int, int32_t)
		OBJECT_TAG_GETTER_SETTER(uint, uint32_t)
		OBJECT_TAG_GETTER_SETTER(long, int64_t)
		OBJECT_TAG_GETTER_SETTER(ulong, uint64_t)

	private:
		tag_map tags;

	};

	class list_tag : public tag {
	public:
		list_tag();
		~list_tag();

		tag* get_tag(const uint32_t& index) const;
		void set_tag(const uint32_t& index, tag* value);

		uint32_t size() const;
		void reserve(const uint32_t& size);
		void resize(const uint32_t& size);

		void read(std::istream& input);
		void write(std::ostream& output) const;

		object_tag* get_object(const uint32_t& index) const;
		void set_object(const uint32_t& index, object_tag* value);

		std::string get_string(const uint32_t& index) const;
		void set_string(const uint32_t& index, const std::string& value);

		list_tag* get_list(const uint32_t& index) const;
		void set_list(const uint32_t& index, list_tag* value);

		void add_tag(tag* value);
		void add_object(object_tag* value);
		void add_string(const std::string& value);
		void add_list(list_tag* value);

		LIST_TAG_GETTER_SETTER(bool, bool)
		LIST_TAG_GETTER_SETTER(byte, int8_t)
		LIST_TAG_GETTER_SETTER(ubyte, uint8_t)
		LIST_TAG_GETTER_SETTER(short, int16_t)
		LIST_TAG_GETTER_SETTER(ushort, uint16_t)
		LIST_TAG_GETTER_SETTER(int, int32_t)
		LIST_TAG_GETTER_SETTER(uint, uint32_t)
		LIST_TAG_GETTER_SETTER(long, int64_t)
		LIST_TAG_GETTER_SETTER(ulong, uint64_t)

	private:
		tag_list tags;
	};

	PRIMATIVE_TAG_CLASS(bool, bool)
	PRIMATIVE_TAG_CLASS(byte, int8_t)
	PRIMATIVE_TAG_CLASS(ubyte, uint8_t)
	PRIMATIVE_TAG_CLASS(short, int16_t)
	PRIMATIVE_TAG_CLASS(ushort, uint16_t)
	PRIMATIVE_TAG_CLASS(int, int32_t)
	PRIMATIVE_TAG_CLASS(uint, uint32_t)
	PRIMATIVE_TAG_CLASS(long, int64_t)
	PRIMATIVE_TAG_CLASS(ulong, uint64_t)
	PRIMATIVE_TAG_CLASS(float, float)
	PRIMATIVE_TAG_CLASS(double, double)

	tag* create_empty_tag(const tag_type& type);
}

#endif // !JBT_TAG_H
