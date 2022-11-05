#include <jbt/jbt.hpp>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
	std::ofstream out("D:/github/jbt/lmao.dat");
	jbt::write_string(out, "1234567890123");
	jbt::write_string(out, "abc");
	jbt::write_string(out, "1dsdsadsad0123");
	out.close();

	jbt::ushort_tag tag;
	std::ifstream f("example.json");
	json data = json::parse(f);
	std::ifstream in("D:/github/jbt/lmao.dat");
	std::string s;
	jbt::read_string(in, s);
	std::cout << s.size() << ' ' << s;
	in.close();
}