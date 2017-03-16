/*
 * POJ 2674: Linear world
 * 题意：L长的平台上有n个人匀速移动，给出初始位置和移动方向。相遇的两个人会立刻掉头。求最后一个走出平台的人及所花时间。
 * 类型：智力题
 * 算法：两个人相遇后掉头可以看作是两个人都沿原来的方向继续前进，不影响时间，遍历可得最长时间。同时可知走出平台的方向和初始方向人数对应。n个人的相对顺序永远不变，若最后一个人的方向向左，共a个人从左边消失，则第a人就是最后消失的人；反向同理。
 */

#include <cstdio>

char name[32010][260];
char op[3];

int main() {
  double l, v;
  double ans;
  bool left;
  int n, a;
  while (scanf("%d", &n) != EOF && n) {
    a = 0;
    scanf("%lf%lf", &l, &v);
    ans = 0;
    for (int i = 0; i < n; ++i) {
      double pos;
      scanf("%s%lf", op, &pos);
      scanf("%s", name[i]);
      if (op[0] == 'p' || op[0] == 'P') {
        pos = l - pos;
        if (pos > ans) {
          ans = pos;
          left = false;
        }
      } else {
        ++a;
        if (pos > ans) {
          ans = pos;
          left = true;
        }
      }
    }

    long long time = (long long) (ans / v * 100);
    ans = time / 100.0;
    printf("%13.2f %s\n", ans, name[a - left]);
  }

  return 0;
}