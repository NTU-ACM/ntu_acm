#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 1e6 + 10;
int nx[maxn][30];
string s;
 
void init() {
	int len = s.length();
	for(int i = 0; i < 26; i ++)
		nx[len][i] = nx[len + 1][i] = len + 1;
	for(int i = len - 1; i >= 1; i --) {
		for(int j = 0; j < 26; j ++)
			nx[i - 1][j] = nx[i][j];
		nx[i - 1][s[i] - 'a'] = i;
	}
}
 
int main() {
	cin >> s;
	init();
	int Q;
	scanf("%d", &Q);
	while(Q --) {
		string t;
		cin >> t;
		bool flag = true;
		int lt = t.length();
		int st = 0;
		for(int i = 0; i < lt; i ++) {
			st = nx[st][t[i] - 'a'];
			if(st == 0) {
				flag = false;
				break;
			}
		}
 
		if(flag) printf("YES\n");
		else printf("NO\n");
 
	}
	return 0;
}