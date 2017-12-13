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

class TGrid {
public:
    TGrid()
    : X(0)
    , Y(0)
    {}

    void Move(const std::string& direction) {
        if (direction == "s") {
            Y--;
        } else if (direction == "n") {
            Y++;
        } else if (direction == "ne") {
            X++;
        } else if (direction == "sw") {
            X--;
        } else if (direction == "nw") {
            Y++;
            X--;
        } else if (direction == "se") {
            Y--;
            X++;
        }
    }

    int DistanceFromOrigin() {
        int z = 0;
        int x = X, y = Y;
        while (x > 0 && y < 0) {
            x--;
            y++;
            z++;
        }
        while (X < 0 && Y > 0) {
            x++;
            y--;
            z++;
        }
        return std::abs(x) + std::abs(y) + z;
    }

private:
    int X, Y;
};

int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    while (getline(input, line)) {
        TGrid grid;
        for (const auto& direction : SplitBy<std::string>(line, ",")) {
            grid.Move(direction);
        }
        std::cout << grid.DistanceFromOrigin() << std::endl;
    }

}
