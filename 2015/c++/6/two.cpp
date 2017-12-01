#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
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

class TGrid {
	public:
		TGrid()
		: Grid(1000 * 1000, 0)
		{}
		
		void ProcessRule(const std::string& s) {
			std::vector<std::string> parts = SplitBy<std::string>(s, ' ');
			if (parts[0] == "turn" && parts[1] == "on") {
				TurnOn(parts[2], parts[4]);
			} 
			if (parts[0] == "turn" && parts[1] == "off") {
				TurnOff(parts[2], parts[4]);
			} 
			if (parts[0] == "toggle") {
				Toggle(parts[1], parts[3]);
			} 
		}

		size_t EnabledLights() const {
			return std::accumulate(Grid.begin(), Grid.end(), 0);
		}

	private:
		void TurnOn(const std::string& lb, const std::string& tr){
			std::vector<int> lbInt = SplitBy<int>(lb, ',');
			std::vector<int> trInt = SplitBy<int>(tr, ',');

			for (size_t x = lbInt[0]; x <= trInt[0]; ++x) {
				for (size_t y = lbInt[1]; y <= trInt[1]; ++y) {
					Grid[x * 1000 + y] += 1;
				}
			}
		}

		void TurnOff(const std::string& lb, const std::string& tr){
			std::vector<int> lbInt = SplitBy<int>(lb, ',');
			std::vector<int> trInt = SplitBy<int>(tr, ',');

			for (size_t x = lbInt[0]; x <= trInt[0]; ++x) {
				for (size_t y = lbInt[1]; y <= trInt[1]; ++y) {
					Grid[x * 1000 + y] = std::max(0, Grid[x * 1000 + y] - 1);
				}
			}
		}

		void Toggle(const std::string& lb, const std::string& tr){
			std::vector<int> lbInt = SplitBy<int>(lb, ',');
			std::vector<int> trInt = SplitBy<int>(tr, ',');

			for (size_t x = lbInt[0]; x <= trInt[0]; ++x) {
				for (size_t y = lbInt[1]; y <= trInt[1]; ++y) {
					Grid[x * 1000 + y] += 2;
				}
			}
		}


		std::vector<int> Grid;
};

int main() {
	std::ifstream input{"input.txt"};
	std::string line;

	TGrid grid;
	while (std::getline(input, line)) {
		grid.ProcessRule(line);
	}
	std::cout << grid.EnabledLights() << std::endl;
}
