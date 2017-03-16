/*
 * POJ 3176: Cow Bowling
 * 题意：若干个数摆成三角，每次可以从上一层移动到下一层最近的两个点，求自顶向下的路径和最大值。
 * 类型：DP
 * 算法：滚动数组保存到达每个点的最大和，每个点由上方相邻两点转移。
 */

#include <cstdio>
#include <iostream>

using namespace std;

int d[400];
int a[400];

int main() {
  int n, i, j;
  scanf("%d", &n);
  for(i = 0; i < n; ++i) {
    for(j = 0; j <= i; ++j) {
      scanf("%d", &a[j]);
    }
    if(i > 0) {
      d[i] = d[i - 1] + a[i];
    }
    for(j = i - 1; j > 0; --j) {
      d[j] = max(d[j], d[j - 1]) + a[j];
    }
    d[0] += a[0];
  }
  int ans = 0;
  for(i = 0; i < n; ++i) {
    ans = max(ans, d[i]);
  }
  printf("%d\n", ans);
  return 0;
}