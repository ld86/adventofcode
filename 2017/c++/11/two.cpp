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
    , Max(0)
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

        Max = std::max(Max, DistanceFromOrigin());
    }

    int MaxDistanceFromOrigin() const {
        return Max;
    }

    int DistanceFromOrigin() const {
        int z = 0;
        int x = X, y = Y;
        if (x > 0 && y < 0) {
            int m = std::min(std::abs(x), std::abs(y));
            x = x - m;
            y = y + m;
            z = m;
        }
        if (x < 0 && y > 0) {
            int m = std::min(std::abs(x), std::abs(y));
            x = x + m;
            y = y - m;
            z = m;
        }
        return std::abs(x) + std::abs(y) + z;
    }

private:
    int X, Y;
    int Max;
};

int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    while (getline(input, line)) {
        TGrid grid;
        for (const auto& direction : SplitBy<std::string>(line, ",")) {
            grid.Move(direction);
        }
        std::cout << grid.MaxDistanceFromOrigin() << std::endl;
    }

}
