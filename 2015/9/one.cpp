#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>

using TDistances = std::unordered_map<std::string, std::unordered_map<std::string, int>>;

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

class TRouteTable {
	public:
		TRouteTable()
		{}

		void AddRoute(const std::string& s) {
			std::vector<std::string> parts = SplitBy<std::string>(s, ' ');
			Distances[parts[0]][parts[2]] = std::stoi(parts[4]);
			Distances[parts[2]][parts[0]] = std::stoi(parts[4]);

			Points.insert(parts[0]);
			Points.insert(parts[2]);
		}

		int ShortestDistance(const std::vector<std::string>& path) {
			if (path.size() == Points.size()) {
				int distance = 0;
				for (size_t i = 0; i < path.size() - 1; ++i) {
					distance += Distances.at(path[i]).at(path[i + 1]);
				}
				return distance;
			}
			
			std::vector<int> distances;
			std::set<std::string> pathPoints{path.begin(), path.end()};
			for (const std::string& point : Points) {
				if (pathPoints.find(point) != pathPoints.end()) {
					continue;
				}
				std::vector<std::string> nextPath{path};
				nextPath.push_back(point);
				distances.push_back(ShortestDistance(nextPath));
			}

			return *std::min_element(distances.begin(), distances.end());
		}

	private:
		TDistances Distances;
		std::set<std::string> Points;
};

int main() {
	std::ifstream input{"input.txt"};
	std::string line;

	TRouteTable table;
	while (std::getline(input, line)) {
		table.AddRoute(line);
	}

	std::cout << table.ShortestDistance({}) << std::endl;
}
