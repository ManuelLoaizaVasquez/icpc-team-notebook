void CountingSort(vector<int>& p, vector<int>& c) {
  int n = (int) p.size();
  vector<int> cnt(n, 0);
  for (auto x : c) cnt[x]++;
  vector<int> new_p(n);
  vector<int> pos(n);
  pos[0] = 0;
  for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
  for (auto x : p) {
    int i = c[x];
    new_p[pos[i]] = x;
    pos[i]++;
  }
  p = new_p;
}
vector<int> p, c, lcp;
void Build(string s) {
  s += '$';
  int n = (int) s.size();
  p = vector<int>(n);
  c = vector<int>(n);
  {
    // k = 0
    vector<pair<char, int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {s[i], i};
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) p[i] = a[i].second;
    int nxt = 0;
    for (int i = 0; i < n; i++) {
      if (i > 0 && a[i].first != a[i - 1].first) nxt++;
      c[p[i]] = nxt;
    }
  }
  int k = 0;
  while ((1 << k) < n) {
    // k -> k + 1
    for (int i = 0; i < n; i++) p[i] = (p[i] - (1 << k) + n) % n;
    CountingSort(p, c);
    vector<int> c_new(n);
    int nxt = 0;
    c_new[p[0]] = 0;
    for (int i = 1; i < n; i++) {
      pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
      pair<int, int> now = {c[p[i]], c[(p[i] + (1 << k)) % n]};
      if (prev != now) nxt++;
      c_new[p[i]] = nxt;
    }
    c = c_new;
    k++;
  }
  lcp = vector<int>(n);
  k = 0;
  for (int i = 0; i < n - 1; i++) {
    int pi = c[i];
    int j = p[pi - 1];
    // lcp[i] = lcp(s[i ..], s[j ..])
    while (s[i + k] == s[j + k]) k++;
    lcp[pi] = k;
    k = max(0, k - 1);
  }
}