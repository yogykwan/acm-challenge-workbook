/*
 * POJ 3579: Median
 * 题意：给出n个数，两两相减取绝对值，求所有绝对值的中位数。
 * 类型：二分搜索
 * 算法：二分搜索假定一个中位数m，对已预先排好序的数组，遍历到某数i时，从i+1开始二分查找小于ai+m的个数，累加即为绝对值小于m的数对个数。若m在真实中位数之前更新下届，否则更新上界。
 */

#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

int a[100010];

int main() {
  int n;
  while (scanf("%d", &n) != EOF) {
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }
    sort(a, a + n);

    int l, r;
    l = 0;
    r = 2000000001;
    long long k = ((1ll * n * (n - 1) / 2) - 1) / 2;

    while (l + 1 < r) {
      int m = (1ll * l + r) >> 1;
      long long sm = 0, tmp;
      for (int i = 0; i < n - 1; ++i) {
        tmp = lower_bound(a + i + 1, a + n, a[i] + m) - (a + i + 1);
        sm += tmp;
      }
      if (sm <= k) {
        l = m;
      } else {
        r = m;
      }
    }
    printf("%d\n", l);
  }
  return 0;
}
