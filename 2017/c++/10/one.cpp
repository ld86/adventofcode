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

class TRope {
    public:
        TRope()
        : Pointer(0)
        , SkipSize(0)
        {
            for (int i = 0; i < 256; ++i) {
                Values.push_back(i);
            }
        }

        void ProcessLength(int length) {
            int l = Pointer;
            int r = Pointer + length - 1;
            while (l < r) {
                std::swap(Values[l % Values.size()], Values[r % Values.size()]);
                l++;
                r--;
            }
            Pointer = (Pointer + length + SkipSize) % Values.size();
            SkipSize++;
        }

        void Print() {
            for (const auto& i : Values) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }

        int Mul() {
            return Values[0] * Values[1];
        }

    private:
        std::vector<int> Values;
        int Pointer;
        int SkipSize;
};

int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    while (getline(input, line)) {
        TRope rope;
        for (const auto& length : SplitBy<int>(line, ",")) {
            rope.ProcessLength(length);
        }

        std::cout << rope.Mul() << std::endl;
    }

}
