/// Ahmad Nour Haidar

#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

class BinarySearchTree {
private:
    struct Node {
        int height;
        int value;
        Node *left;
        Node *right;

        // constructor for create node
        explicit Node(const int &value) {
            this->value = value;
            height = 1;
            left = nullptr;
            right = nullptr;
        };
    };

    Node *rootTree;

    bool is_inserted; // use for know if the value inserted or not
    bool is_deleted; // use for know if the value deleted or not

    static void _print_empty() {
        cout << "Sorry, your tree is empty ...!\n";
    }

    bool _empty() {
        return rootTree == nullptr;
    }

    /// functions to check if is BST

    int _min_value_in_subtree(Node *node) {
        if (node == nullptr) {
            return INT_MAX;
        }
        return _min(node->value, _min(_min_value_in_subtree(node->left), _min_value_in_subtree(node->right)));
    }

    int _max_value_in_subtree(Node *node) {
        if (node == nullptr) {
            return INT_MIN;
        }
        return _max(node->value, _max(_max_value_in_subtree(node->left), _max_value_in_subtree(node->right)));
    }

    bool _is_binary_search_tree_recursive(Node *root) {
        if (root == nullptr) {
            return true;
        }
        if (root->left and _max_value_in_subtree(root->left) > root->value) {
            return false;
        }
        if (root->right and _min_value_in_subtree(root->right) < root->value) {
            return false;
        }
        return !(!_is_binary_search_tree_recursive(root->left) or !_is_binary_search_tree_recursive(root->right));
    }

    /// function to insert
    void _insert_iterative(const int &value) {
        Node *newNode = new Node(value);
        if (rootTree == nullptr) {
            rootTree = newNode;
            return;
        }
        Node *current = rootTree;
        Node *parent = rootTree;
        while (current) {
            if (current->value == value) {
                // duplicates not allowed
                is_inserted = false;
                return;
            }
            parent = current;
            if (value < current->value) {
                current = current->left;
            } else if (value > current->value) {
                current = current->right;
            }
        }
        if (value < parent->value) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }

    /// function to search
    Node *_search_iterative(const int &value, int &level_node) {
        Node *current = rootTree;
        while (current) {
            if (current->value == value) {
                return current;
            }
            level_node++;
            if (value < current->value) {
                current = current->left;
            } else if (value > current->value) {
                current = current->right;
            }
        }
        // value not found
        return nullptr;
    }

    /// functions min and height
    int _max_value_in_tree_iterative() {
        Node *current = rootTree;
        while (current->right) {
            current = current->right;
        }
        return current->value;
    }

    int _min_value_in_tree_iterative() {
        Node *current = rootTree;
        while (current->left) {
            current = current->left;
        }
        return current->value;
    }

    /// function to delete
    void _delete_value_iterative(const int &value) {
        Node *parent = nullptr;
        Node *current = rootTree;
        // search for node to delete it
        while (current) {
            if (current->value == value) {
                break;
            }
            parent = current;
            if (value < current->value) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if (current == nullptr) {
            // value not found
            is_deleted = false;
            return;
        }
            // node with only one child or no child
        else if (current->left == nullptr or current->right == nullptr) {
            Node *successor = current->left ? current->left : current->right;
            if (successor == nullptr) {
                // node is leaf, no children
                delete successor;
                if (current == rootTree) {
                    delete rootTree;
                    rootTree = nullptr;
                } else if (current == parent->left) {
                    delete parent->left;
                    parent->left = nullptr;
                } else {
                    delete parent->right;
                    parent->right = nullptr;
                }
            } else {
                // node has one child
                *current = *successor; // copy content successor to current
            }
        }
            // node has two children
        else {
            parent = nullptr;
            // get successor from left subtree
            Node *successor = current->left;
            while (successor->right) {
                parent = successor;
                successor = successor->right;
            }
            current->value = successor->value;
            if (parent) {
                parent->right = successor->left;
            } else {
                current->left = successor->left;
            }
            delete successor;
        }
    }

    /// functions for avl

    static int _height(Node *node) {
        if (node) { // --> node != null
            return node->height;
        }
        return 0;
    };

    static int _max(const int &a, const int &b) {
        return (a > b) ? a : b;
    }

    static int _min(const int &a, const int &b) {
        return (a < b) ? a : b;
    }

    static int _get_balance(Node *node) {
        if (node) {
            return _height(node->left) - _height(node->right);
        }
        return 0;
    }

    static Node *_right_rotate(Node *node) {
        Node *left_node = node->left;
        Node *right_of_left_node = left_node->right;

        left_node->right = node;
        node->left = right_of_left_node;

        node->height = _max(_height(node->left), _height(node->right)) + 1;
        left_node->height = _max(_height(left_node->left), _height(left_node->right)) + 1;

        return left_node;
    }

    static Node *_left_rotate(Node *node) {
        Node *right_node = node->right;
        Node *left_of_right_node = right_node->left;

        right_node->left = node;
        node->right = left_of_right_node;

        node->height = _max(_height(node->left), _height(node->right)) + 1;
        right_node->height = _max(_height(right_node->left), _height(right_node->right)) + 1;

        return right_node;
    }

    Node *_insert_using_avl_function_recursive(Node *node, const int &value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->value) {
            node->left = _insert_using_avl_function_recursive(node->left, value);
        } else if (value > node->value) {
            node->right = _insert_using_avl_function_recursive(node->right, value);
        } else {
            // duplicates are not allowed
            is_inserted = false;
            return node;
        }
        node->height = 1 + _max(_height(node->left), _height(node->right));
        int balance = _get_balance(node);

        // there are 4 cases

        // left left case
        if (balance > 1 and value < node->left->value) {
            return _right_rotate(node);
        }

        // right right case
        if (balance < -1 and value > node->right->value) {
            return _left_rotate(node);
        }

        // left right case
        if (balance > 1 and value > node->left->value) {
            node->left = _left_rotate(node->left);
            return _right_rotate(node);
        }

        // right left case
        if (balance < -1 and value < node->right->value) {
            node->right = _right_rotate(node->right);
            return _left_rotate(node);
        }

        return node;
    }

