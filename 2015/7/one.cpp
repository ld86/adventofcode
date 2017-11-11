#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
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
std::vector<T> SplitBy(const std::string& s, char c) {
	auto l = 0;
	auto r = s.find(c);
	std::vector<T> result;

	while (r != std::string::npos) {
		result.push_back(FromString<T>(s.substr(l, r - l)));
		l = r + 1;
		r = s.find(c, l);
	}

	result.push_back(FromString<T>(s.substr(l)));
	return result;
}

struct TRule {
	TRule(const std::string& s) {
		std::vector<std::string> parts = SplitBy<std::string>(s, ' ');
		if (parts.size() == 3) {
			Operation = "STORE";
			InputName.push_back(parts[0]);
			OutputName = parts[2];
		} else if (parts.size() == 4) {
			Operation = parts[0];
			InputName.push_back(parts[1]);
			OutputName = parts[3];
		} else if (parts.size() == 5) {
			InputName.push_back(parts[0]);
			InputName.push_back(parts[2]);
			OutputName = parts[4];
			Operation = parts[1];
		}
	}

	std::string OutputName;
	std::vector<std::string> InputName;
	std::string Operation;
	uint16_t Value;
};

class TRuleTable {
	public:
		TRuleTable()
		{}

		void AddRule(const std::string& s) {
			TRule rule{s};
			Table.insert(std::make_pair(rule.OutputName, rule));
		}

		uint16_t Evaluate(const std::string& a) {
			if (a.find_first_not_of("0123456789") == std::string::npos) {
				return std::stoi(a);
			}

			auto it = Memory.find(a);
			if (it != Memory.end()) {
				return it->second;
			}

			const TRule& rule = Table.at(a);

			uint16_t value;

			if (rule.Operation == "STORE") {
				value = Evaluate(rule.InputName[0]);
			} else if (rule.Operation == "AND") {
				value = Evaluate(rule.InputName[0]) & Evaluate(rule.InputName[1]);
			} else if (rule.Operation == "OR") {
				value = Evaluate(rule.InputName[0]) | Evaluate(rule.InputName[1]);
			} else if (rule.Operation == "LSHIFT") {
				value = Evaluate(rule.InputName[0]) << Evaluate(rule.InputName[1]);
			} else if (rule.Operation == "RSHIFT") {
				value = Evaluate(rule.InputName[0]) >> Evaluate(rule.InputName[1]);
			} else if (rule.Operation == "NOT") {
				value = ~Evaluate(rule.InputName[0]);
			} else {
				throw std::logic_error("Something goes wrong");
			}

			std::cout << a << " : " << value << std::endl;
			
			Memory.insert(std::make_pair(a, value));
			return value;
		}

	private:
		std::unordered_map<std::string, TRule> Table;
		std::unordered_map<std::string, uint16_t> Memory;
};

int main() {
	std::ifstream input{"input.txt"};
	std::string line;

	TRuleTable table;
	while (std::getline(input, line)) {
		table.AddRule(line);
	}
	std::cout << table.Evaluate("a") << std::endl;
}
