#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <stack>

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

int GetSeverity(int level, int range) {
    if (level == 0) {
        return 0;
    }
    if (level % ((range - 1) * 2) == 0) {
        return level * range;
    }
    return 0;
}

int GetDelay(const std::vector<std::pair<int, int>>& levels) {
    int delay = 0;
    bool found = false;
    while (!found) {
        found = true;
        for (const auto& pair : levels) {
            int level = pair.first;
            int range = pair.second;
            if (GetSeverity(level + delay, range) != 0) {
                found = false;
                break;
            }
        }
        delay++;
    }
    return delay - 1;
}

int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    std::vector<std::pair<int, int>> levels;
    while (getline(input, line)) {
        auto parts = SplitBy<int>(line, ": ");
        levels.push_back(std::make_pair(parts[0], parts[1]));
    }

    std::cout << GetDelay(levels) << std::endl;

}
