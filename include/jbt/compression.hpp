#ifndef JBT_COMPRESSION_H
#define JBT_COMPRESSION_H

#include "jbt/internal.hpp"

namespace jbt {

    std::size_t compress_tag(serializer& ser, std::ostream& dst, const tag& src);
    void decompress_tag(serializer& ser, std::istream& src, tag& dst, const std::size_t& src_size, const std::size_t& dst_size);
}

#endif // JBT_COMPRESSION_H