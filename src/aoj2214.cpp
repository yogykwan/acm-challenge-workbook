/*
 * AOJ 2214: Warp Hall
 * 题意：从(1,1)要到终点(m,n)。每次向右或向上走，但一旦遇到虫洞起点，会直接到达右上方的虫洞终点。问有多少种路线。
 * 类型：计数DP
 * 算法：对于虫洞i(ai,bi)到(ci,di)，(1,1)到(ai,bi)的路线数为di，则对于以虫洞构成的矩形为中心，向上和向右发散的L区，都要去掉di。将虫洞排序，DP求到达到每个虫洞入口的方案数。
 */


#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const LL MOD = 1000000007ll;

inline LL add(LL a, LL b) { return (a + b) % MOD; }

inline LL sub(LL a, LL b) { return (a - b + MOD) % MOD; }

inline LL mul(LL a, LL b) { return a * b % MOD; }

LL f[200010];

LL Inverse(LL a, LL p = MOD) {
  if (a == 1) return 1;
  return sub(0, mul(p / a, Inverse(p % a, p)));
}

LL C(LL a, LL b) {
  return mul(mul(f[a], Inverse(f[b])), Inverse(f[a - b]));
}

struct Warp {
  int sx, sy, tx, ty;

  bool operator<(const Warp &w) const {
    if (sx != w.sx) return sx < w.sx;
    return sy < w.sy;
  }
} w[1010];

LL d[1010];
int m, n, k;

LL Gao(LL sx, LL sy, LL tx, LL ty) {
  if (sx > tx || sy > ty) return 0;
  return C(tx - sx + ty - sy, tx - sx);
}

int main() {
  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  f[0] = 1;
  for (LL i = 1; i <= 200000; ++i) {
    f[i] = mul(f[i - 1], i);
  }
  while (scanf("%d%d%d", &m, &n, &k) != EOF && m + n + k > 0) {
    for (int i = 0; i < k; ++i) {
      scanf("%d%d%d%d", &w[i].sx, &w[i].sy, &w[i].tx, &w[i].ty);
      --w[i].sx;
      --w[i].sy;
      --w[i].tx;
      --w[i].ty;
    }
    memset(d, 0, sizeof(d));
    sort(w, w + k);
    w[k].sx = m - 1;
    w[k].sy = n - 1;
    for (int i = 0; i <= k; ++i) {
      d[i] = C(w[i].sx + w[i].sy, w[i].sx);
      for (int j = 0; j < i; ++j) {
        d[i] = add(d[i],
                   mul(d[j],
                       sub(Gao(w[j].tx, w[j].ty, w[i].sx, w[i].sy),
                           Gao(w[j].sx, w[j].sy, w[i].sx, w[i].sy))));
      }
    }
    printf("%lld\n", d[k]);
  }

  return 0;
}
