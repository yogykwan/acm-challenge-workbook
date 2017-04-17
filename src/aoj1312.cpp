/*
 * AOJ 1312: Where's Wally
 * 题意：给出w*h的矩形，每个位置是一个Base64编码的字符，再给出一个方形的图案。Base64转化为二进制后，要求按01在原矩形中寻找该方形（旋转和翻转也可以）。求能找到多少个。
 * 类型：字符串哈希
 * 算法：将所有Base64编码都转变为二进制，方形图案旋转翻转得到8个匹配图。对每个图，计算行hash，再针对行hash进行列hash。在原来的大图里同样先行后列滚动hash看是否能匹配。
 */


#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef unsigned long long ULL;  // 溢出相当于取模

char mat[200];
ULL bg[1010][1010], sm[110][110], tm[110][110];
ULL h[1010];
ULL pattern[8];

const ULL B = 100000007ull;
const ULL C = 100000009ull;

void Decode(ULL *a) {
  int len = (int) strlen(mat);
  for (int i = 0; i < len; ++i) {
    char ch = mat[i];
    int x = 0;
    if (ch >= 'A' && ch <= 'Z') {
      x = ch - 'A';
    } else if (ch >= 'a' && ch <= 'z') {
      x = ch - 'a' + 26;
    } else if (ch >= '0' && ch <= '9') {
      x = ch - '0' + 52;
    } else if (ch == '+') {
      x = 62;
    } else if (ch == '/') {
      x = 63;
    }
    for (int j = 6 * i + 5; j >= 6 * i; --j) {
      a[j] = (ULL)x & 1;
      x >>= 1;
    }
  }
}

int Find(ULL x) {
  for (int i = 0; i < 8; ++i) {
    if (pattern[i] == x) {
      return i;
    }
  }
  return -1;
}

int main() {
  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int m, n, p;
  while (scanf("%d%d%d", &n, &m, &p) != EOF && m) {
    int ans = 0;
    for (int i = 0; i < m; ++i) {
      scanf("%s", mat);
      Decode(bg[i]);
    }
    for (int i = 0; i < p; ++i) {
      scanf("%s", mat);
      Decode(sm[i]);
    }

    ULL bs = 1ull, cs = 1ull;
    for (int i = 0; i < p; ++i) {
      bs *= B;
      cs *= C;
    }

    for (int k = 0; k < 8; ++k) {
      for (int i = 0; i < p; ++i) {
        for (int j = 0; j < p; ++j) {
          tm[j][p - 1 - i] = sm[i][j];
        }
      }
      if (k == 4) {
        for (int i = 0; i < p; ++i) {
          for (int j = 0; j < p; ++j) {
            tm[i][p - 1 - j] = sm[i][j];
          }
        }
      }

      ULL x = 0ull;
      for (int i = 0; i < p; ++i) {
        ULL y = 0ull;
        for (int j = 0; j < p; ++j) {
          y = y * B + tm[i][j];
        }
        x = x * C + y;
      }
      pattern[k] = x;
      memcpy(sm, tm, sizeof(tm));
    }

    for (int i = 0; i < m; ++i) {
      ULL x = 0ull;
      for (int j = 0; j < p; ++j) {
        x = x * B + bg[i][j];
      }
      h[i] = x;
    }

    for (int j = p; j <= n; ++j) {
      ULL x = 0ull;
      for (int i = 0; i < p; ++i) {
        x = x * C + h[i];
      }
      for (int i = p; i <= m; ++i) {
        if (Find(x) >= 0) {
          ++ans;
        }
        if (i == m) break;
        x = x * C - h[i - p] * cs + h[i];
      }
      if (j == n) break;
      for (int i = 0; i < m; ++i) {
        h[i] = h[i] * B - bs * bg[i][j - p] + bg[i][j];
      }
    }

    printf("%d\n", ans);
  }
  return 0;
}
