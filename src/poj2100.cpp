/*
 * POJ 2100: Graveyard Design
 * 题意：总面积一定，求边长连续的一些正方形，面积和正好等于给出总面积。
 * 类型：尺取法
 * 算法：尺取法控制左右端点向后移动，若累加和等于总面积输出答案同时左右端点移动，小于则右端点右移和增加对应部分，大于则左端点右移和减少。
 */

#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

typedef long long LL;

typedef pair<LL, LL> pll;

pll ans[67000];
int cnt;

int main() {
  LL n;
  scanf("%lld", &n);
  LL l = 1, r = 1;
  LL ub = sqrt(n) + 1;
  LL tmp = 1;
  while(true) {
    if(tmp == n) {
      ans[cnt].first = l;
      ans[cnt++].second = r;
      if(l == r) break;
      ++r;
      tmp += r * r;
      tmp -= l * l + (l + 1) * (l + 1);
      l += 2;
    } else if(tmp > n) {
      if(l == r) break;
      tmp -= l * l;
      ++l;
    } else if(tmp < n){
      ++r;
      tmp += r * r;
    }
  }
  printf("%d\n", cnt);
  for(int i = 0; i < cnt; ++i) {
    l = ans[i].first;
    r = ans[i].second;
    printf("%lld", r - l + 1);
    for(LL j = l; j <= r; ++j) printf(" %lld", j);
    printf("\n");
  }
  return 0;
}