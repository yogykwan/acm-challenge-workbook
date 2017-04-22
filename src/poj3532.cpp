/*
 * POJ 3532: Resistance
 * 题意：n个节点m条导线链接，求点1到点n的等效电阻。
 * 类型：高斯消元
 * 算法：由基尔霍夫电流定理知，流入或流出某节点的电流和恒为0。
 */

#include <cstdio>

const double EPS = 1e-6;

double b[110][110];
int n, m;

void swap(double &x, double &y) {
  double t = x;
  x = y;
  y = t;
}

void Gauss() {
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

    for (j = 0; j < n; ++j) {
      if (j == i) continue;
      if (b[j][i] > EPS || b[j][i] < -EPS) {
        for (int k = n; k > i; --k) {
          b[j][k] -= b[i][k] * b[j][i];
        }
        b[j][i] = 0;
      }
    }
//    for (int ii = 0; ii < n; ++ii) {
//      for (int jj = 0; jj <= n; ++jj) {
//        printf("%f ", b[ii][jj]);
//      }
//      printf("\n");
//    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  while (m--) {
    int x, y, r;
    scanf("%d%d%d", &x, &y, &r);
    --x;
    --y;
    double l = 1.0 / r;
    b[x][x] += l;
    b[y][y] += l;
    b[x][y] -= l;
    b[y][x] -= l;
  }
  ++n;
  b[0][n] = 1.0;
  b[n - 2][n] = -1.0;
  b[n - 1][n - 2] = 1.0;  // n-1为虚拟汇点，但是要保证其变量为0

  Gauss();
  printf("%.2f\n", b[0][n]);
  return 0;
}
