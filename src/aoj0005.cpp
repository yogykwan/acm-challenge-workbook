/*
 * AOJ 0005: GCD and LCM
 * 题意：求两数最大公约数和最小公倍数。
 * 类型：辗转相除法
 * 算法：gcd(a,b)=gcd(b,a%b)，lcm(a,b)=a*b/gcd(a,b)。
 */

#include <cstdio>
#include <iostream>

using namespace std;

int gcd(int a, int b) {
  for(int t; t = a % b; a = b, b = t);
  return b;
}

int main() {
  int a, b, g;
  long long l;
  while(scanf("%d%d", &a, &b) != EOF) {
    g = gcd(a, b);
    l = 1ll * a * b / g;
    printf("%d %lld\n", g, l);
  }
  return 0;
}