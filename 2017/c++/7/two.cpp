#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <numeric>

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

class TTable {
public:
    void AddDisk(const std::string& disk) {
        std::vector<std::string> parts = SplitBy<std::string>(disk, " -> ");
        std::string strWeight = SplitBy<std::string>(parts[0], " ")[1];
        int weight = std::atoi(strWeight.substr(1, strWeight.length() - 1).c_str());
        std::string to = SplitBy<std::string>(parts[0], " ")[0];

        Weight[to] = weight;
        FromRoot[to];

        if (parts.size() == 1) {
            return;
        }

        for (const auto& from : SplitBy<std::string>(parts[1], ", ")) {
            ToRoot[from] = to;
            FromRoot[to].push_back(from);
        }
    }

    std::string FindRoot() const {
        if (ToRoot.size() == 0) {
            return "";
        }
        std::string disk = ToRoot.begin()->first;
        while (ToRoot.find(disk) != ToRoot.end()) {
            disk = ToRoot.at(disk);
        }
        return disk;
    }

    std::vector<int> FindWeightOfSubtree(const std::string& name) const {
        std::vector<int> weights;
        for (const auto& child : FromRoot.at(name)) {
            std::vector<int> childrenWeights = FindWeightOfSubtree(child);
            for (const auto& i : childrenWeights) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
            weights.push_back(std::accumulate(childrenWeights.begin(), childrenWeights.end(), 0));
        }

        if (weights.size()) {
            int max = *std::max_element(weights.begin(), weights.end());
            int min = *std::min_element(weights.begin(), weights.end());
            if (max != min) {
                std::cout << "[!] " << name << " " <<  max - min << std::endl;
            }
        }

        weights.push_back(Weight.at(name));

        return weights;
    }

private:
    std::unordered_map<std::string, std::string> ToRoot;
    std::unordered_map<std::string, std::vector<std::string>> FromRoot;
    std::unordered_map<std::string, int> Weight;
    std::unordered_map<std::string, int> WeightOfSubtree;
};

int main() {
    std::ifstream input{"input.txt"};
    std::string line;

    TTable table;

    while (getline(input, line)) {
        table.AddDisk(line);
    }
    table.FindWeightOfSubtree(table.FindRoot());
}
