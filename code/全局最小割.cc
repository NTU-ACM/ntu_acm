//???’s code
int StoerWagner(int n) {
	int i, j, k, s, t, p = n, min, cut = inf, dist[maxn];
	bool d[maxn], visit[maxn];
	memset(d, false, sizeof(d)); // merged or not
	while (--p > 0) {
		memset(visit, false, sizeof(visit)); // in S or not
		memset(dist, 0, sizeof(dist)); // sum of weights in/not in S
		for (i = 0; d[i]; ++i);
		visit[i] = true;
		for (j = 0; j < n; j++)
			if (!d[j] && !visit[j])
				dist[j] = g[j][i];
		t = i, s = i;
		for (; i < n; i++) {
			for (min = 0, k = i, j = 0; j < n; j++)
				if (!d[j] && !visit[j] && dist[j] > min)
					min = dist[k = j];
			if (!min) break;
			visit[k] = true;
			for (j = 0; j < n; j++)
				if (!d[j] && !visit[j])
					dist[j] += g[j][k];
			s = t; // last element
			t = k; // current element
		}
		if (cut > dist[t]) cut = dist[t];
		d[t] = true;
		for (i = 0; i < n; i++)
			if (!d[i]) {
				g[s][i] += g[t][i];
				g[i][s] += g[i][t];
			}
	}
	return cut;
}
