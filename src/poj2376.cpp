/*
 * POJ 2376: Cleaning Shifts
 * 题意：有1～T连续的T份任务，有N头奶牛，每头牛可以完成某段连续时间的任务。求最少需要多少头牛，完成T个任务。
 * 类型：贪心
 * 算法：将N个区间按起点排序，若1～p已全覆盖，则从剩下的待选区间内找到所有起点不大于p，且终点最大的区间。
 */

#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

pair <int, int> cows[25010];

int main() {
  int T, N;
  scanf("%d%d", &N, &T);
  for(int i = 0; i < N; ++i) {
    scanf("%d%d", &cows[i].first, &cows[i].second);
  }
  sort(cows, cows + N);
  int p = 1;
  int cnt = 0;
  int i = 0;
  while(p <= T) {
    int np = -1;
    for(;i < N; ++i) {
      if(cows[i].first <= p) {
        np = max(np, cows[i].second);
      } else {
        break;
      }
    }
    if(np == -1) {
      printf("-1\n");
      return 0;
    } else {
      p = np + 1;
      ++cnt;
      if(p > T) {
        printf("%d\n", cnt);
        return 0;
      }
    }
  }
  return 0;
}
