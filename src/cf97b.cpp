/*
 * CF 97B: Superset
 * 题意：给出平面上n个不同的点，求该点集的一个超集，使得集合内任意两点：同x，或同y，或构成的矩形包含其他点。（Special Judge不要求添加点最少）
 * 类型：平面分治
 * 算法：将点集按x排序，选取中间点划竖线，将所有点投影到该线上，并添加到答案set里。此时被线分开的左右两边的点互相可以满足条件2或3，接下来需要使它们内部也能互相满足，则问题分治到左右两侧平面的子问题。
 */


#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

typedef pair<int, int> pii;

pii a[10010];
set<pii> b;

void divide(int l, int r) {
  if (l + 1 >= r) return;
  int m = (l + r) >> 1;
  int x = a[m].first;
  for (int i = l; i < r; ++i) {
    b.insert(make_pair(x, a[i].second));
  }
  divide(l, m);
  divide(m + 1, r);
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &a[i].first, &a[i].second);
    b.insert(a[i]);
  }
  sort(a, a + n);
  divide(0, n);
  printf("%d\n", int(b.size()));
  for (auto &i: b) {
    printf("%d %d\n", i.first, i.second);
  }
  return 0;
}
