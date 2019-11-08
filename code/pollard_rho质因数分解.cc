long long factor[100];//质因数分解结果（刚返回时是无序的）
int tol;//质因数的个数。数组小标从0开始

long long gcd(long long a,long long b)
{
	if(a==0)return 1;//???????
	if(a<0) return gcd(-a,b);
	while(b)
	{
		long long t=a%b;
		a=b;
		b=t;
	}
	return a;
}

long long Pollard_rho(long long x,long long c)
{
	long long i=1,k=2;
	long long x0=rand()%x;
	long long y=x0;
	while(1)
	{
		i++;
		x0=(mult_mod(x0,x0,x)+c)%x;
		long long d=gcd(y-x0,x);
		if(d!=1&&d!=x) return d;
		if(y==x0) return x;
		if(i==k){y=x0;k+=k;}
	}
}
//对n进行素因子分解
void findfac(long long n)
{
	if(Miller_Rabin(n))//素数
	{
		factor[tol++]=n;
		return;
	}
	long long p=n;
	while(p>=n)p=Pollard_rho(p,rand()%(n-1)+1);
	findfac(p);
	findfac(n/p);
}
int main()
{
   // srand(time(NULL));//需要time.h头文件  //POJ上G++要去掉这句话
	int T;
	long long n;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%I64d",&n);
		if(Miller_Rabin(n))
		{
			printf("Prime\n");
			continue;
		}
		tol=0;
		findfac(n);
		long long ans=factor[0];
		for(int i=1;i<tol;i++)
		  if(factor[i]<ans)
			 ans=factor[i];
		printf("%I64d\n",ans);
	}
	return 0;
}