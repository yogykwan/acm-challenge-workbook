/*
 * AOJ 0033: Ball
 * 题意：序号为1-10的10个球，按一定排列顺序进入2个队列之一，最终每队入队球的序号都为增序的方案是否存在。
 * 类型：DFS
 * 算法：对于每个球，若大于队列顶端元素，则可以记录该情况并继续递归。
 */

#include <cstdio>
#include <iostream>

using namespace std;

int a[10], b[2][10];
int len[2];
bool ans;


void dfs(int step) {
    if(ans) return;
    if(step == 10){
        ans = true;
    }
    for(int i = 0; i < 2; ++i){
        if(len[i] == 0 || a[step] > b[i][len[i] - 1]){
            b[i][len[i]++] = a[step];
            dfs(step + 1);
            --len[i];
        }
    }
}

void solve() {
    ans = false;
    for(int i = 0; i < 10; ++i) {
        cin >> a[i];
    }
    dfs(0);
}

int main() {
    int T;
    cin >> T;
    while(T--) {
        solve();
        cout << (ans ? "YES" : "NO") << endl;
    }
    return 1;
}