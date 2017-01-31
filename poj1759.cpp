/*
 * POJ 1759: Garland
 * 题意：数列长为n，给出h(0)的值和数列关系式h(i)=(h(i-1)+h(i+1))/2-1。保证数列所有元素非负，求h(n-1)的最小值。
 * 类型：二分搜索
 * 算法：根据关系式得到h(i)=ih(1)-(i-1)h(0)+i(i-1)，所以要找到最小的h(1)满足所有数非负，此时的h(n-1)即为最小值。
 */

#include <cstdio>

const double EPS = 1e-7;

double h[1010];

int main() {
  int n;
  double A;
  scanf("%d%lf", &n, &A);
  h[0] = A;
  double l, r, m;
  l = A / 2 - 1;
  r = A;
  while (r - l > EPS) {
    m = (l + r) / 2;
    h[1] = m;
    bool ok = true;
    for (int i = 2; i < n; ++i) {
      h[i] = 2 * (h[i - 1] + 1) - h[i - 2];
      if (h[i] < -EPS) {
        ok = false;
        break;
      }
    }
    if (ok) {
      r = m;
    } else {
      l = m;
    }
  }
  if (h[n - 1] < 0) h[n - 1] = 0; // -0.00
  printf("%.2f\n", h[n - 1]);

  return 0;
}