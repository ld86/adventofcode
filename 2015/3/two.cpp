#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using THistory = std::set<std::pair<int, int>>;

class TSanta {
	public:
		TSanta(THistory& history)
		: I(0)
		, J(0)
		, History(history)
		{
			History.insert(std::make_pair(I, J));
		}

		void Move(char c) {
			switch (c) {
				case '^':
					J++;
					break;
				case 'v':
					J--;
					break;
				case '>':
					I++;
					break;
				case '<':
					I--;
					break;
			}
			History.insert(std::make_pair(I, J));
		}

		size_t NumberOfHouses() const {
			return History.size();
		}

	private:
		int I, J;
		THistory& History;;
};

size_t CountHouses(const std::string& s) {
	THistory commonHistory;
	std::vector<TSanta> santas(2, commonHistory);
	for (size_t i = 0; i < s.length(); ++i) {
		char c = s[i];
		santas[i % santas.size()].Move(c);
	}

	return commonHistory.size();
}

int main() {
	std::ifstream input{"input.txt"};
	std::string line;

	while (input >> line) {
		std::cout << CountHouses(line) << std::endl;
	}
}
