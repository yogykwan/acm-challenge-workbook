/*
 * POJ 1862: Stripies
 * 题意：n个细胞，质量为m1、m2的结合后会变成质量为2sqrt(m1*m2)的新细胞，求最后形成的终极细胞的最小质量。
 * 类型：贪心
 * 算法：由于越先参与的细胞取根号的次数越多，每次选取最大的两个细胞结合，使得越大的细胞能够越多见减少。
 */

#include <cstdio>
#include <queue>
#include <iostream>
#include <cmath>

using namespace std;

priority_queue<double> s;

int main() {
  int i, n;
  scanf("%d", &n);
  for(i = 0; i < n; ++i) {
    double tmp;
    scanf("%lf", &tmp);
    s.push(tmp);
  }
  while(--n) {
    double a, b;
    a = s.top();
    s.pop();
    b = s.top();
    s. pop();
    s.push(2 * sqrt(a * b));
  }
  printf("%.3f\n", s.top());
  return 0;
}
