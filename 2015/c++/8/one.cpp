#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

size_t Count(const std::string& s) {
	size_t realSize = 0;
	bool inEscape = false;
	for (size_t i = 0; i < s.length(); ++i) {
		if (i == 0 && s[i] == '"') {
			continue;
		}
		if (i == s.length() - 1 && s[i] == '"') {
			continue;
		}

		if (s[i] == '\\' && !inEscape) {
			inEscape = true;
			continue;
		}

		if (s[i] == '\\' && inEscape) {
			inEscape = false;
			realSize += 1;
			continue;
		}

		if (s[i] == '"' && inEscape) {
			inEscape = false;
			realSize += 1;
			continue;
		}

		if (s[i] == 'x' && inEscape) {
			inEscape = false;
			realSize += 1;
			i += 2;
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
	std::cout << a - b << std::endl;
}
