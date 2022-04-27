#include <iostream>

using namespace std;

int t, n,k;

int main() {
#ifdef LOCAL_DEBUG
  std::string path = PROJECT_SRC_DIR;
  path += "/c";
  freopen((path + "/test.in").c_str(), "r", stdin);
  freopen((path + "/test.out").c_str(), "w", stdout);
#endif
  cin >> t;
  while (t--) {
    cin >> n>>k;

    cout << endl;
  }
  return 0;
}