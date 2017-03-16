/*
 * POJ 3666: Making the Grade
 * 题意：给出一个数列，要求把它变成单调非增或单调非减，代价是数列中每个数改变量的绝对值求和，求最小代价。
 * 类型：DP
 * 算法：拷贝数列并排序，d[i][j]表示前i个数变成单调非减数列，并以不大于排序中第j大数的数结尾时的最小代价。单调非增类似，滚动数组降维。
 */


#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int a[2010], b[2010];
long long up[2010], down[2010];

int main() {
  int n, i, j;
  long long ans;
  scanf("%d", &n);
  for(i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  memcpy(b, a, n * sizeof(int));
  sort(b, b + n);
  for(i = 0; i < n; ++i) {
    for(j = 0; j < n; ++j) {  // ai -> bj
      up[j] += abs(a[i] - b[j]);
      down[j] += abs(a[i] - b[j]);
//      printf("%d-%d: %lld %lld\n", i, j, up[j], down[j]);
    }
    for(j = 1; j < n; ++j) {
      up[j] = min(up[j], up[j - 1]);
    }
    for(j = n - 2; j >= 0; --j) {
      down[j] = min(down[j], down[j + 1]);
    }
  }
  ans = min(up[n - 1], down[0]);
  printf("%lld\n", ans);
  return 0;
}

