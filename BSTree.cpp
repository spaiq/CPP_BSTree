#include <iostream>
#include <sstream>

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
            : data(data), parent(parent), left(left), right(right) {
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
            if (comp(data, p->data)) {
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
        if (comp(data, p->data)) {
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
};

struct some_class {
    int some_int;
    bool operator== (const some_class& obj) const {
        return some_int == obj.some_int;
    };
};

int main()
{
    auto compLess = [](const some_class& a, const some_class& b) {
        return a.some_int < b.some_int;
    };

    auto compEq = [](const some_class& a, const some_class& b) {
        return a.some_int == b.some_int;
    };

    BST<some_class>* test = new BST<some_class>;

    return 0;
}