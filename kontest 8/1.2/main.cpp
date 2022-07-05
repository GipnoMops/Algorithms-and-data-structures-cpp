#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

struct Node {
    int y_;
    int sz_;
    int val_;
    Node *l_, *r_;
};

Node *new_node(int val) {
    Node *result = new Node;
    result->y_ = rand();
    result->sz_ = 1;
    result->val_ = val;
    result->l_ = result->r_ = nullptr;
    return result;
}

int get_sz(Node *t) {
    if (t == nullptr) return 0;
    return t->sz_;
}

void upd_sz(Node *t) {
    if (t == nullptr) return;
    t->sz_ = 1 + get_sz(t->l_) + get_sz(t->r_);
}

Node* merge(Node* t1, Node *t2) {
    if (t1 == nullptr) return t2;
    if (t2 == nullptr) return t1;
    if (t1->y_ > t2->y_) {
        t1->r_ = merge(t1->r_, t2);
        upd_sz(t1);
        return t1;
    } else {
        t2->l_ = merge(t1, t2->l_);
        upd_sz(t2);
        return t2;
    }
}

void split(Node *t, int x, Node *&t1, Node *&t2) {
    if (t == nullptr) {
        t1 = t2 = nullptr;
        return;
    }

    if (get_sz(t->l_) < x) {
        split(t->r_, x - get_sz(t->l_) - 1, t->r_, t2);
        t1 = t;
    } else {
        split(t->l_, x, t1, t->l_);
        t2 = t;
    }
    upd_sz(t);
}

Node* to_front(Node *t, int l, int r) {
    Node *t1, *t2, *t3, *t4;
    split(t, r + 1, t1, t2);
    split(t1, l, t3, t4);
    return merge(merge(t4, t3), t2);
}

Node *from_vector(const vector<int>& v) {
    Node *result = nullptr;
    for(int i = 0; i < v.size(); ++i) {
        result = merge(result, new_node(v[i]));
    }
    return result;
}

void print_tree(Node *t) {
    if (t == nullptr) return;
    print_tree(t->l_);
    cout << t->val_ << " ";
    print_tree(t->r_);
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> values;
    for (int i = 1; i <= n; ++i) {
        values.push_back(i);
    }

    Node *tree = from_vector(values);

    for (int i = 0; i < m; ++i) {
        int start, end;
        cin >> start >> end;
        --start;
        --end;
        to_front(tree, start, end);
    }

    print_tree(tree);
    cout << endl;
    return 0;
}
