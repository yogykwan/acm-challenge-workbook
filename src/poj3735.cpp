/*
 * POJ 3735: Training little cats
 * 题意：猫可以三种行为：取坚果、吃完、两只猫交换。给出一个行为序列，重复多次，求最后每只猫的坚果数量。
 * 类型：矩阵快速幂
 * 算法：通过行为序列构造转移矩阵，0列表示坚果，1～n列表示n只猫。初始为单位矩阵，取坚果将0行增加，吃将整列清空，猫交换即交换两列。然后矩阵快速幂，第0行即为答案。
 */


#include <cstdio>
#include <cstring>

typedef long long LL;
LL mat[110][110];
int n;

LL ans[110][110];
LL tmp[110][110];

void Mul(LL a[][110], LL b[][110]) {
  memset(ans, 0, sizeof(ans));
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= n; ++j) {
      if (a[i][j] == 0) continue; // 稀疏矩阵
      for (int k = 0; k <= n; ++k) {
        ans[i][k] += a[i][j] * b[j][k];
      }
    }
  }
  for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) a[i][j] = ans[i][j];
}

void Pow(LL mat[][110], int m) {
  memset(tmp ,0, sizeof(tmp));
  for (int i = 0; i <= n; ++i) tmp[i][i] = 1;
  while (m) {
    if (m & 1) Mul(tmp, mat);
    Mul(mat, mat);
    m >>= 1;
  }
  for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) mat[i][j] = tmp[i][j];
}



int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int m, k;
  while (scanf("%d%d%d", &n, &m, &k) != EOF && n > 0) {
    memset(mat, 0, sizeof(mat));
    for (int i = 0; i <= n; ++i) mat[i][i] = 1;

    while (k--) {
      char ch[5];
      int a, b;
      scanf("%s%d", ch, &a);
      if(ch[0] == 'g') {
        ++mat[0][a];
      } else if(ch[0] == 'e') {
        for (int i = 0; i <= n; ++i) {
          mat[i][a] = 0;
        }
      } else {
        scanf("%d", &b);
        for (int i = 0; i <= n; ++i) {
          LL t = mat[i][a];
          mat[i][a] = mat[i][b];
          mat[i][b] = t;
        }
      }
    }

    Pow(mat, m);
    for (int i = 1; i < n; ++i) {
      printf("%lld ", mat[0][i]);
    }
    printf("%lld\n", mat[0][n]);
  }
  return 0;
}