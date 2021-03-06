bool vis[maxn];
int prim[maxn];
int mu[maxn];
int cnt;

void get_mu(int n){
	mu[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			prim[++cnt]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=cnt && prim[j]*i<=n;j++){
			vis[prim[j]*i]=1;
			if(i%prim[j]==0) break;
			else mu[i*prim[j]]=-mu[i];
		}
	}
}