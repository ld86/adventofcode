#include <fstream>
#include <iostream>

size_t FindSum(const std::string& s) {
    size_t sum = 0;
    size_t offset = s.length() / 2;
    for (size_t i = 0; i < s.length(); ++i) {
        if (s[i] == s[(i + offset) % s.length()]) {
            sum += (s[i] - '0');
        }
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
