#include <iostream>
#include <vector>
#include <algorithm>


class Tree {
private:
    Tree *left = nullptr;
    Tree *right = nullptr;
    int v = 0;

public:
    Tree() {
        left = nullptr;
        right = nullptr;
        v = 0;
    }

    Tree(Tree l, Tree r) {
        left = &l;
        right = &r;
        v = l.v + r.v;
    }

    Tree(Tree* l, Tree* r) {
        left = l;
        right = r;
        v = l->v + r->v;
    }

    Tree(int x) {
        v = x;
    }

    Tree buildTree(int l, int r, std::vector<int>& a) {
        if (l == r) {
            return Tree(a[l]);
        }
        return Tree(buildTree(l, (l + r) / 2, a),
                    buildTree((l + r + 2) / 2, r, a));
    }

    int get(Tree* t, int l, int r, int y) {
        if (y == 0) {
            return l - 1;
        }
        if (t == nullptr) {
            return 0;
        }
        // System.out.println(l + " " + r + " --> " + t.v);
        if (t->v < y || l == r) {
            y -= t->v;
            // System.out.println("ans = " + r);
            return r;
        }
        int ans = get(t->left, l, (l + r) / 2, y);
        if (y > 0) {
            ans = get(t->right, (l + r + 2) / 2, r, y);
        }
        // System.out.println("ans = " + ans);
        return ans;
    }

    Tree* set(Tree* root, int l, int r, int i, int x) {
        if (i < l || r < i) {
            return root;
        }
        if (l == r) {
            return new Tree(x);
        }
        return new Tree(set(root->left, l, (l + r) / 2, i, x), set(root->right, (l + r + 2) / 2, r, i, x));
    }
};

/*class Tree {
private:
    Tree *left;
    Tree *right;
    int v;

public:
    Tree(Tree l, Tree r) {
        left = &l;
        right = &r;
        v = l.v + r.v;
    }

    Tree(int x) {
        v = x;
    }

    Tree build(std::vector<int>& a, int v, int tl, int tr) {
        if (tl == tr)
            return Tree(a[tl]);
        else {
            int tm = (tl + tr) / 2;
            build(a, v * 2, tl, tm);
            build(a, v * 2 + 1, tm + 1, tr);
            Tree new_v();
            answer[v] = answer[v * 2] + answer[v * 2 + 1];
        }
    }

};

void build (std::vector<int>& a, int v, int tl, int tr, std::vector<int>& answer) {
    if (tl == tr)
        answer[v] = a[tl];
    else {
        int tm = (tl + tr) / 2;
        build (a, v * 2, tl, tm, answer);
        build (a, v * 2 + 1, tm + 1, tr, answer);
        answer[v] = answer[v * 2] + answer[v * 2 + 1];
    }
}

int sum (int v, int tl, int tr, int l, int r, std::vector<int>& answer) {
    if (l > r)
        return 0;
    if (l == tl && r == tr)
        return answer[v];
    int tm = (tl + tr) / 2;
    return sum(v * 2, tl, tm, l, std::min(r, tm), answer)
           + sum (v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, answer);
}

void update (int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr)
            t[v] = new_val;
        else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update (v*2, tl, tm, pos, new_val);
            else
                update (v*2+1, tm+1, tr, pos, new_val);
            t[v] = t[v*2] + t[v*2+1];
        }
    }*/

/*struct Tree {
    int lb, rb; // левые и правые границы отрезков
    int sum = 0; // сумма на текущем отрезке
    Tree *l = 0, *r = 0;

    Tree(int _lb, int _rb) {
        lb = _lb, rb = _rb;
        if (lb + 1 < rb) {
            // если не лист, создаем детей
            int t = (lb + rb) / 2;
            l = new Tree(lb, t); r = new Tree(t, rb);
        }
    }

    void add (int k, int x) {
        sum += x;
        if (l) {
            if (k < l->rb)
                l->add(k, x);
            else
                r->add(k, x);
        }
    }



    int get_sum (int lq, int rq) {
        if (lb >= lq && rb <= rq)
            // если мы лежим полностью в отрезке запроса, вывести сумму
            return sum;
        if (std::max(lb, lq) >= std::min(rb, rq))
            // если мы не пересекаемся с отрезком запроса, вывести ноль
            return 0;
        // иначе всё сложно -- запускаемся от детей и пусть они там сами решают
        return l->get_sum(lq, rq) + r->get_sum(lq, rq);
    }
};*/


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

};


int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> server(n);
    for (int i = 0; i < n; ++i) std::cin >> server[i];

    std::vector<int> ANS = {1, 4, 0, 6};

    Tree* root;
    root->buildTree(0, n - 1, server);

    std::vector<Tree> roots;
    for (int i = n - 1; i >= 0; --i) {
        int k = i + 1;
        while (k < n && server[k] != server[i]) ++k;

        if (k < n) {
            root->set(root, 0, n - 1, k, 0);
            root->set(root, 0, n - 1, i, 1);
            roots[i] = *root;
        } else root[i] = *root;
    }

    int q, p = 0;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int x, y;
        std::cin >> x >> y;
        int l = ((x + p) % n) + 1;
        int k = ((y + p) % m) + 1;
        //int r  = основной алгоритм;
        p = ANS[i];
        std::cout << l << " " << k << " : " << ANS[i] << "\n";
    }
    return 0;
}
