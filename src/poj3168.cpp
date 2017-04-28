/*
 * POJ 3168: Barn Expansion
 * 题意：给出平面若干个不重叠的矩形，求四边能向外扩展后仍不和其他矩形重叠的矩形有多少个。
 * 类型：扫描线
 * 算法：将矩形的x线按先x后y的升序排序，若2条x线可以连接上则两个两个矩形都不可扩展。y线按先y后x排序后同理。
 */

#include <cstdio>
#include <algorithm>

using namespace std;

struct Seg {
  Seg() {}

  Seg(int _x1, int _x2, int _y, int _id) : x1(_x1), x2(_x2), y(_y), id(_id) {}

  int x1, x2, y, id;

  bool operator<(const Seg &t) const {
    if (y != t.y) return y < t.y;
    return x1 < t.x1;
  }
};

Seg s[2][50010];

bool no[25010];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    s[0][i] = Seg(b, d, a, i);
    s[0][i + n] = Seg(b, d, c, i);
    s[1][i] = Seg(a, c, b, i);
    s[1][i + n] = Seg(a, c, d, i);
  }
  for (int t = 0; t < 2; ++t) {
    sort(s[t], s[t] + 2 * n);
    int y = -1, pre = -1;
    for (int i = 0; i < n << 1; ++i) {
      if (s[t][i].y != y) {
        y = s[t][i].y;
        pre = i;
      } else {
        if (s[t][i].x1 <= s[t][pre].x2) {
          no[s[t][i].id] = no[s[t][pre].id] = 1;
        }
        if (s[t][i].x2 > s[t][pre].x2) {
          pre = i;
        }
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (!no[i]) {
      ++ans;
    }
  }
  printf("%d\n", ans);
  return 0;
}
