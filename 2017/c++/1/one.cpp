#include <fstream>
#include <iostream>

size_t FindSum(const std::string& s) {
    size_t sum = 0;
    for (size_t i = 0; i < s.length() - 1; ++i) {
        if (s[i] == s[i + 1]) {
            sum += (s[i] - '0');
        }
    }

    if (s[s.length() - 1] == s[0]) {
        sum += (s[s.length() - 1] - '0');
    }

    return sum;
}


int main() {
	std::ifstream input{"input.txt"};
	std::string line;
	while (input >> line) {
		std::cout << FindSum(line) << std::endl;
	}
}
