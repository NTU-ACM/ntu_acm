std::unique(v.begin(), v.end()); 
//去重
//比较相邻元素 一样的放到后面 用前一般先排序
//返回去重完毕的下一个iterator

std::stable_sort(v.begin(), v.end(), cmp);
//stable_sort 和 sort的区别在于 前者作排序可以使原来的"相同"的值在序列中的相对位置不变

std::sort(iter_begin, iter_end, std::greater<int>());
//从大到小排序