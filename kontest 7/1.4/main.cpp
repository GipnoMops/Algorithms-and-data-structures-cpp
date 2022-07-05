#include <iostream>

using namespace std;

class Node{
public:
    int data;
    int counter = 0;
    Node* left_child;
    Node* right_child;
    Node(int x) {
        data = x;
        left_child = nullptr;
        right_child = nullptr;
    }
};

class BST{
public:
    Node* root = nullptr;

    void insert(Node*& node, int data){
        if (node == nullptr) {
            node = new Node(data);
            ++(node->counter);
            return;
        }
        if(data < node->data)
            insert(node->left_child,data);
        else if(data > node->data)
            insert(node->right_child,data);
        else if (data == node->data)
            ++(node->counter);

    }

    void just_insert(int data){
        insert(root, data);
    }

    void PrintTree(Node* Root) {
        if (Root != nullptr) {
            PrintTree(Root->left_child);
            std::cout << Root->data << " " << Root->counter << "\n";
            PrintTree(Root->right_child);
        }
    }

    void just_print_tree() {
        PrintTree(root);
    }


    int HeightBST(Node* Tree) {
        int x = 0, y = 0;
        if (Tree == nullptr) return 0;
        if (Tree->left_child) x = HeightBST(Tree->left_child);
        if (Tree->right_child) y = HeightBST(Tree->right_child);
        if (x > y) return x + 1;
        else return y + 1;
    }

    int HBST() {
        return HeightBST(root);
    };
};

int main() {
    int value;
    BST bst = BST();
    while (true) {
        cin >> value;
        if (value == 0) break;
        bst.just_insert(value);
    }
    bst.just_print_tree();
    return 0;
}