    void _convert_to_avl(Node *root, Node *&new_root) {
        if (root == nullptr) {
            return;
        }
        // in order traversal, you can use post or pre traversal
        _convert_to_avl(root->left, new_root);
        new_root = _insert_using_avl_function_recursive(new_root, root->value);
        _convert_to_avl(root->right, new_root);
    }

    /// functions for print hierarchically

    static const int SPACE = 3;

    // Time Complexity: O(log n)
    //  x^n
    static int _power(int x, int n) {
        int result = 1;
        while (n) {
            if (n & 1) {
                result = result * x;
            }
            x = x * x;
            n >>= 1;
        }
        return result;
    }

    static void _print_space(int &n) {
        for (int i = 0; i < n; ++i) {
            cout << ' ';
        }
    }

    int _count_levels_of_tree_recursive(Node *node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + _max(_count_levels_of_tree_recursive(node->left), _count_levels_of_tree_recursive(node->right));
    }

    void _print_hierarchically() {
        int w = 3;
        int count_level = _count_levels_of_tree_recursive(rootTree);
        int i = 0;
        queue<Node *> q;
        q.emplace(rootTree);
        while (!q.empty()) {
            if (i == count_level) {
                break;
            }
            cout << "l" << setw(2) << i << '.';
            int len = q.size();
            int first = _power(2, count_level - i - 1) - 1;
            first *= SPACE;
            _print_space(first);
            int between = _power(2, count_level - i);
            between *= SPACE;
            between -= w;
            i++;
            while (len--) {
                Node *current = q.front();
                q.pop();
                if (current) {
                    cout << setw(w) << current->value;
                } else {
                    // N : Null
                    cout << setw(w) << "N";
                }
                if (current and current->left) {
                    q.emplace(current->left);
                } else if (i < count_level) {
                    q.emplace(nullptr);
                }
                if (current and current->right) {
                    q.emplace(current->right);
                } else if (i < count_level) {
                    q.emplace(nullptr);
                }
                if (len > 0) {
                    // don't print after last value in the level
                    _print_space(between);
                }
            }
            cout << endl;
        }
    }

    /// functions for traversals algorithm

    void _pre_order_recursive(Node *root) {
        if (root == nullptr) {
            return;
        }
        cout << root->value << ' ';
        _pre_order_recursive(root->left);
        _pre_order_recursive(root->right);
    }

    void _in_order_recursive(Node *root) {
        if (root == nullptr) {
            return;
        }
        _in_order_recursive(root->left);
        cout << root->value << ' ';
        _in_order_recursive(root->right);
    }

    void _post_order_recursive(Node *root) {
        if (root == nullptr) {
            return;
        }
        _post_order_recursive(root->left);
        _post_order_recursive(root->right);
        cout << root->value << ' ';
    }

