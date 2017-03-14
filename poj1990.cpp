/*
 * POJ 1990: MooFest
 * 题意：n头奶牛站成一排，给出每个奶牛的坐标和听力上限。两头奶牛交流的声音为大的听力上限乘以距离。求C(n,2)对奶牛间交流的声音总和。
 * 类型：树状数组（／线段树）
 * 算法：奶牛按听力升序遍历。先从树状数组中它前面的奶牛数和坐标和，减法得到后面的值，依据坐标差正负计算所有牛与当前牛交流的声音总和。然后将该奶牛加入到对应坐标的树状数组里，更新个数和与坐标和。
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int low_bit(int x) {
  return x&-x;
}

long long dis[20010];
int cnt[20010];
int N = 20000;

typedef pair<int, int> pii;
pii cows[20010];

void change(int x) {
  int d = x;
  while(x <= N) {
    dis[x] += d;
    cnt[x] += 1;
    x += low_bit(x);
  }
}

void query(int x, long long &d, int &c) {
  d = c = 0;
  while(x) {
    d += dis[x];
    c += cnt[x];
    x -= low_bit(x);
  }
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int n;
  scanf("%d", &n);
  long long tot_dis = 0;
  int tot_cnt = 0;
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &cows[i].first, &cows[i].second);
  }
  sort(cows, cows + n);
  for (int i = 0; i < n; ++i) {
    long long before_dis, after_dis;
    int before_cnt, after_cnt;
    query(cows[i].second, before_dis, before_cnt);
//    printf("%d : %d %d\n", i, before_dis, before_cnt);
    after_dis = tot_dis - before_dis;
    after_cnt = tot_cnt - before_cnt;
    ans += cows[i].first * ((before_cnt * cows[i].second - before_dis) + (after_dis - after_cnt * cows[i].second));
    change(cows[i].second);
    tot_dis += cows[i].second;
    tot_cnt += 1;
  }
  printf("%lld\n", ans);
  return 0;
}
