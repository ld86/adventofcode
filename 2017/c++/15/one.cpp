#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <stack>
#include <sstream>
#include <iomanip>

class TGenerator {
    public:
        TGenerator(unsigned long long seed, unsigned long long multiplier)
        : State(seed)
        , Multiplier(multiplier)
        {}

        unsigned int Next() {
            State = (State * Multiplier) % 2147483647;
            return State;
        }


    private:
        unsigned long long State;
        unsigned long long Multiplier;
};

int main() {
    TGenerator a{783, 16807};
    TGenerator b{325, 48271};

    int s = 0;
    for (int i = 0; i < 40000000; ++i) {
        unsigned long long aValue = a.Next();
        unsigned long long bValue = b.Next();
        if ((aValue & 0xFFFF) == (bValue & 0xFFFF)) {
            s++;
        }
    }

    std::cout << s << std::endl;
}
