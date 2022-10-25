﻿#include <iostream>

template<typename T>
class BST {
public:
    struct Node {
        T data;
        Node* parent;
        Node* left;
        Node* right;
        // unsigned index;

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

public:
    BST() noexcept
        : root(nullptr), length(0) {
    }

    ~BST() {
        //clear();
    }

    //a)
    template <typename Comp>
    void append(const T& data, Comp comp) {
        if (!root) {
            root = new Node(data);
            return;
        }
        if (data == root->data) {
            root->data = data;
            return;
        }
        Node* newVal;
        auto p = root;
        while (p->left || p->right) {
            if (comp(p->data, data)) {
                if (p->left) {
                    p = p->left;
                }
                else {
                    newVal = new Node(data, p);
                    p->left = newVal;
                    return;
                }
            }
            else {
                if (p->right) {
                    p = p->right;
                }
                else {
                    newVal = new Node(data, p);
                    p->right = newVal;
                    return;
                }
            }
        }
        if (comp(p->data, data)) {
            newVal = new Node(data, p);
            p->left = newVal;
            return;
        }
        else {
            newVal = new Node(data, p);
            p->right = newVal;
            return;
        }
        std::cout << "Ooops... I shouldnt be executed.\n";
    }
};

int main()
{

    return 0;
}