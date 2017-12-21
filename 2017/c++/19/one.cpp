#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <stack>
#include <sstream>
#include <iomanip>

enum class TDirection {
    DOWN,
    UP,
    RIGHT,
    LEFT,
    NONE
};

class TMap {
public:
    TMap(const std::vector<std::string>& lines)
    : Lines(lines)
    , X(0)
    , Y(0)
    , PrevX(X)
    , PrevY(Y)
    , Direction(TDirection::DOWN)
    {
        FindStartingPosition();
    }

    unsigned char GetCurrent() const {
        return Lines.at(Y).at(X);
    }

    TDirection GetDirection() const {
        return Direction;
    }

    unsigned char GetNext() const {
        switch (Direction) {
            case TDirection::DOWN:
                return Lines.at(Y + 1).at(X);
            case TDirection::UP:
                return Lines.at(Y - 1).at(X);
            case TDirection::RIGHT:
                return Lines.at(Y).at(X + 1);
            case TDirection::LEFT:
                return Lines.at(Y).at(X - 1);
            case TDirection::NONE:
                return Lines.at(Y).at(X);
        }
    }

    void Move() {
        switch (Direction) {
            case TDirection::DOWN:
                PrevX = X;
                PrevY = Y;
                Y++;
                break;
            case TDirection::UP:
                PrevX = X;
                PrevY = Y;
                Y--;
                break;
            case TDirection::RIGHT:
                PrevX = X;
                PrevY = Y;
                X++;
                break;
            case TDirection::LEFT:
                PrevX = X;
                PrevY = Y;
                X--;
                break;
            case TDirection::NONE:
                throw std::runtime_error("Nowhere to move");
        }

    }

    bool Step() {
        if (Direction == TDirection::NONE) {
            return false;
        }

        if (GetNext() == '-' || GetNext() == '|') {
            Move();
            return true;
        }

        if (GetNext() == '+') {
            Move();
            Direction = FindNewDirection();
            return true;
        }

        if (GetNext() >= 'A' && GetNext() <= 'Z') {
            Letters << GetNext();
            Move();
            return true;
        }

        return false;
    }

    unsigned char GetByXY(int x, int y) {
        return Lines.at(y).at(x);
    }

    int GetX() const {
        return X;
    }

    int GetY() const {
        return Y;
    }

    std::string GetLetters() const {
        return Letters.str();
    }

private:
    TDirection FindNewDirection() {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (std::abs(i) + std::abs(j) != 1) {
                    continue;
                }
                if (X + i == PrevX && Y + j == PrevY) {
                    continue;
                }

                unsigned char next = Lines.at(Y + j).at(X + i);

                if (next == ' ') {
                    continue;
                }

                if ((next == '-' || next == '+') && i == -1) {
                    return TDirection::LEFT;
                }
                if ((next == '-' || next == '+') && i == 1) {
                    return TDirection::RIGHT;
                }
                if ((next == '|' || next == '+') && j == -1) {
                    return TDirection::UP;
                }
                if ((next == '|' || next == '+') && j == 1) {
                    return TDirection::DOWN;
                }
            }
        }
        return TDirection::NONE;
    }

    void FindStartingPosition() {
        for (size_t i = 0; i < Lines[0].size(); ++i) {
            if (Lines[0][i] == '|') {
                X = i;
                break;
            }
        }
    }

private:
    std::vector<std::string> Lines;
    int X, Y;
    int PrevX, PrevY;
    TDirection Direction;
    std::stringstream Letters;
};

int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    std::vector<std::string> lines;
    while (getline(input, line)) {
        lines.push_back(line);
    }

    TMap map{lines};
    while (map.Step()) {
        std::cout << map.GetX() << " " << map.GetY() << " " << map.GetCurrent() << " " << map.GetNext() << " " << static_cast<int>(map.GetDirection()) << std::endl;
    }
    std::cout << map.GetLetters() << std::endl;

    return 0;
}
