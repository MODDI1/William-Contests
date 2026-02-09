#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> mat(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
        }
    }
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int sheep = 0, wolves = 0;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && mat[i][j] != '#') {
                int local_sheep = 0, local_wolves = 0;
                visited[i][j] = true;
                queue<pair<int, int>> q;
                q.push({i, j});
                while (!q.empty()) {
                    int x = q.front().first;
                    int y = q.front().second;
                    q.pop();
                    if (mat[x][y] == 'o') local_sheep++;
                    else if (mat[x][y] == 'v') local_wolves++;
                    for (int dir = 0; dir < 4; dir++) {
                        int nx = x + dx[dir], ny = y + dy[dir];
                        if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && mat[nx][ny] != '#') {
                            visited[nx][ny] = true;
                            q.push({nx, ny});
                        }
                    }
                }
                if (local_sheep > local_wolves) sheep += local_sheep;
                else wolves += local_wolves;
            }
        }
    }
    cout << sheep << " " << wolves << "\n";
}