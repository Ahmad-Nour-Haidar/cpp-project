

///  Ahmad Nour Haidar

#include <iostream>
#include <queue>
#include <iomanip>

#define myType int
#define endl '\n'

using namespace std;

class BinarySearchTree {
private:
    struct Node {
        myType value;
        int height;
        Node *left;
        Node *right;

        explicit Node(const myType &value) {
            this->value = value;
            height = 1;
            left = nullptr;
            right = nullptr;
        }
    };

    Node *rootTree;
    bool is_inserted; // use for know if the value inserted or not
    bool is_deleted;  // use for know if the value deleted or not
    int count_nodes;

    /// functions for insert in bst
    void _insert_iterative(const myType &value) {
        Node *newNode = new Node(value);
        if (rootTree == nullptr) {
            rootTree = newNode;
            is_inserted = true;
            return;
        }
        Node *current = rootTree;
        Node *parent = nullptr;
        while (current) {
            parent = current;
            if (value == current->value) {
                // duplicate not allowed
                is_inserted = false;
                return;
            }
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
        is_inserted = true;
    }

    Node *_insert_recursive(Node *root, const myType &value) {
        if (root == nullptr) {
            is_inserted = true;
            return new Node(value);
        }
        if (root->value == value) {
            is_inserted = false;
            return root;
        }
        if (value < root->value) {
            root->left = _insert_recursive(root->left, value);
            return root;
        } else {
            root->right = _insert_recursive(root->right, value);
            return root;
        }
    }

    void _insert_random_iterative(const myType &value) {
        if (rootTree == nullptr) {
            rootTree = new Node(value);
            return;
        }
        queue<Node *> q;
        q.push(rootTree);
        while (!q.empty()) {
            Node *current = q.front();
            q.pop();
            if (!current->left) {
                current->left = new Node(value);
                return;
            } else {
                q.push(current->left);
            }
            if (!current->right) {
                current->right = new Node(value);
                return;
            } else {
                q.push(current->right);
            }
        }
    }

    /// functions for AVL: insert and delete

    static int _height(Node *node) {
        if (node) { // --> node != null
            return node->height;
        }
        return 0;
    };

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

    Node *_insert_using_avl_function_recursive(Node *root, const myType &value) {
        if (root == nullptr) {
            return new Node(value);
        }
        if (value < root->value) {
            root->left = _insert_using_avl_function_recursive(root->left, value);
        } else if (value > root->value) {
            root->right = _insert_using_avl_function_recursive(root->right, value);
        } else {
            // duplicates are not allowed
            is_inserted = false;
            return root;
        }
        root->height = 1 + _max(_height(root->left), _height(root->right));
        int balance = _get_balance(root);

        // there are 4 cases

        // left case
        if (balance > 1 and value < root->left->value) {
            return _right_rotate(root);
        }

        // right case
        if (balance < -1 and value > root->right->value) {
            return _left_rotate(root);
        }

        // left right case
        if (balance > 1 and value > root->left->value) {
            root->left = _left_rotate(root->left);
            return _right_rotate(root);
        }

        // right left case
        if (balance < -1 and value < root->right->value) {
            root->right = _right_rotate(root->right);
            return _left_rotate(root);
        }

        return root;
    }

    Node *_delete_value_and_get_successor_from_right_subtree_recursive(Node *root, const myType &value) {
        if (root == nullptr) {
            // value not found
            is_deleted = false;
            return root;
        }
        if (value < root->value) {
            root->left = _delete_value_and_get_successor_from_right_subtree_recursive(root->left, value);
        } else if (value > root->value) {
            root->right = _delete_value_and_get_successor_from_right_subtree_recursive(root->right, value);
        } else {
            // node with only one child or no child
            if (root->left == nullptr or root->right == nullptr) {
                Node *successor = root->left ? root->left : root->right;
                if (successor == nullptr) {
                    // root is leaf
                    delete root;
                    delete successor;
                    root = nullptr;
                } else {
                    // root has one child
                    *root = *successor; // copy content temp to root
                }
            } else {
                // node with tow children
                Node *successor = _min_value_in_right_sub_tree(root->right);
                root->value = successor->value;
                root->right = _delete_value_and_get_successor_from_right_subtree_recursive(root->right, root->value);
            }
        }
        // If the tree had only one node
        if (root == nullptr) {
            return root;
        }

        root->height = 1 + _max(_height(root->left), _height(root->right));
        int balance = _get_balance(root);

        // there are 4 cases

        // left left case
        if (balance > 1 and _get_balance(root->left) >= 0) {
            return _right_rotate(root);
        }

        // left right case
        if (balance > 1 and _get_balance(root->left) < 0) {
            root->left = _left_rotate(root->left);
            return _right_rotate(root);
        }

        // right right case
        if (balance < -1 and _get_balance(root->right) <= 0) {
            return _left_rotate(root);
        }

        // right left case
        if (balance < -1 and _get_balance(root->right) > 0) {
            root->right = _right_rotate(root->right);
            return _left_rotate(root);
        }

        return root;
    }

    Node *_delete_value_and_get_successor_from_left_subtree_recursive(Node *root, const myType &value) {
        if (root == nullptr) {
            // value not found
            is_deleted = false;
            return root;
        }
        if (value < root->value) {
            root->left = _delete_value_and_get_successor_from_left_subtree_recursive(root->left, value);
        } else if (value > root->value) {
            root->right = _delete_value_and_get_successor_from_left_subtree_recursive(root->right, value);
        } else {
            // node with only one child or no child
            if (root->left == nullptr or root->right == nullptr) {
                Node *successor = root->left ? root->left : root->right;
                if (successor == nullptr) {
                    // root is leaf
                    delete root;
                    delete successor;
                    root = nullptr;
                } else {
                    // root has one child
                    *root = *successor;
                }
            } else {
                // node with tow children
                Node *successor = _max_value_in_left_sub_tree(root->left);
                root->value = successor->value;
                root->left = _delete_value_and_get_successor_from_left_subtree_recursive(root->left, root->value);
            }
        }
        // If the tree had only one node
        if (root == nullptr) {
            return root;
        }

        root->height = 1 + _max(_height(root->left), _height(root->right));
        int balance = _get_balance(root);

        // there are 4 cases

        // left left case
        if (balance > 1 and _get_balance(root->left) >= 0) {
            return _right_rotate(root);
        }

        // left right case
        if (balance > 1 and _get_balance(root->left) < 0) {
            root->left = _left_rotate(root->left);
            return _right_rotate(root);
        }

        // right right case
        if (balance < -1 and _get_balance(root->right) <= 0) {
            return _left_rotate(root);
        }

        // right left case
        if (balance < -1 and _get_balance(root->right) > 0) {
            root->right = _right_rotate(root->right);
            return _left_rotate(root);
        }

        return root;
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

    /// helper functions for deletion

    static Node *_max_value_in_left_sub_tree(Node *node) {
        Node *current = node;
        while (current->right) {
            current = current->right;
        }
        return current;
    }

    static Node *_min_value_in_right_sub_tree(Node *node) {
        Node *current = node;
        while (current->left) {
            current = current->left;
        }
        return current;
    }

    /// functions for delete iterative

    void _delete_value_iterative(const myType &value) {
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
        if (current->left == nullptr or current->right == nullptr) {
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
                delete successor;
            }
        } else {
            // If the node to be deleted has two children
            _delete_and_get_node_from_right_sub_tree(current);
//            _delete_and_get_node_from_left_sub_tree(current);
        }
        is_deleted = true;
    }

    static void _delete_and_get_node_from_right_sub_tree(Node *current) {
        // find successor from right sub tree
        Node *parent = nullptr;
        Node *successor = current->right;
        while (successor->left) {
            parent = successor;
            successor = successor->left;
        }
        current->value = successor->value;
        if (parent) {
            // maybe successor->right: nullptr or it has child from right
            parent->left = successor->right;
        } else {
            current->right = successor->right;
        }
        delete successor;
    }

    static void _delete_and_get_node_from_left_sub_tree(Node *current) {
        // find successor from left sub tree
        cout << current->value << endl;
        Node *parent = nullptr;
        Node *successor = current->left;
        while (successor->right) {
            parent = successor;
            successor = successor->right;
        }
        current->value = successor->value;
        if (parent) {
            // maybe successor->left: nullptr or it has child from left
            parent->right = successor->left;
        } else {
            current->left = successor->left;
        }
        delete successor;
    }

    /// functions for delete recursive

    Node *_delete_value_recursive(Node *root, const myType &value) {
        if (root == nullptr) {
            // value not found
            is_deleted = false;
            return root;
        } else if (value < root->value) {
            root->left = _delete_value_recursive(root->left, value);
            return root;
        } else if (value > root->value) {
            root->right = _delete_value_recursive(root->right, value);
            return root;
        } else {
            if (root->left == nullptr) {
                is_deleted = true;
                return root->right;
            } else if (root->right == nullptr) {
                is_deleted = true;
                return root->left;
            } else {
                is_deleted = true;
//                Edge *temp = _max_value_in_left_sub_tree(root->left);
//                root->value = temp->value;
//                root->left = _delete_value_recursive(root->left, temp->value);
//                return root;
//                =====================================================//
                Node *temp = _min_value_in_right_sub_tree(root->right);
                root->value = temp->value;
                root->right = _delete_value_recursive(root->right, temp->value);
                return root;
            }
        }
    }

    /// functions for search

    Node *_search_iterative(const myType &value, int &level_node) {
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
        return nullptr;
    }

    Node *_search_recursive(Node *root, const myType &value, int &level_node) {
        if (root == nullptr) {
            // value not found
            return nullptr;
        } else if (root->value == value) {
            return root;
        } else if (value < root->value) {
            level_node++;
            return _search_recursive(root->left, value, level_node);
        } else {
            level_node++;
            return _search_recursive(root->right, value, level_node);
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

    /// functions for tree attributes

    bool _is_linear_from_left_iterative() {
        Node *current = rootTree;
        if (current->left and current->right) {
            return false;
        }
        if (current->left and !current->right) {
            while (current->left) {
                current = current->left;
                if (current->right) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    bool _is_linear_from_right_iterative() {
        Node *current = rootTree;
        if (current->left and current->right) {
            return false;
        }
        if (!current->left and current->right) {
            while (current->right) {
                current = current->right;
                if (current->left) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    bool _is_complete_iterative() {
        queue<Node *> q;
        q.emplace(rootTree);
        bool check_to_pointer_is_null = false;
        while (!q.empty()) {
            Node *current = q.front();
            q.pop();
            if (check_to_pointer_is_null and current) {
                return false;
            }
            if (current) {
                q.emplace(current->left);
                q.emplace(current->right);
            }
            if (!current) {
                check_to_pointer_is_null = true;
            }
        }
        return true;
    }

    bool _is_complete_recursive(Node *root, int index, int &number_nodes) {
        if (root == nullptr) {
            return true;
        }
        if (index >= number_nodes) {
            return false;
        }
        return (_is_complete_recursive(root->left, 2 * index + 1, number_nodes) and
                _is_complete_recursive(root->right, 2 * index + 2, number_nodes));
    }

    bool _is_full_iterative() {
        queue<Node *> q;
        q.emplace(rootTree);
        while (!q.empty()) {
            Node *current = q.front();
            q.pop();
            if (!current->left and current->right) {
                return false;
            }
            if (current->left and !current->right) {
                return false;
            }
            if (current->left) {
                q.emplace(current->left);
            }
            if (current->right) {
                q.emplace(current->right);
            }
        }
        return true;
    }

    bool _is_full_recursive(Node *root) {
        if (root == nullptr) {
            return true;
        }
        if (root->left and !root->right) {
            return false;
        }
        if (!root->left and root->right) {
            return false;
        }
        return _is_full_recursive(root->left) and _is_full_recursive(root->right);
    }

    bool _is_perfect() {
        int count_level = _count_levels_from_node_to_bottom_recursive(rootTree);
        int original_count_nodes = _power(2, count_level) - 1;
        return count_nodes == original_count_nodes;
    }

    /// functions to check if is BST

    myType _min_value_in_subtree(Node *node) {
        if (node == nullptr) {
            return INT_MAX;
        }
        return _min(node->value, _min(_min_value_in_subtree(node->left), _min_value_in_subtree(node->right)));
    }

    myType _max_value_in_subtree(Node *node) {
        if (node == nullptr) {
            return INT_MIN;
        }
        return _max(node->value, _max(_max_value_in_subtree(node->left), _max_value_in_subtree(node->right)));
    }

    bool _is_binary_search_tree_iterative() {
        queue<Node *> q;
        q.emplace(rootTree);
        while (!q.empty()) {
            Node *current = q.front();
            q.pop();
            if (current->left and _max_value_in_subtree(current->left) > current->value) {
                return false;
            }
            if (current->right and _min_value_in_subtree(current->right) < current->value) {
                return false;
            }
            if (current->left) {
                q.emplace(current->left);
            }
            if (current->right) {
                q.emplace(current->right);
            }
        }
        return true;
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
        if (!_is_binary_search_tree_recursive(root->left) or !_is_binary_search_tree_recursive(root->right)) {
            return false;
        }
        return true;
    }

    /// functions for informations about tree

    int _get_depth_or_level_of_node_iterative(const myType &value) {
        int depth = 0;
        Node *current = rootTree;
        while (current) {
            if (current->value == value) {
                return depth;
            }
            depth++;
            if (value < current->value) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return -1;
    }

    static int _get_tree_degree_iterative(Node *root) {
        queue<Node *> q;
        q.emplace(root);
        int max_degree = 0;
        int current_degree;
        while (!q.empty()) {
            current_degree = 0;
            Node *node = q.front();
            q.pop();
            if (node->left) {
                q.emplace(node->left);
                current_degree++;
            }
            if (node->right) {
                q.emplace(node->right);
                current_degree++;
            }
            max_degree = max(max_degree, current_degree);
            if (max_degree == 2) {
                break;
            }
        }
        return max_degree;
    }

    int _get_tree_width_iterative() {
        int width = 0;
        queue<Node *> q;
        q.emplace(rootTree);
        while (!q.empty()) {
            int size = q.size();
            width = max(width, size);
            while (size--) {
                Node *current = q.front();
                q.pop();
                if (current->left) {
                    q.emplace(current->left);
                }
                if (current->right) {
                    q.emplace(current->right);
                }
            }
        }
        return width;
    }

    int _count_levels_from_node_to_bottom_recursive(Node *root) {
        if (root == nullptr) {
            return 0;
        }
        return 1 + _max(_count_levels_from_node_to_bottom_recursive(root->left),
                        _count_levels_from_node_to_bottom_recursive(root->right));
    }

    /// functions min and height values

    myType _min_value_in_tree_iterative() {
        Node *current = rootTree;
        while (current->left) {
            current = current->left;
        }
        return current->value;
    }

    myType _max_value_in_tree_iterative() {
        Node *current = rootTree;
        while (current->right) {
            current = current->right;
        }
        return current->value;
    }

    /// other functions

    bool _empty() {
        return rootTree == nullptr;
    }

    void _clear_tree_recursive(Node *&root) {
        if (root) {
            _clear_tree_recursive(root->left);
            _clear_tree_recursive(root->right);
            delete root;
            root = nullptr;
        }
    }

    static void _print_empty() {
        cout << "Sorry, your tree is empty ...!\n";
    }

    // Time Complexity: O(log n)
    // Auxiliary Space: O(1)
    static int _power(int x, unsigned n) {
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

    static myType _max(const myType &a, const myType &b) {
        return (a > b) ? a : b;
    }

    static myType _min(const myType &a, const myType &b) {
        return (a < b) ? a : b;
    }

    /// functions for print tree

    static void _print_level_by_level_iterative(Node *root) {
        queue<Node *> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                Node *node = q.front();
                q.pop();
                cout << node->value << ' ';
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            cout << endl;
        }
    }

    static const int SPACE = 3;

    static void _print_space(int &n) {
        for (int i = 0; i < n; ++i) {
            cout << ' ';
        }
    }

    void _print_hierarchically_iterative() {
        int w = 3;
        int count_level = _count_levels_from_node_to_bottom_recursive(rootTree);
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:

    // Constructor
    BinarySearchTree() {
        rootTree = nullptr;
        count_nodes = 0;
        is_deleted = true;
        is_inserted = true;
    }

    // Destructor, it is call in the end of program
    ~BinarySearchTree() {
        _clear_tree_recursive(rootTree);
    }

    void insert_iterative(const myType &value) {
        _insert_iterative(value);
        if (is_inserted) {
            count_nodes++;
            cout << '<' << value << "> Inserted successfully.\n";
        } else {
            cout << '<' << value << "> already in your tree, duplicates are not allowed.\n";
        }
    }

    void insert_recursive(const myType &value) {
        rootTree = _insert_recursive(rootTree, value);
        if (is_inserted) {
            count_nodes++;
            cout << '<' << value << "> Inserted successfully.\n";
        } else {
            cout << '<' << value << "> already in your tree, duplicates are not allowed.\n";
        }
    }

    void insert_random_iterative(const myType &value) {
        // this function insert from left to right
        int level_node = 0;// not use
        Node *is_there = _search_iterative(value, level_node);
        if (is_there) {
            cout << '<' << value << "> already in your tree, duplicates are not allowed.\n";
            return;
        }
        _insert_random_iterative(value);
        count_nodes++;
        cout << '<' << value << "> Inserted successfully.\n";
    }

    void insert_value_using_avl_function(const myType &value) {
        rootTree = _insert_using_avl_function_recursive(rootTree, value);
        if (is_inserted) {
            count_nodes++;
            cout << '<' << value << "> Inserted successfully.\n";
        } else {
            cout << '<' << value << "> already in your tree, duplicates are not allowed.\n";
        }
    }

    void delete_value_iterative(const myType &value) {
        if (_empty()) {
            _print_empty();
            return;
        }
        _delete_value_iterative(value);
        if (is_deleted) {
            count_nodes--;
            cout << '<' << value << "> Deleted successfully.\n";
        } else {
            cout << '<' << value << "> is not found in your tree ...!\n";
        }
    }

    void delete_value_recursive(const myType &value) {
        if (_empty()) {
            _print_empty();
            return;
        }
        rootTree = _delete_value_recursive(rootTree, value);
        if (is_deleted) {
            count_nodes--;
            cout << '<' << value << "> Deleted successfully.\n";
        } else {
            cout << '<' << value << "> is not found in your tree ...!\n";
        }
    }

    void delete_value_using_avl_function_recursive(const myType &value) {
        if (_empty()) {
            _print_empty();
            return;
        }
        rootTree = _delete_value_and_get_successor_from_right_subtree_recursive(rootTree, value);
        if (is_deleted) {
            count_nodes--;
            cout << '<' << value << "> Deleted successfully.\n";
        } else {
            cout << '<' << value << "> is not found in your tree ...!\n";
        }
    }

    void search_iterative(const myType &value) {
        if (_empty()) {
            _print_empty();
            return;
        }
        int level_node = 0;
        bool is_found = _search_iterative(value, level_node);
        if (is_found) {
            cout << '<' << value << "> Is found in your tree at level: " << level_node << ".\n";
        } else {
            cout << '<' << value << "> is not found in your tree.\n";
        }
    }

    void search_recursive(const myType &value) {
        if (_empty()) {
            _print_empty();
            return;
        }
        int level_node = 0;
        bool is_found = _search_recursive(rootTree, value, level_node);
        if (is_found) {
            cout << '<' << value << "> Is found in your tree at level: " << level_node << ".\n";
        } else {
            cout << '<' << value << "> is not found in your tree.\n";
        }
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

    void is_linear_iterative() {
        if (_empty()) {
            cout << "Your tree is empty and can be considered Linear.\n";
            return;
        }
        bool ans = _is_linear_from_left_iterative();
        if (ans) {
            cout << "Your tree is linear and go to the left.\n";
            return;
        }
        ans = _is_linear_from_right_iterative();
        if (ans) {
            cout << "Your tree is linear and go to the right.\n";
        } else {
            cout << "Your tree is not linear ...!\n";
        }
    }

    void is_complete_iterative() {
        if (_empty()) {
            cout << "Your tree is empty and can be considered Complete.\n";
            return;
        }
        bool ans = _is_complete_iterative();
        cout << "Is Complete: " << (ans ? "True" : "False") << '\n';
    }

    void is_complete_recursive() {
        if (_empty()) {
            cout << "Your tree is empty and can be considered Complete.\n";
            return;
        }
        bool ans = _is_complete_recursive(rootTree, 0, count_nodes);
        cout << "Is Complete: " << (ans ? "True" : "False") << '\n';
    }

    void is_full_iterative() {
        if (_empty()) {
            cout << "Your tree is empty and can be considered Full.\n";
            return;
        }
        bool ans = _is_full_iterative();
        cout << "Is Full: " << (ans ? "True" : "False") << '\n';
    }

    void is_full_recursive() {
        if (_empty()) {
            cout << "Your tree is empty and can be considered Full.\n";
            return;
        }
        bool ans = _is_full_recursive(rootTree);
        cout << "Is Full: " << (ans ? "True" : "False") << '\n';
    }

    void is_perfect() {
        if (_empty()) {
            cout << "Your tree is empty and can be considered Perfect.\n";
            return;
        }
        bool ans = _is_perfect();
        cout << "Is perfect: " << (ans ? "True" : "False") << '\n';
    }

    void is_binary_search_tree_iterative() {
        if (_empty()) {
            cout << "Your tree is empty and can be considered Binary Search Tree ...!\n";
            return;
        }
        bool ans = _is_binary_search_tree_iterative();
        cout << "Is BST: " << (ans ? "True" : "False") << '\n';
    }

    void is_binary_search_tree_recursive() {
        if (_empty()) {
            cout << "Your tree is empty and can be considered Binary Search Tree ...!\n";
            return;
        }
        bool ans = _is_binary_search_tree_recursive(rootTree);
        cout << "Is BST: " << (ans ? "True" : "False") << '\n';
    }

    void get_depth_or_level_of_node_iterative(const myType &value) {
        if (_empty()) {
            _print_empty();
            return;
        }
        int depth = _get_depth_or_level_of_node_iterative(value);
        if (depth == -1) {
            cout << '<' << value << "> is not found in your tree.\n";
        } else {
            cout << "Depth of node <" << value << "> is: " << depth << '\n';
        }
    }

    void get_height_of_node_recursive(const myType &value) {
        if (_empty()) {
            _print_empty();
            return;
        }
        int level_node = 0;// not use
        Node *node = _search_iterative(value, level_node);
        if (node == nullptr) {
            cout << '<' << value << "> is not found in your tree.\n";
        }
        int ans = _count_levels_from_node_to_bottom_recursive(node);
//        ans -= 1;
        cout << "Height of node <" << value << "> is: " << ans << '\n';
    }

    void get_tree_degree_iterative() {
        if (_empty()) {
            cout << "Your tree is empty and can be considered degree is: 0.\n";
            return;
        }
        cout << "Tree degree is: " << _get_tree_degree_iterative(rootTree) << '\n';
    }

    void get_tree_width_iterative() {
        if (_empty()) {
            cout << "Your tree is empty and can be considered width is 0.\n";
            return;
        }
        cout << "Tree width is: " << _get_tree_width_iterative() << '\n';
    }

    void count_levels_recursive() {
        if (_empty()) {
            _print_empty();
            return;
        }
        cout << "Count levels of tree is: " << _count_levels_from_node_to_bottom_recursive(rootTree) << '\n';
    }

    void min_value_in_tree_iterative() {
        if (_empty()) {
            _print_empty();
            return;
        }
        cout << "Min value in your tree: " << _min_value_in_tree_iterative() << '\n';
    }

    void max_value_in_tree_iterative() {
        if (_empty()) {
            _print_empty();
            return;
        }
        cout << "Max value in your tree: " << _max_value_in_tree_iterative() << '\n';
    }

    void print_level_by_level_iterative() {
        if (_empty()) {
            _print_empty();
            return;
        }
        cout << "Your tree level by level is:\n";
        _print_level_by_level_iterative(rootTree);
    }

    void print_hierarchically_iterative() {
        if (_empty()) {
            _print_empty();
            return;
        }
        cout << "Your tree as Hierarchically is:\n";
        _print_hierarchically_iterative();
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

    void size_tree() const {
        cout << "Size tree is: " << count_nodes << '\n';
    }

    bool empty() {
        if (_empty()) {
            cout << "Your tree is empty.\n";
        } else {
            cout << "Your tree is not empty ...!\n";
        }
        return _empty();
    }

    void clear_tree_recursive() {
        _clear_tree_recursive(rootTree);
        cout << "Cleared successfully ...!\n";
    }

};

void print_line() {
    for (int i = 0; i < 90; ++i) {
        cout << '=';
    }
    cout << endl;
}

void print_operations() {
    cout << "1  - insert using iterative function\n";
    cout << "2  - insert using recursive function\n";
    cout << "3  - insert randomly using iterative function\n";
    cout << "4  - insert using AVL function recursive\n";
    cout << "5  - delete using iterative function\n";
    cout << "6  - delete using recursive function\n";
    cout << "7  - delete using AVL function recursive\n";
    cout << "8  - search using iterative function\n";
    cout << "9  - search using recursive function\n";
    cout << "10 - pre order traversal\n";
    cout << "11 - in order traversal\n";
    cout << "12 - post order traversal\n";
    cout << "13 - is linear using iterative function\n";
    cout << "14 - is complete using iterative function\n";
    cout << "15 - is complete using recursive function\n";
    cout << "16 - is full using iterative function\n";
    cout << "17 - is full using recursive function\n";
    cout << "18 - is perfect\n";
    cout << "19 - is binary search tree iterative\n";
    cout << "20 - is binary search tree recursive\n";
    cout << "21 - get depth or level of node using iterative function\n";
    cout << "22 - get height of node using recursive function\n";
    cout << "23 - get tree degree using iterative function\n";
    cout << "24 - get tree width using iterative function\n";
    cout << "25 - count levels using recursive function\n";
    cout << "26 - min value in tree using iterative function\n";
    cout << "27 - height value in tree using iterative function\n";
    cout << "28 - print level by level\n";
    cout << "29 - print hierarchically\n";
    cout << "30 - convert to AVL\n";
    cout << "31 - size tree\n";
    cout << "32 - empty\n";
    cout << "33 - clear\n";
    cout << "34 - exit\n";
}

int main() {


    BinarySearchTree b;

    while (true) {

        print_operations();
        print_line();
        cout << "enter number operation:";
        int op;
        myType x;
        cin >> op;

        switch (op) {
            case 1:
                cout << "enter value:";
                cin >> x;
                b.insert_iterative(x);
                break;
            case 2:
                cout << "enter value:";
                cin >> x;
                b.insert_recursive(x);
                break;
            case 3:
                cout << "enter value:";
                cin >> x;
                b.insert_random_iterative(x);
                break;
            case 4:
                cout << "enter value:";
                cin >> x;
                b.insert_value_using_avl_function(x);
            case 5:
                cout << "enter value:";
                cin >> x;
                b.delete_value_iterative(x);
                break;
            case 6:
                cout << "enter value:";
                cin >> x;
                b.delete_value_recursive(x);
                break;
            case 7:
                cout << "enter value:";
                cin >> x;
                b.delete_value_using_avl_function_recursive(x);
                break;
            case 8:
                cout << "enter value:";
                cin >> x;
                b.search_iterative(x);
                break;
            case 9:
                cout << "enter value:";
                cin >> x;
                b.search_recursive(x);
                break;
            case 10:
                b.pre_order();
                break;
            case 11:
                b.in_order();
                break;
            case 12:
                b.post_order();
                break;
            case 13:
                b.is_linear_iterative();
                break;
            case 14:
                b.is_complete_iterative();
                break;
            case 15:
                b.is_complete_recursive();
                break;
            case 16:
                b.is_full_iterative();
                break;
            case 17:
                b.is_full_recursive();
                break;
            case 18:
                b.is_perfect();
                break;
            case 19:
                b.is_binary_search_tree_iterative();
                break;
            case 20:
                b.is_binary_search_tree_recursive();
                break;
            case 21:
                cout << "enter value:";
                cin >> x;
                b.get_depth_or_level_of_node_iterative(x);
                break;
            case 22:
                cout << "enter value:";
                cin >> x;
                b.get_height_of_node_recursive(x);
                break;
            case 23:
                b.get_tree_degree_iterative();
                break;
            case 24:
                b.get_tree_width_iterative();
                break;
            case 25:
                b.count_levels_recursive();
                break;
            case 26:
                b.min_value_in_tree_iterative();
                break;
            case 27:
                b.max_value_in_tree_iterative();
                break;
            case 28:
                b.print_level_by_level_iterative();
                break;
            case 29:
                b.print_hierarchically_iterative();
                break;
            case 30:
                b.convert_to_avl();
                break;
            case 31:
                b.size_tree();
                break;
            case 32:
                b.empty();
                break;
            case 33:
                b.clear_tree_recursive();
                break;
            case 34:
                return 0;
            default: {
                cout << "wrong input ...!\n";
                goto h;
            }
        }
        print_line();
    }

    h:;

    return 0;
}

/*

  1 20 1 30 1 10 1 20 1 15 1 25 1 5 1 35 1 4 1 8 1 13 1 22 1 27 1 34 1 36 1 11 1 3 1 23 1 7 1 37 1 21 1 264 1 9 1 26
  1 15 1 10 1 20 1 5 1 13 1 21 1 17 1 6 1 1
  1 25 1 20 1 36 1 10 1 22 1 30 1 40 1 5 1 14  1 28 1 38 1 48 1 11 1 15

 * */

