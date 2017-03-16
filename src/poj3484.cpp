/*
 * POJ 3484: Showstopper
 * 题意：用x,y,z表示最大不超过y的数列x,x+z,x+2z,...。给出多个数列，求唯一出现过奇数次的数。
 * 类型：二分搜索
 * 算法：二分搜索答案，若所有数列中小于等于该数的总个数为奇数，则更新上届，否则下届。用iostream会超时。
 */

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;

const int MAXN = 100010;

LL x[MAXN], y[MAXN], z[MAXN];
int cnt_ds;

LL bs_check(LL k) {
  LL cnt = 0;
  LL t;
  for (int i = 0; i < cnt_ds; ++i) {
    t = min(k, y[i]);
    if (t >= x[i]) {
      cnt += (t - x[i]) / z[i] + 1;
    }
  }
  return cnt;
}

void gao() {
  LL l = 0, r = 0, m;
  for(int i = 0; i < cnt_ds; ++i) {
    r = max(r, y[i]);
  }
  LL cnt;
  cnt = bs_check(r);
  if (!(cnt & 1)) {
    printf("no corruption\n");
    return;
  }
  while (l + 1 < r) {
    m = (l + r) >> 1;
    cnt = bs_check(m);
    if (cnt & 1) {
      r = m;
    } else {
      l = m;
    }
  }
  printf("%lld %lld\n", r, bs_check(r) - bs_check(r - 1));
}

int main() {
  char ch;
  while (scanf("%c", &ch) != EOF) {
    if (ch != 10) {
      LL tmp = ch - '0';
      while(scanf("%c", &ch) != EOF) {
        if(ch == ' ') break;
        tmp = tmp * 10 + ch - '0';
      }
      x[cnt_ds] = tmp;
      scanf("%lld%lld", &y[cnt_ds], &z[cnt_ds]);
      scanf("%*c");
      ++cnt_ds;
    } else if(cnt_ds){
      gao();
      cnt_ds = 0;
    }
  }
  if (cnt_ds) {
    gao();
  }
  return 0;
}