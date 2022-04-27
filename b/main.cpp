#include <iostream>

using namespace std;

int t, n, k, x, y;

int main() {
#ifdef LOCAL_DEBUG
  std::string path = PROJECT_SRC_DIR;
  path += "/b";
  freopen((path + "/test.in").c_str(), "r", stdin);
  freopen((path + "/test.out").c_str(), "w", stdout);
#endif
  cin >> t;
  while (t--) {
    cin >> n >> k >> x >> y;
    int mx = 0;
    for (int i = 1; i <= n; ++i) {
      int tmp;
      cin >> tmp;
      mx = max(mx, tmp);
    }
    if (k * x >= mx) {
      cout << (mx + x - 1) / x << endl;
    } else {
      cout << (mx - k * x + y - 1) / y + k << endl;
    }
  }
  return 0;
}