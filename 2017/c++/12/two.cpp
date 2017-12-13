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

class TPipes {
public:
    void AddPipe(const std::string& pipe) {
        const auto fromToParts = SplitBy<std::string>(pipe, " <-> ");
        const auto& from = fromToParts[0];
        for (const auto& to : SplitBy<std::string>(fromToParts[1], ", ")) {
            Connections[from].push_back(to);
            Connections[to].push_back(from);
        }
    }

    int NumberOfGroups() {
        int label = 0;
        for (const auto& kv : Connections) {
            if (Groups.find(kv.first) == Groups.end()) {
                FindGroup(kv.first, label);
                label++;
            }
        }
        return label;
    }

    int FindGroup(const std::string& id, int label) {
        std::stack<std::string> s;
        std::unordered_map<std::string, bool> was;

        s.push(id);
        while (!s.empty()) {
            std::string from = s.top();
            s.pop();

            was[from] = true;
            Groups[from] = label;

            for (const auto& to : Connections[from]) {
                if (!was[to]) {
                    s.push(to);
                }
            }
        }

        return was.size();
    }

private:
    std::unordered_map<std::string, std::vector<std::string>> Connections;
    std::unordered_map<std::string, int> Groups;

};


int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    TPipes pipes;

    while (getline(input, line)) {
        pipes.AddPipe(line);
    }

    std::cout << pipes.NumberOfGroups() << std::endl;

}
