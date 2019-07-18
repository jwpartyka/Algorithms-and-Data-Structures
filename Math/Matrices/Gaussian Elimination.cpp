#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int eps = 1e-9, inf = 1e9;

pair<int, vector<double>> Gauss(vector<vector<double>> a) {
  int n = a.size(), m = a[0].size() - 1;
  vector<int> where(m, -1);

  for (int row = 0, col = 0; col < m && row < m; ++col) {
    int pivot = row;
    for (int i = row; i < n; ++i) {
      if (abs(a[i][col]) > abs(a[pivot][col])) {
        pivot = i;
      }
    }
    if (abs(a[pivot][col]) < eps) {
      continue;
    }
    if (pivot != row) {
      for (int i = col; i <= m; ++i) {
        swap(a[row][i], a[pivot][i]);
      }
    }
    where[col] = row;

    for (int i = m; i >= col; --i) {
      a[row][i] /= a[row][col];
    }
    for (int i = row + 1; i < n; ++i) {
      for (int j = m; j >= col; --j) {
        a[i][j] -= a[row][j] * a[i][col];
      }
    }

    row++;
  }

  vector<double> res(m, 0);
  for (int i = m - 1; i >= 0; --i) {
    if (where[i] != -1) {
      res[i] = a[where[i]][m];
      for (int j = m - 1; j > i; --j) {
        res[i] -= a[where[i]][j] * res[j];
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      a[i][m] -= a[i][j] * res[j];
    }
    if (abs(a[i][m]) > eps) {
      return {0, res};
    }
  }
  for (int i = 0; i < m; ++i) {
    if (where[i] == -1) {
      return {inf, res};
    }
  }
  return {1, res};
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  //cout << setprecision(13) << fixed;

  int n, m;
  cin >> n >> m;
  vector<vector<double>> a(n, vector<double>(m, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> a[i][j];
    }
  }

  auto res = Gauss(a);
  for (int i = 0; i < m - 1; ++i) {
    cout << res.second[i] << " ";
  }
  cout << "\n";
}
