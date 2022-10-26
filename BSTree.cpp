﻿#include <iostream>
#include <sstream>

template<typename T>
class BST {
public:
    struct Node {
        T data;
        Node* parent;
        Node* left;
        Node* right;
        unsigned index;

        Node(const T& data, Node* parent = nullptr, unsigned index = 0, Node* left = nullptr, Node* right = nullptr)
            : data(data), parent(parent), index(index), left(left), right(right) {
        }

        Node(T&& data, Node* parent = nullptr, unsigned index = 0 Node* left = nullptr, Node* right = nullptr)
            : data(data), parent(parent), index(index), left(left), right(right) {
        }

        ~Node() {
            parent = nullptr;
            left = nullptr;
            right = nullptr;
            index = NULL;
        }
    };

private:
    Node* root;
    unsigned length;
    unsigned new_index;

public:
    BST() noexcept
        : root(nullptr), length(0), new_index(0) {
    }

    ~BST() {
        deleteTree();
    }

    Node* getRoot() {
        return root;
    }

    //a)
    template <typename Comp>
    void append(const T& data, Comp compLess) {
        if (!root) {
            root = new Node(data, nullptr, new_index);
            new_index++;
            length++;
            return;
        }
        if (data == root->data) {
            root->data = data;
            return;
        }
        Node* newVal;
        auto p = root;
        while (p->left || p->right) {
            if(p->left)
                if (data == p->left->data) {
                    p->left->data = data;
                    return;
                }
            if(p->right)
                if (data == p->right->data) {
                    p->right->data = data;
                    return;
                }
            if (compLess(data, p->data)) {
                if (p->left) {
                    p = p->left;
                }
                else {
                    newVal = new Node(data, p, new_index);
                    p->left = newVal;
                    new_index++;
                    length++;
                    return;
                }
            }
            else {
                if (p->right) {
                    p = p->right;
                }
                else {
                    newVal = new Node(data, p, new_index);
                    p->right = newVal;
                    new_index++;
                    length++;
                    return;
                }
            }
        }
        if (compLess(data, p->data)) {
            newVal = new Node(data, p, new_index);
            p->left = newVal;
            new_index++;
            length++;
            return;
        }
        else {
            newVal = new Node(data, p, new_index);
            p->right = newVal;
            new_index++;
            length++;
            return;
        }
        std::cout << "Ooops... I shouldnt be executed.\n";
    }

    //b)
    template <typename Comp>
    Node* findElement(const T& el, Comp compEq, Comp comp) const {
        auto p = root;
        while (!compEq(el, p->data)) {
            if (comp(el, p->data)) {
                if (!p->left) return nullptr;
                p = p->left;
            }
            else {
                if (!p->right) return nullptr;
                p = p->right;
            }
        }
        return p;
    }

    //c)
    template <typename Comp>
    void findAndRemove(Node* el) {
        auto p = el;
        if (p == nullptr) throw std::domain_error("Proba wywolania nieistniejacego elementu.");
        if (p->right) {
            while (true) {
                while (p->right) {
                    p->data = p->right->data;
                    p = p->right;
                }
                if (p->left) {
                    p->data = p->left->data;
                    p = p->left;
                }
                else {
                    delete p;
                    break;
                }
            }
        }
        else if (p->left) {
            p->data = p->left->data;
            p = p->left;
            while (true) {
                while (p->right) {
                    p->data = p->right->data;
                    p = p->right;
                }
                if (p->left) {
                    p->data = p->left->data;
                    p = p->left;
                }
                else {
                    delete p;
                    break;
                }
            }
        }
        else {
            delete p;
        }
        length--;
        return;
    }

    //d)
    std::string preOrder(Node* node) const {
        std::ostringstream str;
        if (node == nullptr) return str.str();
        str << node->data << " ";
        str << preOrder(node->left);
        str << preOrder(node->right);

        return str.str();
    }

    //e)
    std::string inOrder(Node* node) const {
        std::ostringstream str;
        if (node == nullptr) return str.str();
        str << inOrder(node->left);
        str << node->data << " ";
        str << inOrder(node->right);

        return str.str();
    }
    
    //f)
    void deleteTree(Node* node) {
        if (node == nullptr) return;

        deleteTree(node->left);
        deleteTree(node->right);
        if (node == root) {
            length = 0;
            delete root;
            root = nullptr;
            return;
        }
        delete node;
        node = nullptr;
        return;
    }

    //g)
    unsigned treeHeight(Node* node) const {
        if (node == nullptr) return 0;
        else {
            int leftHeight = treeHeight(node->left);
            int rightHeight = treeHeight(node->right);

            return std::max(leftHeight, rightHeight) + 1;
        }
    }

    //h)
    std::string printGraph(const std::string& prefix, const Node* node, bool isLeft)
    {
        std::ostringstream str;
        if (node != nullptr)
        {
            str << prefix << "|--" << node->data << "\n";
            str << printGraph(prefix + (isLeft ? "|   " : "    "), node->left, true);
            str << printGraph(prefix + (isLeft ? "|   " : "    "), node->right, false);
            return str.str();
        }
        return str.str();
    }
};

struct some_class {
    int some_int;
    bool operator== (const some_class& obj) const {
        return some_int == obj.some_int;
    };
};

std::ostream& operator<< (std::ostream& out, const some_class& obj) {
    out << obj.some_int;
    return out;
}

int main()
{
    auto compLess = [](const some_class& a, const some_class& b) {
        return a.some_int < b.some_int;
    };

    auto compEq = [](const some_class& a, const some_class& b) {
        return a.some_int == b.some_int;
    };

    BST<some_class>* tree = new BST<some_class>;
    tree->append(some_class{ 10 }, compLess);
    tree->append(some_class{ 2 }, compLess);
    tree->append(some_class{ 32 }, compLess);
    tree->append(some_class{ 41 }, compLess);
    tree->append(some_class{ 13 }, compLess);
    tree->append(some_class{ 7 }, compLess);
    tree->append(some_class{ 5 }, compLess);
    tree->append(some_class{ 2 }, compLess);
    tree->append(some_class{ 32 }, compLess);
    tree->append(some_class{ 13 }, compLess);
    tree->append(some_class{ 41 }, compLess);

    std::cout << tree->preOrder(tree->getRoot()) << "\n";
    std::cout << tree->inOrder(tree->getRoot()) << "\n";
    std::cout << tree->treeHeight(tree->getRoot()) << "\n";
    std::cout << "\n" << tree->printGraph("", tree->getRoot(), false) << "\n";
    tree->deleteTree(tree->getRoot());
    std::cout << tree->inOrder(tree->getRoot()) << "\n";

    return 0;
}