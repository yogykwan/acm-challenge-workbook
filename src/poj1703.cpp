/*
 * POJ 1703: Find them, Catch them
 * 题意：一堆人属于2个帮派，给出敌对关系。询问任意两个人是否属于同一帮派。
 * 类型：并查集
 * 算法：每个点i拆为2个点，表示i属于A和i属于B。对给出的异帮关系，连接i属于A、j属于B，i属于B、j属于A。
 */

#include <iostream>
#include <cstdio>

using namespace std;

int fa[200010];

int find(int a) {
  if(a == fa[a]) {
    return a;
  }
  return fa[a] = find(fa[a]);
}

void merge(int a, int b) {
  fa[find(a)] = find(b);
}

int main() {
  int T, n, m, a, b;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= (n<<1); ++i) {
      fa[i] = i;
    }
    while(m--) {
      char op[3];
      scanf("%s%d%d", op, &a, &b);
      if(op[0] == 'A') {
        if(find(a) == find(b)) {
          printf("In the same gang.\n");
        } else if(find(a) == find(b + n)) {
          printf("In different gangs.\n");
        } else {
          printf("Not sure yet.\n");
        }
      } else {
        merge(a, b + n);
        merge(b, a + n);
      }
    }
  }
  return 0;
}