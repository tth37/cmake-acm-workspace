#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;
int n, q;
struct col {
  int x, y, ini;
  bool operator<(const col c) const {
    if (x == c.x)
      return y < c.y;
    return x < c.x;
  }
};
struct row {
  int x, y, ini;
  bool operator<(const row c) const {
    if (y == c.y)
      return x < c.x;
    return y < c.y;
  }
};
char tag[N], vis[N][4];
int dp[N][4];

col c[N], origin[N];
row r[N];

bool is_col(int ch) { return (ch == 0 || ch == 1); }
bool is_row(int ch) { return (ch == 2 || ch == 3); }
int tran(char ch) {
  if (ch == 'U')
    return 0;
  if (ch == 'D')
    return 1;
  if (ch == 'L')
    return 2;
  if (ch == 'R')
    return 3;
}
int change_direction(char ch, int dir) {
  if (ch == 'A')
    return 3 - dir;
  return (dir + 2) % 4;
}
int dfs(int k, int direction) {
  cout << "f:" << k << endl;
  if (vis[k][direction]) {
    if (dp[k][direction] == 0)
      return dp[k][direction] = -1;
    return dp[k][direction];
  }

  vis[k][direction] = 1;
  if (is_row(direction)) {
    col *cur =
        direction == 3
            ? upper_bound(c + 1, c + n + 2, col{origin[k].x, origin[k].y})
            : lower_bound(c + 1, c + n + 2, col{origin[k].x, origin[k].y}) - 1;
    cout << "g:" << cur->ini << endl;
    if (cur->x != origin[k].x) {
      cout << "stop" << k << endl;
      return dp[k][direction] = k;
    }

    return dp[k][direction] =
               dfs(cur->ini, change_direction(tag[cur->ini], direction));
  }
  if (is_col(direction)) {
    row *cur =
        direction == 0
            ? upper_bound(r + 1, r + n + 2, row{origin[k].x, origin[k].y})
            : lower_bound(r + 1, r + n + 2, row{origin[k].x, origin[k].y}) - 1;
    cout << "gg:" << cur->ini << endl;
    if (cur->y != origin[k].y)
      return dp[k][direction] = k;
    return dp[k][direction] =
               dfs(cur->ini, change_direction(tag[cur->ini], direction));
  }
}
int main() {
#ifdef LOCAL_DEBUG
  std::string path = PROJECT_SRC_DIR;
  path += "/d";
  freopen((path + "/test.in").c_str(), "r", stdin);
  freopen((path + "/test.out").c_str(), "w", stdout);
#endif
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> c[i].x >> c[i].y >> tag[i];
    // scanf("%d%d%c", &c[i].x, &c[i].y, &tag[i]);
    origin[i].x = r[i].x = c[i].x, origin[i].y = r[i].y = c[i].y;
    c[i].ini = r[i].ini = i;
  }
  sort(r + 1, r + n + 1);
  sort(c + 1, c + n + 1);
  r[n + 1].x = r[n + 1].y = INF;
  c[n + 1].x = c[n + 1].y = INF;

  for (int i = 1; i <= q; i++) {
    int x, y, direction;
    char ch;
    cin >> x >> y >> ch;
    // scanf("%d%d%c", &x, &y, &ch);
    direction = tran(ch);

    if (is_col(direction)) {
      col *cur = lower_bound(c + 1, c + n + 2, col{x, y});
      if (cur->x > x)
        printf("0\n");
      else {
        int ans = dfs(cur->ini, direction);
        printf("%d\n", ans);
      }
    }
    if (is_row(direction)) {
      row *cur = lower_bound(r + 1, r + n + 2, row{x, y});
      if (cur->y > y)
        printf("0\n");
      else
        printf("%d\n", dfs(cur->ini, direction));
    }
  }
  return 0;
}