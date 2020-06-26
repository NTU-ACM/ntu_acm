d[0] = inf;
d[n+1] = inf;
for (int i = n; i >= 1; i--) {
	if (d[i+1] > d[i]) {
		arrow[i] = i+1;
	} else {
		arrow[i] = arrow[i+1];
		while (d[arrow[i]] <= d[i]) {
			arrow[i] = arrow[arrow[i]];
		}
	}
}