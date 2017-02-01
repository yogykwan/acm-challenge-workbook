/*
 * POJ 3185: The Water Bowls
 * 题意：长为20的01序列a，反转任意数字，其两侧数同样被反转。求将序列变为全0的最少反转次数。
 * 类型：位运算+贪心（/枚举／高斯消元）
 * 算法：是否反转用一个21位序列b表示，则b[i]=a[i-1]^b[i-1]^b[i-2]。只要枚举b[1]的0、1两种状态，反转序列即可确定，最后b[21]为1则非法。
 */

#include <cstdio>

int a[22], b[22];

int main() {
  for (int i = 1; i <= 20; ++i) scanf("%d", &a[i]);
  int ans = 21, cnt;
  for (b[1] = 0; b[1] <= 1; ++b[1]) {
    cnt = b[1];
    for (int i = 2; i <= 21; ++i) {
      b[i] = a[i - 1] ^ b[i - 1] ^ b[i - 2];
      if(b[i]) ++cnt;
    }
    if (!b[21] && cnt < ans) ans = cnt;
  }
  printf("%d\n", ans);
  return 0;
}