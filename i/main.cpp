#include <iostream>

using namespace std;

long long T, n, a[5010], b[5010], arr[5010], brr[5010], f[5010];
int main() {
#ifdef LOCAL_DEBUG
  std::string path = PROJECT_SRC_DIR;
  path += "/i";
  freopen((path + "/test.in").c_str(), "r", stdin);
  freopen((path + "/test.out").c_str(), "w", stdout);
#endif
  std::cin >> T;
  while (T--) {
    std::cin >> n;
    arr[0] = 0;
    brr[0] = 0;
    for (int i = 1; i <= n; i++) {
      std::cin >> a[i];
      arr[i] = a[i] + arr[i - 1];
    }
    for (int i = 1; i <= n; i++) {
      std::cin >> b[i];
      brr[i] = b[i] + brr[i - 1];
      f[i] = arr[i] >= brr[i] ? 1 : 0;
    }
    if (f[n]) {
      for (int i = 2; i <= n; i++)
        for (int j = 1; j <= i - 1; j++)
          if (f[j] && arr[i] - arr[j] >= brr[i] - brr[j] && f[j] + 1 > f[i])
            f[i] = f[j] + 1;
      std::cout << f[n] << std::endl;
    } else
      std::cout << -1 << std::endl;
  }
  return 0;
}