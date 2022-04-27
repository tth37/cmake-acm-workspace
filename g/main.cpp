#include <algorithm>
#include <iostream>

using namespace std;

const int N = 3e5 + 5;
const int INF = 2e9 + 7;

int t, n;
int a[N], b[N], c[N], d[N], w[N];
int u[N << 2], L;
int max_right[N << 2], max_left[N << 2];
int max_up[N << 2], max_down[N << 2];

int main() {
#ifdef LOCAL_DEBUG
  std::string path = PROJECT_SRC_DIR;
  path += "/g";
  freopen((path + "/test.in").c_str(), "r", stdin);
  freopen((path + "/test.out").c_str(), "w", stdout);
#endif
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d%d%d%d", &a[i], &b[i], &c[i], &d[i]),
          u[++L] = a[i], u[++L] = b[i], u[++L] = c[i], u[++L] = d[i];
    for (int i = 1; i <= n; ++i)
      scanf("%d", &w[i]);
    sort(u + 1, u + L + 1);
    L = unique(u + 1, u + L + 1) - u - 1;
    for (int i = 0; i <= L + 1; ++i) {
      max_right[i] = max_left[i] = max_up[i] = max_down[i] = -INF;
    }
    for (int i = 1; i <= n; ++i) {
      a[i] = lower_bound(u + 1, u + L + 1, a[i]) - u;
      b[i] = lower_bound(u + 1, u + L + 1, b[i]) - u;
      c[i] = lower_bound(u + 1, u + L + 1, c[i]) - u;
      d[i] = lower_bound(u + 1, u + L + 1, d[i]) - u;
      max_right[a[i]] = max(max_right[a[i]], w[i]);
      max_left[c[i]] = max(max_left[c[i]], w[i]);
      max_up[b[i]] = max(max_up[b[i]], w[i]);
      max_down[d[i]] = max(max_down[d[i]], w[i]);
    }
    for (int i = 1; i <= L; ++i)
      max_left[i] = max(max_left[i], max_left[i - 1]);
    for (int i = 1; i <= L; ++i)
      max_down[i] = max(max_down[i], max_down[i - 1]);
    for (int i = L; i >= 1; --i)
      max_right[i] = max(max_right[i], max_right[i + 1]);
    for (int i = L; i >= 1; --i)
      max_up[i] = max(max_up[i], max_up[i + 1]);
    int ans = -INF;
    for (int i = 1; i <= n; ++i) {
      int mx = -INF;
      int right = c[i];
      if (right != L)
        mx = max(mx, max_right[right + 1]);
      int left = a[i];
      if (left != 1)
        mx = max(mx, max_left[left - 1]);
      int up = d[i];
      if (up != L)
        mx = max(mx, max_up[up + 1]);
      int down = b[i];
      if (down != 1)
        mx = max(mx, max_down[down - 1]);
      if (mx != -INF)
        ans = max(ans, mx + w[i]);
      //      cout << i << ' ' << max_right[right + 1] << ' ' << max_left[left -
      //      1]
      //           << ' ' << max_up[up + 1] << ' ' << max_down[down - 1] << ' '
      //           << mx
      //           << ' ' << ans << endl;
    }
    if (ans == -INF)
      printf("-1\n");
    else
      printf("%d\n", ans);
  }
  return 0;
}