#include <iostream>
#include <string>

using namespace std;

int n, T, sa[200010], rk[200010], height[200010];
std::string st;

void build_sa() {
  int *bucket = new int[n + 3];
  int *bucket2 = new int[n + 5];
  int *t = new int[n + 5];
  int *A = new int[n + 5];
  int *B = new int[n + 5];
  for (int i = 0; i < 26; i++)
    bucket[i] = 0;
  for (int i = 1; i <= n; i++)
    bucket[st[i - 1] - 'a']++;
  for (int i = 1; i < 26; i++)
    bucket[i] += bucket[i - 1];
  for (int i = n; i; i--)
    sa[bucket[st[i - 1] - 'a']--] = i;

  rk[sa[1]] = 1;
  for (int i = 2; i <= n; i++) {
    rk[sa[i]] = rk[sa[i - 1]] + (st[sa[i]] != st[sa[i - 1]]);
  }
  for (int len = 1; rk[sa[n]] < n; len <<= 1) {
    for (int i = 1; i <= n; i++)
      bucket[i] = bucket2[i] = 0;
    for (int i = 1; i <= n; i++) {
      A[i] = rk[i];
      B[i] = ((i + len <= n) ? rk[i + len] : 0);
      bucket[A[i]]++;
      bucket[B[i]]++;
    }
    for (int i = 1; i <= n; i++)
      bucket2[i] += bucket2[i - 1];
    for (int i = n; i; --i)
      t[bucket2[B[i]--]] = i;
    for (int i = 1; i <= n; i++)
      bucket[i] += bucket[i - 1];
    for (int i = n; i; --i)
      sa[bucket[A[t[i]]]--] = t[i];

    rk[sa[1]] = 1;
    for (int i = 2; i <= n; i++)
      rk[sa[i]] = rk[sa[i - 1]] +
                  (A[sa[i]] != A[sa[i - 1]] || B[sa[i]] != B[sa[i - 1]]);
  }
  delete[] bucket;
  delete[] bucket2;
  delete[] t;
  delete[] A;
  delete[] B;
}

void get_height() {
  int h = 0;
  for (int i = 1; i <= n; i++) {
    if (h)
      h--;
    while (st[i + h - 1] == st[sa[rk[i] - 2] + h])
      h++;
    height[rk[i]] = h;
  }
}

int main() {
#ifdef LOCAL_DEBUG
  std::string path = PROJECT_SRC_DIR;
  path += "/k";
  freopen((path + "/test.in").c_str(), "r", stdin);
  freopen((path + "/test.out").c_str(), "w", stdout);
#endif
  std::cin >> T;
  while (T--) {
    std::cin >> n;
    std::cin >> st;
    build_sa();
    get_height();
    for (int i = 1; i <= n; i++)
      std::cout << sa[i] << " " << height[i] << std::endl;
  }
  return 0;
}