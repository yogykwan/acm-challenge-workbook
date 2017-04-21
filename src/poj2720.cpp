/*
 * POJ 2720: Last Digits
 * 题意：求b^b^b^...的最后n位。
 * 类型：费马小定理+快速幂
 * 算法：预处理不超过7位的数打表。因为当b>phi(c)，a^b%c=a^(b%phi(c)+phi(c))%c，递归并用快速幂求解。
 */

#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

map<int, int> phi;

bool np[3000];
int prime[1000];
int cntp;

int ta[110][110];
int ans[110][110];
int ten[8];

void SievePrime(int n = 3000) {
  for (int i = 2; i < n; ++i) {
    if (!np[i]) {
      prime[cntp++] = i;
    }
    int t;
    for (int j = 0; j < cntp && (t = i * prime[j]) < n; ++j) {
      np[t] = 1;
      if (i % prime[j]) break;
    }
  }
}


int Euler(int x) {
  if (x == 1) return 0;
  int ret = x;
  for (int i = 0; i < cntp && x > 1; ++i) {
    if (x % prime[i] == 0) {
      ret /= prime[i];
      ret *= prime[i] - 1;
    }
    while (x % prime[i] == 0) {
      x /= prime[i];
    }
  }
  if (x > 1) {
    ret /= x;
    ret *= x - 1;
  }
  return ret;
}

int Ksm(long long a, int b, int mod) {
  if (b == 0) return 1;
  long long ans = 1ll;
  while (b) {
    if (b & 1) {
      ans = (ans * a) % mod;
    }
    a = (a * a) % mod;
    b >>=1;
  }
  return (int)ans;
}

int Gao(int b, int m, int mod) {
  if (m == 0) {
    return 1;
  }
  if (mod == 1) {
    return 0;
  }
  if (ta[b][m] != -1) {
    return ta[b][m] % mod;
  } else {
    return Ksm(b, Gao(b, m - 1, phi[mod]) + phi[mod], mod);
  }
}


int main() {
  SievePrime();
  memset(ans, -1, sizeof(ans));
  ten[0] = 1;
  for (int i = 1; i <= 7; ++i) ten[i] = ten[i-1] * 10;

  int t = ten[7];
  while (t) {
    phi[t] = Euler(t);
    t = phi[t];
  }

  memset(ta, -1, sizeof(ta));
  for (int i = 1; i <= 100; ++i) {
    ta[i][0] =1;
    for (int j = 1; j <= 100; ++j) {
      int x = 1;
      for (int k = 0; k < ta[i][j - 1]; ++k) {
        x *= i;
        if (x >= ten[7]) break;
      }
      if (x >= ten[7]) break;
      ta[i][j] = x;
    }
  }

  int b, m, n;
  while (scanf("%d", &b) != EOF && b) {
    scanf("%d%d", &m, &n);
    int ret;
    if (ans[b][m] != -1) {
      ret = ans[b][m];
    } else {
      ret = ans[b][m] = Gao(b, m, ten[7]);
    }
    ret %= ten[n];
    t = ret;
    int cnt = 0;
    while (t) {
      ++cnt;
      t /= 10;
    }
    cnt = n - cnt;
    while (cnt--) printf("0");
    if (ret) printf("%d", ret);
    printf("\n");
  }

  return 0;
}