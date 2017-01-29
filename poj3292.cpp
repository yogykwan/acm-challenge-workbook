/*
 * POJ 3292: Semi-prime H-numbers
 * 题意：所有运算基于4n+1形数，定义其上的素数、合数，定义恰能写成2个素数相乘的合数为半素数。求不大于n的半素数个数。
 * 类型：素数
 * 算法：艾式筛法得到素有4n+1形素数表，同时将素数与合数的乘积作为非半素数的合数筛去。对每个n用upper_bound求范围内的半素数个数。
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

const int MAXN = 250000;

int p[MAXN >> 3];
bool np[MAXN + 10];
bool nsp[MAXN + 10];
int cntp;

vector<int> sp;

void SievePrime(int n) {
  for (int i = 1; i < n; ++i) {
    if (!np[i]) {
      p[cntp++] = i;
      long long t;
      for (int j = 0; j < cntp && (t = 4ll * i * p[j] + i + p[j]) < n; ++j) {
        np[t] = true;
      }
    } else {
      if (!nsp[i]) {
        sp.push_back(i);
      }
      long long t;
      for (int j = 0; j < cntp && (t = 4ll * i * p[j] + i + p[j]) < n; ++j) {
        np[t] = true;
        nsp[t] = true;
        if ((4 * i + 1) % (4 * p[j] + 1) == 0) {
          break;
        }
      }
    }
  }
}

int main() {
  SievePrime(MAXN + 1);
  sort(sp.begin(), sp.end());
  int n;
  while (cin >> n, n) {
    cout << n << " " << upper_bound(sp.begin(), sp.end(), n >> 2) - sp.begin() << endl;
  }
  return 0;
}