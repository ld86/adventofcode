#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <stack>
#include <sstream>
#include <iomanip>
#include <map>

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

class TRope {
    public:
        TRope(const std::string& line)
        : Pointer(0)
        , SkipSize(0)
        {
            for (int i = 0; i < 256; ++i) {
                State.push_back(i);
            }
            for (const unsigned char& i : line) {
                Lengths.push_back(i);
            }
            for (const unsigned char& i : {17,31,73,47,23}) {
                Lengths.push_back(i);
            }
        }

        std::string GetHash() {
            if (Hash == "") {
                Hash = MakeHash();
            }
            return Hash;
        }
    private:
        std::string MakeHash() {
            for (int i = 0; i < 64; ++i) {
                for (const auto& length : Lengths) {
                    ProcessLength(length);
                }
            }

            std::stringstream ss;
            std::vector<unsigned char> parts(16, 0);
            for (int i = 0; i < 256; ++i) {
                parts[i / 16] = parts[i / 16] ^  State[i];
            }

            for (const auto& part : parts) {
                ss << std::setfill('0')
                   << std::setw(2)
                   << std::hex
                   << static_cast<unsigned int>(part);
            }


            return ss.str();
        }

        void ProcessLength(int length) {
            int l = Pointer;
            int r = Pointer + length - 1;
            while (l < r) {
                std::swap(State[l % State.size()], State[r % State.size()]);
                l++;
                r--;
            }
            Pointer = (Pointer + length + SkipSize) % State.size();
            SkipSize++;
        }


    private:
        std::vector<int> State;
        std::vector<unsigned char> Lengths;
        int Pointer;
        int SkipSize;

        std::string Hash;
};

std::map<std::pair<int, int>, bool> BuildMap(const std::string& line) {
    std::map<std::pair<int, int>, bool> map;

    for (int i = 0; i < 128; ++i) {
        std::stringstream input;
        input << line << "-" << i;

        TRope rope(input.str());

        auto hash = rope.GetHash();
        for (int j = 0; j < hash.size(); ++j) {
            char c = hash[j];
            int value = (c >= 'a') ? (c - 'a' + 10) : (c - '0');

            for (int k = 0; k < 4; ++k) {
                if (value & 1) {
                    map.insert({{i, 3 - k + j * 4}, true});
                }
                value = value >> 1;
            }
        }

    }
    return map;
}

void LabelComponent(
        const std::map<std::pair<int, int>, bool>& map,
        std::map<std::pair<int, int>, int>& components,
        std::pair<int, int> start,
        int label)
{
    std::stack<std::pair<int, int>> s;
    s.push(start);
    while (!s.empty()) {
        std::pair<int, int> node = s.top();
        s.pop();
        components.insert({node, label});
        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                if (std::abs(i) + std::abs(j) == 1) {
                    std::pair<int, int> next{node.first + i, node.second + j};
                    if (components.find(next) != components.end()) {
                        continue;
                    }
                    if (map.find(next) != map.end()) {
                        s.push(next);
                    }
                }
            }
        }
    }
}

int CountComponents(const std::map<std::pair<int, int>, bool>& map) {
    int label = 0;

    std::map<std::pair<int, int>, int> components;

    for (int i = 0; i < 128; ++i) {
        for (int j = 0; j < 128; ++j) {
            if (map.find({i, j}) == map.end()) {
                continue;
            }

            if (components.find({i, j}) == components.end()) {
                LabelComponent(map, components, {i, j}, label);
                label++;
            }
        }
    }

    return label;
}

int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    while (getline(input, line)) {
        auto map = BuildMap(line);
        std::cout << CountComponents(map) << std::endl;
    }

}
