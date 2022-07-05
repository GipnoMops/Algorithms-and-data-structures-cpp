#include <iostream>

class BST {
private:
    int dips_;
    int value_;
    BST* left_;
    BST* right_;

public:
    BST (int value = 0, BST* left = nullptr, BST* rigt = nullptr): value_(value), left_(left), right_(rigt) {};

    void newBST(int val, BST** Tree = nullptr) {
        if ((*Tree) == nullptr) {
            *Tree = new BST;
            (*Tree)->value_ = val;
            (*Tree)->left_ = (*Tree)->right_ = nullptr;
            return;
        }
        if (val > (*Tree)->value_) newBST(val, &(*Tree)->right_);
        else newBST(val, &(*Tree)->left_);
    }

    int value() {
        return value_;
    };

    /*void insert(int key)
    {
        BST* curr = this;
        while (curr && curr->value_ != key) {
            if (curr->value_ > key && curr->left_ == nullptr) {
                curr->left_ = new BST(key);
                return;
            }
            if (curr->value_ < key && curr->right_ == nullptr) {
                curr->right_ = new BST(key);
                return;
            }

            if (curr->value_ > key)
                curr = curr->left_;
            else
                curr = curr->right_;
        }
    }*/

    int maxDepth() {
        if(this == nullptr)
            return 0;
        else {
            int lchild = left_->maxDepth();
            int rchild = right_->maxDepth();

            if(lchild <= rchild)
                return ++rchild;
            else
                return ++lchild;
        }
    }

    ~BST() {
        delete_tree(this);
    }

    void delete_tree(BST* curr) {
        if (curr) {
            delete_tree(curr->left_);
            delete_tree(curr->right_);
            delete curr;
        }
    }
};

int main() {
    int key;
    std::cin >> key;
    /*if (key != 0) {
        BST tree(key);
        std::cout << tree.value();
        while (true) {
            std::cin >> key;
            if (key == 0) break;
            tree.insert(key);
            std::cout << tree.value();
        }
    }*/
    //std::cout << tree.maxDepth();
    BST f(key);
    return 0;
}
