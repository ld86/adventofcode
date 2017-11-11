#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

bool FirstRule(const std::string& s) {
	std::string vowels{"aeiou"};
	size_t count = 0;
	for (const char& c : s) {
		if (vowels.find(c) != std::string::npos) {
			count++;
		}
	}
	return count > 2;
}

bool SecondRule(const std::string& s) {
	for (size_t i = 0; i < s.length() - 1; ++i) {
		if (s[i] == s[i+1]) {
			return true;
		}
	}
	return false;
}

bool ThirdRule(const std::string& s) {
	std::vector<std::string> patterns{"ab", "cd", "pq", "xy"};
	for (const std::string& pattern : patterns) {
		if (s.find(pattern) != std::string::npos) {
			return false;
		}
	}
	return true;
}

bool IsNice(const std::string& s) {
	return FirstRule(s) && SecondRule(s) && ThirdRule(s);
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
