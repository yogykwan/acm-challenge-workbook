/*
 * POJ 3040; Allowance
 * 题意：有一些面值不同的硬币，排序后相邻两个的面值可以整除。每周需要支付定额的最低福利C，求这些硬币可以成功应付多少周。
 * 类型：贪心
 * 算法：求可行硬币组合的方法是，从大到小取不超过C的硬币组合，如果不够C，再从小到达取1枚超过C。求满足该组合的套数，再计算新的组合。
 */

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

pair <int, int> c[22];

int cnt[22];

int main() {
  int n, s, ans = 0;
  scanf("%d%d", &n, &s);
  for(int i = 0; i < n; ++i) {
    scanf("%d%d", &c[i].first , &c[i].second);
  }

  sort(c, c + n, greater<pair <int, int> > ());

  while(1) {
    int tmp = 100000000, ss = s;
    for(int i = 0; i < n && s > 0; ++i) {
      cnt[i] = min(c[i].second, ss / c[i].first);
      ss -= cnt[i] * c[i].first;
    }
    if(ss > 0) {
      for(int i = n - 1; i >= 0; --i) {
        if(c[i].second > cnt[i]) {
          ss -= c[i].first;
          cnt[i]++;
          break;
        }
      }
    }
    if(ss > 0) break;
    for(int i = 0; i < n; ++i) {
      if (cnt[i] > 0) {
        tmp = min(tmp, c[i].second / cnt[i]);
      }
    }
    ans += tmp;
    for(int i = 0; i < n; ++i) {
      if (cnt[i] > 0) {
        c[i].second -= tmp * cnt[i];
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}