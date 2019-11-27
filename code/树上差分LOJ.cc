//树上差分 路径加值 节点查询 子树权值和
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <algorithm>
#include <sys/mman.h>
#define N 1000010
#define LL long long
using namespace std;
struct buf {
	char* s;
	buf() : s((char*)mmap(0, 150000010, PROT_READ, MAP_PRIVATE, fileno(stdin), 0)) {}
	operator int() {
		int x = 0, y = 0;
		while (*s < 48)
			if (*s++ == 45)
				y = 1;
		while (*s > 32) x = x * 10 + *s++ - 48;
		return y ? -x : x;
	}
	//	operator int(){ int x; scanf("%d",&x); return x; }
} it;
struct ouf {
	char *s, *t, *r, *l;
	ouf() : s((char*)malloc(10000000)), r((char*)malloc(20)), t(s) {}
	~ouf() { write(fileno(stdout), s, t - s); }
	inline void operator()(LL x) {
		if (x < 0)
			*t++ = 45, x = -x;
		if (!x)
			*t++ = 48;
		else {
			for (l = r; x; x /= 10) *++l = x % 10 | 48;
			for (; l != r; *t++ = *l--)
				;
		}
		*t++ = '\n';
	}
} ot;
struct edge {
	int v, nt;
} G[N << 1];
int t, n, m, R, clk = 0, h[N], l[N], r[N], v[N], d[N];
int sz[N], top[N], son[N], f[N];
LL w[N], s[N], sd[N];
inline void dfs(const int& x, const int& p) {
	d[x] = d[p] + 1;
	sz[x] = 1;
	f[x] = p;
	for (int v, i = h[x]; i; i = G[i].nt)
		if (!d[v = G[i].v]) {
			dfs(v, x);
			sz[x] += sz[v];
			if (sz[v] > sz[son[x]])
				son[x] = v;
		}
}
inline void dgs(const int& x, const int& p) {
	l[x] = ++clk;
	top[x] = p;
	w[clk] = v[x];
	if (son[x])
		dgs(son[x], p);
	for (int v, i = h[x]; i; i = G[i].nt)
		if (!l[v = G[i].v])
			dgs(v, v);
	r[x] = clk;
}
inline void add(int y, LL v) {
	for (int x = l[y]; x <= n; x += x & -x) s[x] += v, sd[x] += v * d[y];
}
inline LL s1(int y, LL v = 0) {
	v = w[l[y]] - w[l[y] - 1];
	for (int x = l[y] - 1; x; x &= x - 1) v -= s[x];
	for (int x = r[y]; x; x &= x - 1) v += s[x];
	return v;
}
inline LL s2(int y, LL v = 0) {
	v = w[r[y]] - w[l[y] - 1];
	for (int x = l[y] - 1; x; x &= x - 1) v -= sd[x] - s[x] * (d[y] - 1);
	for (int x = r[y]; x; x &= x - 1) v += sd[x] - s[x] * (d[y] - 1);
	return v;
}
inline void lca(int& x, int& y) {
	for (; top[x] ^ top[y]; y = f[top[y]])
		if (d[top[x]] > d[top[y]])
			swap(x, y);
	if (d[x] > d[y])
		swap(x, y);
}
int main() {
	n = it, m = it;
	R = it;
	for (int i = 1; i <= n; ++i) v[i] = it;
	for (int x, y, i = 1; i < n; ++i) {
		x = it;
		y = it;
		G[++t] = (edge){ y, h[x] };
		h[x] = t;
		G[++t] = (edge){ x, h[y] };
		h[y] = t;
	}
	dfs(R, 0);
	dgs(R, R);
	for (int i = 1; i <= n; ++i) w[i] += w[i - 1];
	for (int o, x, y; m--;) {
		o = it;
		if (o == 1) {
			x = it;
			y = it;
			o = it;
			add(x, o);
			add(y, o);
			lca(x, y);
			add(x, -o);
			if (x ^ R)
				add(f[x], -o);
		} else if (o == 2)
			ot(s1(it));
		else
			ot(s2(it));
	}
}