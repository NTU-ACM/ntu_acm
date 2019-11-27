//by UESTC_retared
从左边的未匹配点开始进行BFS，对于左边的点，依次检查所有向连的点并加入BFS（判断是否加过），右边的点只能走匹配边，然后对访问到的点进行标记，取左边没被标记的，右边标记了的如果一个图是二分图，那么它的最大独立集就是多项式时间可以解决的问题了 |最大独立集| = |V|-|最大匹配数|

二分图的最大团 = 补图的最大独立集

先做一次最大匹配 然后对于已经匹配的点 如果他存在与之相连 但是不是被匹配的点 那么他总是在最小覆盖集里面

1.给一张图，问有多少条边肯定在 MST 上？
 对所有边排序,每次扫出权值相同的边,然后跑tarjan_dcc(求割边),有多少条割边，表示对答案的贡献就是多少，之后将这些边的两边点进行缩点(并查集维护)
for(int i = 0 ; i < m ; ++ i) {
	int base = e[i].w;
	for(int j = i + 1 ; j < m ; ++ j){
					//扫描相同权值的边
					//进行tarjan_dcc算法
					//合并
	}
}

2.给一张图，问有多少条边可能在 MST 上？
 对所有边排序，每次新加入一条边之后，向后扫描所有相同权值的边，如果有边也可以合并两端，则打上标记
for(int i = 0 ; i < m ; ++ i) {
	if (find_set(e[i].u) == find_set(e[i].v) ) continue;
	int a1 = find_set(e[i].u) ,a2 = find_set(e[i].v);
	if (a1 > a2)
	swap(a1,a2);
	for(int j = i + 1 ; j < m ; ++ j) {
		if (e[j].w != e[i].w ) break;
		int b1 = find_set(e[j].u) , b2 =find_set(e[j].v);
		if (b1 > b2)
			 swap(b1,b2);
		if ( a1 == b1 && a2 == b2)
			flag[j] = 1;
	}
	union_set(e[i].u ,e[i].v);
	flag[i] = 1;
}

3.可以一次dfs用n^2的时间预处理出树上任意两点的某个属性，用dp做
dfs(int u) {
	 vis[u] = 1;
	 for(int i = head[u] ; ~i ; i =e[i].nxt) {
	 	int v = e[i].v;
		for(int j = 1 ; j <= n ; ++ j)
			if(vis[j])
				更新dp
	}
}