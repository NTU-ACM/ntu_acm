#include<bits/stdc++.h>
using namespace std;
const int N=210,M=20810,INF=1e9;
int sum[N],S,T,num=1,to[M],c[M],la[M],he[N],preflow[M],d[N],cur[N],maxflow;
queue<int>q;
int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch&15),ch=getchar();
	return x*f;
}
void addedge(int x,int y,int ca)
{
	to[++num]=y;c[num]=ca;la[num]=he[x];he[x]=num;
	to[++num]=x;c[num]=0;la[num]=he[y];he[y]=num;
}
bool BFS()
{
	memset(d,-1,sizeof(d));while (!q.empty()) q.pop();
	d[S]=1;q.push(S);
	while (!q.empty())
	{
		int u=q.front();q.pop();
		for (register int i=he[u];i;i=la[i])
		{
			int v=to[i];
			if (c[i]&&d[v]==-1)
			{
				d[v]=d[u]+1;q.push(v);
				if (v==T) return 1;
			}
		}
	}
	return 0;
}
int DFS(int u,int flow)
{
	if (u==T||!flow) return flow;
	int rest=flow;
	for (register int i=cur[u];i;i=la[i])
	{
		int v=to[i];cur[u]=i;
		if (c[i]&&d[u]+1==d[v])
		{
			int k=DFS(v,min(rest,c[i]));
			if (!k) {d[v]=-1;continue;}
			rest-=k;c[i]-=k;c[i^1]+=k;
			if (!rest) return flow;
		}
	}
	return flow-rest;
}
void Dinic()
{
	while (BFS())
	{
		memcpy(cur,he,sizeof(he));
		maxflow+=DFS(S,INF);
	}
}
int main()
{
	int n=read(),m=read();
	for (register int i=1;i<=m;++i)
	{
		int x=read(),y=read(),lower=read(),upper=read();
		sum[x]+=lower;sum[y]-=lower;addedge(x,y,upper-lower);preflow[i]=upper;
	}
	S=n+1;T=S+1;int sumflow=0;
	for (register int i=1;i<=n;++i) if (sum[i]>0) addedge(i,T,sum[i]),sumflow+=sum[i]; else addedge(S,i,-sum[i]);
	Dinic();
	if (maxflow<sumflow) {printf("NO\n");return 0;}
	printf("YES\n");
	for (register int i=1;i<=m;++i) printf("%d\n",preflow[i]-c[i<<1]);
	return 0;
}