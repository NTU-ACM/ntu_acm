/*
RMQģ�壺
AΪԭʼ���飬d[i][j]��ʾ��i��ʼ������Ϊ(1<<j)��������Сֵ
*/

int A[maxn];
int d[maxn][30];

void init(int A[], int len) {
	for (int i = 0; i < len; i++)d[i][0] = A[i];
	for (int j = 1; (1 << j) <= len; j++) {
		for (int i = 0; i + (1 << j) - 1 < len; i++) {
			d[i][j] = min(d[i][j - 1], d[i + (1 << (j - 1))][j - 1]);
		}
	}
}

int query(int l, int r) {
	int p = 0;
	while ((1 << (p + 1)) <= r - l + 1)p++;
	return min(d[l][p], d[r - (1 << p) + 1][p]);
}

int main()
{
	init(A, n);
	cout << query(0, n - 1);
	return 0;
}