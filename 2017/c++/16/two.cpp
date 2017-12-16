#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <stack>
#include <sstream>
#include <iomanip>

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

class TDance {
    public:
        TDance()
        : Programs("abcdefghijklmnop")
        {}
        
        void Exec(const std::string& command) {
            if (command[0] == 'x') {
                auto parts = SplitBy<int>(command.substr(1), "/");
                std::swap(Programs[parts[0]], Programs[parts[1]]);
            } else if (command[0] == 'p') {
                auto parts = SplitBy<std::string>(command.substr(1), "/");
                size_t part0 = Programs.find(parts[0]);
                size_t part1 = Programs.find(parts[1]);
                std::swap(Programs[part0], Programs[part1]);
            } else if (command[0] == 's') {
                int shift = std::atoi(command.substr(1).c_str());
                Programs = Programs.substr(16 - shift) + Programs.substr(0, 16 - shift);
            }
        }

        const std::string& GetPrograms() const {
            return Programs;
        }
        
    private:
        std::string Programs;
};

int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    while (getline(input, line)) {
        TDance dance;
        auto moves = SplitBy<std::string>(line, ",");
        for (size_t i = 0; i < 1000000; ++i) {
            dance.Exec(moves[i % moves.size()]);
        }
        std::cout << dance.GetPrograms() << std::endl;
    }

}
