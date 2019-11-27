//1插入 2删除 3排名 4k大 5前驱 6后继
#include <cstdio>
#include <algorithm>
#define N 100005
using namespace std;
struct io_t{
	char p[1<<20],*s;
	char e[1<<20],*t;
	int a[24];
	io_t():s(p),t(e){
		fread(s,1,sizeof p,stdin);
	}
	~io_t(){
		fwrite(e,1,t-e,stdout);
	}
	operator int(){
		static int v,j;
		v=0,j=1;
		while(*s<48)
			j=*s++^45;
		do
			v=v*10+*s++-48;
		while(*s>32);
		return j?v:-v;
	}
	void print(int v){
		static int* q=a;
		if(!v)*t++=48;
		else{
			if(v<0)
				*t++=45,v*=-1;
			while(v)
				*q++=v%10+48,v/=10;
			while(q!=a)
				*t++=*--q;
		}
		*t++=10;
	}
}ip;
int f[N],a[N],u[N],v[N];
int m,z=ip;
int foo(int i){
	int j=1;
	for(--i;i;i^=i&-i)
		j+=a[i];
	return j;
}
void add(int i,int j){
	for(;i<=m;i+=i&-i)
		a[i]+=j;
}
int bar(int v){
	int s=0;
	for(int j=1<<16;j;j>>=1)
		if(s+j<=m&&v>a[s+j])
			v-=a[s+=j];
	return s;
}
int pre(int i){
	for(--i;;i^=i&-i)
		if(a[i]){
			int j=i&-i,s=i^j,v=a[i];
			for(;j;j>>=1)
				if(s+j<=m&&v>a[s+j])
					v-=a[s+=j];
			return s;
		}
}
int main(){
	for(int i=0;i!=z;++i){
		u[i]=ip,v[i]=ip;
		if(u[i]==1)
			f[m++]=v[i];
	}
	sort(f,f+m);
	m=unique(f,f+m)-f;
	for(int i=0;i!=z;++i){
		int k=u[i],s=v[i];
		if(k==6)
			s=upper_bound(f,f+m,s)-f;
		else if(k!=4)
			s=lower_bound(f,f+m,s)-f+1;
		if(k==1)
			add(s,1);
		if(k==2)
			add(s,-1);
		if(k==3)
			ip.print(foo(s));
		if(k==4)
			ip.print(f[bar(s)]);
		if(k==5)
			ip.print(f[pre(s)]);
		if(k==6)
			ip.print(f[bar(foo(s+1))]);
	}
}