#include <bits/stdc++.h>
#define ll long long
#define N 200010
using namespace std;
ll read() {
	ll x=0,f=1; char ch=getchar();
	for (;ch<'0'||ch>'9';ch=getchar()) if (ch=='-') f=-1;
	for (;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
	return x*f;
}
struct node {int a,b,c,id,f,ans;} a[N],b[N],t[N];
int n,m,n0,sum[N],ans[N],cnt[N];
bool operator<(node a,node b) {
	return a.a==b.a?(a.b==b.b?a.c<b.c:a.b<b.b):a.a<b.a;
}
int lowbit(int x) {return x&-x;}
void update(int x,int k) {for (;x<=m;x+=lowbit(x)) sum[x]+=k;}
int query(int x) {
	int ret=0; for (;x;x-=lowbit(x)) ret+=sum[x]; return ret;
}
void cdq(int l,int r) {
	if (l==r) return;
	int mid=(l+r)>>1;
	cdq(l,mid),cdq(mid+1,r);
	int i=l,j=mid+1,k=l;
	while (i<=mid&&j<=r) {
		if (a[i].b<=a[j].b) update(a[i].c,a[i].f),t[k++]=a[i++];
		else a[j].ans+=query(a[j].c),t[k++]=a[j++];
	}
	while (i<=mid) update(a[i].c,a[i].f),t[k++]=a[i++];
	while (j<=r) a[j].ans+=query(a[j].c),t[k++]=a[j++];
	for (int _=l;_<=mid;_++) update(a[_].c,-a[_].f);
	for (int _=l;_<=r;_++) a[_]=t[_];
}
int main() {
	n=read(),m=read();
	for (int i=1;i<=n;i++) {
		int x=read(),y=read(),z=read();
		b[i]=(node){x,y,z,0,0,0};
	}
	sort(b+1,b+n+1);
	for (int i=1,t=0;i<=n;i++) {
		++t;
		if (b[i].a!=b[i+1].a||b[i].b!=b[i+1].b||b[i].c!=b[i+1].c) {
			a[++n0]=b[i],a[n0].id=n0,a[n0].f=t,t=0;
		}
	}
	cdq(1,n0);
	for (int i=1;i<=n0;i++) cnt[a[i].ans+a[i].f-1]+=a[i].f;
	for (int i=0;i<n;i++) printf("%d\n",cnt[i]);
	return 0;
}