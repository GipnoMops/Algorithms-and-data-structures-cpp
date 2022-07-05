#include <iostream>

class BST {
private:
    int dips_;
    int value_;
    BST* left_;
    BST* right_;

public:
    BST(int value = 0, BST* left = nullptr, BST* right = nullptr): value_(value), left_(left), right_(right) {};

    void insert(int key) {
        BST* curr = this;
        while (curr && curr->value_ != key)
        {
            if (curr->value_ > key && curr->left_ == nullptr)
            {
                BST l(key);
                curr->left_ = &l;
                return;
            }
            if (curr->value_ < key && curr->right_ == nullptr)
            {
                BST r(key);
                curr->right_ = &r;
                return;
            }
            if (curr->value_ > key)
                curr = curr->left_;
            else
                curr = curr->right_;
        }
    }

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
};

int main() {
    BST tree;
    int key;
    std::cin >> key;
    while (key != 0) {
        tree.insert(key);
        std::cin >> key;
    }

    std::cout << tree.maxDepth();
    return 0;
}
