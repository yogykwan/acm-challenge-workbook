/*
 * POJ 3708: Recurrent Function
 * 题意：定义f(j)=aj(j<d), f(d*n+j)=d*f(n)+bj，a和b分别是[1,d)和(0,d)的集合。给出m和k，求对m最少进行多少次f操作可以得到k。
 * 类型：大数+线性同余
 * 算法：将m转化为d进制S(n)S(n-1)...S(0)，则f(m)的d进制为a[S(n)]b[S(n-1)]...b[S(0)]。针对每一位找a和b中的循环节和相差步数。由于不互素不能直接中国剩余定理，可两两合并利用扩展扩展欧几里得求解。
 */

#include <cstdio>
#include <cstring>


char m[110], k[110];
int a[110], b[110];
int mm[350], kk[350];
int lm, lk;
int loop[350], dist[350];

bool Zero(int *s, int n) {
  for (int i = 0; i < n; ++i) {
    if (s[i]) return false;
  }
  return true;
}

int s[110];
void TenToD(int d, char *m, int *mm, int &lm) {
  lm = 0;
  int n = (int)strlen(m);
  for (int i = 0; i < n; ++i) {
    s[i] = m[i] - '0';
  }
  while (!Zero(s, n)) {
    int r = 0;
    for (int i = 0; i < n; ++i) {
      s[i] += r * 10;
      r = s[i] % d;
      s[i] /= d;
    }
    mm[lm++] = r;
  }
}


int dep[110];
int GaoLoop(int p, int *a) {
  memset(dep, 0, sizeof(dep));
  dep[mm[p]] = 1;
  int cur;
  cur = a[mm[p]];
  int step = 1;
  while (!dep[cur]) {
    dep[cur] = ++step;
    cur = a[cur];
  }
  dist[p] = dep[kk[p]] - dep[mm[p]];
  loop[p] = step - dep[cur] + 1;
  return dep[kk[p]];
}

typedef long long LL;

LL ExtGcd(LL a, LL b, LL &x, LL &y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  }
  LL d = ExtGcd(b, a % b, y, x);
  y -= a / b  *x;
  return d;
}


LL LC(int n) {
  LL d, r;
  d = loop[0];
  r = dist[0];
  for (int i = 1; i < n; ++i) {
    LL x, y;
    LL g = ExtGcd(d, loop[i] , x, y);
    if ((dist[i] - r) % g) {
      return -1;
    }
    x *= (dist[i] - r) / g;
    LL t = loop[i] / g;
    x = (x % t + t) % t;
    r += d * x;
    d *= t;
    r = (r % d + d) % d;
  }
  return r;
}

int main() {
  //freopen("/home/yogy/CLionProjects/acm-challenge-workbook/d.in", "r", stdin);
  int d;
  while (scanf("%d", &d) != EOF && d != -1) {
    LL ans;
    for (int i = 1;i < d; ++i) scanf("%d", &a[i]);
    for (int i = 0; i < d; ++i) scanf("%d", &b[i]);
    scanf("%s%s", m, k);
    TenToD(d, m, mm, lm);
    TenToD(d, k, kk, lk);
    if (lm != lk) {
      printf("NO\n");
      continue;
    }
    if (GaoLoop(lm - 1, a) == 0) {
      printf("NO\n");
      continue;
    }
    for (int i = 0; i < lm - 1; ++i) {
      if (GaoLoop(i, b) == 0) {
        printf("NO\n");
        goto L;
      }
    }
    ans = LC(lm);
    if (ans == -1) printf("NO\n");
    else printf("%lld\n", ans);
    L:;
  }
  return 0;
}
