//Author:CookiC
//返回下标最大的匹配串
#include <cstring>

void getFail(char *P, int *f) {
	int i, j;
	f[0] = 0;
	f[1] = 0;
	for(i=1; P[i]; ++i) {
		j = f[i];
		while(j && P[i]!=P[j]) {
			j = f[j];
		}
		f[i+1] = P[i]==P[j]? j+1: 0;
	}
}

int kmp(char *T, char *P) {
	int ans = -1;
	int n = strlen(T), m = strlen(P);
	int f[maxn];
	getFail(P, f);
	int j = 0;
	for(int i=0; i<n; ++i){
		while(j && P[j]!=T[i])
		j = f[j];
		if(P[j]==T[i]) {
			++j;
		}
		if(j==m) {
			j = f[j];
			ans = i-m+1;
		}
	}
	return ans;
}


/*
* Author: Simon * 复 杂 度: O(n) 
*/
int Next[maxn]; /*i之前相同前缀后缀的长度， 例ababc,Next[5]=2; */ 
void getNext(int m, char p[]) {
	memset(Next, 0, sizeof(int)*(m+5)); 
	int k=-1,j=0;
	Next[0]=-1;
	while (j<m) {
		if (k==-1||p[k]==p[j]) { 
		k++,j++;
		if (p[k]!=p[j]) Next[j]=k;
		else Next[j]=Next[k]; 
		}
		else k=Next[k]; 
	}
}

int KMP(int n,int m,char s[],char p[]){
	int i=0,j=0,ans=0; 
	while(i<n){
		if(j==-1||s[i]==p[j]) i++,j++;
		else j=Next[j];
		if(j==m) ans++; /*计 数 (可 重 叠)*/
		//if(j==m) ans++,j=0;/*计 数 ( 不 可 重 叠 )*/ 
		//if(j==m) return i-m+1; /*返回第一个匹配的位置 */
	}
	//return j;/*返回s后缀与p前缀匹配的最长长度 */
	return ans; 
}
