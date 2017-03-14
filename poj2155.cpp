/*
 * POJ 2155: Matrix
 * 题意：一个方阵初始化全为0，多次反转和查询操作。每次反转所给矩阵范围内所有的点，询问某个点的值。
 * 类型：树状数组（／线段树）
 * 算法：二维树状数组，第一维数组的每个节点对应一个第二维的树状数组。对于反转操作，将左端点上+1，右端点后-1。求值即为求从头开始的累加和。
 */

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int low_bit(int x) {
  return x&-x;
}

int bit[1010][1010];
int N;

void change(int x, int y, int d) {
  while(y <= N) {
    bit[x][y] += d;
    y += low_bit(y);
  }
}

int sum(int x, int y) {
  int ans = 0;
  while(y) {
    ans += bit[x][y];
    y -= low_bit(y);
  }
  return ans;
}

void change2(int x, int y, int d) {
  while(x <= N) {
    change(x, y, d);
    x += low_bit(x);
  }
}

int sum2(int x, int y) {
  int ans = 0;
  while(x) {
    ans += sum(x, y);
    x -= low_bit(x);
  }
  return ans;
}

int main() {
  // freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int T, tc, k;
  scanf("%d", &T);
  for(tc = 0; tc < T; ++tc) {
    if(tc) {
      printf("\n");
    }
    memset(bit, 0, sizeof(bit));
    scanf("%d%d", &N, &k);
    while(k--) {
      char op[5];
      scanf("%s", op);
      if(op[0] == 'Q') {
        int x, y;
        scanf("%d%d", &x, &y);
        int ans = sum2(x, y) & 1;
        printf("%d\n", ans);
      } else {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        change2(x1, y1, 1);
        change2(x1, y2 + 1, -1);
        change2(x2 + 1, y1, -1);
        change2(x2 + 1, y2 + 1, 1);
      }
    }
  }
  return 0;
}
