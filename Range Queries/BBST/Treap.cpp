// Treap
// Source: Benq, cp-algorithms.com

#define st first
#define nd second

const int inf = 1e9;

set<int> S;

struct Node {
    int pri, val, sz;
    int sum;
    Node *l, *r;
    bool flip;

    Node() {}
    Node(int v) : val(v), sz(1), flip(0), l(nullptr), r(nullptr) {
        pri = rand() + (rand()<<15);
    }
};

int getsz(Node *t) {
    return (t ? t->sz : 0);
}

int getsum(Node *t) {
    return (t ? t->sum : 0);
}

void touch(Node *t) {
    if (!t || !t->flip) {
        return;
    }
    swap(t->l, t->r);
    t->flip = 0;
    t->l->flip ^= 1;
    t->r->flip ^= 1;
}

Node* update(Node *t) {
    touch(t->l);
    touch(t->r);
    t->sz = getsz(t->l) + 1 + getsz(t->r);
    t->sum = getsum(t->l) + t->val + getsum(t->r);
    return t;
}

pair<Node*, Node*> split_by_key(Node *t, int k) {
    if (!t) {
        return {t, t};
    }
    touch(t);
    if (t->val >= k) {
        auto p = split_by_key(t->l, k);
        t->l = p.nd;
        return {p.st, update(t)};
    } else {
        auto p = split_by_key(t->r, k);
        t->r = p.st;
        return {update(t), p.nd};
    }
}

pair<Node*, Node*> split_by_order(Node* t, int k) {
    if (!t) {
        return {t, t};
    }
    touch(t);
    if (getsz(t->l) >= k) {
        auto p = split_by_order(t->l, k);
        t->l = p.nd;
        return {p.st, update(t)};
    } else {
        auto p = split_by_order(t->r, k - getsz(t->l) - 1);
        t->r = p.st;
        return {update(t), p.nd};
    }
}

Node* merge(Node *l, Node *r) {
    if (!l || !r) {
        return (l ? l : r);
    }
    touch(l);
    touch(r);
    Node *t;
    if (l->pri > r->pri) {
        l->r = merge(l->r, r);
        t = l;
    } else {
        r->l = merge(l, r->l);
        t = r;
    }
    return update(t);
}

Node* ins(Node *t, int k) {
    auto a = split_by_key(t, k);
    //auto b = split_by_key(a.nd, k + 1);
    //return merge(a.st, merge(new Node(v), b.nd));
    return merge(a.st, merge(new Node(k), a.nd));
}

Node* ins(Node *t, int k, int v) {
    auto a = split_by_order(t, k);
    //auto b = split_by_order(a.nd, k + 1);
    //return merge(a.st, merge(new Node(v), b.nd));
    return merge(a.st, merge(new Node(v), a.nd));
}

Node* del(Node *t, int k) {
    auto a = split_by_key(t, k);
    auto b = split_by_key(a.nd, k + 1);
    return merge(a.st, b.nd);
}

int kth(Node *t, int k) {
    if (!t) {
        return inf + 1;
    }
    touch(t);
    if (getsz(t->l) >= k) {
        return kth(t->l, k);
    }
    if (getsz(t->l) + 1 == k) {
        return t->val;
    }
    return kth(t->r, k - getsz(t->l) - 1);
}

int countSmaller(Node *t, int k, int res = 0) {
    if (!t) {
        return res;
    }
    touch(t);
    if (t->val >= k) {
        return countSmaller(t->l, k, res);
    }
    return countSmaller(t->r, k, res + getsz(t->l) + 1);
}

void prt(Node *t) {
    if (!t) {
        return;
    }
    prt(t->l);
    cout << t->val << " ";
    prt(t->r);
}

Node* Treap;
