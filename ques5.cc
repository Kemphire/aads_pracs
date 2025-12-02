#include <iostream>
using namespace std;

const int M = 4;  // Max children = 4 → Max keys = 3

// ----------------------------------------------------
// BTreeNode
// ----------------------------------------------------
class BTreeNode {
   public:
    BTreeNode();
    BTreeNode(int val);

   private:
    bool leaf;
    int keyTally;
    int keys[M - 1];
    BTreeNode* pointers[M];

    friend class BTree;
};

BTreeNode::BTreeNode() : leaf(true), keyTally(0) {
    for (int i = 0; i < M; i++) pointers[i] = nullptr;
}

BTreeNode::BTreeNode(int val) : leaf(true), keyTally(1) {
    keys[0] = val;
    for (int i = 1; i < M - 1; i++) keys[i] = 0;
    for (int i = 0; i < M; i++) pointers[i] = nullptr;
}

// ----------------------------------------------------
// BTree
// ----------------------------------------------------
class BTree {
   public:
    BTree();
    BTree(int val);

    BTreeNode* search(int key);
    bool insert(int key);
    void printTree();

   private:
    BTreeNode* root;

    BTreeNode* search_impl(int key, BTreeNode* node);
    BTreeNode* insert_impl(int key, BTreeNode* node);
    void print_impl(BTreeNode* node, int depth);

    void splitChild(BTreeNode* parent, int idx);
};

BTree::BTree() { root = nullptr; }
BTree::BTree(int val) { root = new BTreeNode(val); }

// ----------------------------------------------------
// Search (your implementation)
// ----------------------------------------------------
BTreeNode* BTree::search_impl(int key, BTreeNode* node) {
    if (node == nullptr) return nullptr;

    int i = 0;
    while (i < node->keyTally && key > node->keys[i]) {
        i++;
    }

    // Key found
    if (i < node->keyTally && key == node->keys[i]) {
        return node;
    }

    // Leaf → key not found
    if (node->leaf) return nullptr;

    // Go deeper
    return search_impl(key, node->pointers[i]);
}

BTreeNode* BTree::search(int key) {
    if (root == nullptr) return nullptr;
    return search_impl(key, root);
}

// ----------------------------------------------------
// INSERT LOGIC STARTS HERE
// ----------------------------------------------------

// Split a full child of parent at index idx
void BTree::splitChild(BTreeNode* parent, int idx) {
    BTreeNode* full = parent->pointers[idx];
    BTreeNode* half = new BTreeNode();
    half->leaf = full->leaf;

    // Right node gets the last key (index 2)
    half->keys[0] = full->keys[2];
    half->keyTally = 1;

    // Move children if internal node
    if (!full->leaf) {
        half->pointers[0] = full->pointers[2];
        half->pointers[1] = full->pointers[3];
    }

    // Left node keeps first key only
    full->keyTally = 1;

    // Shift parent's children to make room
    for (int i = parent->keyTally; i >= idx + 1; i--)
        parent->pointers[i + 1] = parent->pointers[i];

    parent->pointers[idx + 1] = half;

    // Shift parent's keys to make room
    for (int i = parent->keyTally - 1; i >= idx; i--)
        parent->keys[i + 1] = parent->keys[i];

    // Promote middle key (index 1)
    parent->keys[idx] = full->keys[1];
    parent->keyTally++;
}

// Recursive insert into non-full node
BTreeNode* BTree::insert_impl(int key, BTreeNode* node) {
    int i = node->keyTally - 1;

    if (node->leaf) {
        // Shift keys to make space
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->keyTally++;
        return node;
    }

    // Find child
    while (i >= 0 && key < node->keys[i]) i--;
    i++;

    // Split child if full
    if (node->pointers[i]->keyTally == M - 1) {
        splitChild(node, i);

        // After split, choose correct child
        if (key > node->keys[i]) i++;
    }

    return insert_impl(key, node->pointers[i]);
}

// Public insert
bool BTree::insert(int key) {
    if (root == nullptr) {
        root = new BTreeNode(key);
        return true;
    }

    // If root full → split
    if (root->keyTally == M - 1) {
        BTreeNode* newRoot = new BTreeNode();
        newRoot->leaf = false;
        newRoot->pointers[0] = root;

        splitChild(newRoot, 0);

        int i = (key > newRoot->keys[0]) ? 1 : 0;
        insert_impl(key, newRoot->pointers[i]);

        root = newRoot;
    } else {
        insert_impl(key, root);
    }

    return true;
}

void BTree::print_impl(BTreeNode* node, int depth) {
    if (!node) return;

    cout << string(depth * 2, ' ');
    for (int i = 0; i < node->keyTally; i++) cout << node->keys[i] << " ";
    cout << "\n";

    if (!node->leaf) {
        for (int i = 0; i <= node->keyTally; i++)
            print_impl(node->pointers[i], depth + 1);
    }
}

void BTree::printTree() {
    if (!root)
        cout << "(empty)\n";
    else
        print_impl(root, 0);
}

int main() {
    BTree tree;

    cout << "Inserting values:\n";
    int values[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int v : values) {
        cout << "Insert: " << v << "\n";
        tree.insert(v);
        tree.printTree();
        cout << "---------------------\n";
    }

    cout << "\nSearching for keys:\n";

    auto node = tree.search(1004);
    if (node != nullptr) {
        cout << "Found Insert Working\n";
    } else {
        cout << "Key Not Found\n";
    }
    return 0;
}
