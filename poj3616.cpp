/*
 * POJ 3616: Milking Time
 * 题意：多个时间区间，每个区间包含一个价值，选中的任意两个区间间相隔至少R。求最大价值。
 * 类型：DP
 * 算法：将区间按终点排序后，对于每个区间，得到以该区间结尾的最大价值，可以从它之前相距至少R的区间转移。
 */


#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

struct Cow{
  int s, t, e;
  bool operator < (const Cow& c) const {
    return t < c.t;
  }
}c[1010];

int d[1010];

int main() {
  int n, m, r;
  scanf("%d%d%d", &m, &n, &r);
  for(int i = 0; i < n; ++i) {
    scanf("%d%d%d", &c[i].s, &c[i].t, &c[i].e);
  }
  sort(c, c + n);

  for(int i = 0; i < n; ++i) {
    if(c[i].t > m) {
      n = i;
      break;
    }
    d[i] = 0;
    for(int j = i - 1; j >= 0; --j) {
      if(c[i].s - c[j].t >= r) {
        d[i] = max(d[i], d[j]);
      }
    }
    d[i] += c[i].e;
  }

  int ans = 0;
  for(int i = 0; i < n; ++i) {
    ans = max(ans, d[i]);
  }

  printf("%d\n", ans);

  return 0;
}