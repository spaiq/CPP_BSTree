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
    Node* ROOT;
    unsigned LENGTH;
    unsigned NEW_INDEX;

public:
    binary_search_tree() noexcept
        : ROOT(nullptr), LENGTH(0), NEW_INDEX(0) {
    }

    ~binary_search_tree() {
        delete_tree();
    }

    Node* get_root() {
        return ROOT;
    }

    //a)
    template <typename Comp>
    void append(const T& data, Comp comp_less) {
        if (!ROOT) {
            ROOT = new Node(data, nullptr, NEW_INDEX);
            NEW_INDEX++;
            LENGTH++;
            return;
        }
        if (data == ROOT->data) {
            ROOT->data = data;
            return;
        }
        Node* new_value;
        auto temp = ROOT;
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
                    new_value = new Node(data, temp, NEW_INDEX);
                    temp->left = new_value;
                    NEW_INDEX++;
                    LENGTH++;
                    return;
                }
            }
            else {
                if (temp->right) {
                    temp = temp->right;
                }
                else {
                    new_value = new Node(data, temp, NEW_INDEX);
                    temp->right = new_value;
                    NEW_INDEX++;
                    LENGTH++;
                    return;
                }
            }
        }
        if (comp_less(data, temp->data)) {
            new_value = new Node(data, temp, NEW_INDEX);
            temp->left = new_value;
            NEW_INDEX++;
            LENGTH++;
        }
        else {
            new_value = new Node(data, temp, NEW_INDEX);
            temp->right = new_value;
            NEW_INDEX++;
            LENGTH++;
        }
        
        return;
    }

    //b)
    template <typename Comp>
    Node* find_element(const T& el, Comp comp_less) const {
        auto temp = ROOT;
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
            if (temp->right) {
                if (temp == temp->parent->right) {
                    temp->right->parent = temp->parent;
                    temp->parent->right = temp->right;
                }
                else {
                    temp->right->parent = temp->parent;
                    temp->parent->left = temp->right;
                }
            }
        }
        else if (temp->left) {
            temp = temp->left;
            while (temp->right) {
                temp = temp->right;
            }
            node->data = temp->data;
            node->index = temp->index;
            if (temp->left) {
                if (temp == temp->parent->right) {
                    temp->left->parent = temp->parent;
                    temp->parent->left = temp->left;
                }
                else {
                    temp->left->parent = temp->parent;
                    temp->parent->right = temp->left;
                }
            }
        }
        else if (temp == temp->parent->right) temp->parent->right = nullptr;
        else if (temp == temp->parent->left) temp->parent->left = nullptr;
        delete temp;
        temp = nullptr;
        LENGTH--;
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
    void delete_tree() {
        /*if (node == nullptr) return; //RECURSIVE METHOD

        delete_tree(node->left);
        delete_tree(node->right);
        if (node == ROOT) {
            LENGTH = 0;
            delete ROOT;
            ROOT = nullptr;
            return;
        }
        delete node;
        node = nullptr;
        return;*/
        if (ROOT == nullptr) return;
        auto temp = ROOT;
        Node* del;
        while (temp) {
            while (temp->left)
                temp = temp->left;
            if (temp->right)
                temp = temp->right;
            else if (temp == ROOT) break;
            else {
                del = temp;
                temp = temp->parent;
                if (del == temp->left) temp->left = nullptr;
                else temp->right = nullptr;
                delete del;
                del = nullptr;
            }
        }
        delete ROOT;
        ROOT = nullptr;
        LENGTH = 0;
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
        if (ROOT == NULL)
            return "Tree is empty";
        std::stack<Node*> nodeStack;
        nodeStack.push(ROOT);
        std::ostringstream stream;
        stream << "size: " << LENGTH
            << "\nheight: " << tree_height(ROOT)
            << "\n\nindex\tparent\tleft\tright\tdata\n";
        if (LENGTH > 10) {
            for (unsigned i = 0; i < 10; i++) {
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
            stream << prefix << (isLeft ? "|--" : "L--") << node->data << "\n";
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

    //binary_search_tree<some_class>* tree = new binary_search_tree<some_class>;
    //tree->append(some_class{ 10 }, comp_less);
    //tree->append(some_class{ 2 }, comp_less);
    //tree->append(some_class{ 32 }, comp_less);
    //tree->append(some_class{ 41 }, comp_less);
    //tree->append(some_class{ 13 }, comp_less);
    //tree->append(some_class{ 7 }, comp_less);
    //tree->append(some_class{ 5 }, comp_less);
    //tree->append(some_class{ 2 }, comp_less);
    //tree->append(some_class{ 32 }, comp_less);
    //tree->append(some_class{ 13 }, comp_less);
    //tree->append(some_class{ 41 }, comp_less);
    //for (int i = 0; i < 20; i++)
    //    tree->append(some_class{ i }, comp_less);

    //std::cout << tree->pre_order(tree->get_root()) << "\n";
    //std::cout << tree->in_order(tree->get_root()) << "\n";
    //std::cout << tree->tree_height(tree->get_root()) << "\n";
    //std::cout << "\n" << tree->print_graph("", tree->get_root(), false) << "\n";
    //tree->find_and_remove(tree->find_element(some_class{ 41 }, comp_less));
    //tree->find_and_remove(tree->find_element(some_class{ 16 }, comp_less));
    //std::cout << "\n" << tree->print_graph("", tree->get_root(), false) << "\n";
    //tree->find_and_remove(tree->find_element(some_class{ 10 }, comp_less));
    //std::cout << "\n" << tree->print_graph("", tree->get_root(), false) << "\n";
    //std::cout << tree->to_string() << "\n";

    //tree->delete_tree();
    //std::cout << tree->in_order(tree->get_root()) << "\n";
    //delete tree;

    const int MAX_ORDER = 7; // maksymalny rzad wielkosci dodawanych danych
    binary_search_tree<some_class>* bst = new binary_search_tree<some_class>; // stworzenie drzewa
    srand(time(NULL));
    int random;
    for (int o = 1; o <= MAX_ORDER; o++)
    {
        const int n = pow(10, o); // rozmiar danych
        // dodawanie do drzewa
        clock_t t1 = clock();
        for (int i = 0; i < n; i++)
        {
            random = rand() % 10001;
            some_class so = some_class{ random }; // losowe dane
            bst->append(so, comp_less); // dodanie ( drugi argument to wskaznik na komparator )
        }
        clock_t t2 = clock();
        double mstimediff = 1000 * (t2 - t1) / (double)CLOCKS_PER_SEC;
        std::cout << bst->to_string() 
            << "\nPomiar 1 (dodawanie), rzedu " << o 
            << "\nCzas calkowity: " << mstimediff
            << "ms\nCzas zamortyzowany: " << mstimediff / n << "ms\n\n";; // wypis na ekran aktualnej postaci drzewa ( skrotowej ) wraz z pomiarami czasowymi i w / w wielkosciami
        // wyszukiwanie
        const int m = pow(10, 4); // liczba prob wyszukiwania
        int hits = 0; // liczba trafien
        t1 = clock();
        for (int i = 0; i < m; i++)
        {
            random = rand() % 10001;
            some_class* so = new some_class{ random }; // losowe dane jako wzorzec do wyszukiwania ( obiekt chwilowy )
            if (bst->find_element(*so, comp_less) != NULL)
                hits++;
            delete so;
        }
        t2 = clock();
        mstimediff = 1000 * (t2 - t1) / (double)CLOCKS_PER_SEC;
        double log_result = log2(n);
        unsigned height = bst->tree_height(bst->get_root());
        std::cout << bst->to_string()
            << "\nPomiar 2 (wyszukiwanie), rzedu " << o
            << "\nCzas calkowity: " << mstimediff
            << "ms\nCzas zamortyzowany: " << mstimediff / n << "ms"
            << "\nTrafienia: " << hits << "\n\n"
            << "\nStosunek wysokosci drzewa do rozmiaru danych: " << height / n
            << "\nLogarytm z rozmiaru danych: " << log_result
            << "\nStosunek wysokosci drzewa do logarytmu z rozmiaru danych: " << height/log_result << "\n"; // wypis na ekran pomiarow czasowych i liczby trafien
            bst->delete_tree(); // czyszczenie drzewa wraz z uwalnianiem pamieci danych
    }
    delete bst;


    return 0;
}