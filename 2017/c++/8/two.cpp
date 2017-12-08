#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>

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

using TMemory = std::unordered_map<std::string, int>;

class TCondition {
    enum EType {
        LESS = 0,
        GREATER,
        LESS_OR_EQUAL,
        GREATER_OR_EQUAL,
        EQUAL,
        NOT_EQUAL
    };
    public:
        TCondition(const std::string& line)
        : RawLine(line)
        {
            std::vector<std::string> parts = SplitBy<std::string>(line, " ");
            RegisterName = parts[4];
            Value = std::atoi(parts[6].c_str());
            if (parts[5] == "<=") {
                Type = LESS_OR_EQUAL;
            } else if (parts[5] == ">=") {
                Type = GREATER_OR_EQUAL;
            } else if (parts[5] == ">") {
                Type = GREATER;
            } else if (parts[5] == "<") {
                Type = LESS;
            } else if (parts[5] == "==") {
                Type = EQUAL;
            } else if (parts[5] == "!=") {
                Type = NOT_EQUAL;
            }

        }

        bool Check(const TMemory& memory) const {
            int memoryValue = 0;
            auto it = memory.find(RegisterName);
            if (it != memory.end()) {
                memoryValue = it->second;
            }

            switch (Type) {
                case LESS:
                    return memoryValue < Value;
                case GREATER:
                    return memoryValue > Value;
                case LESS_OR_EQUAL:
                    return memoryValue <= Value;
                case GREATER_OR_EQUAL:
                    return memoryValue >= Value;
                case EQUAL:
                    return memoryValue == Value;
                case NOT_EQUAL:
                    return memoryValue != Value;
            }
        }
    private:
        std::string RegisterName;
        std::string RawLine;
        int Value;
        EType Type;
};

class TInstruction {
    enum EType {
        INC = 0,
        DEC
    };
    public:
        TInstruction(const std::string& line)
        : Condition(line)
        , RawLine(line)
        {
            std::vector<std::string> parts = SplitBy<std::string>(line, " ");
            RegisterName = parts[0];
            Value = std::atoi(parts[2].c_str());

            if (parts[1] == "inc") {
                Type = INC;
            } else {
                Type = DEC;
            }
        }

        int Apply(TMemory& memory) const {
            if (!Condition.Check(memory)) {
                return memory[RegisterName];
            }
            switch (Type) {
                case INC:
                    memory[RegisterName] += Value;
                    break;
                case DEC:
                    memory[RegisterName] -= Value;
                    break;
                default:
                    throw std::runtime_error("Apply");
            }

            return memory[RegisterName];
        }

    private:
        TCondition Condition;
        std::string RawLine;
        std::string RegisterName;
        int Value;
        EType Type;
};

class TCPU {
    public:
        void Exec(const TInstruction& instruction) {
           int value = instruction.Apply(Memory);
           if (value > MaxValue) {
               MaxValue = value;
           }
        }

        const TMemory& GetMemory() const {
            return Memory;
        }

        int GetMaxValue() const {
            return MaxValue;
        }

    private:
        TMemory Memory;
        int MaxValue;
};

int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    TCPU cpu;

    while (getline(input, line)) {
        TInstruction instruction{line};
        cpu.Exec(instruction);

    }

    std::cout << cpu.GetMaxValue() << std::endl;
}
