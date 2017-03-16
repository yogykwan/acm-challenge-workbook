/*
 * POJ 2236: Wireless Network
 * 题意：给出多台损坏的电脑的坐标，任意两台修好且距离不超过d的电脑可以连线。给出修复某些电脑的指令，随时确认给出某两台之间是否有通路。
 * 类型：并查集
 * 算法：修复某台电脑时，将已修复的电脑中距离符合的和当前电脑所在的集合合并。判断是否有通路找到各自的集合代表元素看是否相同即可。
 */

#include <iostream>
#include <cstdio>

using namespace std;

int x[1010], y[1010];
int fa[1010];
bool fxd[1010];
int n, d;

bool close(int a, int b) {
  return d * d - (x[a] - x[b]) * (x[a] - x[b]) >= (y[a] - y[b]) * (y[a] - y[b]);
}

int find(int a) {
  if(fa[a] != a) {
    fa[a] = find(fa[a]);
  }
  return fa[a];
}

void merge(int a, int b) {
  fa[find(a)] = find(b);
}

int main() {
  scanf("%d%d", &n, &d);
  for(int i = 1; i <= n; ++i) {
    scanf("%d%d", &x[i], &y[i]);
    fa[i] = i;
  }
  char op[5];
  int a, b;
  while(scanf("%s", op) != EOF) {
    if(op[0] == 'O') {
      scanf("%d", &a);
      if(!fxd[a]) {
        fxd[a] = true;
        for(b = 1; b <= n; ++b) {
          if(!fxd[b]) continue;
          if(find(a) == find(b)) continue;
          if(close(a, b)) {
            merge(a, b);
          }
        }
      }
    } else {
      scanf("%d%d", &a, &b);
      if(find(a) == find(b)) {
        printf("SUCCESS\n");
      } else {
        printf("FAIL\n");
      }
    }
  }
  return 0;
}