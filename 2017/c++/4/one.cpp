#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>

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

bool IsValid(const std::string& s) {
    const std::vector<std::string> parts = SplitBy<std::string>(s, ' ');
    std::set<std::string> words;
    for (const auto& part : parts) {
        if (words.find(part) != words.end()) {
            return false;
        }
        words.insert(part);
    }
    return true;
}


int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    size_t count = 0;

    while (getline(input, line)) {
        if (IsValid(line)) {
            count++;
        }
    }

    std::cout << count << std::endl;
}
