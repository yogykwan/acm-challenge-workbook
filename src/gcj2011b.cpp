/*
 * GCJ 2011 Final B: Bacterial Reproduction
 * 题意：x个细菌一小时后繁殖为x^x个，求A个细菌B小时后的数量模C。
 * 类型：数论
 * 算法：d(n,m)=(d(n-1)%m)^d(n-1),次幂对结果有循环节，所以先预处理出所有d(n,m)的循环节。如果次幂是否在循环头，则直接求；否则次幂为d(n-1,loop)。
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

int a[1010];
int d[1010][1010];
int h[1010][1010];
int l[1010][1010];
int vis[1010];

int A, B, C;

void InitLoop() {
  for (int i = 1; i <= 1000; ++i) {
    for (int j = 1; j <= 1000; ++j) {
      memset(vis, -1, sizeof(vis));
      int a = 1;
      int step = 0;
      while (1) {
        a = a * i % j;
        if (vis[a] != -1) {
          h[i][j] = vis[a];
          l[i][j] = step - vis[a];
          break;
        }
        vis[a] = step++;
      }
    }
  }
}

int Power(int a, int b) {
  if (b == 0) return 1;
  int ans = 1;
  while (b) {
    if (b & 1) {
      ans = min(1111, ans * a);
    }
    a = min(1111, a * a);
    b >>= 1;
  }
  return ans;
}

int Power(int a, int b, int mod) {
  if (b == 0) return 1;
  if (mod == 1) return 0;
  int ans = 1;
  while (b) {
    if (b & 1) {
      ans = ans * a % mod;
    }
    a = a * a % mod;
    b >>= 1;
  }
  return ans;
}

void InitTable() {
  a[0] = A;
  for (int i = 1; i <= B; ++i) {
    a[i] = Power(a[i - 1], a[i - 1]);
  }
}

int Gao(int A, int B, int C) {
  if (B == 0) return A % C;
  if (C == 1) return 0;
  if (d[B][C] != -1) {
    return d[B][C];
  }
  int x = Gao(A, B - 1, C);
  if (a[B - 1] <= 1000) {
    return d[B][C] = Power(x, a[B - 1], C);
  }
  int y = Gao(A, B - 1, l[x][C]);
  y = ((y - (h[x][C] + 1)) % l[x][C] + l[x][C]) % l[x][C] + h[x][C] + 1;
  return d[B][C] = Power(x, y, C);
}

int main() {
  int T;
  InitLoop();
  scanf("%d", &T);
  for (int tc = 1; tc <= T; ++tc) {
    memset(d, -1, sizeof(d));
    scanf("%d%d%d", &A, &B, &C);
    InitTable();
    printf("Case #%d: %d\n", tc, Gao(A, B, C));
  }
  return 0;
}