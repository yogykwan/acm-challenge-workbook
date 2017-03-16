/*
 * POJ 1930: Dead Fraction
 * 题意：给出小于1的无限循环小数的前几位，求可能相等的最简分数中分母最小的。
 * 类型：辗转相除法
 * 算法：枚举循环后缀长度，将小数点向后移动该长度，相减再相除，得到对应的分子分母，分别除以最大公约数得到最简分数。
 */

#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

typedef long long LL;

LL Gcd(LL a, LL b) {
  LL t;
  while(b) {
    t = a % b;
    a = b;
    b = t;
  }
  return a;
}

LL _stoll(string s) { // c++11 std::stoll
  LL v = 0;
  for(int i = 0; i < s.length(); ++i) {
    v = v * 10 + s[i] - '0';
  }
  return v;
}

int main() {
  string s, sa, sb;
  LL la, lb;
  LL num, den, g;
  LL ansd, ansn;
  while(cin >> s && s.length() > 1) {
    s = s.substr(2, s.length() - 5);
    int n = s.length();
    ansd = 0;
    for(int i = 0; i < n; ++i) {
      int j = n - i;
      sa = s.substr(0, i);
      sb = s.substr(i);
      la = i ? _stoll(sa): 0;
      lb = _stoll(sb);
      num = la * (LL)pow(10, j) + lb - la;
      den = ((LL)pow(10, j) - 1) * (LL)pow(10, i);
      g = Gcd(num, den);
      num /= g;
      den /= g;
      if(!ansd || den < ansd) {
        ansd = den;
        ansn = num;
      }
    }
    printf("%lld/%lld\n", ansn, ansd);
  }
  return 0;
}