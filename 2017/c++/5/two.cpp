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

int EscapeTheMaze(std::vector<int> maze) {
    int offset = 0;
    int step = 0;
    while (offset >= 0 && offset < maze.size()) {
        int oldOffset = maze[offset];
        if (maze[offset] >= 3) {
            maze[offset]--;
        } else {
            maze[offset]++;
        }
        offset = offset + oldOffset;
        step++;
    }
    return step;
}

int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    std::vector<int> maze;
    while (getline(input, line)) {
        maze.push_back(std::stoi(line));
    }
    std::cout << EscapeTheMaze(maze) << std::endl;
}
