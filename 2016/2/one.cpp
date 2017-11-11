#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

template<typename T>
T FromString(const std::string&& s);

template<>
int FromString(const std::string&& s) {
	return std::stoi(s);
}

template<>
std::string FromString(const std::string&& s) {
	return s;
}

template<typename T>
std::vector<T> SplitBy(const std::string& s, char c) {
	auto l = 0;
	auto r = s.find(c);
	std::vector<T> result;

	while (r != std::string::npos) {
		result.push_back(FromString<T>(s.substr(l, r - l)));
		l = r + 1;
		r = s.find(c, l);
	}

	result.push_back(FromString<T>(s.substr(l)));
	return result;
}

size_t FindWrapArea(const std::string& s) {
	auto d = SplitBy<int>(s, 'x');
	std::sort(d.begin(), d.end());
	return 2 * d[0] * d[1] + 2 * d[1] * d[2] + 2 * d[2] * d[0] + d[0] * d[1];
}

int main() {
	std::ifstream input{"input.txt"};
	std::string line;
	size_t wrapArea = 0;

	while (input >> line) {
		wrapArea += FindWrapArea(line);
	}

	std::cout << wrapArea << std::endl;
}
