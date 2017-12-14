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

int GetSeverity(const std::string& line) {
    auto parts = SplitBy<int>(line, ": ");
    if (parts[0] == 0) {
        return 0;
    }
    if (parts[0] % ((parts[1] - 1) * 2) == 0) {
        return parts[0] * parts[1];
    }
    return 0;
}

int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    int sum = 0;
    while (getline(input, line)) {
        sum += GetSeverity(line);
    }

    std::cout << sum << std::endl;

}
