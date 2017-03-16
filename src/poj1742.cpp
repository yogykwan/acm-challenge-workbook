/*
 * POJ 1742: Coins
 * 题意：给出多种硬币的面值和数量，求可以组成的金额种类。
 * 类型：DP+多重背包
 * 算法：d[i][j]表示使用前i种硬币组成总价j时，使用第i种硬币的最小数量。若d[i-1][j]合法，d[i][j]=0；否则若d[i][j-Ai]<Ci，d[i][j]=d[i][j-Ai]+1。滚动数组降维。
 */


#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

int d[100010];
int A[110];
int C[110];

int main() {
  int n, m;
  while(scanf("%d%d", &n, &m) !=EOF && n > 0) {
    for(int i = 0; i < n; ++i) {
      scanf("%d", &A[i]);
    }
    for(int i = 0; i < n; ++i) {
      scanf("%d", &C[i]);
    }
    memset(d, -1, sizeof(d));
    d[0] = 0;
    for(int i = 0; i < n; ++i) {
      for(int j = 0; j <= m; ++j) {
        if(d[j] > -1) {
          d[j] = 0;
        } else if(j >= A[i] && d[j - A[i]] > -1 && d[j - A[i]] < C[i]){
          d[j] = d[j - A[i]] + 1;
        }
      }
    }
    int ans = 0;
    for(int i = 1; i <= m; ++i) {
      if(d[i] > -1) {
        ++ans;
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}