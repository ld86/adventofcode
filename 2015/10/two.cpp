#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>

std::string MakeTurn(const std::string& s) {
	std::stringstream ss;

	size_t count = 1;
	for (size_t i = 1; i < s.length(); ++i) {
		if (s[i - 1] != s[i]) {
			ss << count << s[i - 1];
			count = 0;
		}
		count++;
	}

	ss << count << s[s.length() - 1];

	return ss.str();
}

int main() {
	std::ifstream input{"input.txt"};
	std::string line;

	while (std::getline(input, line)) {
		for (size_t i = 0; i < 50; ++i) {
			line = MakeTurn(line);
		}
		break;
	}

	std::cout << line.length() << std::endl;
}
