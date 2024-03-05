#include <iostream>

using namespace std;

class BTree {
private:
    class Node {
    public:
        int *keys; // array of keys
        int t; // minimum degree
        Node **children; // array of child pointers
        int n; // current number of keys
        bool leaf; // is this node a leaf?

        Node(int t, bool leaf) {
            this->t = t;
            this->leaf = leaf;
            keys = new int[2 * t]; // maximum of 2t keys
            children = new Node *[2 * t + 1]; // maximum of 2t+1 children
            n = 0;
        }

        void insertNonFull(int k) {
            int i = n - 1;
            if (leaf) {
                while (i >= 0 && keys[i] > k) {
                    keys[i + 1] = keys[i];
                    i--;
                }
                keys[i + 1] = k;
                n = n + 1;
            } else {
                while (i >= 0 && keys[i] > k)
                    i--;
                if (children[i + 1]->n == 2 * t) { // maximum of 2t keys
                    splitChild(i + 1, children[i + 1]);
                    if (keys[i + 1] < k)
                        i++;
                }
                children[i + 1]->insertNonFull(k);
            }
        }

        void splitChild(int i, Node *y) {
            Node *z = new Node(y->t, y->leaf);
            z->n = t;
            for (int j = 0; j < t; j++)
                z->keys[j] = y->keys[j + t];
            if (!y->leaf) {
                for (int j = 0; j < t + 1; j++) // maximum of 2t+1 children
                    z->children[j] = y->children[j + t];
            }
            y->n = t;
            for (int j = n; j >= i + 1; j--)
                children[j + 1] = children[j];
            children[i + 1] = z;
            for (int j = n - 1; j >= i; j--)
                keys[j + 1] = keys[j];
            keys[i] = y->keys[t - 1]; // t- 1
            n = n + 1; // 1 2 3 3 4 5 7
        }

        void traverse() {
            int i;
            for (i = 0; i < n; i++) {
                if (!leaf) {
                    children[i]->traverse();
                }
                cout << keys[i] << " ";
            }
            if (!leaf)
                children[i]->traverse();
        }

        Node *search(int k) {
            int i = 0;
            while (i < n && k > keys[i])
                i++;
            if (keys[i] == k)
                return this;
            if (leaf)
                return NULL;
            return children[i]->search(k);
        }

        friend class BTree;
    };

    Node *root;
    int t;

public:
    BTree(int t) {
        root = NULL;
        this->t = t;
    }

    void traverse() {
        if (root != NULL)
            root->traverse();
    }

    Node *search(int k) {
        return (root == NULL) ? NULL : root->search(k);
    }

    void insert(int k) {
        if (root == NULL) {
            root = new Node(t, true);
            root->keys[0] = k;
            root->n = 1;
        } else {
            if (root->n == 2 * t) { // maximum of 2t keys
                Node *s = new Node(t, false);
                s->children[0] = root;
                s->splitChild(0, root);
                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->children[i]->insertNonFull(k);
                root = s;
            } else {
                root->insertNonFull(k);
            }
        }
    }


};

int main() {
    BTree t(2);

    t.insert(1);
    t.insert(7);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(5);

    t.traverse();

    return 0;
}