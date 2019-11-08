ll C(const ll &n, const ll &m, const int &pr) {
	ll ans = 1;
	for (int i = 1; i <= m; i++) {
		ll a = (n - m + i) % pr;
		ll b = i % pr;
		ans = (ans * (a * Inv(b, pr)) % pr) % pr;
	}
	return ans;
}