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

int FindDifference(const std::string& line) {
    std::vector<int> values = SplitBy<int>(line, '\t');
    for (size_t i = 0; i < values.size(); i++) {
        for (size_t j = 0; j < values.size(); ++j) {
            if (i != j && values[i] % values[j] == 0) {
                return values[i] / values[j];
            }
        }
    }
    return 0;
}

int main() {
	std::ifstream input{"input.txt"};
	std::string line;

	int sum = 0;

	while (getline(input, line)) {
		sum += FindDifference(line);
	}

	std::cout << sum << std::endl;
}
