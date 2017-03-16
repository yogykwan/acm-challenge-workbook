/*
 * POJ 1631: Bridging signals
 * 题意：左右两套接口一对一连线，求最多有多少条线不相交。
 * 类型：DP+二分
 * 算法：d[i]表示当前已枚举的连线中保留i条不相交线时，右侧被连端口的最高点，d严格降序。每次二分查找d中第一个小于等于的右端口的位置并更新。
 */

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>  // lower_bound()

using namespace std;

int d[40010];

int main() {
  int T, n, i, j, t;
  scanf("%d", &T);
  while(T--){
    scanf("%d", &n);
    memset(d, -1, sizeof(d));
    for(i = 0; i < n; ++i) {
      scanf("%d", &t);
      t = n - t;
      *lower_bound(d, d + n, t, greater<int>()) = t;  // d[] <= t
    }
    int ans = int(lower_bound(d, d + n, -1, greater<int>()) - d);
    printf("%d\n", ans);
  }
  return 0;
}