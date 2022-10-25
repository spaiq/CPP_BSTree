#include <iostream>

template<typename T>
class BST {
public:
    struct Node {
        T data;
        Node* parent;
        Node* left;
        Node* right;

        Node(const T& data, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr)
            : data(data), parent(parent), left(left),  right(right) {
        }

        Node(T&& data, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr)
            : data(data), parent(parent), left(left), right(right) {
        }

        ~Node() {
            parent = nullptr;
            left = nullptr;
            right = nullptr;
        }
    };

private:
    Node* root;
    unsigned length;
};

int main()
{

    return 0;
}