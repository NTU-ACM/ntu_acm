#include <iostream>
#include <cstdio>

using uchar=unsigned char;

constexpr int Maxn(1000000);

namespace IOManager{
	constexpr int FILESZ(131072);
	char buf[FILESZ];
	const char*ibuf=buf,*tbuf=buf;
	struct IOManager{
		inline char gc() {
			return (ibuf==tbuf) && (tbuf=(ibuf=buf)+fread(buf,1,FILESZ,stdin),ibuf==tbuf) ? EOF : *ibuf++;
		}

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

int main(int argc, char *argv[]) {  
	int n;
	n = io;
}