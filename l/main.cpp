#include <iostream>
#include <queue>

typedef long long ll;

using namespace std;

int t, n, k;
ll a[200005], strength, ans;

int main() {
#ifdef LOCAL_DEBUG
  std::string path = PROJECT_SRC_DIR;
  path += "/l";
  freopen((path + "/test.in").c_str(), "r", stdin);
  freopen((path + "/test.out").c_str(), "w", stdout);
#endif
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  cin >> t;
  while (t--) {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
      cin >> a[i];
    priority_queue<ll> q;
    for (int i = 1; i <= k; ++i)
      q.push(-a[i]);
    int p = k + 1;
    strength = ans = 0;
    while (!q.empty()) {
      ll cur = q.top();
      cur = -cur;
      q.pop();
      if (p <= n) {
        q.push(-a[p]);
        ++p;
      }
      if (cur > strength) {
        ans += cur - strength;
        strength = cur;
      }
      strength += cur;
    }
    cout << ans << endl;
  }

  return 0;
}