/*
 * POJ 2566: Bound Found
 * 题意：给出一个可正可负的系列和一个非负目标值，求一段和的绝对值最接近目标值的子序列。
 * 类型：尺取法
 * 算法：求累加和后排序，尺取法控制递增的左右端点，使得累加和相减最接近目标值。
 */

#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

typedef pair<int, int> pii;

pii s[100010];

inline int ABS(int x) {
  if (x >= 0) return x;
  return -x;
}

int main() {
  int n, k, a;
  while (scanf("%d%d", &n, &k) != EOF && n) {
    s[0].first = 0;
    s[0].second = 0;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &a);
      s[i].first = s[i - 1].first + a;
      s[i].second = i;
    }
    sort(s, s + n + 1);
    while (k--) {
      int t, tmp;
      int ans, p, q;
      ans = 2000000001;
      scanf("%d", &t);

      int i = 0, j = 1;
      while (i < j && j <= n) {
        tmp = s[j].first - s[i].first;
        if (ABS(tmp - t) < ABS(ans - t)) {
          ans = tmp;
          p = i;
          q = j;
        }

        if (tmp == t) { // two pointers
          break;
        } else if (tmp > t) {
          ++i;
          if (i == j) ++j;
        } else if (tmp < t) {
          ++j;
        }
      }
      p = s[p].second;
      q = s[q].second;
      printf("%d %d %d\n", ans, min(p, q) + 1, max(p, q));
    }
  }
  return 0;
}