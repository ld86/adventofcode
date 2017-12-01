#include <fstream>
#include <iostream>

size_t FindBasement(const std::string& s) {
	int level = 0;
	for (size_t i = 0; i < s.length(); ++i) {
		if (s[i] == '(') {
			level++;
		} else {
			level--;
		}
		if (level == -1) {
			return i + 1;
		}
	}
	return 0;
}

int main() {
	std::ifstream input{"input.txt"};
	std::string line;
	while (input >> line) {
		std::cout << FindBasement(line) << std::endl;
	}
}
