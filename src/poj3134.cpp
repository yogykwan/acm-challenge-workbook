/*
 * POJ 3134: Power Calculus
 * 题意：给出x，通过乘法和除法得到中间结果，通过中间结果互相运算得到x^n需要最少多少步。
 * 类型：DFS
 * 算法：数的乘除转化为指数幂的加减，对每个n评估步数上届剪枝。将n转为二进制，则步数上届=最左1位置+1的个数-1。DFS时每次拿最后一个数和前面每个尝试加减并继续DFS。
 */

#include <cstdio>


int ans[1 << 10];
int e[22] = {1};

void Dfs(int d) {
  if (d > 20) return;
  for (int i = 0; i <= d; ++i) {
    e[d + 1] = e[i] + e[d];
    if (e[d + 1] < (1 << 10) && ans[e[d + 1]] >= d + 1) {
      ans[e[d + 1]] = d + 1;
      Dfs(d + 1);
    }
    e[d + 1] = e[d] - e[i];
    if (e[d + 1] > 0 && ans[e[d + 1]] >= d + 1) {
      ans[e[d + 1]] = d + 1;
      Dfs(d + 1);
    }
  }
}

int main() {
  int n;
  for (int i = 1; i < 1 << 10; ++i) {
    ans[i] = (31 - __builtin_clz(i)) + __builtin_popcount(i) - 1;
  }
  Dfs(0);
  while (scanf("%d", &n) != EOF && n) {
    printf("%d\n", ans[n]);
  }
  return 0;
}
