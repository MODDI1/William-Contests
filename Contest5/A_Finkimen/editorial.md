# Finkimen — Editorial

## Problem Summary

We are given an `N × M` grid of heights.

A robot can move from a cell to any of its 4 neighbors (up, down, left, right) **only if the next cell has height ≥ current height**.

So a robot can move:
- on flat terrain (equal height),
- uphill (higher height),
- but **never downhill**.

We can place robots on any cells.  
A robot can move any number of times as long as heights never decrease.

### Goal
Find the **minimum number of robots** so that every cell can be reached by at least one robot.

---

# Key Observations

## Observation 1 — Movement is monotonic

Every move satisfies:

```

height[next] ≥ height[current]

```

So along any path, heights never go down.

This means:
- From a low cell you can reach higher cells,
- From a high cell you can NEVER reach lower cells.

So lower cells are always "more powerful" starting points.

---

## Observation 2 — Lower starting points dominate higher ones

If a robot at a lower cell can reach some higher cells,
starting a robot at those higher cells is unnecessary.

Why?

Because:
- The lower robot can already cover them.
- The higher robot cannot cover the lower cell.

So lower cells are always better starting points.

---

# Strategy

We process cells in **increasing height order**.

For each cell:
- If it is already reachable from some earlier robot → skip it.
- Otherwise → we must place a robot here.

When we place a robot:
- We BFS from that cell,
- Move only to neighbors with height ≥ current,
- Mark all reachable cells as covered.

This simulates exactly what that robot can cover.

---

# Why This Greedy Works

## Key Idea

When we process cells from smallest height to largest:

If a cell is still uncovered,
it means **no lower or equal cell can reach it**.

So the only way to cover it is to place a robot there.

Thus every robot placement is necessary.

---

## Important Fact

If some cell A could reach cell B,
then height[A] ≤ height[B].

So A would appear earlier (or same time) in sorted order.

If A could reach B,
B would already be marked visited.

Therefore:

> Any unvisited cell we encounter cannot be reached from any lower cell.

So we must place a robot there.

---

## Proof of Optimality

### Claim 1
Whenever we place a robot, it is necessary.

If we didn't place it:
- That cell would remain unreachable,
- No other robot could reach it (all lower cells already tried).

So it must be a starting point.

---

### Claim 2
We never place unnecessary robots.

If a cell can be reached from a lower cell,
it will already be marked visited.

So we never place a robot where a lower robot could cover it.

---

### Conclusion

We place robots:
- exactly when needed,
- never more than needed.

Therefore the number of robots is minimal.

---

# Intuition

Imagine water that can only flow uphill.

Starting from the lowest spots,
the water spreads to everything it can reach.

Only places where water cannot reach
require a new source.

Those sources are exactly the robots we place.

---

# Algorithm

1. Read grid
2. Sort all cells by height ascending
3. For each cell in that order:
   - if not visited:
     - place robot (ans++)
     - BFS to all neighbors with ≥ height
     - mark visited
4. Print answer

---

# Complexity

Sorting:
```

O(NM log(NM))

```

BFS over grid:
```

O(NM)

```

Total:
```

O(NM log(NM))

````

For N,M ≤ 50 this is easily fast.

---

# Reference Solution

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> mat(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> mat[i][j];

    vector<vector<bool>> visited(n, vector<bool>(m, false));

    vector<pair<int,int>> order;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            order.push_back({i,j});

    sort(order.begin(), order.end(), [&](auto a, auto b){
        return mat[a.first][a.second] < mat[b.first][b.second];
    });

    int ans = 0;

    int dx[4]={1,0,-1,0};
    int dy[4]={0,1,0,-1};

    for(auto [i,j]:order){
        if(!visited[i][j]){
            ans++;
            queue<pair<int,int>> q;
            q.push({i,j});
            visited[i][j]=true;

            while(!q.empty()){
                auto [x,y]=q.front(); q.pop();
                for(int d=0; d<4; d++){
                    int nx=x+dx[d], ny=y+dy[d];
                    if(nx>=0&&nx<n&&ny>=0&&ny<m
                       && !visited[nx][ny]
                       && mat[nx][ny]>=mat[x][y]){
                        visited[nx][ny]=true;
                        q.push({nx,ny});
                    }
                }
            }
        }
    }

    cout<<ans<<"\n";
}
````

---

# Common Mistakes

### ❌ Using `>` instead of `>=`

Equal heights must be allowed.

### ❌ Allowing diagonal moves

Only 4-direction moves are valid.

### ❌ Processing from largest to smallest

That breaks correctness.

---

# Final Takeaway

This problem looks complex,
but the monotonic movement rule makes it simple:

> Start from lowest cells and spread uphill.
> Only cells unreachable from below need robots.

That greedy strategy is optimal.
