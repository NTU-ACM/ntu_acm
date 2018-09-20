/**
 * top[v] 表示v所在的重链的顶端节点
 * fa[v] 表示v的父节点
 * deep[v] 表示v的深度(根的深度为1)
 * snum[v] 表示以v为根的子树的节点数
 * p[v] 表示v所在(线段树中)的位置
 * fp[v] 与p[v]相反，表示对应位置的节点
 * son[v] 表示v的重儿子
 * vector v 存树边
**/

int pos, n;	// n 为节点数
int top[maxn], fa[maxn], deep[maxn], num[maxn], p[maxn], fp[maxn], son[maxn];
vector<int> v[maxn];
void init() {
	pos = 1;
	memset(son, -1 ,sizeof(son));
	for (int i = 0; i <= n; i++)
		v[i].clear();
}
void dfs1(int u, int pre, int d) {
	deep[u] = d;
	fa[u] = pre;
	num[u] = 1;
	for (int i = 0; i <v[u].size(); i++) {
		int to = v[u][i];
		if (to != pre) {
			dfs1(to, u, d + 1);
			num[u] += num[to];
			if (son[u] == -1 || num[to] > num[son[u]])
				son[u] = to;
		}
	}
}
void dfs2(int u, int sp) {
	top[u] = sp;
	p[u] = pos++;
	fp[p[u]] = u;
	if (son[u] == -1) return;
	dfs2(son[u], sp);
	for (int i = 0; i <v[u].size(); i++) {
		int to = v[u][i];
		if (to != son[u] && to != fa[u])
			dfs2(to, to);
	}
}
/*
// 使用范例
int getsum(int a, int b) {
	int f1 = top[a], f2 = top[b];
	int ret = 0;
	while (f1 != f2) {
		if (deep[f1] < deep[f2]) {
			swap(f1, f2);
			swap(a, b);
		}
		ret += query(p[f1], p[a], 1, n - 1, 1);
		a = fa[f1]; f1 = top[a];
	}
	if (a == b) return ret;
	if (deep[a] > deep[b]) swap(a, b);
	return ret + query(p[son[a]], p[b], 1, n - 1, 1);
}
*/