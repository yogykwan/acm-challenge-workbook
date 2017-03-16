/*
 * POJ 3262: Protecting the Flowers
 * 题意：每头牛牵回牛棚需要不同的时间，在回去前单位时间会破坏不同数量的草。求牵回最优策略下，最少破坏多少草。
 * 类型：贪心
 * 算法：利用冒泡的思想，考虑两两相邻的牛在t1d2>t2d1时需要交换，所以牛牵回顺序与t/d升序一致。
 */

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef pair<int, int> pii;

pii c[100010];

bool cmp(const pii a, const pii b) {
  return a.first * b.second < a.second * b.first;
}

int main() {
  int n, i;
  scanf("%d", &n);
  for(i = 0; i < n; ++i) {
    scanf("%d%d", &c[i].first, &c[i].second);
  }
  sort(c, c + n, cmp);
  long long ans = 0, t = 0;
  for(i = 0; i < n; ++i) {
    ans += t * c[i].second;
    t += 2 * c[i].first;
  }
  printf("%lld\n", ans);
  return 0;
}