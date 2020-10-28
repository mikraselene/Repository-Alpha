#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;

bool cmp(int a, int b)
{
    return abs(a - b) <= 2;
}

int main()
{
    vector<int> a = {1, 14, 5, 1, 4, 1, 9, 1, 9, 8, 1, 0};
    a.insert(a.begin() + 1, 4);
    copy(a.begin(), a.end(), ostream_iterator<int>(cout, " "));
    string s = "helloolleh";
    vector<int> b = {1, 14, 15, 12, 19, 19, 8, 1, 0};
    vector<int> c = {1, 9, 1, 9};
    vector<int>::iterator adj = adjacent_find(b.begin(), b.end());
    bool binary = binary_search(a.begin(), a.end(), 1);
    int cnt = count(a.begin(), a.end(), 9);
    int cntif = count_if(a.begin(), a.end(), [](int i) { return i % 2 == 0; });
    bool equ = equal(s.begin(), s.end(), s.rbegin());

    vector<int>::iterator fd = find(a.begin(), a.end(), 5);
    vector<int>::iterator fde = find_end(a.begin(), a.end(), c.begin(), c.end());
    vector<int>::iterator fdfo = find_first_of(a.begin(), a.end(), c.begin(), c.end());
    vector<int>::iterator fdif = find_if(a.begin(), a.end(), [](int i) { return i % 2 == 0; });
    vector<int>::iterator sch = search(a.begin(), a.end(), c.begin(), c.end());
    vector<int>::iterator schn = search_n(b.begin(), b.end(), 2, 19);
    vector<int> mg;
    //merge(a.begin(), a.end(), b.begin(), b.end(), mg);

    pair<vector<int>::iterator, vector<int>::iterator> it = mismatch(a.begin(), a.end(), b.begin());
}
/*
   equal_range:             功能类似equal，返回一对iterator，第一个表示lower_bound，第二个表示upper_bound。
   lower_bound:             返回一个ForwardIterator，指向在有序序列范围内的可以插入指定值而不破坏容器顺序的第一个位置。重载函数使用自定义比较操作。
   upper_bound:             返回一个ForwardIterator，指向在有序序列范围内插入value而不破坏容器顺序的最后一个位置，该位置标志一个大于value的值。重载函数使用自定义比较操作。


   <二>排序和通用算法(14个)：提供元素排序策略
   inplace_merge:           合并两个有序序列，结果序列覆盖两端范围。重载版本使用输入的操作进行排序。

   nth_element:             将范围内的序列重新排序，使所有小于第n个元素的元素都出现在它前面，而大于它的都出现在后面。重载版本使用自定义的比较操作。
  
    partial_sort_copy:       与partial_sort类似，不过将经过排序的序列复制到另一个容器。
   partition:               对指定范围内元素重新排序，使用输入的函数，把结果为true的元素放在结果为false的元素之前。
   random_shuffle:           对指定范围内的元素随机调整次序。重载版本输入一个随机数产生操作。
   reverse:                 将指定范围内元素重新反序排序。
   reverse_copy:            与reverse类似，不过将结果写入另一个容器。
   rotate:                  将指定范围内元素移到容器末尾，由middle指向的元素成为容器第一个元素。
    rotate_copy:             与rotate类似，不过将结果写入另一个容器。
   stable_partition:         与partition类似，不过不保证保留容器中的相对顺序。

   <三>删除和替换算法(15个)
    copy:                    复制序列
   copy_backward:           与copy相同，不过元素是以相反顺序被拷贝。
   iter_swap:               交换两个ForwardIterator的值。
   remove:                  删除指定范围内所有等于指定元素的元素。注意，该函数不是真正删除函数。内置函数不适合使用remove和remove_if函数。
   remove_copy:             将所有不匹配元素复制到一个制定容器，返回OutputIterator指向被拷贝的末元素的下一个位置。
   remove_if:               删除指定范围内输入操作结果为true的所有元素。
   remove_copy_if:           将所有不匹配元素拷贝到一个指定容器。
   replace:                 将指定范围内所有等于vold的元素都用vnew代替。
    replace_copy:            与replace类似，不过将结果写入另一个容器。
   replace_if:              将指定范围内所有操作结果为true的元素用新值代替。
   replace_copy_if:          与replace_if，不过将结果写入另一个容器。
   swap:                    交换存储在两个对象中的值。
   swap_range:              将指定范围内的元素与另一个序列元素值进行交换。
   unique:                  清除序列中重复元素，和remove类似，它也不能真正删除元素。重载版本使用自定义比较操作。
   unique_copy:             与unique类似，不过把结果输出到另一个容器。



   <四>排列组合算法(2个)：提供计算给定集合按一定顺序的所有可能排列组合
   next_permutation:         取出当前范围内的排列，并重新排序为下一个排列。重载版本使用自定义的比较操作。
    prev_permutation:        取出指定范围内的序列并将它重新排序为上一个序列。如果不存在上一个序列则返回false。重载版本使用自定义的比较操作。



   <五>算术算法(4个)
   accumulate:              iterator对标识的序列段元素之和，加到一个由val指定的初始值上。重载版本不再做加法，而是传进来的二元操作符被应用到元素上。
   partial_sum:             创建一个新序列，其中每个元素值代表指定范围内该位置前所有元素之和。重载版本使用自定义操作代替加法。
   inner_product:           对两个序列做内积(对应元素相乘，再求和)并将内积加到一个输入的初始值上。重载版本使用用户定义的操作。
   adjacent_difference:      创建一个新序列，新序列中每个新值代表当前元素与上一个元素的差。重载版本用指定二元操作计算相邻元素的差。



   <六>生成和异变算法(6个)
   fill:                    将输入值赋给标志范围内的所有元素。
   fill_n:                  将输入值赋给first到first+n范围内的所有元素。
   for_each:                用指定函数依次对指定范围内所有元素进行迭代访问，返回所指定的函数类型。该函数不得修改序列中的元素。
   generate:                连续调用输入的函数来填充指定的范围。
   generate_n:              与generate函数类似，填充从指定iterator开始的n个元素。
   transform:               将输入的操作作用与指定范围内的每个元素，并产生一个新的序列。重载版本将操作作用在一对元素上，另外一个元素来自输入的另外一个序列。结果输出到指定容器。

   <七>关系算法(8个)
   equal:                   如果两个序列在标志范围内元素都相等，返回true。重载版本使用输入的操作符代替默认的等于操作符。
   includes:                判断第一个指定范围内的所有元素是否都被第二个范围包含，使用底层元素的<操作符，成功返回true。重载版本使用用户输入的函数。
   lexicographical_compare:  比较两个序列。重载版本使用用户自定义比较操作。


*/
