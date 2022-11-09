#include <iostream>
#include <jbt/jbt.hpp>

int main() {
    std::ofstream out("D:/github/jbt/lmao.dat", std::ios_base::binary | std::ios_base::out);
    
    jbt::tag inventory(jbt::tag_type::LIST);
    
    for (int i = 0; i < 1000000; ++i) {
        if (i % 2 == 0)
            inventory.add_int(i);
        else
            inventory.add_double(i * 2.0);
    }

    jbt::serializer::write_tag(out, inventory);

    out.close();

    std::ifstream in("D:/github/jbt/lmao.dat", std::ios_base::binary | std::ios_base::in);

    in.close();
    //while (1);
    std::cout << "done\n";
}