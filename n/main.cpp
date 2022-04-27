#include <iostream>

using namespace std;

int main() {
#ifdef LOCAL_DEBUG
  std::string path = PROJECT_SRC_DIR;
  path += "/a";
  freopen((path + "/test.in").c_str(), "r", stdin);
  freopen((path + "/test.out").c_str(), "w", stdout);
#endif
  int a, b;
  cin >> a >> b;
  cout << a + b << endl;
  return 0;
}