/*
 * POJ 2429: GCD & LCM Inverse
 * 题意：给出两个正数的最大公约数和最小公倍数，求满足条件的数对中和最小的。
 * 类型：因式分解
 * 算法：筛法打1万内素数表，求两数相异部分lcm/gcd，用Pollard Rho质因数分解。分解时，小因子用素数表判断，大数用Miller Rabin强伪素数测试。最多20种素因子，二进制枚举得到两数。
 */

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstdlib>

using namespace std;

typedef long long LL;
const int MAXN = 100000;

int prime[MAXN >> 2];
int cntp;
bool np[MAXN + 10];
LL p[30];
int a[30];

void SievePrime(int maxn) {
  int i, j;
  LL temp;
  for (i = 2; i <= maxn; ++i) {
    if (!np[i]) prime[cntp++] = i;
    for (j = 0; j < cntp && (temp = 1LL * i * prime[j]) <= maxn; ++j) {
      np[temp] = 1;
      if (i % prime[j] == 0) break;
    }
  }
}

LL power(LL a, int b) {
  LL ans = 1;
  while (b) {
    if (b & 1) ans *= a;
    a *= a;
    b >>= 1;
  }
  return ans;
}

LL mul(LL a, LL b, LL p) {
  a = (a % p + p) % p;
  b = (b % p + p) % p;
  LL ans = 0;
  while(b) {
    if(b & 1) ans = (ans + a) %p;
    a = (a << 1) % p;
    b >>= 1;
  }
  return ans;
}

LL ksm(LL a, LL b, LL p) {
  LL ans = 1;
  while(b) {
    if(b & 1) ans = mul(ans, a, p);
    a = mul(a, a, p);
    b >>= 1;
  }
  return ans;
}

LL gcd(LL a, LL b) {
  LL t;
  while(b) {
    t = a % b;
    a = b;
    b = t;
  }
  return a;
}

bool MillerRabin(LL n) {
  int i, S = 10;
  if (n == 2) return true;
  if (n < 2 || !(n & 1)) return false;
  LL a, x, y, u = n - 1;
  int t = 0;
  while ((u & 1) == 0) t++, u >>= 1;
  for (i = 0; i < S; i++) {
    a = rand() % (n - 1) + 1;
    x = ksm(a, u, n);
    for (int j = 1; j <= t; j++) {
      y = mul(x, x, n);
      if (y == 1 && x != 1 && x != n - 1) return false;
      x = y;
    }
    if (x != 1) return false;
  }
  return true;
}

bool IsPrime(LL n) {
  if(n <= MAXN) return !np[n];
  return MillerRabin(n);
}

void PollarRho(LL n, LL *p, int &cnt) {
  if (IsPrime(n)) {
    p[cnt++] = n;
    return;
  }
  LL x, y, z, c, d;
  int i, j;
  while(true) {
    x = rand() * rand() % (n - 1) + 1;
    c = rand() * rand() % (n - 1) + 1;
    for (y = x, i = j = 2;; i++) {
      x = (mul(x, x, n) + c) % n;
      z = x - y;
      if (z < 0) z = -z;
      d = gcd(z, n);
      if (d > 1 && d < n) {
        PollarRho(d, p, cnt);
        PollarRho(n / d, p, cnt);
        return;
      }
      if (x == y) break;
      if (i == j) y = x, j <<= 1;
    }
  }
}

int main() {
  SievePrime(MAXN);
  LL l, g, ta, ans, tmp, n, ansa;
  while(scanf("%lld%lld", &g, & l) != EOF) {
    if(g == l) {
      printf("%lld %lld\n", g, l);
      continue;
    }

    n = l / g;
    int cnt = 0;
    PollarRho(n, p, cnt);

    sort(p, p + cnt);

    int tot = 1;
    a[0] = 1;
    for(int i = 1; i < cnt; ++i) {
      if(p[i] == p[i - 1]) {
        ++a[tot - 1];
      } else {
        p[tot] = p[i];
        a[tot] = 1;
        ++tot;
      }
    }

    for(int i = 0; i < tot; ++i) {
      p[i] = power(p[i], a[i]);
    }

    ans = l;
    for(int i = (1 << (tot - 1)) - 1; i >= 0; --i) {
      ta = 1;
      int ti = i;
      for(int j = 0; j < tot - 1 && ti > 0; ++j) {
        if(ti & 1) {
          ta *= p[j];
        }
        ti >>= 1;
      }

      tmp = ta + n / ta;
      if(tmp < ans) {
        ans = tmp;
        ansa = ta;
      }
    }

    ansa = min(ansa, ans - ansa);
    printf("%lld %lld\n", g * ansa, g * (ans - ansa));
  }
  return 0;
}