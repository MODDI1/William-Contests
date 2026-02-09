#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> mat(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
        }
    }
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<pair<int, int>> order;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            order.push_back({i, j});
        }
    }
    sort(order.begin(), order.end(), [&](pair<int, int> a, pair<int, int> b) {
        return mat[a.first][a.second] < mat[b.first][b.second];
    });
    int ans = 0;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    for(int k = 0; k < order.size(); k++) { 
        int i = order[k].first, j = order[k].second;
        if (!visited[i][j]) {
            ans++;
            visited[i][j] = true;
            queue<pair<int, int>> q;
            q.push({i, j});
            while (!q.empty()) {
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                for (int dir = 0; dir < 4; dir++){
                    int nx = x + dx[dir], ny = y + dy[dir];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && mat[nx][ny] >= mat[x][y]) {
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
               }
            }
        }
    }
    cout << ans << "\n";
}