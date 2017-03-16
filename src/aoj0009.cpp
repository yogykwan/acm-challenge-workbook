/*
 * AOJ 0009: Prime Number
 * 题意：给出n，求不大于n的素数有多少个。
 * 类型：素数
 * 算法：先用线性时间复杂度的筛法打素数表，对于每个输入统计不超过的素数个数。
 */


#include <cstdio>

typedef long long LL;

int p[100010];
bool np[1000010];
int cntp;

void SievePrime(int n) {
  LL t;
  for(int i = 2; i <= n; ++i) {
    if(!np[i]) p[cntp++] = i;
    for(int j = 0; j < cntp && (t = 1ll * i * p[j]) <= n; ++j) {
      np[t] = true;
      if(i % p[j] == 0) break;
    }
  }
}

int main() {
  SievePrime(1000000);
  int n;
  while(scanf("%d", &n) != EOF) {
    int ans = 0;
    for(int i = 2; i <= n; ++i) {
      if(!np[i]) ++ans;
    }
    printf("%d\n", ans);
  }
  return 0;
}
