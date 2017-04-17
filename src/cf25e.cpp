/*
 * CF 25E: Test
 * 题意：给出三个串，求包含它们的最短母串的长度。在母串中，子串可重叠且顺序任意。
 * 类型：字符串哈希
 * 算法：枚举三个子串开头出现的6种顺序，前两个先处理得到母串，再和第三个得到母串。最短母串的获得可通过hash值是否相同判断是否重叠部分可行，预处理出每个前缀的hash值。
 */


#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef unsigned long long ULL;  // 溢出相当于取模

char s[5][300010];
ULL h[2][200010];
ULL bs[100010];

const ULL B = 100000007ull;

void InitHash(char *s, int len, ULL *h) {
  h[0] = 0;
  for (int i = 1; i <= len; ++i) {
    h[i] = h[i - 1] * B + s[i - 1];
  }
}

ULL Hash(ULL *h, int b, int len) {
  return h[b + len] - h[b] * bs[len];
}

void Gao(char *s0, char *s1, char *s2) {
  int l0, l1, l2;
  l0 = (int)strlen(s0);
  l1 = (int)strlen(s1);
  InitHash(s0, l0, h[0]);
  InitHash(s1, l1, h[1]);
  int ol = 0;
  for (int i = 0; i < l0; ++i) {
    int to = min(l0 - i, l1);
    if (Hash(h[0], i, to) == Hash(h[1], 0, to)) {
      ol = to;
      break;
    }
  }
  l2 = 0;
  for (int i = 0; i < l0; ++i) {
    s2[l2++] = s0[i];
  }
  for (int i = ol; i < l1; ++i) {
    s2[l2++] = s1[i];
  }
  s2[l2] = 0;
}

int main() {
  int ans = 300000;
  bs[0] = 1;
  for (int i = 1; i <= 100000; ++i) {
    bs[i] = bs[i - 1] * B;
  }
  scanf("%s%s%s", s[0], s[1], s[2]);
  int order[] = {0, 1, 2};
  do {
    Gao(s[order[0]], s[order[1]], s[3]);
    Gao(s[order[2]], s[3], s[4]);
    ans = min(ans, (int)strlen(s[4]));
  } while (next_permutation(order, order + 3));
  printf("%d\n", ans);
  return 0;
}
