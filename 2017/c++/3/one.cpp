#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <cmath>

template<typename T>
T FromString(const std::string& s);

template<>
int FromString<int>(const std::string& s) {
    return std::stoi(s);
}

template<>
std::string FromString<std::string>(const std::string& s) {
    return s;
}

int FindDistance(const std::string& strSquare) {
    int square = FromString<int>(strSquare);

    int squareRank = std::ceil(std::sqrt(square));
    if (squareRank % 2 == 0) {
        squareRank++;
    }

    int rightBottom = squareRank * squareRank;
    int leftTop = rightBottom - 2 * (squareRank - 1);

    if (square < leftTop) {
        square += 2 * (leftTop - square);
    }

    int x = 0, y = 0;
    if (rightBottom - square > squareRank) {
        x = 0;
    } else {
        x = rightBottom - square;
    }

    if (rightBottom - square < squareRank) {
        y = 0;
    } else {
        y = square - leftTop;
    }

    return std::abs((squareRank - 1) / 2 -  x) + std::abs((squareRank - 1) / 2 - y);
}

int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    while (getline(input, line)) {
        std::cout << FindDistance(line) << std::endl;
    }
}
