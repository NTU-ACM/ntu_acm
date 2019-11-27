#include<cstdio>

using int64=long long;
using uchar=unsigned char;

constexpr int Maxn(1000000);

namespace IOManager{
	constexpr int FILESZ(131072);
	char buf[FILESZ];
	const char*ibuf=buf,*tbuf=buf;

	struct IOManager{
		inline char gc()
			{return(ibuf==tbuf)&&(tbuf=(ibuf=buf)+fread(buf,1,FILESZ,stdin),ibuf==tbuf)?EOF:*ibuf++;}

		template<class _Tp>
			inline operator _Tp(){
				_Tp s=0u;char c=gc(),w=0;
				for(;c<48;c=gc())
					c==45&&(w=1);
				for(;c>47;c=gc())
					s=(_Tp)(s*10u+c-48u);
				return w?-s:s;
			}
	};
}IOManager::IOManager io;

struct Edge{
	int v;Edge*las;

	inline Edge* init(const int&to,Edge*const&ls)
		{return v=to,las=ls,this;}
}*las[Maxn+1];

inline void AddEdge(){
	static Edge pool[Maxn<<1],*alc=pool-1;
	const int u=io,v=io;
	las[u]=(++alc)->init(v,las[u]);
	las[v]=(++alc)->init(u,las[v]);
}

int idx,
	s[Maxn+1],
	t[Maxn+1],
	v[Maxn+1];
int64 bit[Maxn+1];

const int n=io;
inline void update(int i,const int&d){
	for(;i<=n;i+=i&-i)
		bit[i]+=d;
}
inline int64 sum(int i){
	int64 qs=0;
	for(;i;i-=i&-i)
		qs+=bit[i];
	return qs;
}

void calc(const int&now,const int&Fa){
	update(s[now]=++idx,v[now]);

	for(Edge*o=las[now];o;o=o->las)
		if(o->v!=Fa)
			calc(o->v,now);

	t[now]=idx;
}

int main(){
	int m=io;const int r=io;
	for(int i=1;i<=n;++i)
		v[i]=io;
	for(int i=1;i<n;++i)
		AddEdge();

	int a;
	for(calc(r,0);m;--m)
		if((int)io==1)
			a=io,update(s[a],(int)io);
		else
			a=io,printf("%lld\n",sum(t[a])-sum(s[a]-1));

	return 0;
}