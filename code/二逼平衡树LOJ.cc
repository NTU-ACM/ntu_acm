//1排名 2k大 3点修改 4前驱 5后继
/*All my love*/
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double D;
typedef pair<int,int> Pii;
template<class _T>inline void rd(_T&_a){int _ch,_f=0;
while(!isdigit(_ch=getchar()))_f=_ch=='-';_a=_ch-'0';
while(isdigit(_ch=getchar()))_a=_a*10+_ch-'0';if(_f)_a=-_a;}
template<class _T>inline _T dmin(const _T _a,const _T _b){ return _a<_b?_a:_b;}
template<class _T>inline _T dmax(const _T _a,const _T _b){ return _a>_b?_a:_b;}
template<class _T>inline bool cmin(_T&_a,const _T _b){ return _a>_b?_a=_b,1:0;}
template<class _T>inline bool cmax(_T&_a,const _T _b){ return _a<_b?_a=_b,1:0;}
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)
#define fir first
#define sec second
#define LC t[r0].l,l,m
#define RC t[r0].r,m+1,r
const int inf=0x3f3f3f3f;
const D eps=1e-8;
const int N=5e4+5;
struct tree{int l,r,sz;}t[N<<6];
int P,X,rt[N],rt0[N],lr[N],rr[N],lc,rc,idx,ct;
int b[N<<1],a[N],op[N],opl[N],opr[N],opx[N];
void U0(int&r1,int r0,int l,int r){
	t[r1=++idx]=t[r0];t[r1].sz++;
	if(l==r)return;
	int m=l+r>>1;
	if(P>m)U0(t[r1].r,RC);
	else U0(t[r1].l,LC);
}
void U1(int&r0,int l,int r){
	if(!r0)r0=++idx;t[r0].sz+=X;
	if(l==r)return;
	int m=l+r>>1;if(P>m)U1(RC);else U1(LC);
}
void Rt(int l,int r){
	lc=rc=0;lr[0]=rt0[l];rr[0]=rt0[r];
	for(;l;l^=(l&-l))lr[++lc]=rt[l];
	for(;r;r^=(r&-r))rr[++rc]=rt[r];
}
void Gl(){for(int i=0;i<=lc;i++)lr[i]=t[lr[i]].l; for(int i=0;i<=rc;i++)rr[i]=t[rr[i]].l;}
void Gr(){for(int i=0;i<=lc;i++)lr[i]=t[lr[i]].r; for(int i=0;i<=rc;i++)rr[i]=t[rr[i]].r;}
int Ls(){int r=0;for(int i=0;i<=lc;i++)r-=t[t[lr[i]].l].sz; for(int i=0;i<=rc;i++)r+=t[t[rr[i]].l].sz;return r;}
void Rk(){
	X=0;int l=1,r=ct;
	while(r>P){
		int m=l+r>>1;
		if(P>m)X+=Ls(),l=m+1,Gr();
		else r=m,Gl();
	}
	for(int i=0;i<=lc;i++)X-=t[lr[i]].sz;
	for(int i=0;i<=rc;i++)X+=t[rr[i]].sz;
}
void Qy(){
	int l=1,r=ct;
	while(l<r){
		int m=l+r>>1,tmp=Ls();
		if(tmp>=P)r=m,Gl();else l=m+1,P-=tmp,Gr();
	}
	X=l;
}
int main(){
	//freopen("test.in","r",stdin);
	//freopen("test.out","w",stdout);
	int n,m;rd(n);rd(m);
	for(int i=1;i<=n;i++)rd(a[i]),b[++ct]=a[i];
	for(int i=1;i<=m;i++){rd(op[i]);rd(opl[i]);
	rd(opr[i]);if(op[i]^3){rd(opx[i]);
	if(op[i]^2)b[++ct]=opx[i];}else b[++ct]=opr[i];}
	sort(b+1,b+ct+1);ct=unique(b+1,b+ct+1)-b-1;
	for(int i=1;i<=n;i++)
		P=a[i]=lower_bound(b+1,b+ct+1,a[i])-b, U0(rt0[i],rt0[i-1], 1, ct);
	for(int i=1;i<=m;i++){
		int l=opl[i],r=opr[i],x=opx[i];
		switch(op[i]){
			case 1:
				Rt(l-1,r);P=lower_bound(b+1,b+ct+1,x)-b-1;
				Rk();printf("%d\n",X+1);break;
			case 2:
				Rt(l-1,r);P=x;Qy();
				printf("%d\n",b[X]);break;
			case 3:
				P=a[l];X=-1;
				for(int p=l;p<=n;p+=(p&-p))U1(rt[p],1,ct);
				P=a[l]=lower_bound(b+1,b+ct+1,r)-b;X=1;
				for(int p=l;p<=n;p+=(p&-p))U1(rt[p],1,ct);break;
			case 4:
				Rt(l-1,r);P=lower_bound(b+1,b+ct+1,x)-b-1;
				Rk();P=X;Rt(l-1,r);Qy();
				printf("%d\n",b[X]);break;
			case 5:
				Rt(l-1,r);P=lower_bound(b+1,b+ct+1,x)-b;Rk();
				P=X+1;Rt(l-1,r);Qy();printf("%d\n",b[X]);break;
		}
	}
	return 0;
}
/*Said it don't*/