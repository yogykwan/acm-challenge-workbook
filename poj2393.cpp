/*
 * POJ 2393: Yogurt factory
 * 题意：每个时段产奶单位成本不同，单位重量单位时间储奶花费为s常量。已知每个时段的牛奶需求量，求最小成本。
 * 类型：贪心
 * 算法：可以将第i时刻的单位成本减去s*i修正，第i时段需要的奶应该由前i个时段修正成本最小的产出，加入总成本时再每单位加s*i恢复并存储。
 */

#include <cstdio>
#include <iostream>

using namespace std;


int main() {
  int n, s;
  int c, y;
  double ans = 0, mm = 100000;
  int p = -1;
  scanf("%d%d", &n, &s);
  for(int i = 0; i < n; ++i) {
    scanf("%d%d", &c, &y);
    c -= i * s;
    if(c < mm) {
      mm = c;
      p = i;
    }
    ans += (mm + i * s) * y;
  }
  printf("%.0f\n", ans);
  return 0;
}

