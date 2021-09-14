#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

template<typename V> struct SuperVector {
    int getrand(int x) { static uint32_t y = time(0); y ^= (y << 13); y ^= (y >> 17); y ^= (y << 5); return y % x; }
    struct Node { V val; Node *lch, *rch; int sz; Node(V a) :val(a), lch(0), rch(0), sz(1) {  } };
 
    SuperVector() :root(NULL) {}
    Node *root;
    inline int size(Node *t) { return t ? t->sz : 0; }
    int size() { return size(root); }
    inline Node *update(Node *t) {
        if (!t)return 0; t->sz = size(t->lch) + size(t->rch) + 1; return t;
    }
 
    Node *merge(Node *a, Node *b) {
        if (!a)return b;
        if (!b)return a;
 
        if (getrand(size(a) + size(b)) < size(a)) {
            a->rch = merge(a->rch, b);
            return update(a);
        }
        else {
            b->lch = merge(a, b->lch);
            return update(b);
        }
    }
 
    template<class... T> Node *merge(Node *a, T... y) { return merge(a, merge(y...)); }
 
    pair<Node *, Node *>split(Node *t, int k) {//[0,k) [k,N)
        if (!t)return make_pair(t, t);
        if (k <= size(t->lch)) {
            pair<Node *, Node *>s = split(t->lch, k);
            t->lch = s.second;
            return make_pair(s.first, update(t));
        }
        else {
            pair<Node *, Node *>s = split(t->rch, k - size(t->lch) - 1);
            t->rch = s.first;
            return make_pair(update(t), s.second);
        }
    }
 
    // [l,r]番目でa,b,cに分ける(終わったらちゃんとマージすること)
    // rootは0になってる
    tuple<Node*, Node*, Node*> split3(int l, int r) {
        auto p = split(root, l);
 
        auto a = p.first;
 
        auto q = split(p.second, r - l + 1);
 
        auto b = q.first;
        auto c = q.second;
        root = 0;
 
        return make_tuple(a, b, c);
    }
 
    void change(int i, Node* v) { // i番目をvに更新
        auto p = split(root, i);
        auto a = p.first;
        auto q = split(p.second, 1);
        Node* b = q.first;
        auto c = q.second;
 
        b = v;
 
        root = merge(merge(a, b), c);
    }
 
    void dump() {
        dump(root);
        cout << endl;
    }
    void dump(Node *t) {
        if (t == NULL)return;
        dump(t->lch);
        cout << t->val << " ";
        dump(t->rch);
    }
 
    void push_back(V v) {
        Node *t = new Node(v);
        root = merge(root, t);
    }
 
    void push_front(V v) {
        Node *t = new Node(v);
        root = merge(t, root);
    }
 
    void shift(int l, int r) { // [l,r]の範囲を右にシフトする(最右は左へ移る)
        Node *a, *b, *c;
        tie(a, b, c) = split3(l, r);
 
        Node *ba, *bb;
        tie(ba, bb) = split(b, r - l);
 
        root = merge(root, a, bb, ba, c);
    }
 
    V operator[](int i) { 
        auto p = split(root, i);
        auto a = p.first;
        auto q = split(p.second, 1);
        Node* b = q.first;
        auto c = q.second;
 
        root = merge(merge(a, b), c);
 
        return b->val;
    }
 
    SuperVector cut(int L, int R) { // [L,R]を切り取る
        Node *a, *b, *c;
        tie(a, b, c) = split3(L, R);
 
        root = merge(a, c);
 
        SuperVector res;
        res.root = b;
        return res;
    }
 
    void insert(int i, V v) { // i番目としてndを追加する(i-1番目の後ろに追加)
        Node *a, *b;
        Node* nd = new Node(v);
        tie(a, b) = split(root, i);
        root = merge(a, nd, b);
    }
 
    template<typename Func> void foreach(Func f) { foreach(root, f); }
    template<typename Func> void foreach(Node* n, Func &f) {
        if (!n) return;
        if (n->lch) foreach(n->lch, f);
        f(n);
        if (n->rch) foreach(n->rch, f);
    }
};


int main(void){
  SuperVector<int> sv;
  sv.push_back(3);
  sv.push_back(7);
  sv.push_back(9);
  sv.push_back(4);  
  cout << sv[3] << endl;
}
