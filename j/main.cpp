//Author:rabbyte
#include <cstdio>
#include <cstring>
#include <algorithm>

const int max_len = 2e5 + 10;
const int key = 1e9 + 7;
int T, n, bucket[max_len], bucket2[max_len], t[max_len], A[max_len], B[max_len], sa[max_len], rk[max_len], height[max_len];
char st[max_len];
long long ans;

void SA_sort(char * S, int n) {
  for (int i = 0; i < 26; i++) bucket[i] = 0;
  for (int i = 1; i <= n; i++) bucket[S[i] - 'a']++;
  for (int i = 1; i < 26; i++) bucket[i] += bucket[i - 1];
  for (int i = n; i; i--) sa[bucket[S[i] - 'a']--] = i;

  rk[sa[1]] = 1;
  for (int i = 2; i <= n; i++) {
    rk[sa[i]] = rk[sa[i - 1]];
    if(S[sa[i]] != S[sa[i - 1]]) rk[sa[i]]++;
  }

  for (int len = 1; rk[sa[n]] < n; len <<= 1) {
    for (int i = 1; i <= n; i++) bucket[i] = bucket2[i] = 0;
    for (int i = 1; i <= n; i++) {
      A[i] = rk[i]; B[i] = ((i + len <= n) ? rk[i + len] : 0);
      bucket[A[i]]++; bucket2[B[i]]++;
    }
    for (int i = 1; i <= n; i++) bucket2[i] += bucket2[i - 1];
    for (int i = n; i; i--) t[bucket2[B[i]]--] = i;
    for (int i = 1; i <= n; i++) bucket[i] += bucket[i - 1];
    for (int i = n; i; i--) sa[bucket[A[t[i]]]--] = t[i];

    rk[sa[1]] = 1;
    for (int i = 2; i <= n; i++) {
      rk[sa[i]] = rk[sa[i - 1]];
      if(A[sa[i]] != A[sa[i - 1]] || B[sa[i]] != B[sa[i - 1]]) rk[sa[i]]++;
    }
  }
  int h = 0;
  for (int i = 1; i <= n; i++) {
    if (rk[i] == 1) continue;
    if (h) h--;
    while (S[i + h] == S[sa[rk[i] - 1] + h]) h++;
    height[rk[i]] = h;
  }
}

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    scanf("%s", st + 1);
    SA_sort(st, n);
    ans = 0;
    for (int i = 1, a, b, c; i <= n; i++) {
      a = height[i];
      for (int j = i - 1; j; j--) {
        if (sa[i] < sa[j]) {
          b = n - sa[i] + 1 - a;
          c = n - sa[j] + 1 - a;
          ans = (ans + (long long)a * b % key + a * (a - 1) / 2ll % key + (long long)b * c % key) % key;
        }
        a = std::min(a, height[j]);
      }
      a = height[i + 1];
      for (int j = i + 1; j <= n; j++) {
        if (sa[i] < sa[j]) {
          b = n - sa[i] + 1 - a;
          c = n - sa[j] + 1 - a;
          ans = (ans + (long long)a * b % key + a * (a - 1) / 2ll % key) % key;
        }
        a = std::min(a, height[j + 1]);
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}