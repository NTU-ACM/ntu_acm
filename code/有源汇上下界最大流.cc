#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

template <typename T>void read(T &t)
{
	t=0;int f=0;char c=getchar();
	while(!isdigit(c)){f|=c=='-';c=getchar();}
	while(isdigit(c)){t=t*10+c-'0';c=getchar();}
	if(f)t=-t;
}

const ll inf=0x3f3f3f3f3f3f3f3f;
const int maxn=202+5,maxm=9999+5;
int n,m,s,t;
int ss,tt;

struct edge
{
	int u,v,nxt;
	ll f;
}g[maxm<<2];

int head[maxn],ecnt=1;
void eADD(int u,int v,ll f)
{
	g[++ecnt].u=u;g[ecnt].v=v;g[ecnt].f=f;g[ecnt].nxt=head[u];head[u]=ecnt;
	g[++ecnt].u=v;g[ecnt].v=u;g[ecnt].f=0;g[ecnt].nxt=head[v];head[v]=ecnt;
}

ll A[maxn];

int dep[maxn],cur[maxn];
bool BFS()
{
	queue<int> q;
	for(register int i=1;i<=n;++i)
		dep[i]=0,cur[i]=head[i];
	dep[ss]=dep[tt]=0,cur[ss]=head[ss],cur[tt]=head[tt];
	dep[ss]=1;
	q.push(ss);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(register int i=head[u];i;i=g[i].nxt)
		{
			int v=g[i].v;
			if(!dep[v] && g[i].f)
			{
				dep[v]=dep[u]+1;
				if(v==tt)return true;
				q.push(v);
			}
		}
	}
	return false;
}

ll dfs(int u,ll infl)
{
	if(u==tt)return infl;
	ll rest=infl;
	for(register int i=cur[u];i && rest;i=g[i].nxt)
	{
		int v=g[i].v;
		cur[u]=i;
		if(g[i].f && dep[v]==dep[u]+1)
		{
			ll flow=dfs(v,min(rest,g[i].f));
			rest-=flow;
			g[i].f-=flow;
			g[i^1].f+=flow;
		}
	}
	return infl-rest;
}

int main()
{
	read(n),read(m),read(s),read(t);
	ss=n+1,tt=n+2;
	for(register int i=1;i<=m;++i)
	{
		int u,v;
		ll up,low;
		read(u),read(v),read(low),read(up);
		eADD(u,v,up-low);
		A[u]-=low;
		A[v]+=low;
	}
	eADD(t,s,inf);
	ll tot=0;
	for(register int i=1;i<=n;++i)
		if(A[i]<0)
			eADD(i,tt,-A[i]);
		else if(A[i]>0)
			eADD(ss,i,A[i]),tot+=A[i];
	ll ans=0;
	while(BFS())
		ans+=dfs(ss,inf);
	if(ans<tot)
	{
		puts("please go home to sleep");
		return 0;
	}
	ans=0;
	ss=s,tt=t;
	while(BFS())
		ans+=dfs(ss,inf);
	printf("%lld",ans);
	return 0;
}