/*
 * AOJ 0033: Ball
 * 题意：序号为1-10的10个球，按一定排列顺序进入2个队列之一，最终每队入队球的序号都为增序的方案是否存在。
 * 类型：贪心
 * 算法：对于每个球，若大于队列顶端元素，则可以记录该情况并继续递归。每次优先加入左边，可保证保证左边的顶端元素大于右边。
 */

#include <cstdio>

int a[10];


int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    bool ans = true;
    for (int i = 0; i < 10; ++i) {
      scanf("%d", &a[i]);
    }
    int l, r;
    l = r = 0;
    for (int i = 0; i < 10; ++i) {
      if (a[i] > l) {
        l = a[i];
      } else if (a[i] > r) {
        r = a[i];
      } else {
        ans = false;
        break;
      }
    }
    printf("%s\n", ans ? "YES" : "NO");
  }
  return 0;
}
