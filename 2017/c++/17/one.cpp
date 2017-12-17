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
struct Node {
    Node(const T& value)
    : Value(value)
    {}

    T Value;
    Node<T>* Next = nullptr;
};

class TCircularList {
public:
    TCircularList()
    : Head(new Node<int>(0))
    , Current(Head)
    {
        Head->Next = Head;
    }

    int CurrentValue() const {
        return Current->Value;
    }

    int NextValue() const {
        return Current->Next->Value;
    }

    void MoveForward(int steps) {
        for (int i = 0; i < steps; ++i) {
            Current = Current->Next;
        }
    }

    void InsertValueAfterCurrent(int value) {
        Node<int>* node = new Node<int>(value);
        node->Next = Current->Next;
        Current->Next = node;

        Current = node;
    }


private:
    Node<int>* Head;
    Node<int>* Current;
};

int main() {
    int stepSize = 371;
    TCircularList list;

    for (int i = 0; i < 2017; ++i) {
        list.MoveForward(stepSize);
        list.InsertValueAfterCurrent(i + 1);
    }

    std::cout << list.CurrentValue() << " " << list.NextValue() << std::endl;

    return 0;
}
