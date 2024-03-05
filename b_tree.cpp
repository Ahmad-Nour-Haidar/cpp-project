/// Ahmad Nour Haidar

#include <iostream>

using namespace std;

class BTree {
private:
    class Node {
        int keys[5]{};
        int t;
        int n;
        bool leaf;
        Node *children[6]{};

        // Constructor
        Node(int t, bool leaf) {
            this->t = t;
            this->leaf = leaf;
            n = 0;
        }

        void splitChild(int i, int k, Node *y) {
            Node *z = new Node(y->t, y->leaf);
            z->n = t;
            int mid = y->keys[t];
            y->keys[t] = k;
            for (int j = 0; j < t - 1; ++j) {
                z->keys[j] = y->keys[j + t + 1];
            }

            // Copy the last t children of y to z
            if (y->leaf == false) {
                for (int j = 0; j < t; j++)
                    z->children[j] = y->children[j + t];
            }
            y->n = t;

            // Since this node is going to have a new child,
            // create space of new child
            for (int j = n; j >= i + 1; --j) {
                children[j + 1] = children[j];
            }
            children[i + 1] = z;
            keys[i] = mid;
            n = n + 1;
        }

    };
};