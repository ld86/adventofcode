#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>

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
std::vector<T> SplitBy(const std::string& s, const std::string& c) {
    auto l = 0;
    auto r = s.find(c);
    std::vector<T> result;

    while (r != std::string::npos) {
        result.push_back(FromString<T>(s.substr(l, r - l)));
        l = r + c.size();
        r = s.find(c, l);
    }

    result.push_back(FromString<T>(s.substr(l)));
    return result;
}

class TTable {
public:
    void AddDisk(const std::string& disk) {
        std::vector<std::string> parts = SplitBy<std::string>(disk, " -> ");
        if (parts.size() == 1) {
            return;
        }
        for (const auto& from : SplitBy<std::string>(parts[1], ", ")) {
            Routes[from] = SplitBy<std::string>(parts[0], " ")[0];
        }
    }

    std::string FindRoot() const {
        if (Routes.size() == 0) {
            return "";
        }
        std::string disk = Routes.begin()->first;
        while (Routes.find(disk) != Routes.end()) {
            disk = Routes.at(disk);
        }
        return disk;
    }

private:
    std::unordered_map<std::string, std::string> Routes;
};

int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    TTable table;

    while (getline(input, line)) {
        table.AddDisk(line);
    }
    std::cout << table.FindRoot() << std::endl;
}
