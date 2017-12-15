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

int CountBits(const std::string& line) {
    int s = 0;
    for (int i = 0; i < 128; ++i) {
        std::stringstream input;
        input << line << "-" << i;
        TRope rope(input.str());
        for (const char& c : rope.GetHash()) {
            int value = (c >= 'a') ? (c - 'a' + 10) : (c - '0');
            for (int j = 0; j < 4; ++j) {
                if (value & 1) {
                    s++;
                }
                value = value >> 1;
            }
        }
    }
    return s;
}

int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    while (getline(input, line)) {
        std::cout << CountBits(line) << std::endl;
    }

}
