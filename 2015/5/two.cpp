#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

bool FirstRule(const std::string& s) {
	for (size_t i = 0; i < s.length() - 1; ++i) {
		for (size_t j = i + 2; j < s.length() - 1; ++j) {
			if (s.substr(i, 2) == s.substr(j, 2)) {
				return true;
			}
		}
	}
	return false;
}

bool SecondRule(const std::string& s) {
	for (size_t i = 0; i < s.length() - 2; ++i) {
		if (s[i] == s[i+2]) {
			return true;
		}
	}
	return false;
}

bool IsNice(const std::string& s) {
	return FirstRule(s) && SecondRule(s);
}


int main() {
	std::ifstream input{"input.txt"};
	std::string line;

	size_t niceCount = 0;
	while (input >> line) {
		if (IsNice(line)) {
			niceCount++;
		}
	}
	std::cout << niceCount << std::endl;
}
