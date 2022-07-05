#include <iostream>
#include <algorithm>

class item {
private:
	int key, prior;
	item *l, *r;

public:
	item() { };
	item (int key, int prior) : key(key), prior(prior), l(nullptr), r(nullptr) { };

    typedef item *pitem;

    void split (item *t, int key, item *&l, item *&r) {
        if (!t)
            l = r = NULL;
        else if (key < t->key)
            split (t->l, key, l, t->l),  r = t;
        else
            split (t->r, key, t->r, r),  l = t;
    }

    void insert (item *&t, pitem it) {
        if (!t)
            t = it;
        else if (it->prior > t->prior)
            split (t, it->key, it->l, it->r),  t = it;
        else
            insert (it->key < t->key ? t->l : t->r, it);
    }

    void merge (pitem & t, pitem l, pitem r) {
        if (!l || !r)
            t = l ? l : r;
        else if (l->prior > r->prior)
            merge (l->r, l->r, r),  t = l;
        else
            merge (r->l, l, r->l),  t = r;
    }

    void erase (pitem & t, int key) {
        if (t->key == key)
            merge (t, t->l, t->r);
        else
            erase (key < t->key ? t->l : t->r, key);
    }

    pitem unite (pitem l, pitem r) {
        if (!l || !r)  return l ? l : r;
        if (l->prior < r->prior)  std::swap(l, r);
        pitem lt, rt;
        split (r, l->key, lt, rt);
        l->l = unite (l->l, lt);
        l->r = unite (l->r, rt);
        return l;
    }
};



int main() {
    item tree(1, 2);
    item tr1(2, 2);
    tree.insert(reinterpret_cast<item *&>(tree), &tr1);

    return 0;
}
