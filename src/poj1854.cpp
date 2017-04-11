/*
 * POJ 1854: Evil Straw Warts Live
 * 题意：给出一个字符串，每次交换相邻字符，求使其变为回文的最少交换次数。
 * 类型：贪心
 * 算法：每次保证最左边被匹配（贪心可证明匹配最左和最右答案一样，且至少优于其他字符）。从右边对应位置向左搜索该字符，发现则移动到对应右侧。若未有匹配且该字符应该放在结果的中心，则将距离加入结果，然后忽略它继续匹配下一个字符。
 */

#include <cstdio>
#include <cstring>

char s[8010];
int cnt;

void move(int a, int b) {
  char t = s[a];
  for (int i = a; i < b; ++i) s[i] = s[i + 1];
  s[b] = t;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    cnt = 0;
    scanf("%s", s);
    int n = strlen(s);
    int i, j;
    bool mid = 0;
    int m = n - 1;

    for (i = 0; i < n / 2; ++i) {
      for (j = m; j > i; --j) {
        if (s[i] == s[j]) break;
      }
      if (i == j) {
        if (n % 2 == 0 || mid) {
          printf("Impossible\n");
          goto L;
        } else {
          mid = true;
          cnt += n / 2 - i;
        }
      } else {
        move(j, m);
        cnt += m - j;
        --m;
      }
    }
    if (n & 1 && mid && s[n/2] != s[n/2+1]) {
      printf("Impossible\n");
      goto L;
    }
    printf("%d\n", cnt);
    L:;
  }
  return 0;
}