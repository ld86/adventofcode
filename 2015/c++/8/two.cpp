#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

size_t Count(const std::string& s) {
	size_t realSize = 2;
	for (size_t i = 0; i < s.length(); ++i) {
		if (s[i] == '\\') {
			realSize += 2;
			continue;
		}
		if (s[i] == '"') {
			realSize += 2;
			continue;
		}
		realSize += 1;
	}

	return realSize;
}

int main() {
	std::ifstream input{"input.txt"};
	std::string line;

	size_t a = 0, b = 0;
	while (std::getline(input, line)) {
		a += line.length();
		b += Count(line);
	}
	std::cout << b - a << std::endl;
}
