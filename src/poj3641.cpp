/*
 * POJ 3641: Pseudoprime numbers
 * 题意：给出a和p，判断p是否为合数，且满足a^p是否与a模p同余。
 * 类型：快速幂
 * 算法：筛法打1万的素数表预判p。再将幂指数的二进制形式表示，从右到左移位，每次底数自乘。
 */

#include <cstdio>

typedef long long LL;

int p[10010];
bool np[100010];
int cntp;

void SievePrime(int n) {
  LL t;
  for(int i = 2; i <= n; ++i) {
    if(!np[i]) p[cntp++] = i;
    for(int j = 0; j < cntp && (t = 1ll * i * p[j]) <= n; ++j) {
      np[t] = true;
      if(i % p[j] == 0) break;
    }
  }
}

LL Ksm(LL a, LL b, LL p) {
  LL ans = 1;
  while(b) {
    if(b & 1) {
      ans = (ans * a) % p;
    }
    a = (a * a) % p;
    b >>= 1;
  }
  return ans;
}

bool IsPrime(LL a) {
  if(a <= 100000) return !np[a];
  for(int i = 0; i < cntp; ++i) {
    if(a % p[i] == 0) return false;
  }
  return true;
}

int main() {
  SievePrime(100000);
  LL a, p;
  while(scanf("%lld%lld", &p, &a) != EOF && p) {
    if(IsPrime(p)) {
      printf("no\n");
    } else {
      printf("%s\n", Ksm(a, p, p) == a ? "yes" : "no");
    }
  }

  return 0;
}