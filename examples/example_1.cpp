#include <iostream>
#include <jbt/jbt.hpp>
#include <algorithm>
#include <iomanip>

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
    inventory.add_int(123);

    player.set_byte_array("avatar", { new int8_t[4*1024*1024], 4*1024*1024, true });

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

void print_info(const jbt::hjbt_file& file) {
    std::vector < std::pair<std::uint32_t, std::pair<std::int32_t, std::uint32_t>>> info_list;

    auto cur = file.m_first_range;
    while (cur) {
        info_list.push_back({ cur->offset, { -1, cur->size } });
        cur = cur->next;
    }

    for (const auto& [id, info] : file.m_info_map) {
        const auto& [offset, size] = info;
        info_list.push_back({ offset, { id, size } });
    }   
    std::sort(info_list.begin(), info_list.end());

    for (const auto& [offset, info] : info_list) {
        const auto& [id, size] = info;
        if (id >= 0) {
            std::cout << "[" << std::setw(1) << id << "]";
        }
        else {
            std::cout << "[ ]";
        }
        std::cout << std::setw(4) << offset << " ->";
        if (size) std::cout << std::setw(4) << size + offset << '\n'; else std::cout << std::setw(4) << " +oo\n";
    }
    std::cout << "--------------\n";

}

void build(jbt::tag& a_tag, std::uint32_t size) {
    auto data = new int8_t[size];

    for (int i = 0; i < size; ++i) data[i] = std::sin(i)*255+i;

    a_tag.set_byte_array("data", { data , size, true });
}

int main() {
    jbt::init();
    //jbt::hjbt_util::create_empty_file("D:/github/jbt/cc.hjbt", 16, 64);
    jbt::hjbt_file file("D:/github/jbt/cc.hjbt");
    jbt::tag x(jbt::tag_type::OBJECT);

    //std::cout << file.size() << '\n';
    //file.begin_write();
    //
    //
    //for (int i = 1; i < 10; ++i) {
    //    build(x, i * 100);
    //    file.write(i, x);
    //}
    //
    //print_info(file);
    //
    //build(x, 1000);
    //file.write(2, x);
    //
    //file.remove(4);
    //file.remove(7);
    //
    //file.end_write();

    print_info(file);

    file.begin_write();
    build(x, 10);
    file.write(0, x);

    print_info(file);

    file.remove(3);

    print_info(file);

    build(x, 2000);
    file.write(9, x);

    print_info(file);

    file.remove(8);

    print_info(file);

}