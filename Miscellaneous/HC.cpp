#include <iostream>
#include <fstream>
#include <stdio.h>
#define N 1270
#define K 1200
#define G 70
//#define HAIMING
using namespace std;
int len[N];
int i_2_r(int a) //求一个2^n次方的数的幂
{
	int count = 0;
	if (a == 1)
		return 0;
	while (a > 1)
	{
		a = a / 2;
		count++;
	}
	return count;
}
void in_to_Group(int a[], int b, int n) //添加到各组中
{
	int i;
	for (i = 1; i <= n; i++)
		if (a[i] == -1)
			a[i] = b;
}
int _2_r_gt_k_r(int k, int r) //判断 2^r >= k+r+1
{
	int i, s = 1;
	for (i = 1; i <= r; i++)
		s = 2 * s;
	if (s >= k + r + 1)
		return 1;
	else
		return 0;
}
int is_i_2_r(int i) //判断 i 是否为 2^n 位
{
	if (i == 1)
		return 1;
	if (i % 2 != 0)
		return 0;
	while (i % 2 == 0 && i != 1)
		i = i / 2;
	if (i == 1)
		return 1;
	return 0;
}
int int_to_invdec(int a[], int n) //求一个整数的逆序的二进制码
{
	int i = 1; //以计算校验位号
	while (n)
	{
		a[i++] = n % 2;
		n /= 2;
	}
	return i - 1; //返回位数
}
int count1(int a[], int n) //计算 1 的个数
{
	int i, count = 0;
	for (i = 1; i <= n; i++)
		if (a[i] == 1)
			count++;
	if (count % 2 == 0)
		return 1;
	return 0;
}
int main()
{
#ifdef HAIMING
	freopen("海明码.txt", "r", stdin);
#endif
	int infor[N], i, k, r, findr = 1;
	int group[G][K], g, j; // group 用于分组检测 1 的个数
	int a[N], a_l;
	printf("\n输入有效信息位位数 k(0=<k<=1200):");
	scanf("%d", &k);
	i = 2;
	while (findr) //找所需检测位数 r 的值
	{
		r = i;
		if (_2_r_gt_k_r(k, r))
			findr = 0;
		i++;
	}
	printf("\n需添加 %d 位检测位.\n", r);
	printf("\n输入信息码:\n");
	for (i = 1; i <= k + r; i++)
	{
		infor[i] = -1;
		if (!is_i_2_r(i))
			scanf("%d", &infor[i]);
	}
	printf("\n");
	for (i = 1; i <= r; i++)
		for (j = 1; j <= k; j++)
			group[i][j] = -1; //***初始化各组为 -1 表示空信息
	for (i = 1; i <= k; i++)
		len[i] = 0; //***初始化各组元素个数为 0
	printf("海明码(偶校验)为:\n");
	for (i = 1; i <= k + r; i++) //!!!*从添加检测位后的第 1 位开始进行分组 ( 关键 )
	{
		a_l = int_to_invdec(a, i); //**将位号转化为逆序的二进制数存入数组 a[] 中,返回数组长度
		for (g = 1; g <= r; g++)   //共分为 r 组
			for (j = 1; j <= a_l; j++)
				if (a[j] == 1)	//**查转化后 a[] 中为 1 的下标位(如为1则分给第1组,为2则分给第二组等等)
					if (g == j) //若分组号与下标位相同,
					{
						in_to_Group(group[g], infor[i], len[g]); //**将该信息码添加到第 g 小组中
						len[g]++;								 //*第 g 小组长度增 1
						break;
					}
	}
	for (i = 1; i <= k + r; i++) //******检测各小组中 1 的个数
	{
		if (is_i_2_r(i) && count1(group[i_2_r(i) + 1], len[i_2_r(i) + 1]))	//如果位号为2^n位即检测位
			infor[i] = 0;													//***且该小组中 1 的个数为偶数,则该检测位上添为 0 用以校验
		if (is_i_2_r(i) && !count1(group[i_2_r(i) + 1], len[i_2_r(i) + 1])) //如果位号为2^n位即检测位
			infor[i] = 1;													//***且该小组中 1 的个数为奇数,则该检测位上添为 1 用以校验
	}
	for (i = 1; i <= k + r; i++)
		cout << infor[i] << ""; //输出编写好的海明码
	printf("\n");
}