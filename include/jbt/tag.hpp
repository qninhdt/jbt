#ifndef JBT_TAG_H
#define JBT_TAG_H

#include "jbt/internal.hpp"

#define PRIMATIVE_TAG_CLASS(name, type)         \
	class name##_tag: public base_tag {         \
	public:                                     \
		name##_tag();                           \
		name##_tag(const type& value);          \
		name##_tag(type&& value);               \
		void read(std::istream& input);         \
		void write(std::ostream& output) const; \
	private:                                    \
		type value;                             \
	};

namespace jbt {

	class base_tag {
	public:
		virtual void read(std::istream& input) = 0;
		virtual void write(std::ostream& output) const = 0;
		tag_type get_type() const;

		base_tag(const tag_type& type);
		base_tag(tag_type&& type);

	protected:
		tag_type type;
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

}

#endif // !JBT_TAG_H
