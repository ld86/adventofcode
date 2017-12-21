#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <stack>
#include <sstream>
#include <iomanip>
#include <queue>
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

class TPipe {
public:
    void Push(unsigned long long value) {
        Queue.push(value);
    }

    std::pair<unsigned long long, bool> Pop() {
        if (Queue.size() == 0) {
            return std::make_pair(0, false);
        }
        int value = Queue.front();
        Queue.pop();
        return std::make_pair(value, true);
    }
private:
    std::queue<unsigned long long> Queue;
};

class TIPC {
public:
    void Send(unsigned long long value, int cpuId) {
        Pipes[cpuId].Push(value);
    }

    std::pair<unsigned long long, bool> Recv(int cpuId) {
        return Pipes[cpuId].Pop();
    }

private:
    std::map<int, TPipe> Pipes;
};

class TCPU {
public:
    TCPU(const int cpuId,
         const std::vector<TInstruction>& program,
         TIPC& ipc)
    : Program(program)
    , CpuID(cpuId)
    , IP(0)
    , IPC(ipc)
    , Debug(0)
    {
        Memory["p"] = CpuID;
    }

    void Run() {
        while (IP < Program.size()) {
            Step();
        }
    }

    int Step() {
        const auto& instruction = Program[IP];
        int offset = Exec(instruction);
        IP += offset;
        return offset;
    }

    int Exec(const TInstruction& i) {
        int step = 1;

        if (i.Command == "snd") {
            Debug++;
            IPC.Send(GetValue(i.OP1), 1 - CpuID);
        } else if (i.Command == "set") {
            Memory[i.OP1] = GetValue(i.OP2);
        } else if (i.Command == "add") {
            Memory[i.OP1] = Memory[i.OP1] + GetValue(i.OP2);
        } else if (i.Command == "mul") {
            Memory[i.OP1] = Memory[i.OP1] * GetValue(i.OP2);
        } else if (i.Command == "mod") {
            Memory[i.OP1] = Memory[i.OP1] % GetValue(i.OP2);
        } else if (i.Command == "rcv") {
            auto value = IPC.Recv(CpuID);
            if (value.second == false) {
                step = 0;
            } else {
                Memory[i.OP1] = value.first;
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

    int GetDebug() const {
        return Debug;
    }

private:
    std::vector<TInstruction> Program;
    unsigned long long IP;
    int CpuID;
    TIPC& IPC;
    std::unordered_map<std::string, unsigned long long> Memory;

    unsigned long long Debug;
};

int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    std::vector<TInstruction> program;
    while (getline(input, line)) {
        program.push_back(TInstruction{line});
    }

    TIPC ipc;
    TCPU cpu0{0, program, ipc};
    TCPU cpu1{1, program, ipc};

    int makedSteps = 1;
    while (makedSteps) {
        makedSteps = 0;

        makedSteps += std::abs(cpu0.Step());
        makedSteps += std::abs(cpu1.Step());
    }

    std::cout << cpu0.GetDebug() << std::endl;
    std::cout << cpu1.GetDebug() << std::endl;

    return 0;
}
