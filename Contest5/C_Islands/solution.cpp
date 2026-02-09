#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> mat(n+2, vector<char>(m+2, '.'));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mat[i][j];
        }
    }
    int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
    int dy[8] = {0, 1, 0, -1, 1, -1, 1, -1};
    vector<vector<int>> water_id(n+2, vector<int>(m+2, -1));
    vector<vector<int>> land_id(n+2, vector<int>(m+2, -1));
    int water_count = 0, land_count = 0;
    for (int i = 0; i < n + 2; i++){
        for (int j = 0; j < m + 2; j++) {
            if (mat[i][j] != '.' || water_id[i][j] != -1) continue;
            queue<pair<int, int>> q;
            water_id[i][j] = water_count;
            q.push({i, j});
            while (!q.empty()) {
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                for (int dir = 0; dir < 4; dir++) {
                    int nx = x + dx[dir], ny = y + dy[dir];
                    if (nx >= 0 && nx < n + 2 && ny >= 0 && ny < m + 2 && mat[nx][ny] == '.' && water_id[nx][ny] == -1) {
                        water_id[nx][ny] = water_count;
                        q.push({nx, ny});
                    }
                }
            }
            water_count++;
        }
    }
    for (int i = 0; i < n + 2; i++) {
        for (int j = 0; j < m + 2; j++) {
            if (mat[i][j] != 'x' || land_id[i][j] != -1) continue;
            queue<pair<int, int>> q;
            land_id[i][j] = land_count;
            q.push({i, j});
            while (!q.empty()) {
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                for (int dir = 0; dir < 8; dir++) {
                    int nx = x + dx[dir], ny = y + dy[dir];
                    if (nx >= 0 && nx < n + 2 && ny >= 0 && ny < m + 2 && mat[nx][ny] == 'x' && land_id[nx][ny] == -1) {
                        land_id[nx][ny] = land_count;
                        q.push({nx, ny});
                    }
                }
            }
            land_count++;
        }
    }
    int V = water_count + land_count;
    vector<vector<int>> adj(V);
    vector<set<int>> touches(land_count);
    for (int i = 0; i < n + 2; i++) {
        for (int j = 0; j < m + 2; j++) {
            if (mat[i][j] == 'x') {
                int id = land_id[i][j];
                for (int dir = 0; dir < 4; dir++) {
                    int nx = i + dx[dir], ny = j + dy[dir];
                    if (nx >= 0 && nx < n + 2 && ny >= 0 && ny < m + 2 && mat[nx][ny] == '.') {
                        touches[id].insert(water_id[nx][ny]);
                    }
                }
            }
        }
    }
    for (int id = 0; id < land_count; id++) {
        int islandNode = water_count + id;
        for (int waterId : touches[id]) {
            adj[islandNode].push_back(waterId);
            adj[waterId].push_back(islandNode);
        }
    }
    int root = water_id[0][0];
    vector<int> parent(V, -1);
    vector<vector<int>> children(V);
    vector<int> order;
    queue<int> q;
    parent[root] = root;
    q.push(root);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : adj[u]) {
            if (parent[v] == -1) {
                parent[v] = u;
                children[u].push_back(v);
                q.push(v);
            }
        }
    }
    vector<int> maxLand(V, -1), level(land_count,0);
    for (int idx = (int)order.size()-1; idx >= 0; idx--) {
        int u = order[idx];
        if (u < water_count) {
            int mx = -1;
            for (int ch : children[u]) mx = max(mx, maxLand[ch]);
            maxLand[u] = mx;
        }
        else {
            int id = u - water_count;
            int enclosedMax = -1;
            for (int ch : children[u]) enclosedMax = max(enclosedMax, maxLand[ch]);
            if (enclosedMax == -1)  level[id] = 0;
            else level[id] = enclosedMax + 1;
            maxLand[u] = max(level[id], enclosedMax);
        }
    }

    int Lmax = 0;
    for (int id = 0; id < land_count; id++) Lmax = max(Lmax, level[id]);

    vector<int> cnt(Lmax + 1, 0);
    for (int id = 0; id < land_count; id++) cnt[level[id]]++;
    for (int i = 0; i <= Lmax; i++) cout << cnt[i] << "\n";
    return 0;

}