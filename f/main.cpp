#include <iostream>
#define ll long long
using namespace std;

int main() {
#ifdef LOCAL_DEBUG
  std::string path = PROJECT_SRC_DIR;
  path += "/f";
  freopen((path + "/test.in").c_str(), "r", stdin);
  freopen((path + "/test.out").c_str(), "w", stdout);
#endif
  ll t, n, k;
  cin >> t;
  while (t--) {
    cin >> n >> k;
    ll i, j, sum = 0, ini = 0;
    ini = n * (n + 1) / 2;
    for (i = 2, j = 1; j <= k && i <= n; i *= 2, j++) {
      ll tot = n / i;
      sum = (1 + tot) * tot / 2;
      ini -= sum;
    }
    cout << ini << endl;
  }
  return 0;
}