    /// function to clear tree
    void _clear_tree_recursive(Node *&root) {
        if (root) {
            _clear_tree_recursive(root->left);
            _clear_tree_recursive(root->right);
            delete root;
            root = nullptr;
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
public:
    // constructor
    BinarySearchTree() {
        rootTree = nullptr;
        is_inserted = true;
        is_deleted = true;
    }

    // Destructor, it is call in the end of program
    ~BinarySearchTree() {
        _clear_tree_recursive(rootTree);
    }

    void is_binary_search_tree_recursive() {
        if (_empty()) {
            cout << "Your tree is empty and can be considered Binary Search Tree ...!\n";
            return;
        }
        bool ans = _is_binary_search_tree_recursive(rootTree);
        cout << "Is BST: " << (ans ? "True" : "False") << '\n';
    }

    void insert_iterative(const int &value) {
        is_inserted = true;
        _insert_iterative(value);
        if (is_inserted) {
            cout << '<' << value << "> Inserted successfully.\n";
        } else {
            cout << '<' << value << "> Already in your tree, duplicates are not allowed.\n";
        }
    }

    void search_iterative(const int &value) {
        if (_empty()) {
            _print_empty();
            return;
        }
        int level_node = 0;
        Node *result = _search_iterative(value, level_node);
        if (result) {
            cout << '<' << value << "> Is found in your tree at level: " << level_node << ".\n";
        } else {
            cout << '<' << value << "> Is not found in your tree.\n";
        }

    }

    void max_value_in_tree_iterative() {
        if (_empty()) {
            _print_empty();
            return;
        }
        cout << "Max value in your tree: " << _max_value_in_tree_iterative() << '\n';
    }

    void min_value_in_tree_iterative() {
        if (_empty()) {
            _print_empty();
            return;
        }
        cout << "Min value in your tree: " << _min_value_in_tree_iterative() << '\n';
    }

    void delete_value_iterative(const int &value) {
        if (_empty()) {
            _print_empty();
            return;
        }
        is_deleted = true;
        _delete_value_iterative(value);
        if (is_deleted) {
            cout << '<' << value << "> Deleted successfully.\n";
        } else {
            cout << '<' << value << "> Is not found in your tree ...!\n";
        }
    }

    void print_hierarchically() {
        if (_empty()) {
            _print_empty();
            return;
        }
        cout << "Your tree as Hierarchically is:\n";
        _print_hierarchically();
    }

    void insert_using_avl_function(const int &value, bool print_statement) {
        is_inserted = true;
        rootTree = _insert_using_avl_function_recursive(rootTree, value);
        if (print_statement) {
            if (is_inserted) {
                cout << "Inserted successfully.\n";
            } else {
                cout << '<' << value << "> Already in your tree, duplicates are not allowed.\n";
            }
        }
    }

    void convert_to_avl() {
        if (_empty()) {
            _print_empty();
            return;
        }
        Node *new_root = nullptr;
        _convert_to_avl(rootTree, new_root);
        _clear_tree_recursive(rootTree);
        rootTree = new_root;
        cout << "Converted successfully.\n";
    }

    void pre_order() {
        if (_empty()) {
            _print_empty();
            return;
        }
        cout << "Pre Order traversal is:\n";
        _pre_order_recursive(rootTree);
        cout << endl;
    }

    void in_order() {
        if (_empty()) {
            _print_empty();
            return;
        }
        cout << "In Order traversal is:\n";
        _in_order_recursive(rootTree);
        cout << "\nNotice that the values appear in ascending order by (In Order Traversal).\n";
    }

    void post_order() {
        if (_empty()) {
            _print_empty();
            return;
        }
        cout << "Post Order traversal is:\n";
        _post_order_recursive(rootTree);
        cout << endl;
    }

}; // end class ..

void print_line() {
    for (int i = 1; i <= 100; ++i) {
        cout << '*';
    }
    cout << endl;
}

int main() {

    BinarySearchTree bst;
    int a[] = {9, 2, 4, 7, 11, 8, 3, 10, 5};

    for (int &i : a) {
        bst.insert_iterative(i);
    }

    print_line();
    bst.delete_value_iterative(7);

    print_line();
    bst.min_value_in_tree_iterative();

    print_line();
    bst.print_hierarchically();

    print_line();
    bst.convert_to_avl();

    print_line();
    bst.print_hierarchically();

    print_line();
    bst.pre_order();

    print_line();
    bst.in_order();

    print_line();
    bst.post_order();

    return 0;
}