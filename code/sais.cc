namespace SA {
	int sa[N], rk[N], ht[N], s[N<<1], t[N<<1], p[N], cnt[N], cur[N];
	#define pushS(x) sa[cur[s[x]]--] = x
	#define pushL(x) sa[cur[s[x]]++] = x
	#define inducedSort(v) std::fill_n(sa, n, -1); std::fill_n(cnt, m, 0);        \
		for (int i = 0; i < n; i++) cnt[s[i]]++;                                  \
		for (int i = 1; i < m; i++) cnt[i] += cnt[i-1];                           \
		for (int i = 0; i < m; i++) cur[i] = cnt[i]-1;                            \
		for (int i = n1-1; ~i; i--) pushS(v[i]);                                  \
		for (int i = 1; i < m; i++) cur[i] = cnt[i-1];                            \
		for (int i = 0; i < n; i++) if (sa[i] > 0 &&  t[sa[i]-1]) pushL(sa[i]-1); \
		for (int i = 0; i < m; i++) cur[i] = cnt[i]-1;                            \
		for (int i = n-1;  ~i; i--) if (sa[i] > 0 && !t[sa[i]-1]) pushS(sa[i]-1)
	void sais(int n, int m, int *s, int *t, int *p) {
		int n1 = t[n-1] = 0, ch = rk[0] = -1, *s1 = s+n;
		for (int i = n-2; ~i; i--) t[i] = s[i] == s[i+1] ? t[i+1] : s[i] > s[i+1];
		for (int i = 1; i < n; i++) rk[i] = t[i-1] && !t[i] ? (p[n1] = i, n1++) : -1;
		inducedSort(p);
		for (int i = 0, x, y; i < n; i++) if (~(x = rk[sa[i]])) {
			if (ch < 1 || p[x+1] - p[x] != p[y+1] - p[y]) ch++;
			else for (int j = p[x], k = p[y]; j <= p[x+1]; j++, k++)
				if ((s[j]<<1|t[j]) != (s[k]<<1|t[k])) {ch++; break;}
			s1[y = x] = ch;
		}
		if (ch+1 < n1) sais(n1, ch+1, s1, t+n, p+n1);
		else for (int i = 0; i < n1; i++) sa[s1[i]] = i;
		for (int i = 0; i < n1; i++) s1[i] = p[sa[i]];
		inducedSort(s1);
	}
	template<typename T>
	int mapCharToInt(int n, const T *str) {
		int m = *max_element(str, str+n);
		std::fill_n(rk, m+1, 0);
		for (int i = 0; i < n; i++) rk[str[i]] = 1;
		for (int i = 0; i < m; i++) rk[i+1] += rk[i];
		for (int i = 0; i < n; i++) s[i] = rk[str[i]] - 1;
		return rk[m];
	}
	// Ensure that str[n] is the unique lexicographically smallest character in str.
	template<typename T>
	void suffixArray(int n, const T *str) {
		int m = mapCharToInt(++n, str);
		sais(n, m, s, t, p);
		for (int i = 0; i < n; i++) rk[sa[i]] = i;
		for (int i = 0, h = ht[0] = 0; i < n-1; i++) {
			int j = sa[rk[i]-1];
			while (i+h < n && j+h < n && s[i+h] == s[j+h]) h++;
			if (ht[rk[i]] = h) h--;
		}
	}
};

//另一种写法
//from LOJ
//读入一个长度为n的由大小写英文字母或数字组成的字符串，请把这个字符串的所有非空后缀按字典序从小到大排序，然后按顺序输出后缀的第一个字符在原串中的位置。位置编号为1到n。
#include <cstdio>
#include <algorithm>
#include <numeric>
#include <cstring>

struct IO_Tp {
	const static int _O_Buffer_Size = 10 << 20;
	char _O_Buffer[_O_Buffer_Size], *_O_pos = _O_Buffer;

	~IO_Tp() { fwrite(_O_Buffer, 1, _O_pos - _O_Buffer, stdout); }

	IO_Tp &operator<<(int n) {
		static char _buf[10];
		char *_pos = _buf;
		do
			*_pos++ = '0' + n % 10;
		while (n /= 10);
		while (_pos != _buf) *_O_pos++ = *--_pos;
		return *this;
	}

	IO_Tp &operator<<(char ch) {
		*_O_pos++ = ch;
		return *this;
	}
} IO;

const int Max_N = 1000005;

namespace SA_IS {
int *sa;

template <typename _Char>
void sais_core(const int n, const int m, const _Char s[], char type[], int lms[], int cnt[]) {
	int n1 = 0, ch = -1;

	type[n - 1] = 1;
	for (int i = n - 2; i >= 0; --i) type[i] = s[i] == s[i + 1] ? type[i + 1] : s[i] < s[i + 1];

	std::fill(cnt, cnt + m, 0);
	for (int i = 0; i < n; ++i) ++cnt[static_cast<int>(s[i])];
	std::partial_sum(cnt, cnt + m, cnt);

	auto induced_sort = [&](const int v[]) {
		std::fill(sa, sa + n, 0);

		int *cur = cnt + m;
		auto push_S = [&](const int x) { sa[--cur[static_cast<int>(s[x])]] = x; };
		auto push_L = [&](const int x) { sa[cur[static_cast<int>(s[x])]++] = x; };

		std::copy(cnt, cnt + m, cur);
		for (int i = n1 - 1; i >= 0; --i) push_S(v[i]);

		std::copy(cnt, cnt + m - 1, cur + 1);
		for (int i = 0; i < n; ++i)
			if (sa[i] > 0 && type[sa[i] - 1] == 0)
				push_L(sa[i] - 1);

		std::copy(cnt, cnt + m, cur);
		for (int i = n - 1; i >= 0; --i)
			if (sa[i] > 0 && type[sa[i] - 1])
				push_S(sa[i] - 1);
	};

	for (int i = 1; i < n; ++i)
		if (type[i - 1] == 0 && type[i] == 1)
			type[i] = 2, lms[n1++] = i;
	induced_sort(lms);

	auto lms_equal = [&](int x, int y) {
		if (s[x] == s[y])
			while (s[++x] == s[++y] && type[x] == type[y])
				if (type[x] == 2 || type[y] == 2)
					return true;
		return false;
	};

	int *s1 = std::remove_if(sa, sa + n, [&](const int x) { return type[x] != 2; });
	for (int i = 0; i < n1; ++i) s1[sa[i] >> 1] = ch += ch <= 0 || !lms_equal(sa[i], sa[i - 1]);
	for (int i = 0; i < n1; ++i) s1[i] = s1[lms[i] >> 1];

	if (ch + 1 < n1)
		sais_core(n1, ch + 1, s1, type + n, lms + n1, cnt + m);
	else
		for (int i = 0; i < n1; ++i) sa[s1[i]] = i;

	for (int i = 0; i < n1; ++i) lms[n1 + i] = lms[sa[i]];
	induced_sort(lms + n1);
}

template <typename _Char>
void main(const _Char s[], const int n, const int m) {
	static int _lms[Max_N], _cnt[Max_N << 1];
	static char _type[Max_N << 1];
	sais_core(n + 1, m, s, _type, _lms, _cnt);
}
}  // namespace SA_IS

char s[Max_N];
int N;
int sa[Max_N];

int main(int argc, char **argv) {
	scanf("%s", s);
	N = strlen(s);

	SA_IS::sa = sa;
	SA_IS::main(s, N, 128);

	for (int i = 1; i <= N; ++i) IO << sa[i] + 1 << " \n"[i == N];

	return 0;
}