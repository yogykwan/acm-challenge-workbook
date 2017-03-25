/*
 * POJ 3420: Quad Tilin
 * 题意：nx4的矩形用1x2地砖拼，有多少种拼法？
 * 类型：状态DP+矩阵快速幂
 * 算法：状态压缩为4位二进制，若i状态可以累加到j状态，则将转移矩阵i行j列置1。矩阵快速幂后右下角为答案。
 */


#include <cstdio>
#include <cstring>

typedef long long LL;
LL mat[16][16];
int MOD;
LL ans[16][16];

void Mul(LL a[][16], LL b[][16]) {
  memset(ans, 0, sizeof(ans));
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 16; ++j) {
      for (int k = 0; k < 16; ++k) {
        ans[i][j] += a[i][k] * b[k][j];
        ans[i][j] %= MOD;
      }
    }
  }
  for (int i = 0; i < 16; ++i) for (int j = 0; j < 16; ++j) a[i][j] = ans[i][j];
}

void Pow(LL mat[][16], int n) {
  if (n == 1) return;
  LL tmp[16][16];
  for (int i = 0; i < 16; ++i) for (int j = 0; j < 16; ++j) tmp[i][j] = mat[i][j];
  Pow(tmp, n >> 1);
  Mul(tmp, tmp);
  if (n & 1) {
    Mul(tmp, mat);
  }
  for (int i = 0; i < 16; ++i) for (int j = 0; j < 16; ++j) mat[i][j] = tmp[i][j];
}


int main() {
  int n;
  while (scanf("%d%d", &n, &MOD) != EOF && n > 0) {
    if(MOD == 1) {
      printf("0\n");
      continue;
    }
    memset(mat, 0, sizeof(mat));
    for (int i = 0; i < 16; ++i) {
      mat[i][15 - i] = 1;
    }
    mat[15][7] = mat[15][13] = 1;
    mat[8][14] = mat[8][11] = 1;
    mat[13][14] = 1;
    mat[11][7] = 1;

    mat[6][15] = 1;
    mat[12][15] = 1;
    mat[3][15] = 1;

    mat[15][3] = mat[15][6] = mat[15][12] = mat[15][15] = 1;

    Pow(mat, n);
    printf("%lld\n", mat[15][15]);
  }
  return 0;
}