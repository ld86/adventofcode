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

int GetScore(const std::string& line) {
    std::stack<char> s;

    int score = 0;

    bool inGarbage = false;
    bool skipNext = false;

    for (const char& c : line) {
        if (skipNext) {
            skipNext = false;
            continue;
        }

        if (inGarbage) {
            bool a = (c == '!' && skipNext == false);
            bool b = (c == '>');
            if (!a && !b) {
                score++;
            }
        }

        switch (c) {
            case '<':
                inGarbage = true;
                break;
            case '>':
                inGarbage = false;
                break;
            case '!':
                skipNext = true;
                break;
            case ',':
                if (inGarbage) {
                    continue;
                }
                break;
            case '{':
                if (inGarbage) {
                    continue;
                }
                s.push(c);
                break;
            case '}':
                if (inGarbage) {
                    continue;
                }
                s.pop();
                break;
        }
    }
    return score;
}

int main() {
    std::ifstream input{"input.txt"};
    std::string line;


    while (getline(input, line)) {
        std::cout << GetScore(line) << std::endl;
    }

}
