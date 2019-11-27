def PrimeInit():
	IsPrime = [True] * maxn
	Prime = []
	for i in range(2, maxn):
		if IsPrime[i]:
			Prime.append(i)
			for j in range(i * i, maxn, i):
				IsPrime[j] = False;
	return Prime