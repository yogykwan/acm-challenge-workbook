/*
 * POJ 1082: Calendar Game
 * 题意：随机给出一个日期，它每次只能转移到下一天或下一个月的同一天（不存在则不转），最终达到比赛日期则为胜者。问先手的胜负。
 * 类型：NP博弈
 * 算法：比赛日期为必败态，倒着转移。从每个必败态出发，将上一天或上个月同一天（若存在）标记为必胜态。
 */

#include <cstdio>
#include <algorithm>

using namespace std;

int dp[37500];

int md[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int rmd[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int sum[13];
int rsum[13];

bool isrun(int y) {
  if (y % 400 == 0 || (y % 100 && y % 4 == 0)) return true;
  return false;
}

bool valid(int y, int m, int d) {
  if (y < 1900) return -1;
  if (isrun(y)) return d <= rmd[m];
  return d <= md[m];
}

int s2i(int y, int m, int d) {
  if (!valid(y, m, d)) {
    return -1;
  }
  int x = 0;
  if (y > 1900) {
    x += 365;
    x += (y - 1901) / 4 * 1461 + (y - 1901) % 4 * 365;
  }

  if (isrun(y)) {
    x += rsum[m - 1] + d;
  } else {
    x += sum[m - 1] + d;
  }
  return x;
}


void i2s(int x, int &y, int &m, int &d) {
  if (x <= 365) {
    y = 1900;
  } else {
    x -= 365;
    y = 1901 + 4 * (x / 1461);
    x %= 1461;
  }
  y += x / 365;
  x %= 365;
  if (x == 0) {
    --y;
    m = 12;
    d = 31;
    return;
  }

  if (isrun(y)) {
    m = int(lower_bound(rsum, rsum + 13, x) - rsum);
    d = x - rsum[m - 1];
  } else {
    m = int(lower_bound(sum, sum + 12, x) - sum);
    d = x - sum[m - 1];
  }
}

int pre_month(int x) {
  int y, m, d;
  i2s(x, y, m ,d);
  --m;
  if (m == 0) {
    m = 12;
    --y;
  }
  return s2i(y, m, d);
}

int main() {
  int T;
  scanf("%d", &T);
  int y, m, d;
  for (int i = 1; i <= 12; ++i)  {
    sum[i] = sum[i - 1] + md[i];
    rsum[i] = rsum[i - 1] + rmd[i];
  }


  for (int i = s2i(2001, 11, 4); i >= 1; --i) {
    if (dp[i] == 0) {
      dp[i - 1] = 1;
      int x = pre_month(i);
      if (x > 0) dp[x] = 1;
    }
  }
  while (T--) {
    scanf("%d%d%d", &y, &m, &d);
    int x = s2i(y, m, d);
    if(dp[x] == 0) {
      printf("NO\n");
    } else {
      printf("YES\n");
    }
  }
  return 0;
}
