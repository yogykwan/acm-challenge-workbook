/*
 * AOJ 0121: Seven Puzzle
 * 题意：2行4列的矩阵，标号为0～7，每次可以将0和其相邻格交换，问达到增序局面的最少移动步数。
 * 类型：BFS＋Map
 * 算法：用String表示局面，用Map建立局面与最短路的映射。从队列中取出前局面，搜索可移动且未出现过的局面再加入队列，直到局面为增序或队列空。
 */


#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <string>

using namespace std;

int a[8];
int d[4] = {-1 , 1, -4, 4};
string s = "";
string t = "01234567";

int bfs() {
    if(s == t) {
        return 0;
    }
    queue <string> q;
    q.push(s);
    map <string, int> mymap;
    mymap[s] = 0;
    while(!q.empty()) {
        string cur = q.front();
        string nxt;
        q.pop();
        int p = (int)cur.find("0");
        for(int i = 0; i < 4; ++i) {
            int np = p + d[i];
            if(np >= 0 && np < 8 && (p != 3 || d[i] != 1) && (p != 4 || d[i] != -1)) {
                nxt = cur;
                nxt[np] = '0';
                nxt[p] = cur[np];
                if(mymap.find(nxt) == mymap.end()) {
                    mymap[nxt] = mymap[cur] + 1;
                    if(nxt == t) {
                        return mymap[nxt];
                    }
                    q.push(nxt);
                }
            }

        }
    }
    return -1;
}

int solve() {
    s = "";
    for(int i = 0; i < 8; ++i) {
        s += a[i] + '0';
    }
    return bfs();
}

int main() {
    while(cin >> a[0]) {
        for(int i = 1; i < 8; ++i) {
            cin >> a[i];
        }
        cout << solve() << endl;
    }
    return 0;
}
