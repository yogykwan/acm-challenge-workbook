/*
 * POJ 2976: K Bests
 * 题意：给出每件首饰的价值和重量，选取k个使总价值除以总重量最大，求选取方案。
 * 类型：二分搜索+贪心
 * 算法：二分搜索最大的单位价值，有E(v)/E(w)>=m，将成绩按vi-wj*m排序，取最大的k个相加看是否能大于等于0使得前式被满足。
 */

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

typedef long long LL;
typedef pair<double, int> pdi;

const double EPS = 1e-7;

LL a[100010], b[100010];
double c[100010];

vector<pdi> d;

int main() {
  int n, k;
  while (scanf("%d%d", &n, &k) != EOF) {
    d.clear();
    for (int i = 0; i < n; ++i) {
      scanf("%lld%lld", &a[i], &b[i]);
    }
    double l, r, m;
    l = 0.0;
    r = 1000000.0;
    while (r - l > EPS) {
      m = (l + r) / 2;
      for (int i = 0; i < n; ++i) {
        c[i] = a[i] - m * b[i];
      }
      sort(c, c + n);
      double tmp = 0;
      for(int i = n - k; i < n; ++i) {
        tmp += c[i];
      }
      if(tmp > -EPS) {
        l = m;
      } else {
        r = m;
      }
    }

    for (int i = 0; i < n; ++i) {
      c[i] = a[i] - m * b[i];
      d.push_back(make_pair(c[i], i));
    }
    sort(d.begin(), d.end());

    bool first = true;
    for(int i = n - k; i < n; ++i) {
      if(first) first = false;
      else printf(" ");
      printf("%d", d[i].second + 1);
    }
    printf("\n");
  }
  return 0;
}