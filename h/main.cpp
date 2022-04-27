#include <algorithm>
#include <iostream>

using namespace std;

const int N = 2e5 + 5;
typedef long long ll;

int n;
int l[N], r[N], b[N << 1], L;
ll sl[N], sr[N], ssl[N], ssr[N];

struct SegmentTree {
  struct Node {
    int l, r, val, tag; // min value
  } node[N << 2];
  int cnt, R;
#define lson(u) node[u].l
#define rson(u) node[u].r
#define val(u) node[u].val
#define tag(u) node[u].tag
  void build(int &u, int l, int r) {
    u = ++cnt;
    val(u) = 0;
    if (l == r)
      return;
    int mid = (l + r) >> 1;
    build(lson(u), l, mid);
    build(rson(u), mid + 1, r);
  }

  void pushdown(int u) {
    if (tag(u)) {
      tag(lson(u)) += tag(u);
      val(lson(u)) += tag(u);
      tag(rson(u)) += tag(u);
      val(rson(u)) += tag(u);
      tag(u) = 0;
    }
  }

  void modify(int u, int l, int r, int ql, int qr, int x) {
    if (ql <= l && r <= qr) {
      val(u) += x;
      tag(u) += x;
      return;
    }
    pushdown(u);
    int mid = (l + r) >> 1;
    if (ql <= mid)
      modify(lson(u), l, mid, ql, qr, x);
    if (qr > mid)
      modify(rson(u), mid + 1, r, ql, qr, x);
    val(u) = min(val(lson(u)), val(rson(u)));
  }

  int find(int u, int l, int r) {
    if (l == r)
      return l;
    pushdown(u);
    int mid = (l + r) >> 1;
    if (val(rson(u)) < 0)
      return find(rson(u), mid + 1, r);
    return find(lson(u), l, mid);
  }
} T;

struct BIT {
  ll c[N << 1];
  void modify(int p, ll x) {
    for (; p <= L - 2; p += p & -p)
      c[p] += x;
  }
  ll query(int p) {
    ll res = 0;
    for (; p; p -= p & -p)
      res += c[p];
    return res;
  }
} BT1, BT2, BT3, BT4;

int main() {
#ifdef LOCAL_DEBUG
  std::string path = PROJECT_SRC_DIR;
  path += "/h";
  freopen((path + "/test.in").c_str(), "r", stdin);
  freopen((path + "/test.out").c_str(), "w", stdout);
#endif
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &l[i], &r[i]);
    b[++L] = l[i];
    b[++L] = r[i];
    sl[i] = l[i];
    sr[i] = r[i];
  }
  b[++L] = -(1e9 + 1);
  b[++L] = 1e9 + 1;
  sort(b + 1, b + L + 1);
  L = unique(b + 1, b + L + 1) - b - 1;
  T.build(T.R, 1, L - 1);
  sort(sl + 1, sl + n + 1);
  sort(sr + 1, sr + n + 1);
  for (int i = 1; i <= n; ++i)
    ssl[i] = ssl[i - 1] + sl[i], ssr[i] = ssr[i - 1] + sr[i];
  for (int i = 1; i <= n; ++i) {
    int neg_l = 1;
    int neg_r = lower_bound(b + 1, b + L + 1, l[i]) - b - 1;
    int pos_l = lower_bound(b + 1, b + L + 1, r[i]) - b;
    int pos_r = L - 1;
    T.modify(T.R, 1, L - 1, neg_l, neg_r, -1);
    T.modify(T.R, 1, L - 1, pos_l, pos_r, 1);

    int pos = T.find(T.R, 1, L - 1);
    int val = b[pos + 1];

    int l_ = neg_r;
    int r_ = pos_l - 1;
    BT1.modify(l_, 1);
    BT2.modify(l_, l[i]);
    BT3.modify(r_, 1);
    BT4.modify(r_, r[i]);

    ll ans = 0;
    ll lcnt = BT3.query(pos);
    ll lsum = BT4.query(pos);
    ll rcnt = BT1.query(L - 2) - BT1.query(pos - 1);
    ll rsum = BT2.query(L - 2) - BT2.query(pos - 1);

    //    cout << lcnt << ' ' << lsum << ' ' << rcnt << ' ' << rsum << ' ' <<
    //    val
    //         << endl;

    ans += 1ll * val * lcnt - lsum;
    ans += rsum - 1ll * val * rcnt;
    printf("%lld\n", ans);
  }
  return 0;
}