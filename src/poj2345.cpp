/*
 * POJ 2345: Central heating
 * 题意：n个技工，n个炉子。每个技工负责若干个炉子，收到指令后会去反转炉子开关状，任何技工工作不会被其他组合替换。初始时全为关闭，问最少选择多少个技工可以使得炉子全开。
 * 类型：高斯消元
 * 算法：n个变量表示是否调用该技工，可得到n元1次模方程组，方程右边都是对2取模为1。由于题目规定任意技工都不能表示为其他的组合，所以矩阵的秩为n，可以高斯消元求解到唯一解，不会出现多解或无解。
 */

#include <cstdio>

int b[255][255];
int n;

void swap(int &x, int &y) {
  int t = x;
  x = y;
  y = t;
}

void Gauss() {
  for (int i = 0; i < n; ++i) {
    int j;
    for (j = i; j < n; ++j) {
      if (b[j][i]) break;
    }
    if (j > i) {
      for (int k = 0; k <= n; ++k) {
        swap(b[i][k], b[j][k]);
      }
    }
    for (j = 0; j < n; ++j) {
      if (j == i) continue;
      if (b[j][i]) {
        for (int k = 0; k <= n; ++k) {
          b[j][k] ^= b[i][k];
        }
      }
    }
//    for (int ii = 0; ii < n; ++ii) {
//      for (int jj = 0; jj <= n; ++jj) {
//        printf("%d ", b[ii][jj]);
//      }
//      printf("\n");
//    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int j;
    while (scanf("%d", &j) != EOF && j != -1) {
      b[j - 1][i] = 1;
    }
    b[i][n] = 1;
  }

  Gauss();

  bool first = true;
  for (int i = 0; i < n; ++i) {
    if (b[i][n]) {
      if (first) first = false;
      else printf(" ");
      printf("%d", i + 1);
    }
  }
  printf("\n");
  return 0;
}
