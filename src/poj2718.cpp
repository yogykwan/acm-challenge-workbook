/*
 * POJ 2718: Smallest Difference
 * 题意：给出不重复升序单数字，将其分为两组打乱顺序后组成整数，求两个整数的最小差值。
 * 类型：穷竭搜索＋全排列
 * 算法：将序列全排列，按长度均分成两组，计算每个排列下的差值。
 */


#include <cstdio>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

const int INF = 1000000000;

int n, a[10], ans, d[2];

int array2int(int s, int t) {
    int x = 0;
    if(a[s] == 0 && s + 1 < t){
        return -1;
    }
    for(int i = s; i < t; ++i) {
        x = x * 10 + a[i];
    }
    return x;
}

void solve() {
    ans = INF;
    d[0] = n / 2;
    d[1] = (n + 1) /2;
    int x, y;
    do{
        for(int i = 0; i < 2; ++i) {
            if(i == 1 && d[1] == d[0]){
                continue;
            }
            x = array2int(0, d[i]);
            y = array2int(d[i], n);
            if(x != -1 && y != -1){
                ans = min(ans, abs(x - y));
            }
        }
    }while(next_permutation(a, a + n));
}

int main() {
    int Tcase;
    cin >> Tcase;
    cin.get();
    while(Tcase--) {
        string str;
        getline(cin, str);
        stringstream ss(str);
        n = 0;
        while(ss >> a[n]){
            ++n;
        };
        solve();
        cout << ans << endl;
    }
    return 0;
}