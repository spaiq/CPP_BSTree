#include <iostream>
#include <sstream>
#include <stack>

template<typename T>
class binary_search_tree {
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

        Node(T&& data, Node* parent = nullptr, unsigned index = 0, Node* left = nullptr, Node* right = nullptr)
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
    binary_search_tree() noexcept
        : root(nullptr), length(0), new_index(0) {
    }

    ~binary_search_tree() {
        delete_tree();
    }

    Node* get_root() {
        return root;
    }

    //a)
    template <typename Comp>
    void append(const T& data, Comp comp_less) {
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
        Node* new_value;
        auto temp = root;
        while (temp->left || temp->right) {
            if(temp->left)
                if (data == temp->left->data) {
                    temp->left->data = data;
                    return;
                }
            if(temp->right)
                if (data == temp->right->data) {
                    temp->right->data = data;
                    return;
                }
            if (comp_less(data, temp->data)) {
                if (temp->left) {
                    temp = temp->left;
                }
                else {
                    new_value = new Node(data, temp, new_index);
                    temp->left = new_value;
                    new_index++;
                    length++;
                    return;
                }
            }
            else {
                if (temp->right) {
                    temp = temp->right;
                }
                else {
                    new_value = new Node(data, temp, new_index);
                    temp->right = new_value;
                    new_index++;
                    length++;
                    return;
                }
            }
        }
        if (comp_less(data, temp->data)) {
            new_value = new Node(data, temp, new_index);
            temp->left = new_value;
            new_index++;
            length++;
            return;
        }
        else {
            new_value = new Node(data, temp, new_index);
            temp->right = new_value;
            new_index++;
            length++;
            return;
        }
        std::cout << "Ooops... I shouldnt be executed.\n";
    }

    //b)
    template <typename Comp>
    Node* find_element(const T& el, Comp comp_less) const {
        auto temp = root;
        while (!(el == temp->data)) {
            if (comp_less(el, temp->data)) {
                if (!temp->left) return nullptr;
                temp = temp->left;
            }
            else {
                if (!temp->right) return nullptr;
                temp = temp->right;
            }
        }
        return temp;
    }

    //c)
    void find_and_remove(Node* node) {
        auto temp = node;
        if (temp == nullptr) throw std::domain_error("Proba wywolania nieistniejacego elementu.");
        if (temp->right) {
            temp = temp->right;
            while (temp->left) {
                temp = temp->left;
            }
            node->data = temp->data;
            node->index = temp->index;
            temp->parent->left = nullptr;
        }
        else if (temp->left) {
            temp = temp->left;
            while (temp->right) {
                temp = temp->right;
            }
            node->data = temp->data;
            node->index = temp->index;
            temp->parent->right = nullptr;
        }
        delete temp;
        temp = nullptr;
        length--;
        return;
    }

    //d)
    std::string pre_order(Node* node) const {
        std::ostringstream stream;
        if (node == nullptr) return stream.str();
        stream << node->data << " "
               << pre_order(node->left)
               << pre_order(node->right);

        return stream.str();
    }

    //e)
    std::string in_order(Node* node) const {
        std::ostringstream stream;
        if (node == nullptr) return stream.str();
        stream << in_order(node->left)
               << node->data << " "
               << in_order(node->right);

        return stream.str();
    }
    
    //f)
    void delete_tree(Node* node) {
        /*if (node == nullptr) return;

        delete_tree(node->left);
        delete_tree(node->right);
        if (node == root) {
            length = 0;
            delete root;
            root = nullptr;
            return;
        }
        delete node;
        node = nullptr;
        return;*/
        auto temp = root;
        Node* del;
        while (true) {
            while (temp->left)
                temp = temp->left;
            if (temp->right)
                temp = temp->right;
            else if (temp == root) break;
            else{
                del = temp;
                temp = temp->parent;
                if (del == temp->left) temp->left = nullptr;
                else temp->right = nullptr;
                delete del;
                del = nullptr;
            }
        }
        delete root;
        root = nullptr;
        return;
    }

    //g)
    unsigned tree_height(Node* node) const {
        if (node == nullptr) return 0;
        else {
            int left_height = tree_height(node->left);
            int right_height = tree_height(node->right);

            return std::max(left_height, right_height) + 1;
        }
    }

    //h)
    /*std::string test(Node* node) const { //RECURSIVE METHOD
        std::ostringstream stream;
        if (node == nullptr) return stream.str();
        stream << node->index << "\t";
        if (node->parent) stream << node->parent->index << "\t";
        else stream << "NULL" << "\t";
        if (node->left) stream << node->left->index << "\t";
        else stream << "NULL" << "\t";
        if (node->right) stream << node->right->index << "\t";
        else stream << "NULL" << "\t";
        stream << node->data << "\n"
               << test(node->left) << test(node->right);

        return stream.str();
    }*/

    std::string to_string() {
        if (root == NULL)
            return "Tree is empty";
        std::stack<Node*> nodeStack;
        nodeStack.push(root);
        std::ostringstream stream;
        stream << "size: " << length
            << "\nheight: " << tree_height(root)
            << "\n\nindex\tparent\tleft\tright\tdata\n";

        while (nodeStack.empty() == false) {
            Node* node = nodeStack.top();
            stream << node->index << "\t";

            if (node->parent) stream << node->parent->index << "\t";
            else stream << "NULL" << "\t";

            if (node->left) stream << node->left->index << "\t";
            else stream << "NULL" << "\t";

            if (node->right) stream << node->right->index << "\t";
            else stream << "NULL" << "\t";

            stream << node->data << "\n";
            nodeStack.pop();

            if (node->right)
                nodeStack.push(node->right);
            if (node->left)
                nodeStack.push(node->left);
        }
        return stream.str();
    }

    std::string print_graph(const std::string& prefix, const Node* node, bool isLeft)
    {
        std::ostringstream stream;
        if (node != nullptr)
        {
            stream << prefix << "|--" << node->data << "\n";
            stream << print_graph(prefix + (isLeft ? "|   " : "    "), node->left, true);
            stream << print_graph(prefix + (isLeft ? "|   " : "    "), node->right, false);
            return stream.str();
        }
        return stream.str();
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
    auto comp_less = [](const some_class& a, const some_class& b) {
        return a.some_int < b.some_int;
    };

    binary_search_tree<some_class>* tree = new binary_search_tree<some_class>;
    tree->append(some_class{ 10 }, comp_less);
    tree->append(some_class{ 2 }, comp_less);
    tree->append(some_class{ 32 }, comp_less);
    tree->append(some_class{ 41 }, comp_less);
    tree->append(some_class{ 13 }, comp_less);
    tree->append(some_class{ 7 }, comp_less);
    tree->append(some_class{ 5 }, comp_less);
    tree->append(some_class{ 2 }, comp_less);
    tree->append(some_class{ 32 }, comp_less);
    tree->append(some_class{ 13 }, comp_less);
    tree->append(some_class{ 41 }, comp_less);

    std::cout << tree->pre_order(tree->get_root()) << "\n";
    std::cout << tree->in_order(tree->get_root()) << "\n";
    std::cout << tree->tree_height(tree->get_root()) << "\n";
    std::cout << "\n" << tree->print_graph("", tree->get_root(), false) << "\n";
    tree->find_and_remove(tree->get_root());
    std::cout << "\n" << tree->print_graph("", tree->get_root(), false) << "\n";

    tree->delete_tree(tree->get_root());
    std::cout << tree->in_order(tree->get_root()) << "\n";

    return 0;
}