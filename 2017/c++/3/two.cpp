#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <cmath>
#include <map>

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

enum TDirection {
    RIGHT = 0,
    UP = 1,
    LEFT = 2,
    DOWN = 3
};

class TGrid {
    public:
        TGrid()
        : CurrentRank(1)
        , X(0)
        , Y(0)
        , AddedCount(0)
        , Direction(RIGHT)
        {
            Grid[std::make_pair(X, Y)] = 1;
        }

        int MoveToNextCell() {
            if (AddedCount == CurrentRank - 2 && Direction == UP) {
                Direction = LEFT;
                AddedCount = 0;
            }
            if (AddedCount == CurrentRank - 1 && Direction == LEFT) {
                Direction = DOWN;
                AddedCount = 0;
            }
            if (AddedCount == CurrentRank - 1 && Direction == DOWN) {
                Direction = RIGHT;
                AddedCount = 0;
            }
            if (AddedCount == CurrentRank && Direction == RIGHT) {
                Direction = UP;
                AddedCount = 0;
                CurrentRank += 2;
            }

            if (Direction == UP) {
                Y++;
            }
            if (Direction == LEFT) {
                X--;
            }
            if (Direction == DOWN) {
                Y--;
            }
            if (Direction == RIGHT) {
                X++;
            }

            return AddValueToGrid();
        }

    private:
        int AddValueToGrid() {
            int sum = 0;
            for (int i = -1; i < 2; ++i) {
                for (int j = -1; j < 2; ++j) {
                    if (i == 0 && j == 0) {
                        continue;
                    }
                    auto it = Grid.find(std::make_pair(X + i, Y + j));
                    if (it != Grid.end()) {
                        sum += it->second;
                    }
                }
            }

            if (sum == 0) {
                sum = 1;
            }

            Grid[std::make_pair(X, Y)] = sum;
            AddedCount++;

            return sum;
        }

    private:
        int CurrentRank;
        int AddedCount;
        int X, Y;
        TDirection Direction;
        std::map<std::pair<int, int>, int> Grid;
};

int Find(const std::string& strSquare) {
    int squareValue = FromString<int>(strSquare);
    TGrid grid;
    int cellValue = 1;
    while (cellValue < squareValue) {
        cellValue = grid.MoveToNextCell();
    }
    return cellValue;
}

int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    while (getline(input, line)) {
        std::cout << Find(line) << std::endl;
    }
}
