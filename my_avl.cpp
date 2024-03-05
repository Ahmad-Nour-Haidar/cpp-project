/// Ahmad Nour Haidar

#include <iostream>
#include <queue>

using namespace std;

const int SPACE = 10;

/// named after inventors Adelson ,Velsky ,Landis
class AVLTree {
private:
    struct Node {
        int value;
        int height;
        Node *left;
        Node *right;

        Node(int value) {
            this->value = value;
            height = 1;
            left = nullptr;
            right = nullptr;
        }
    };

    Node *rootTree;

/// functions for avl

    static int _height(Node *node) {
        if (node) { /// --> node != null
            return node->height;
        }
        return 0;
    }

    static int _max(const int &a, const int &b) {
        return (a > b) ? a : b;
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

    Node *_insert_using_avl_function_recursive(Node *node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->value) {
            node->left = _insert_using_avl_function_recursive(node->left, value);
        } else if (value > node->value) {
            node->right = _insert_using_avl_function_recursive(node->right, value);
        } else {
            /// duplicates are not allowed
            return node;
        }
        node->height = 1 + _max(_height(node->left), _height(node->right));
        int balance = _get_balance(node);

        /// there are 4 cases

        /// left case
        if (balance > 1 and value < node->left->value) {
            return _right_rotate(node);
        }

        /// right case
        if (balance < -1 and value > node->right->value) {
            return _left_rotate(node);
        }

        /// left right case
        if (balance > 1 and value > node->left->value) {
            node->left = _left_rotate(node->left);
            return _right_rotate(node);
        }

        /// right left case
        if (balance < -1 and value < node->right->value) {
            node->right = _right_rotate(node->right);
            return _left_rotate(node);
        }

        return node;
    }

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

    Node *_delete_value_and_get_successor_from_right_subtree_recursive(Node *root, int value) {
        if (root == nullptr) {
            /// value not found
            return root;
        }
        if (value < root->value) {
            root->left = _delete_value_and_get_successor_from_right_subtree_recursive(root->left, value);
        } else if (value > root->value) {
            root->right = _delete_value_and_get_successor_from_right_subtree_recursive(root->right, value);
        } else {
            /// node with only one child or no child
            if (root->left == nullptr or root->right == nullptr) {
                Node *successor = root->left ? root->left : root->right;
                if (successor == nullptr) {
                    /// root is leaf
                    delete root;
                    delete successor;
                    root = nullptr;
                } else {
                    /// root has one child
                    *root = *successor; /// copy content temp to root
                }
            } else {
                /// node with tow children
                Node *successor = _min_value_in_right_sub_tree(root->right);
                root->value = successor->value;
                root->right = _delete_value_and_get_successor_from_right_subtree_recursive(root->right, root->value);
            }
        }
        /// If the tree had only one node
        if (root == nullptr) {
            return root;
        }

        root->height = 1 + _max(_height(root->left), _height(root->right));
        int balance = _get_balance(root);

        /// there are 4 cases

        /// left left case
        if (balance > 1 and _get_balance(root->left) >= 0) {
            return _right_rotate(root);
        }

        /// right right case
        if (balance < -1 and _get_balance(root->right) <= 0) {
            return _left_rotate(root);
        }

        /// left right case
        if (balance > 1 and _get_balance(root->left) < 0) {
            root->left = _left_rotate(root->left);
            return _right_rotate(root);
        }

        /// right left case
        if (balance < -1 and _get_balance(root->right) > 0) {
            root->right = _right_rotate(root->right);
            return _left_rotate(root);
        }

        return root;
    }

    Node *_delete_value_and_get_successor_from_left_subtree_recursive(Node *root, int value) {
        if (root == nullptr) {
            /// value not found
            return root;
        }
        if (value < root->value) {
            root->left = _delete_value_and_get_successor_from_left_subtree_recursive(root->left, value);
        } else if (value > root->value) {
            root->right = _delete_value_and_get_successor_from_left_subtree_recursive(root->right, value);
        } else {
            /// node with only one child or no child
            if (root->left == nullptr or root->right == nullptr) {
                Node *successor = root->left ? root->left : root->right;
                if (successor == nullptr) {
                    /// root is leaf
                    delete root;
                    delete successor;
                    root = nullptr;
                } else {
                    /// root has one child
                    *root = *successor;
                }
            } else {
                /// node with tow children
                Node *successor = _max_value_in_left_sub_tree(root->left);
                root->value = successor->value;
                root->left = _delete_value_and_get_successor_from_left_subtree_recursive(root->left, root->value);
            }
        }
        /// If the tree had only one node
        if (root == nullptr) {
            return root;
        }

        root->height = 1 + _max(_height(root->left), _height(root->right));
        int balance = _get_balance(root);

        /// there are 4 cases

        /// left left case
        if (balance > 1 and _get_balance(root->left) >= 0) {
            return _right_rotate(root);
        }

        /// right right case
        if (balance < -1 and _get_balance(root->right) <= 0) {
            return _left_rotate(root);
        }

        /// left right case
        if (balance > 1 and _get_balance(root->left) < 0) {
            root->left = _left_rotate(root->left);
            return _right_rotate(root);
        }

        /// right left case
        if (balance < -1 and _get_balance(root->right) > 0) {
            root->right = _right_rotate(root->right);
            return _left_rotate(root);
        }

        return root;
    }

    static void _print_empty() {
        cout << "Sorry, your tree is empty ...!\n";
    }

    bool _empty() {
        return rootTree == nullptr;
    }

    void _print_hierarchically(Node *root, int space) {
        if (root == nullptr) {
            return;
        }
        space += SPACE;
        _print_hierarchically(root->right, space);
        for (int i = SPACE; i < space; i++) {
            cout << ' ';
        }
        cout << root->value << '\n';
        _print_hierarchically(root->left, space);
    }

public:

    /// constructor
    AVLTree() : rootTree(nullptr) {}

    void print_hierarchically() {
        if (_empty()) {
            _print_empty();
            return;
        }
        cout << "Your tree as Hierarchically is:\n";
        _print_hierarchically(rootTree, 0);
    }

    /// Time Complexity: O(log n) for each element.
    void insert(const int &value) {
        rootTree = _insert_using_avl_function_recursive(rootTree, value);
    }

    /// Time Complexity: O(log n) for each element.
    void delete_value(const int &value) {
        /// you can choose any of them.
//        rootTree = _delete_value_and_get_successor_from_right_subtree_recursive(rootTree, value);
        rootTree = _delete_value_and_get_successor_from_left_subtree_recursive(rootTree, value);
    }

    /// end class AVLTree
};


int main() {

    AVLTree avl;
    int b[] = {5, 3, 10, 2, 4, 7, 11, 1, 6, 9, 12, 8};

    for (int &i : b) {
        avl.insert(i);
        avl.print_hierarchically();
    }

    avl.delete_value(4);
    avl.print_hierarchically();


    return 0;
}


/// int a[] = {9, 2, 4, 7, 11, 8, 3, 10, 5};
/// int in[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
/// int ix[] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
/// int iy[] = {9, 27, 50, 15, 2, 21, 36};
