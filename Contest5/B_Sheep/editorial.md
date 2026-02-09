# Sheep and Wolves — Editorial

## Problem Summary

We are given an `R × S` grid representing a yard.

Each cell can be:

```

'.'  empty
'#'  fence (blocked)
'o'  sheep
'v'  wolf

```

Movement is allowed only:
- up, down, left, right (4-directional),
- and only through cells that are NOT fences (`#`).

So fences split the yard into separate enclosed areas.

---

## Rules Inside One Area

For each enclosed area:

- If sheep > wolves → sheep survive, wolves die
- Otherwise → wolves survive, sheep die

We must compute:
```

total surviving sheep and wolves

```

across all areas.

---

# Key Observations

## Observation 1 — Fences define independent regions

Fences (`#`) cannot be crossed.

So the grid splits into multiple independent regions
consisting of cells:
```

'.', 'o', 'v'

```

Each region can be processed separately.

Nothing in one region affects another.

---

## Observation 2 — Regions are just connected components

Two cells belong to the same region if:
- both are not `#`,
- and there exists a path between them using 4-direction moves.

So each region is simply a **connected component** of non-fence cells.

---

# Strategy

We iterate through the grid.

Whenever we find a cell that:
- is not `#`,
- and not yet visited,

we BFS from it to explore its entire region.

During BFS we count:
```

sheep_count
wolf_count

```

After finishing BFS for that region:

```

if sheep_count > wolf_count:
sheep survive
else:
wolves survive

```

Add survivors to global totals.

---

# Why BFS Works Perfectly

BFS explores exactly all cells reachable without crossing fences.

So it finds exactly one enclosed area.

Every cell is visited once,
so every region is processed once.

---

# Proof of Correctness

## Claim 1 — BFS finds exactly one region

BFS only moves to neighbors that:
- are inside grid,
- are not fences,
- are not visited.

So BFS explores exactly one connected component.

---

## Claim 2 — The rule is applied correctly

The problem states survival depends only on counts inside the enclosed area.

Since BFS collects all cells of that area,
the decision is correct.

---

## Claim 3 — All regions are processed

We start BFS from every unvisited non-fence cell.

So every region is covered.

---

## Conclusion

We:
- find all regions,
- count sheep and wolves inside each,
- apply the rule correctly,
- sum survivors.

Therefore the algorithm is correct.

---

# Algorithm

For each cell (i,j):
```

if not visited and not '#':
BFS from (i,j)
count sheep and wolves
apply rule
add survivors to totals

```

---

# Complexity

Each cell is visited at most once.

Each BFS processes a region once.

So total time:
```

O(R × S)

```

For R,S ≤ 250 this is very fast.

Memory:
```

O(R × S)

````

---

# Reference Solution

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int R,S;
    cin>>R>>S;

    vector<string> g(R);
    for(int i=0;i<R;i++) cin>>g[i];

    vector<vector<bool>> vis(R, vector<bool>(S,false));

    int totalSheep=0, totalWolves=0;

    int dr[4]={1,0,-1,0};
    int dc[4]={0,1,0,-1};

    for(int i=0;i<R;i++){
        for(int j=0;j<S;j++){

            if(g[i][j]=='#' || vis[i][j]) continue;

            int sheep=0, wolves=0;

            queue<pair<int,int>> q;
            q.push({i,j});
            vis[i][j]=true;

            if(g[i][j]=='o') sheep++;
            if(g[i][j]=='v') wolves++;

            while(!q.empty()){
                auto [r,c]=q.front(); q.pop();

                for(int d=0;d<4;d++){
                    int nr=r+dr[d], nc=c+dc[d];

                    if(nr<0||nr>=R||nc<0||nc>=S) continue;
                    if(vis[nr][nc]) continue;
                    if(g[nr][nc]=='#') continue;

                    vis[nr][nc]=true;

                    if(g[nr][nc]=='o') sheep++;
                    if(g[nr][nc]=='v') wolves++;

                    q.push({nr,nc});
                }
            }

            if(sheep>wolves) totalSheep+=sheep;
            else totalWolves+=wolves;
        }
    }

    cout<<totalSheep<<" "<<totalWolves<<"\n";
}
````
# Intuition

Each fenced region is like a separate battlefield.

Inside each battlefield:

* either sheep win,
* or wolves win.

We just simulate each battlefield independently.

---

# Final Takeaway

This is a classic grid BFS problem:

> Find connected components and apply rules per component.

Simple once you see fences split the grid.