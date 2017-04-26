/*
 * UVa 10181: 15-Puzzle Problem
 * 题意：给一个4x4的滑块拼图，图中有1～15块和1个空白块。求复原为顺序状态的最短移动路径。
 * 类型：IDA*
 * 算法：因为移动不改变逆序对加上空格到末尾的行数的奇偶，所以根据开局状态可预判是否存在解。之后IDA*的评估函数为曼哈顿距离，用评估函数确定IDA*下届，每次迭代增加DFS的搜索深度限制。DFS时若当前步数和当前状态的评估函数的和大于深度限制则剪枝，同时禁止连续两步抵消的走法。
 */

#include <cstdio>
#include <cstring>

using namespace std;

int a[16];
int pos[16][2];
int target[16];

int dx[] = {-1, 0, 0, 1};
int dy[] = {0, 1, -1, 0};
char dir[] = {'U', 'R', 'L', 'D'};

char path[100];

int Abs(int x) {
  return x < 0 ? -x : x;
}

int GaoH() {
  int ret = 0;
  for (int i = 0; i < 16; ++i) {
    if (a[i]) {
      ret += Abs(pos[a[i]][0] - (i >> 2));
      ret += Abs(pos[a[i]][1] - (i & 3));
    }
  }
  return ret;
}

bool Solvable() {
  int ret = 0;
  for (int i = 0; i < 16; ++i) {
    if (!a[i]) {
      ret += 3 - i / 4;
    } else {
      for (int j = 0; j < i; ++j) {
        if (a[j] && a[j] > a[i]) {
          ++ret;
        }
      }
    }
  }
  return !(ret & 1);
}

bool Dfs(int cur, int dep, int p, int limit) {
  if (dep + GaoH() > limit) {
    return false;
  }
  if (dep == limit) {
    return !memcmp(a, target, sizeof(target));
  }

  int x, y, xx, yy, xy;
  x = cur >> 2, y = cur & 3;
  for (int i = 0; i < 4; ++i) {
    if (i + p == 3) continue;
    xx = x + dx[i];
    yy = y + dy[i];
    if (xx >= 0 && xx < 4 && yy >= 0 && yy < 4) {
      path[dep] = dir[i];
      xy = xx << 2 | yy;
      a[cur] = a[xy];
      a[xy] = 0;
      if (Dfs(xy, dep + 1, i, limit)) {
        return true;
      }
      a[xy] = a[cur];
      a[cur] = 0;
    }
  }
  return false;
}

int main() {
  for (int i = 0; i < 15; ++i) {
    target[i] = i + 1;
    pos[i + 1][0] = i >> 2;
    pos[i + 1][1] = i & 3;
  }
  target[15] = 0;
  pos[0][0] = pos[0][1] = 3;

  int T;
  scanf("%d", &T);
  while (T--) {
    int tot = 0;
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        scanf("%d", &a[tot++]);
      }
    }
    if (Solvable()) {
      int cur;
      for (int i = 0; i < 16; ++i) {
        if (!a[i]) {
          cur = i;
          break;
        }
      }
      for (int limit = GaoH();; ++limit) {
        if (Dfs(cur, 0, -1, limit)) {
          path[limit] = 0;
          printf("%s\n", path);
          break;
        }
        break;
      }
    } else {
      printf("This puzzle is not solvable.\n");
    }
  }
  return 0;
}
