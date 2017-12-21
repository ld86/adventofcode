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

struct TInstruction{
public:
    TInstruction(const std::string& line) {
        auto parts = SplitBy<std::string>(line, " ");
        Command = parts[0];
        OP1 = parts[1];
        if (parts.size() == 3) {
            OP2 = parts[2];
        }
    }

    std::string Command;
    std::string OP1;
    std::string OP2;
};

class TCPU {
public:
    TCPU(const std::vector<TInstruction>& program)
    : Program(program)
    , IP(0)
    , LastSND(0)
    {}

    void Run() {
        while (IP < Program.size()) {
            const auto& instruction = Program[IP];
            IP += Exec(instruction);
        }
    }

    int Exec(const TInstruction& i) {
        int step = 1;

        if (i.Command == "snd") {
            LastSND = GetValue(i.OP1);
        } else if (i.Command == "set") {
            Memory[i.OP1] = GetValue(i.OP2);
        } else if (i.Command == "add") {
            Memory[i.OP1] = Memory[i.OP1] + GetValue(i.OP2);
        } else if (i.Command == "mul") {
            Memory[i.OP1] = Memory[i.OP1] * GetValue(i.OP2);
        } else if (i.Command == "mod") {
            Memory[i.OP1] = Memory[i.OP1] % GetValue(i.OP2);
        } else if (i.Command == "rcv") {
            if (GetValue(i.OP1) != 0) {
                std::cout << LastSND << std::endl;
                throw std::runtime_error("HALT");
            }
        } else if (i.Command == "jgz") {
            if (GetValue(i.OP1) > 0) {
                step = GetValue(i.OP2);
            }
        } else {
            throw std::runtime_error("BAD INSTRUCTION");
        }

        return step;
    }

    int GetValue(const std::string& op) {
        if (op.length() == 1 && op[0] >= 'a' && op[0] <= 'z') {
            return Memory[op];
        }

        return std::atoi(op.c_str());
    }

private:
    std::vector<TInstruction> Program;
    unsigned long long IP;
    unsigned long long LastSND;
    std::vector<unsigned long long> RecoveredSND;
    std::unordered_map<std::string, unsigned long long> Memory;
};

int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    std::vector<TInstruction> program;
    while (getline(input, line)) {
        program.push_back(TInstruction{line});
    }

    TCPU cpu{program};

    cpu.Run();


    return 0;
}
