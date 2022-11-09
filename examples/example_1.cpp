#include <iostream>
#include <jbt/jbt.hpp>

int main() {
    std::ofstream out("D:/github/jbt/lmao.dat", std::ios_base::binary | std::ios_base::out);
    
    jbt::tag player(jbt::tag_type::OBJECT);

    jbt::tag inventory(jbt::tag_type::LIST);

    jbt::tag axe(jbt::tag_type::OBJECT);
    axe.set_string("type", "tool");
    axe.set_byte("power", 12);

    jbt::tag sword(jbt::tag_type::OBJECT);
    sword.set_string("type", "weapon");
    sword.set_byte("power", 90);

    jbt::tag sword_stones(jbt::tag_type::LIST);
    sword_stones.add_string("lava_sonte");
    sword_stones.add_string("earth_sonte");

    sword.set_tag("stones", std::move(sword_stones));

    jbt::tag dirt(jbt::tag_type::OBJECT);
    dirt.set_string("type", "shit");
    dirt.set_byte("power", -255);

    inventory.add_tag(std::move(axe));
    inventory.add_tag(std::move(sword));
    inventory.add_tag(std::move(dirt));

    player.set_string("name", "qninh");
    player.set_ushort("health", 100);

    player.set_tag("inventory", std::move(inventory));

    jbt::serializer::write_tag(out, player);

    out.close();

    std::ifstream in("D:/github/jbt/lmao.dat", std::ios_base::binary | std::ios_base::in);

    jbt::tag xplayer;
    jbt::serializer::read_tag(in, xplayer);

    std::cout << xplayer << '\n';

    in.close();
    std::cout << "done\n";
}