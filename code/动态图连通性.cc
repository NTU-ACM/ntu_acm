#include"bits/stdc++.h"

using namespace std;

namespace io{
	const int L=(1<<20)+1;
	char _buf[L],*S,*T,c;
	#define gc (S==T ? T=(S=_buf)+fread(_buf,1,L,stdin), *S++ : *S++)
	void gi(int&x){
		for(c=gc;c<'0'||c>'9';c=gc); x=c&15;
		for(c=gc;c>='0'&&c<='9';c=gc) x=x*10+(c&15);
	}
	char obuf[L],*op=obuf,*end=obuf+(L-1);
	void writechar(char x){
		*op++=x;
		if(op==end)fwrite(obuf,1,L-1,stdout),op=obuf;
	}
	void cbuf(){
		fwrite(obuf,1,op-obuf,stdout),op=obuf;
	}
};
using io::gi;
using io::writechar;

#define pb push_back
#define mfy(x,y) (va[++sk]=x,*(stk[sk]=&x)=y)
const int N=1050005,M=25000005,L=500005,A=5005,D=33554435;

vector<int>E[N];
int n,m,l=1,d,lm,x,y;
int _O[L],u[L],tu[N],tv[N],sk,va[M],fa[A],sz[A],lst[D],au[N],av[N];
bool exi[N];

int find(int x){return fa[x]==x?x:find(fa[x]);}
void addedge(int s,int t,int ins){
	int q,p;
	while(s<=t){
		q=min(31-__builtin_clz(t-s+1), __builtin_ctz(s-1));
		if(exi[p=s+l-1>>q])E[p].pb(ins);
		s+=1<<q;
	}
}
void addtag(int p){for(p+=l-1,au[p]=x,av[p]=y;p;p>>=1)exi[p]=true;}

void solve(int x,int l,int r){
	if(!exi[x])return;
	int mid=(l+r)>>1,ls=x<<1,rs=ls|1,k=sk,fu,fv;
	for(auto e:E[x]){
		fu=find(e>>d),fv=find(e&lm);
		if(fu!=fv){
			if(sz[fu]<sz[fv]) swap(fu,fv);
			tu[++sk]=fu,tv[sk]=fv,fa[fv]=fu,sz[fu]+=sz[fv];
		}
	}
	if(l==r){
		writechar(find(au[x])==find(av[x])?'Y':'N');
		writechar('\n');
		return;
	}
	solve(ls,l,mid),solve(rs,mid+1,r);
	while(sk!=k){
		fa[tv[sk]]=tv[sk];
		sz[tu[sk]]-=sz[tv[sk]];
		sk--;
	}
}

int main(){
	gi(n),gi(m);
	int i,o,j;
	while(l<m)l<<=1;
	while(n>>d)d++;lm=(1<<d)-1;
	for(i=1;i<=n;i++)fa[i]=i,sz[i]=1;
	for(i=1;i<=m;i++){
		gi(o),gi(x),gi(y);
		if(x>y)swap(x,y);
		_O[i]=o;u[i]=x<<d|y;
		if(o==2)addtag(i);
	}
	for(i=1;i<=m;i++){
		j=u[i];
		if(_O[i]==0)lst[j]=i;
		if(_O[i]==1)addedge(lst[j],i,j),lst[j]=0;
	}
	for(i=1;i<=m;i++)if(lst[j=u[i]]==i)addedge(lst[j],l,j);
	solve(1,1,l);
	io::cbuf();
	cerr<<clock()<<endl; 
	return 0;
}