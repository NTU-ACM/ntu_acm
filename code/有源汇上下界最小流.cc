#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
#define ll long long
static char buf[100000],*pa,*pd;
#define gc pa==pd&&(pd=(pa=buf)+fread(buf,1,100000,stdin),pa==pd)?EOF:*pa++
inline int read(){
 	register int x(0);register char c(gc);
	while(c>'9'||c<'0')c=gc;
	while(c>='0'&&c<='9')x=x*10+c-48,c=gc;
	return x;
} 
const int N=510000;
const ll INF=987654321987654321;
struct edge{
 	int to,next;
	ll w;
}e[N];
int head[51000],vis[51000],tot=1,deep[110000];
void add(int x,int y,ll z){
 	e[++tot].next=head[x];e[tot].to=y;e[tot].w=z;head[x]=tot;
	e[++tot].next=head[y];e[tot].to=x;e[tot].w=0;head[y]=tot;
} 
ll out[N],sum,ans;
queue<int> q;
int n,m,s,t,S=0,T=51000-1;
bool BFS(){
	memset(deep,-1,sizeof(deep));
 	deep[S]=0;
	q.push(S);
	while(!q.empty()){
	 	int u=q.front();q.pop();
	//	cout<<u<<' '<<deep[u]<<'\n';
		for(int i=head[u];i;i=e[i].next)
			if(deep[e[i].to]<0&&e[i].w){
			 	deep[e[i].to]=deep[u]+1;
				q.push(e[i].to);
			} 
	}
	//cout<<deep[T]<<'\n';
	return deep[T]>0;
} 
ll DFS(int u,ll MIN){
 	int a=0,b;
	if(u==T||!MIN)return MIN;
	for(int &i=vis[u];i;i=e[i].next)
		if(e[i].w&&deep[e[i].to]==deep[u]+1&&(b=DFS(e[i].to,min(MIN,e[i].w)))){
		 	a+=b;
			e[i].w-=b;
			MIN-=b;
			e[i^1].w+=b;
			if(!MIN)break;
		} 
	if(!a)deep[u]=-1;
	return a;
} 
int main(){
//	freopen("1.in","r",stdin);
	n=read();m=read();s=read();t=read();
	register int i,x,y,a,b;
	for(i=1;i<=m;i++){
	 	x=read();y=read();a=read();b=read();
		add(x,y,b-a);
		out[x]+=a;
		out[y]-=a;
	} 
	for(i=1;i<=n;i++){
		//cout<<i<<' '<<out[i]<<'\n';
	 	if(out[i]>0)add(i,T,out[i]),sum+=out[i];
		if(out[i]<=0)add(S,i,-out[i]);
	}
	//cout<<ans<<'\n';
	while(BFS()){
		//cout<<ans;
		memcpy(vis,head,sizeof(vis));
	 	ans+=DFS(S,INF);
	} 
	add(t,s,INF);
	while(BFS()){
		memcpy(vis,head,sizeof(vis));
	 	ans+=DFS(S,INF);
	}
	//cout<<ans<<' '<<sum<<'\n';
	if(ans!=sum){
	 	cout<<"please go home to sleep";
		return 0;
	} 
	cout<<e[tot].w;
 	return 0;
} 