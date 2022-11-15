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

    player.set_byte_array("avatar", { new int8_t[4*1024*1024], 4*1024*1024 });

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

        build_player(player);

        jbt::compress_tag(*tool, out, player);

        out.close();
    }

    // decompress
    {
        std::ifstream in("D:/github/jbt/lmao.dat", std::ios_base::binary | std::ios_base::in);

        in.seekg(0, std::ios::end);
        size_t compressed_size = in.tellg();
        in.seekg(0, std::ios::beg);

        jbt::tag xplayer;

        jbt::decompress_tag(*tool, in, xplayer, compressed_size, 8 * 1024 * 1024);

        std::cout << xplayer << '\n';

        in.close();
    }
    while (1);
    std::cout << "done\n";
}