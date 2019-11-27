//by UESTC_retared
#include <ext/pb_ds/priority_queue.hpp>
__gnu_pbds::priority_queue < int > Q;
优先队列，配对堆默认，从小到大!

__gnu_pbds::priority_queue < int , greater < int > , pairing_heap_tag  > Q;
__gnu_pbds::priority_queue < int , greater < int > , pairing_heap_tag  > :: point_iterator id[ maxn ];
id[x] = Q.push( 5 ) ;
Q.modify( id[x] , 6) ; //直接修改

支持join , push , pop操作

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> rbt;
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> :: iterator it ;

find_by_order(size_type order)
找第order+1小的元素的迭代器

order_of_key(int val)
问有多少个比val小


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>

__gnu_pbds::gp_hash_table < key , value > hs;
哈希
支持[]和find操作