//多组询问路径 最大边权最小
#include <cstdio>
#include <cstring>
#include <algorithm>
#define getchar() (*sS++)
#define Min(x,y) (fir[x]<fir[y]?x:y)
const int maxa=14;
const int maxm=1e5+3;
const int maxn=1e4+3;
struct Road{
	int to;
	int last;
}a[maxn];
struct Edge{
	int x,y;
	int dis;
	Edge(){}
	Edge(int a,int b,int c){x=a,y=b,dis=c;}
	bool operator <(const Edge&a)const{
		return dis<a.dis;
	}
}c[maxm];
int n, m, q, T, tot, num;
int bin[maxa], fir[maxn], Max[maxn], que[maxn], haha[maxn], head[maxn], pos[maxn<<1], f[maxn<<1][maxa];
char s[1<<21];
char *sS=s;
void Init();
void I(int&);
int Find(int);
void Dfs(int);
void Kruskal();
void HA(int,int);
int LCA(int,int);
int main(){
	fread(s,1,1<<21,stdin);
	I(n),I(m),I(q);
	for(register int i=1,x,y,z;i<=m;++i)
		I(x),I(y),I(z),c[i]=Edge(x,y,z);
	Kruskal();
	while(q--){
		register int x,y;I(x),I(y);
		if(Find(x)^Find(y))puts("-1");
		else printf("%d\n",Max[LCA(x,y)]);
	}return 0;
}
inline void I(int&x){
	register char ch;
	while(ch=getchar(),ch<'/');x=ch-'0';
	while(ch=getchar(),ch>'/')x=((x+(x<<2))<<1)+ch-'0';
}
inline void HA(int x,int y){
	a[++tot].to=y;
	a[tot].last=head[x];
	head[x]=tot;
}
inline int Find(int x){
	if(haha[x]==x)return x;
	return haha[x]=Find(haha[x]);
}
inline void Kruskal(){
	int k=0,num=n;
	std::sort(c+1,c+m+1);
	register int i,x,y;
	for(i=1;i<=n;++i)haha[i]=i;
	for(i=1;i<=m;++i){
		x=Find(c[i].x),y=Find(c[i].y);
		if(x==y)continue;
//		printf("%d %d\n",c[i].x,c[i].y);
		haha[x]=haha[y]=++num,haha[num]=num;
		Max[num]=c[i].dis,HA(num,x),HA(num,y);
		if((++k)==n-1)break;
	}
	for(i=num;i>n;--i)
		if(!fir[i])Dfs(i);
	Init();
}
#define y a[i].to
inline void Dfs(int x){
	fir[x]=++T,pos[T]=x;
	for(int i=head[x];i;i=a[i].last)
		Dfs(y),pos[++T]=x;
}
#undef y
inline void Init(){
	register int i,j;
	for(i=bin[0]=1;i<maxa;++i)bin[i]=bin[i-1]<<1;
	for(i=2,que[1]=0;i<=T;++i)que[i]=que[i>>1]+1;
	for(i=1;i<=T;++i)f[i][0]=pos[i];
	for(j=1;bin[j]<=T;++j)for(i=1;i+bin[j]-1<=T;++i)
		f[i][j]=Min(f[i][j-1],f[i+bin[j-1]][j-1]);
}
inline int LCA(int x,int y){
	x=fir[x],y=fir[y];
	if(x>y)std::swap(x,y);
	register int k=que[y-x+1];
	return Min(f[x][k],f[y-bin[k]+1][k]);
}