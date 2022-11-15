#include <jbt/jbt.hpp>
#include <iostream>

int main() {
    jbt::omem_streambuf buf;
    std::ostream out((std::streambuf*) &buf);
    out.write(new char[1000000], 1000000);
    //for (int i = 0; i < buf.get_size(); ++i) std::cout << buf.buffer[i];
}