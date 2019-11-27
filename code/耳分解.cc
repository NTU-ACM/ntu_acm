//written by zerol
//在无向图中，耳朵就定义为一条路径，其中除了端点外的点的度数均为 2（端点可以重合），而且删去后不破坏图的连通性。耳分解就是将图中的耳朵依次删去直至删完，不是所有无向图都能被耳分解，同时耳分解的方案很可能是不唯一的。
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0)
void err() { cout << "\033[39;0m" << endl; }
template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x) { for (auto v: a) cout << v << ' '; err(x...); }
template<typename T, typename... A>
void err(T a, A... x) { cout << a << ' '; err(x...); }
#else
#define dbg(...)
#endif
// -----------------------------------------------------------------------------
const int N = 2E4 + 100;
using VI = vector<int>;
vector<int> G[N];
int dfn[N], low[N], clk;
VI ears[N * 20];
int sz;
VI* cur[N];
vector<VI*> ans;

void dfs(int u, int fa) {
	dfn[u] = low[u] = ++clk;
	int _fst = 0;
	vector<VI*> V;
	for (int& v: G[u]) {
		if (v == fa && ++_fst == 1) continue;
		if (!dfn[v]) {
			dfs(v, u);
			if (low[v] > dfn[u]) { puts("-1"); exit(0); }
			low[u] = min(low[u], low[v]);
			cur[v]->push_back(u);
			V.push_back(cur[v]);
		} else if (dfn[v] < dfn[u]) {
			low[u] = min(low[u], dfn[v]);
			ears[sz].push_back(v);
			ears[sz].push_back(u);
			V.push_back(&ears[sz++]);
		}
	}
	_fst = 0;
	for (VI* x: V) {
		int d = dfn[*x->begin()];
		if (d > low[u] || (d == low[u] && ++_fst > 1)) {
			ans.push_back(x);
		} else cur[u] = x;
	}
	if (u == 1) ans.push_back(cur[u]);
}

int main() {
	int n, m; cin >> n >> m;
	FOR (_, 0, m) {
		int u, v; scanf("%d%d", &u, &v);
		G[u].push_back(v); G[v].push_back(u);
	}
	dfs(1, -1);
	cout << ans.size() << endl;
	for (VI* x: ans) {
		printf("%d ", x->size() - 1);
		FOR (i, 0, x->size()) printf("%d%c", x->at(i), i == _i - 1 ? '\n' : ' ');
	}
}