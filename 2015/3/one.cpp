#include <iostream>
#include <fstream>
#include <set>

size_t CountHouses(const std::string& s) {
	int i = 0, j = 0;
	std::set<std::pair<int, int>> positions;

	positions.insert(std::make_pair(i, j));
	
	for (const char& c : s) {
		switch (c) {
			case '^':
				j++;
				break;
			case 'v':
				j--;
				break;
			case '>':
				i++;
				break;
			case '<':
				i--;
				break;
		}
		positions.insert(std::make_pair(i, j));
	}

	return positions.size();
}

int main() {
	std::ifstream input{"input.txt"};
	std::string line;

	while (input >> line) {
		std::cout << CountHouses(line) << std::endl;
	}
}
