#include "jbt/jbt.hpp"
#include <lz4.h>

namespace jbt {

    std::size_t compress_tag(serializer& ser, std::ostream& dst, const tag& src) {
        omem_stream src_stream;
        ser.write_tag(src_stream, src);

        const std::size_t src_size = src_stream.size();
        const std::size_t max_compressed_size = LZ4_COMPRESSBOUND(src_size);

        char* compressed_data = new char[max_compressed_size];
        const std::int32_t compressed_size = LZ4_compress_default(src_stream.buffer(),
            compressed_data, src_size, max_compressed_size);

        assert(compressed_size > 0 && "Compression is failed");
        
        /// TODO: compress tag into dst stream directly without temp var
        dst.write(compressed_data, compressed_size);

        delete[] compressed_data;

        return compressed_size;
    }

    void decompress_tag(serializer& ser, std::istream& src, tag& dst,
        const std::size_t& src_size, const std::size_t& dst_size) {
        char* compressed_data = new char[src_size];
        char* decompressed_data = new char[dst_size];

        src.read(compressed_data, src_size);
        const std::size_t decompressed_size = LZ4_decompress_safe(compressed_data,
            decompressed_data, src_size, dst_size);
        
        imem_stream dst_stream(decompressed_data, decompressed_size);
        ser.read_tag(dst_stream, dst);

        delete[] compressed_data;
        delete[] decompressed_data;
    }
}