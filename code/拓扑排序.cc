#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

std::vector<int> g[maxn];
int du[maxn], n, m, l[maxn];

bool topsort() {
	std::fill(du, du+maxn, 0);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < g[i].size(); j++) {
			du[g[i][j]]++;
		}
	}
	int tot = 0;
	std::queue<int> q;
	for(int i = 0; i < n; i++) {
		if(!du[i]) {
			q.push(i);
		}
	}
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		l[tot++] = x;
		for(int j = 0; j < g[x].size(); j++) {
			int t = g[x][j];
			du[t]--;
			if(!du[t]) {
				q.push(t);
			}
		}
	}
	if(tot == n) {
		return 1;
	}
	return 0;
}