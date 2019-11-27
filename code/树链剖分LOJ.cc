//换根
//路径加值
//子树加值
//路径求和
//子树求和
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#define ll long long
const int N = 101000;
int last[N],cnt;
int r,fa[N],n,m,d[N],size[N],ws[N],top[N],id[N],q[N],tot;
ll v[N],a[N];
ll sum[N][2];
struct edge{
	int next,to;
}e[N<<1];
void add(int x,ll v){
	for(int i=x;x<=n;x+=x&-x){
		sum[x][0]+=v,sum[x][1]+=v*i;
	}
}
ll ask(int x){
	ll ans=0;
	for(int i=x;x;x-=x&-x)
		ans+=sum[x][0]*(i+1)-sum[x][1];
	return ans;
}
void modify(int l,int r,ll v){
	add(l,v),add(r+1,-v);
}
ll query(int l,int r){
	return ask(r)-ask(l-1);
}
int read(){
	int x=0,fl=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')fl=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
	return x*fl;
}
void add(int a,int b){
	cnt++;e[cnt].next=last[a],last[a]=cnt;e[cnt].to=b;
}
void dfs(int x,int f){
	fa[x]=f,d[x]=d[f]+1;size[x]=1;
	for(int i=last[x];i;i=e[i].next){
		if(e[i].to==f) continue;
		dfs(e[i].to,x);
		if(size[e[i].to]>size[ws[x]])	ws[x]=e[i].to;
		size[x]+=size[e[i].to];
	}
}
void dfs2(int x,int topf){
	top[x]=topf;id[x]=++tot;q[tot]=x;
	modify(id[x],id[x],a[x]);
	if(ws[x]) dfs2(ws[x],topf);
	for(int i=last[x];i;i=e[i].next){
		if(e[i].to==fa[x]||e[i].to==ws[x]) continue;
		dfs2(e[i].to,e[i].to);
	}
}
int get_lca(int x,int y){
	while(top[x]!=top[y]){
		if(d[top[x]]<d[top[y]]) std::swap(x,y);
		x=fa[top[x]];
	}
	return d[x]>d[y]?y:x;
}
void Tmodify(int x,int y,ll v){
	while(top[x]!=top[y]){
		if(d[top[x]]<d[top[y]]) std::swap(x,y);
		modify(id[top[x]],id[x],v);
		x=fa[top[x]];
	}
	if(id[x]>id[y]) std::swap(x,y);
	modify(id[x],id[y],v);
}
ll Task(int x,int y){
	ll ans=0;
	while(top[x]!=top[y]){
		if(d[top[x]]<d[top[y]]) std::swap(x,y);
		ans+=query(id[top[x]],id[x]);
		x=fa[top[x]];
	}
	if(id[x]>id[y]) std::swap(x,y);
	ans+=query(id[x],id[y]);
	return ans;
}
int get_top(int x,int dth){
	while(dth+1<d[top[x]]) x=fa[top[x]];
	return q[id[top[x]]-(d[top[x]]-dth-1)];
}
int main(){
	n=read();r=1;
	for(int i=1;i<=n;++i)
		a[i]=read();
	for(int i=2;i<=n;++i){
		int a=read();add(a,i);
	}
	m=read();
	dfs(r,0);
	dfs2(r,r);
	while(m--){
		int opt=read();
		if(opt==1){
			r=read();
		}
		if(opt==2){
			int l=read(),r=read(),v=read();
			Tmodify(l,r,v);
		}
		if(opt==3){
			int x=read();
			ll v=read();
			if(x==r){
				modify(id[1],id[1]+size[1]-1,v);
			}
			else if(r!=x&&id[x]<=id[r]&&id[r]<=id[x]+size[x]-1){
				int ss=get_top(r,d[x]);
				modify(id[1],id[1]+size[1]-1,v);
				modify(id[ss],id[ss]+size[ss]-1,-v);
			}
			else{
				modify(id[x],id[x]+size[x]-1,v);
			}
		}
		if(opt==4){
			int l=read(),r=read();
			ll ans=Task(l,r);
			printf("%lld\n",ans);
		}
		if(opt==5){
			int x=read();
			if(x==r){
				ll ans=query(id[1],id[1]+size[1]-1);
				printf("%lld\n",ans);
			}
			else
			if(id[x]<=id[r]&&id[r]<=id[x]+size[x]-1){
				ll ans=0;
				int ss=get_top(r,d[x]);
				ans+=query(id[1],id[1]+size[1]-1);
				ans-=query(id[ss],id[ss]+size[ss]-1);
				printf("%lld\n",ans);
			}
			else{
				ll ans=query(id[x],id[x]+size[x]-1);
				printf("%lld\n",ans);
			}
		}
	}
}