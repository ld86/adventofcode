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

size_t IndexOfMax(const std::vector<int>& blocks) {
    int max = blocks[0];
    size_t maxI = 0;
    for (size_t i = 1; i < blocks.size(); ++i) {
        if (blocks[i] > max) {
            max = blocks[i];
            maxI = i;
        }
    }
    return maxI;
}

int Count(std::vector<int>& blocks) {
    std::set<std::vector<int>> history;
    int steps = 0;
    while (history.find(blocks) == history.end()) {
        history.insert(blocks);
        int maxI = IndexOfMax(blocks);
        int max = blocks[maxI];

        blocks[maxI] = 0;
        int i = (maxI + 1) % blocks.size();

        while (max > 0) {
            blocks[i]++;
            i = (i + 1) % blocks.size();
            max--;
        }
        steps++;
    }

    return steps;
}

int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    while (getline(input, line)) {
        std::vector<int> blocks = SplitBy<int>(line, ' ');
        std::cout << Count(blocks) << std::endl;
    }
}
