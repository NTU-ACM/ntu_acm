using ll = long long;

ll PowMod(ll a, ll b, const ll &Mod) { 
	a %= Mod;
	ll ans = 1; 
	while(b) {
		if (b & 1){
			ans = (ans * a) % Mod; 
		} 
		a = (a * a) % Mod;
		b >>= 1;
	}
	return ans; 
}

ll Inv(ll a, ll n){ 
	return PowMod(a,n-2,n);
}

//可能是错的...
ll C(const ll &n, const ll &m, const int &pr) {
	ll ans = 1;
	for (int i = 1; i <= m; i++) {
		ll a = (n - m + i) % pr;
		ll b = i % pr;
		ans = (ans * (a * Inv(b, pr)) % pr) % pr;
	}
	return ans;
}