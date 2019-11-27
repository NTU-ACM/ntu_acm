#include <unistd.h>
#include <sys/mman.h>
#include <cctype>
#include <algorithm>
#include <utility>
#include <iostream>
int N;
typedef long long LL;
namespace fast {
char *inP = static_cast<char *>(mmap(0, 3 << 24, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0)) - 1;
class istream {
public:
	inline istream &operator>>(int &RHS) {
		RHS = 0;
		bool neg = 0;
		while (std::isspace(*++inP))
			;
		if (*inP == '-')
			neg = 1, ++inP;
		do
			RHS = 10 * RHS + (*inP ^ 48);
		while (std::isdigit(*++inP));
		if (neg)
			RHS = -RHS;
		return *this;
	}
} in;
char pool[1 << 24], *outP = pool - 1;
class ostream {
public:
	inline ostream &operator<<(LL RHS) {
		if (RHS < 0)
			*++outP = '-', RHS = -RHS;
		char buf[13], *out = buf;
		do
			*out++ = RHS % 10 ^ 48;
		while (RHS /= 10);
		while (out > buf) *++outP = *--out;
		return *this;
	}
	inline ostream &operator<<(const char &RHS) {
		*++outP = RHS;
		return *this;
	}
	inline ~ostream() { std::cout.rdbuf()->sputn(pool, outP - pool + 1); }
} out;
}  // namespace fast
const int max = 1E6;
typedef int AI[max | 1];
AI v, idx;
std::pair<int, int> edge[max - 1 << 1 | 1];
inline void link(int u, int v) {
	static int cnt;
	edge[++cnt] = { v, idx[u] }, idx[u] = cnt;
}
AI in;
namespace BIT {
LL a[max | 1], b[max | 1];
inline void add(int pos, int val) {
	LL val_ = static_cast<LL>(val) * pos;
	while (pos <= N) {
		a[pos] += val, b[pos] += val_;
		pos += pos & -pos;
	}
}
inline LL query(int pos) {
	int pos_ = pos;
	LL resa = 0, resb = 0;
	while (pos) {
		resa += a[pos], resb += b[pos];
		pos &= pos - 1;
	}
	return (pos_ + 1) * resa - resb;
}
}  // namespace BIT
AI out;
void DFS(int cur, int fa) {
	static int clock;
	BIT::add(in[cur] = ++clock, v[cur]), BIT::add(clock + 1, -v[cur]);
	for (int i = idx[cur]; i; i = edge[i].second)
		if (edge[i].first != fa)
			DFS(edge[i].first, cur);
	out[cur] = clock;
}
main() {
	int M, R;
	fast::in >> N >> M >> R;
	std::for_each(v + 1, v + N + 1, [](int &v) { fast::in >> v; });
	for (int n = N; --n;) {
		int u, v;
		fast::in >> u >> v;
		link(u, v), link(v, u);
	}
	for (DFS(R, 0); M--;) {
		int op, a;
		fast::in >> op >> a;
		if (op == 1) {
			int x;
			fast::in >> x;
			BIT::add(in[a], x), BIT::add(out[a] + 1, -x);
		} else
			fast::out << BIT::query(out[a]) - BIT::query(in[a] - 1) << '\n';
	}
}