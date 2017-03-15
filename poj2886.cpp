/*
 * POJ 2886: Who Gets the Most Candies?
 * 题意：n个孩子围成一圈，每个人手上有个数字。先选择一个孩子出局，根据他手上的数字选择下一个孩子，以此类推。第k轮出局的人获得k的因子个数的糖果，求获得最多的孩子及糖果数。
 * 类型：二分+树状数组（／线段树）
 * 算法：预处理打表n内的因子数。若已经出局k人，他手上数字是x，则先将x%(n-k)得到单圈内转移的人数。二分下一个孩子的序号，树状数组得到他们间剩余孩子数和模数相比，得到最小等于模数的序号。
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>

using namespace std;

int prime[800];
bool np[800];
int cnt_prime;

int factor[500010];
int mf[500010];

void seive_factor(int n) {
  int max_factor = 0;
  fill(factor, factor + n, 1);
  for (int i  = 2; i < n; ++i) {
    if (factor[i] == 1) {
      for (int j = i; j < n; j += i) {
        int k = 0, t = j;
        while(t % i == 0) {
          ++k;
          t /= i;
        }
        factor[j] *= k + 1;
      }
    }
    if (factor[i] > max_factor) {
      max_factor = factor[i];
      mf[i] = i;
    } else {
      mf[i] = mf[i - 1];
    }
  }
}

int bit[500010];
int n;

int low_bit(int x) {
  return x & -x;
}

void change(int x) {
  ++x;
  while (x <= n) {
    bit[x] += 1;
    x += low_bit(x);
  }
}

int query(int x) {
  ++x;
  int ans = 0;
  while (x) {
    ans += bit[x];
    x -= low_bit(x);
  }
  return ans;
}

char name[500010][12];
int card[500010];

int main() {
  seive_factor(500010); // seive factor as seive prime then caculate factor will TLE
  int k, move, cnt;
  while (scanf("%d%d", &n, &k) != EOF) {
    memset(bit, 0, sizeof(bit));
    --k;
    for (int i = 0; i < n; ++i) {
      scanf("%s%d", name[i], &card[i]);
    }
    int des = mf[n];
    cnt = 1;
    while (cnt < des) {
      change(k);
      int mod = n - cnt;
      move = k - query(k) + card[k];
      if (card[k] < 0) move += 1;
      move = ((move % mod) + mod) % mod;

      int l, r, m;
      l = -1;
      r = n - 1;
      while(l + 1 < r) {
        m = (l + r) >> 1;
        int t = m - query(m);
        if (t >= move) {
          r = m;
        } else {
          l = m;
        }
      }
      k = r;
      ++cnt;
    }
    printf("%s %d\n", name[k], factor[des]);
  }
  return 0;
}
