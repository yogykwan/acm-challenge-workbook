/*
 * POJ 3526: The Teacher’s Side of Math
 * 题意：给出根x=m√a+n√b，其中a和b是素数，求原多项式。
 * 类型：高斯消元
 * 算法：以多项式系数为变量，因为f(x)=0，所以各个x的次幂展开后系数相加和为0。保证多项式最高次数项的系数为1，高斯消元求解。
 */

#include <cstdio>
#include <cmath>
#include <cstring>

typedef long long LL;

LL C[22][22];

const double EPS = 1e-6;

int A, M, B, N;
int tot;

double b[22][22];

void swap(double &x, double &y) {
  double t = x;
  x = y;
  y = t;
}

void Gauss(int n) {
  for (int i = 0; i < n; ++i) {
    int j;
    for (j = i; j < n; ++j) {
      if (b[j][i] > EPS || b[j][i] < -EPS) break;
    }
    if (j == n) continue;
    if (j > i) {
      for (int k = 0; k <= n; ++k) {
        swap(b[i][k], b[j][k]);
      }
    }
    for (int k = n; k > i; --k) {
      b[i][k] /= b[i][i];
    }
    b[i][i] = 1;

    for (j = i + 1; j < n; ++j) {
      if (b[j][i] > EPS || b[j][i] < -EPS) {
        for (int k = n; k > i; --k) {
          b[j][k] -= b[i][k] * b[j][i];
        }
        b[j][i] = 0;
      }
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    b[i][n] /= b[i][i];
    for (int j = i - 1; j >= 0; --j) {
      b[j][n] -= b[i][n] * b[j][i];
    }
  }
}

inline int Round(double x) {
  return int(x >= 0.0 ? floor(x + 0.5) : ceil(x - 0.5));
}

int main() {
  for (int i = 0; i <= 20; ++i) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; ++j) {
      C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
  }
  while (scanf("%d%d%d%d", &A, &M, &B, &N) != EOF && (A || M || B || N)) {
    memset(b, 0, sizeof(b));
    tot = M * N + 1;
    b[0][0] = b[0][tot] = 1.0;
    for (int i = 0; i < tot; ++i) {
      for (int j = 0; j <= i; ++j) {
        int id = j % M * N + (i - j) % N + 1;
        b[id][tot - 1 - i] += C[i][j] * pow((double)A, j / M) * pow((double)B, (i - j) / N);
      }
    }

    Gauss(tot);
    for (int i = 0; i < tot - 1; ++i) {
      printf("%d ", Round(b[i][tot]));
    }
    printf("%d\n", Round(b[tot - 1][tot]));
  }
  return 0;
}
