#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define ll long long
#define re register
#define gc get_char
#define cs const

namespace IO{
	inline char get_char(){
		static cs int Rlen=1<<20|1;
		static char buf[Rlen],*p1,*p2;
		return (p1==p2)&&(p2=(p1=buf)+fread(buf,1,Rlen,stdin),p1==p2)?EOF:*p1++;
	}
	
	inline int getint(){
		re char c;
		while(!isdigit(c=gc()));re int num=c^48;
		while(isdigit(c=gc()))num=(num+(num<<2)<<1)+(c^48);
		return num;
	}
}
using namespace IO;

using std::cerr;
using std::cout;

cs int N=1203;
cs int INF=0x3f3f3f3f;
int n,m;
struct edge{
	int to,cap,rev;
	edge(cs int &_to,cs int &_cap,cs int &_rev):to(_to),cap(_cap),rev(_rev){}
};

std::vector<edge> G[N];
inline void addedge(int u,int v,int val){
	G[u].push_back(edge(v,val,G[v].size()));
	G[v].push_back(edge(u,0,G[u].size()-1));
} 

std::vector<int> lst[N],gap[N];
int rest[N];
int ht,h[N],cnt[N],work;
int S,T;

inline void upd_h(int v,int nh){
	++work;
	if(h[v]!=INF)--cnt[h[v]];
	h[v]=nh;
	if(nh==INF)return ;
	++cnt[nh],ht=nh;
	gap[nh].push_back(v);
	if(rest[v])lst[nh].push_back(v);
}

inline void relabel(){
	work=0;
	memset(h,0x3f,sizeof h);
	memset(cnt,0,sizeof cnt);
	for(int re i=0;i<=ht;++i)lst[i].clear(),gap[i].clear();
	h[T]=0;
	std::queue<int> q;q.push(T);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(edge &e:G[u])if(h[e.to]==INF&&G[e.to][e.rev].cap)
		q.push(e.to),upd_h(e.to,h[u]+1);
		ht=h[u];
	} 
}

inline void push(int u,edge &e){
	if(rest[e.to]==0)lst[h[e.to]].push_back(e.to);
	int delta=std::min(rest[u],e.cap);
	e.cap-=delta;
	G[e.to][e.rev].cap+=delta;
	rest[u]-=delta;
	rest[e.to]+=delta;
}

inline void push_flow(int u){
	int nh=INF;
	for(edge &e:G[u])if(e.cap){
		if(h[u]==h[e.to]+1){
			push(u,e);
			if(rest[u]<=0)return ;
		}
		else nh=std::min(nh,h[e.to]+1);
	}
	if(cnt[h[u]]>1)upd_h(u,nh);
	else for(int re i=h[u];i<N;++i){
		for(int j:gap[i])upd_h(j,INF);
		gap[i].clear();
	}
}

inline int HLPP(int lim=20000){
	memset(rest,0,sizeof rest);
	rest[S]=2147483647;//,rest[T]=-INF;
	relabel();
	for(edge &e:G[S])push(S,e);
	for(;~ht;--ht)
	while(!lst[ht].empty()){
		int u=lst[ht].back();
		lst[ht].pop_back();
		push_flow(u);
		if(work>lim)
		relabel();
	}
	return rest[T];
}

signed main(){
//	freopen("test.in","r",stdin);
	n=getint(),m=getint();
	S=getint(),T=getint();
	for(int re i=1,u,v,val;i<=m;++i){
		u=getint(),v=getint(),val=getint();
		addedge(u,v,val);
	}
	cout<<HLPP()<<"\n";
	return 0;
}