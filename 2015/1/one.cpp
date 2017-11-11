#include <fstream>
#include <iostream>

size_t CountPar(const std::string& s) {
	int i = 0;
	for (const auto& c : s) {
		if (c == '(') {
			i++;
		} else {
			i--;
		}
	}
	return i;
}

int main() {
	std::ifstream input{"input.txt"};
	std::string line;
	while (input >> line) {
		std::cout << CountPar(line) << std::endl;
	}
}
