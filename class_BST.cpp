#include <iostream>
#include <queue>

#define type int

using namespace std;

class BST {
private:
    struct Node {
        type value;
        Node *left;
        Node *right;

        explicit Node(const type &value) {
            this->value = value;
            left = nullptr;
            right = nullptr;
        }
    };

    Node *rootTree;

    /// functions for insert in bst
    void _insert_iterative(const type &value) {
        Node *newNode = new Node(value);
        if (rootTree == nullptr) {
            rootTree = newNode;
            return;
        }
        Node *current = rootTree;
        Node *parent = nullptr;
        while (current) {
            parent = current;
            if (value == current->value) {
                /// duplicate not allowed
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
    }

    Node *_insert_recursive(Node *root, const type &value) {
        if (root == nullptr) {
            return new Node(value);
        }
        if (root->value == value) {
            /// duplicate not allowed
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

    void _delete_value_iterative(const type &value) {
        Node *parent = nullptr;
        Node *current = rootTree;
        /// search for node to delete it
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
            /// value not found
            return;
        }
        /// node with only one child or no child
        if (current->left == nullptr or current->right == nullptr) {
            Node *successor = current->left ? current->left : current->right;
            if (successor == nullptr) {
                /// node is leaf, no children
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
                /// node has one child
                *current = *successor; /// copy content successor to current
                delete successor;
            }
        } else {
            /// If the node to be deleted has two children
            _delete_and_get_node_from_right_sub_tree(current);
            ///  _delete_and_get_node_from_left_sub_tree(current);
        }
    }

    static void _delete_and_get_node_from_right_sub_tree(Node *current) {
        /// find successor from right sub tree
        Node *parent = nullptr;
        Node *successor = current->right;
        while (successor->left) {
            parent = successor;
            successor = successor->left;
        }
        current->value = successor->value;
        if (parent) {
            /// maybe successor->right: nullptr or it has child from right
            parent->left = successor->right;
        } else {
            current->right = successor->right;
        }
        delete successor;
    }

    static void _delete_and_get_node_from_left_sub_tree(Node *current) {
        /// find successor from left sub tree
        cout << current->value << endl;
        Node *parent = nullptr;
        Node *successor = current->left;
        while (successor->right) {
            parent = successor;
            successor = successor->right;
        }
        current->value = successor->value;
        if (parent) {
            /// maybe successor->left: nullptr or it has child from left
            parent->right = successor->left;
        } else {
            current->left = successor->left;
        }
        delete successor;
    }

    /// functions for delete recursive

    Node *_delete_value_recursive(Node *root, const type &value) {
        if (root == nullptr) {
            /// value not found
            return root;
        } else if (value < root->value) {
            root->left = _delete_value_recursive(root->left, value);
            return root;
        } else if (value > root->value) {
            root->right = _delete_value_recursive(root->right, value);
            return root;
        } else {
            if (root->left == nullptr) {
                return root->right;
            } else if (root->right == nullptr) {
                return root->left;
            } else {
                //   Edge *temp = _max_value_in_left_sub_tree(root->left);
                //   root->value = temp->value;
                //  root->left = _delete_value_recursive(root->left, temp->value);
                //  return root;
                ///   =====================================================//
                Node *temp = _min_value_in_right_sub_tree(root->right);
                root->value = temp->value;
                root->right = _delete_value_recursive(root->right, temp->value);
                return root;
            }
        }
    }

    /// functions for search

    Node *_search_iterative(const type &value, int &level_node) {
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
        return nullptr; /// value not found
    }

    Node *_search_recursive(Node *root, const type &value, int &level_node) {
        if (root == nullptr) {
            /// value not found
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

    /// other functions

    bool _empty() {
        return rootTree == nullptr;
    }

    static void _print_empty() {
        cout << "Sorry, your tree is empty ...!\n";
    }

    /// functions for print tree

    static const int SPACE = 3;

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

    ///////////////////////////////////////////////////////////////////////

public:
    /// Constructor
    BST() : rootTree(nullptr) {};

    void insert_iterative(const type &value) {
        _insert_iterative(value);
    }

    void insert_recursive(const type &value) {
        rootTree = _insert_recursive(rootTree, value);
    }

    void delete_value_iterative(const type &value) {
        if (_empty()) {
            _print_empty();
            return;
        }
        _delete_value_iterative(value);
    }

    void delete_value_recursive(const type &value) {
        if (_empty()) {
            _print_empty();
            return;
        }
        rootTree = _delete_value_recursive(rootTree, value);
    }

    void search_iterative(const type &value) {
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

    void search_recursive(const type &value) {
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

    void print_hierarchically() {
        if (_empty()) {
            _print_empty();
            return;
        }
        cout << "Your tree as Hierarchically is:\n";
        _print_hierarchically(rootTree, 0);
    }

    /// end class BST.
};


int main() {

    BST bst;
    bst.insert_recursive(2);
    bst.insert_recursive(22);
    bst.insert_recursive(-6);
    bst.insert_recursive(33);
    bst.insert_iterative(-25);
    bst.insert_iterative(0);
    bst.insert_iterative(5);
    bst.insert_iterative(1);
    bst.insert_iterative(10);
    bst.insert_iterative(3);
    bst.insert_iterative(15);
    bst.insert_recursive(4);

    bst.print_hierarchically();

    bst.search_iterative(5);
    bst.search_recursive(9);


    return 0;
}