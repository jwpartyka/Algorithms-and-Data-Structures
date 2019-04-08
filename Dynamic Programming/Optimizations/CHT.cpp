// Convex Hull Trick 
// 1) Sorted slopes
// 2) Sorted xs
// Complexity:
// O(n)

struct Line {
    ll a, b;
    int id;
    ll f(int x) {
        return a * x + b;
    }

    ll operator *(const Line &l)const {
        if (a == l.a) {
            if (b == l.b) {
                return 0;
            }
            return inf;
        }
        return (l.b - b + a - l.a - 1) / (a - l.a);
    }
};

struct CHT {
    deque<Line> Q;

    CHT(Line l) {
        Q = {l};
    }

    Line Max(int x) {
        while (Q.size() > 1 && Q[1] * Q[0] <= x) {
            Q.pop_front();
        }
        return Q[0];
    }

    void insert(Line l) {
        while (Q.size() > 1 && l * Q.back() <= Q.back() * Q[Q.size() - 2]) {
            Q.pop_back();
        }
        Q.push_back(l);
    }
};
