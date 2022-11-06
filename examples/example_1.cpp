#include <jbt/jbt.hpp>
#include <iostream>

int main() {
    std::ofstream out("D:/github/jbt/lmao.dat", std::ios_base::binary | std::ios_base::out);
    
    {
        jbt::list_tag list;
        auto a = new uint32_t[1000000];
        for (int i = 0; i < 1000000; ++i) {
           //list.add_uint(i);
           a[i] = i;
        }

        list.write(out);
    }
   
    out.close();
    while (1);
    std::ifstream in("D:/github/jbt/lmao.dat");

    in.close();
}