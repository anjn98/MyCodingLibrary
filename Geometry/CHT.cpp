//Attribution - https://csacademy.com/submission/1375368/   
// lines inserted should be in decreasing order of slope

const ll is_query = -(1LL<<62);
struct Line {
    ll m, b;
    mutable function<const Line*()> succ;
    bool operator<(const Line& rhs) const {
        if (rhs.b != is_query) return m < rhs.m;
        const Line* s = succ();
        if (!s) return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};
struct CHT : public multiset<Line> { // will maintain upper hull for maximum
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end()) return y->m == x->m && y->b <= x->b;
        return double(x->b - y->b)*(z->m - y->m) >= double(y->b - z->b)*(y->m - x->m);
    }
    void insert_line(ll m, ll b) {
        auto y = insert({ m, b });
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) { erase(y); return; }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }
    ll eval(ll x) {
        auto l = *lower_bound((Line) { x, is_query });
        return l.m * x + l.b;
    }
};

struct pts {
	ll x, y, a;
	bool operator<(const pts &o) {
		if (x != o.x) {
			return x < o.x;
		} else {
			return y < o.y;
		}
	}
};

pts p[N];



int main() {
	fast_cin();
	int n; cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> p[i].x >> p[i].y >> p[i].a;
	}
	sort(p + 1, p + 1 + n);
	CHT cht;
	cht.insert_line(0, 0);
	ll ans = 0;
	for (int i = 1; i <= n; ++i) {
		ll cur = cht.eval(p[i].y) + p[i].x * p[i].y - p[i].a;
		// cout << i << ' ' << cur << endl;
		ans = max(ans, cur);
		cht.insert_line(-p[i].x, cur);
	}
	cout << ans << endl;
}
