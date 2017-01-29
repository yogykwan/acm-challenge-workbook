/*
 * POJ 3104: Drying
 * 题意：每件衣服含一定水，自然情况每分钟水量-1，如果使用熨斗每分钟-k。熨斗每分钟只能熨一件衣服，求干燥所有衣服总时间的最小值。
 * 类型：二分搜索+贪心
 * 算法：二分搜索，最小化时间最大值。计算每件衣服除给出的自然晾干时间外需要使用熨斗的次数，总次数不超过总时间则可更新上届。
 */

#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

long long a[100010];

int main() {
  int n, k;
  scanf("%d", &n);
  long long lv, rv, mv;
  lv = rv = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &a[i]);
    rv = max(rv, a[i]);
  }
  scanf("%d", &k);
  if(k >= 2) {
    while (lv + 1 < rv) {
      mv = (lv + rv) >> 1;
      long long cnt = 0;
      for(int i = 0; i < n; ++i) {
        if(a[i] > mv) {
          cnt += (a[i] - mv - 1) / (k - 1) + 1;
        }
      }
      if(cnt <= mv) {
        rv = mv;
      } else {
        lv = mv;
      }
    }
  }
  printf("%lld\n", rv);
  return 0;
}