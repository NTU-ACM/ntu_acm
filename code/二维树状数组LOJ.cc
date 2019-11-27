//区间加 区间求和
#pragma once
#include<cstdio>
#define LL long long
#define R register int
const int N=2050;
int n,m,T,a,b,c,d,e,f;LL C[N][N][4];
inline void in(int &x){
	x=f=0;char c=getchar();
	while(c<'0'||c>'9')f|=c=='-',c=getchar();
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;
}
void add(int x,int y,int z){
	R i=x,j;
	while(i<=n){
		j=y;
		while(j<=m)C[i][j][0]+=z,C[i][j][1]+=z*x, C[i][j][2]+=z*y,C[i][j][3]+=z*x*y,j+=j&(-j);
		i+=i&(-i);
	}
}
LL ask_matrix(int x,int y){
	LL ans=0;
	R i=x,j;
	while(i){
		j=y;
		while(j)ans+=(x+1)*(y+1)*C[i][j][0]-(y+1) * C[i][j][1]-(x+1) * C[i][j][2] + C[i][j][3], j-=j&(-j);
		i-=i&(-i);
	}
	return ans;
}
int main(){
	in(n),in(m);
	while(scanf("%d",&a)>0){
		in(b),in(c),in(d),in(e);
		if(a==1)in(a), add(b,c,a), add(b,e+1,-a), add(d+1,c,-a), add(d+1,e+1,a);
		else --b,--c,printf("%lld\n",ask_matrix(d,e)-ask_matrix(d,c) - ask_matrix(b,e)+ask_matrix(b,c));
	}
}