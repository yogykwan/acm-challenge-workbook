/*
 * POJ 2886: Who Gets the Most Candies?
 * 题意：n个孩子围成一圈，每个人手上有个数字。先选择一个孩子出局，根据他手上的数字选择下一个孩子，以此类推。第k轮出局的人获得k的因子个数的糖果，求获得最多的孩子及糖果数。
 * 类型：二分+树状数组（／线段树）
 * 算法：预处理打表n内的因子数。若已经出局k人，他手上数字是x，则先将x%(n-k)得到单圈内转移的人数。二分下一个孩子的序号，树状数组得到他们间剩余孩子数和模数相比，得到最小等于模数的序号。
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;



int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);

  return 0;
}
