using ll = long long;
const int maxn=60;

ll c[maxn][maxn];

void gaoC() {
	int i,j;
	for (i = 0; i < maxn; i++) {
		c[i][0] = c[i][i] = 1;
	}
	for (i = 1; i < maxn; i++) {
		for(j = 1; j <= i; j++) {
			c[i][j]=c[i-1][j]+c[i-1][j-1];
//			c[i][j] %= mod;
		}
	}
}