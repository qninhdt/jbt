#include <iostream>
#include <sstream>
#include <jbt/jbt.hpp>
#include <lz4.h>

void build_player(jbt::tag& player) {
    jbt::tag inventory(jbt::tag_type::LIST);

    jbt::tag axe(jbt::tag_type::OBJECT);
    axe.set_string("type", "tool");
    axe.set_byte("power", 12);

    jbt::tag sword(jbt::tag_type::OBJECT);
    sword.set_string("type", "weapon");
    sword.set_byte("power", 90);

    jbt::tag sword_stones(jbt::tag_type::LIST);
    sword_stones.add_string("lava_stone");
    sword_stones.add_string("earth_stone");

    sword.set_tag("stones", std::move(sword_stones));

    jbt::tag dirt(jbt::tag_type::OBJECT);
    dirt.set_string("type", "shit");
    dirt.set_byte("power", -255);

    inventory.add_tag(std::move(axe));
    inventory.add_tag(std::move(sword));
    inventory.add_tag(std::move(dirt));

    player.set_byte_array("avatar", { new int8_t[4*1024], 4*1024 });

    player.set_string("name", "qninh");
    player.set_ushort("health", 100);

    player.set_float("pos_x", 10.0f / 7);
    player.set_float("pos_y", 4.8f / 7);
    player.set_float("pos_z", -94.0f / 7);

    player.set_double("pi", 3.14159265359);

    player.set_ulong("tick", 100000000000000);

    player.set_tag("inventory", std::move(inventory));

    player.set_bool("is_sleeping", true);
}

int main() {
    jbt::serializer* tool = new jbt::diff_endian_serializer();
        
    {
        std::ofstream out("D:/github/jbt/lmao.dat", std::ios_base::binary | std::ios_base::out);

        jbt::tag player(jbt::tag_type::OBJECT);
        jbt::omem_stream output;

        build_player(player);

        tool->write_tag(output, player);

        // compress
        size_t output_size = output.size();
        auto max_compressed_size = LZ4_COMPRESSBOUND(output_size);

        std::cout << "Compress " << output_size << " bytes - Max compressed size: " << max_compressed_size << " byte\n";

        char* compressed_data = new char[max_compressed_size];
        size_t compressed_size = LZ4_compress_default(output.buffer(), compressed_data, output_size, max_compressed_size);

        std::cout << "Compressed size: " << compressed_size << '\n';

        out.write(compressed_data, compressed_size);

        delete[] compressed_data;
        
        out.close();
    }

    

    // decompress
    {
        std::ifstream in("D:/github/jbt/lmao.dat", std::ios_base::binary | std::ios_base::in);

        in.seekg(0, std::ios::end);
        size_t compressed_size = in.tellg();
        in.seekg(0, std::ios::beg);

        char* compressed_data = new char[compressed_size];
        char* decompressed_data = new char[2 * 1024 * 1024]; // 2Mb

        in.read(compressed_data, compressed_size);

        int decompressed_size = LZ4_decompress_safe(compressed_data, decompressed_data, compressed_size, 2 * 1024 * 1024);
        std::cout << "Decompressed size: " << decompressed_size << '\n';
        jbt::imem_stream input(decompressed_data, decompressed_size);

        jbt::tag xplayer;
        tool->read_tag(input, xplayer);

        std::cout << xplayer << '\n';

        delete[] compressed_data;
        delete[] decompressed_data;

        in.close();
    }
    while (1);
    std::cout << "done\n";
}