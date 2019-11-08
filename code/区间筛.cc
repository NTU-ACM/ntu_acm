#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 1e5;
bool is_prime[MAXN];
bool is_prime_small[MAXN];
ll prime[MAXN];
ll prime_num = 0;

//对区间[a,b)内的整数执行筛法，is_prime[i-a]=true <=> 表示i是素数（下标偏移了a） 
void segment_sieve(ll a, ll b) {
	for (ll i = 0; i * i < b; i++) //对[2,sqrt(b))的初始化全为质数
		is_prime_small[i] = true;
	for (ll i = 0; i < b - a; i++) //对下标偏移后的[a,b)进行初始化
		is_prime[i] = true;
		
	for (ll i = 2; i * i < b; i++) { //筛选[2,sqrt(b))
		if (is_prime_small[i]) {
			for (ll j = 2 * i; j * j < b; j += i) 
				is_prime_small[j] = false;
			//(a+i-1)/i 得到最接近a的i的倍数，最低是i的2倍，然后筛选
			for (ll j = max(2LL, (a + i - 1) / i) * i; j < b; j += i)
				is_prime[j - a] = false;
		}
	}
	for (ll i = 0; i < b - a; i++) //统计个数 
		if (is_prime[i])
			prime[prime_num++] = i + a;
}

int main() {
	ll a, b;
	while (~scanf("%lld%lld", &a, &b)) {
		prime_num = 0;
		memset(prime, 0, sizeof(prime));
		segment_sieve(a, b);
		printf("%lld\n", prime_num);
	}
	return 0;
}