//解决如下问题：定义母串s和子串T，设s的长度为n,T的长度为m,求T与S的每一个后缀的最长公共前缀
//extend[i]表示T与S[i,n-1]的最长公共前缀。（0<=i<n）
//一个辅助工具为nxt[i]表示T[i,m-1]和T的最长公共前缀长度
//下标都从0开始

O(n+m)

const int maxn=100010;   //字符串长度最大值
int nxt[maxn],ex[maxn]; //ex数组即为extend数组
//预处理计算next数组
void GETNEXT(char *str)
{
	int i=0,j,po,len=strlen(str);
	nxt[0]=len;//初始化next[0]
	while(str[i]==str[i+1]&&i+1<len)//计算next[1]
	i++;
	nxt[1]=i;
	po=1;//初始化po的位置
	for(i=2;i<len;i++)
	{
		if(nxt[i-po]+i<nxt[po]+po)//第一种情况，可以直接得到next[i]的值
		nxt[i]=nxt[i-po];
		else//第二种情况，要继续匹配才能得到next[i]的值
		{
			j=nxt[po]+po-i;
			if(j<0)j=0;//如果i>po+nxt[po],则要从头开始匹配
			while(i+j<len&&str[j]==str[j+i])//计算next[i]
			j++;
			nxt[i]=j;
			po=i;//更新po的位置
		}
	}
}
//计算extend数组
void EXKMP(char *s1,char *s2)
{
	int i=0,j,po,len=strlen(s1),l2=strlen(s2);
	GETNEXT(s2);//计算子串的next数组
	while(s1[i]==s2[i]&&i<l2&&i<len)//计算ex[0]
	i++;
	ex[0]=i;
	po=0;//初始化po的位置
	for(i=1;i<len;i++)
	{
		if(nxt[i-po]+i<ex[po]+po)//第一种情况，直接可以得到ex[i]的值
		ex[i]=nxt[i-po];
		else//第二种情况，要继续匹配才能得到ex[i]的值
		{
			j=ex[po]+po-i;
			if(j<0)j=0;//如果i>ex[po]+po则要从头开始匹配
			while(i+j<len&&j<l2&&s1[j+i]==s2[j])//计算ex[i]
			j++;
			ex[i]=j;
			po=i;//更新po的位置
		}
	}
}