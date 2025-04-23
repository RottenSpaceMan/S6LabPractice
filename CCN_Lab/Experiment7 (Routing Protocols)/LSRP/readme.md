# Aim
Implement and simulate algorithm for Link State Routing Protocol (LSRP) using C

# Theory
Link State Routing Protocol (LSRP) is a routing protocol in which each router shares its neighborhood information with every other router in the network. Each router maintains a complete map of the network topology and uses this information to calculate the shortest path to each destination. It uses Dijkstra's algorithm to find the shortest path.

# Algorithm
1. Read the number of nodes in the network(N)
2. Initialize a distance matrix of size N x N as dm[N][N]
3. Set dm[i][i] = 0 for all i in range(N) (distance to itself is 0)
4. Set dm[i][j] = 99999 for all i != j (initially set to infinity)
5. Read the number of links in the network
6. For each link, read the two nodes (i, j), read src, dest, and cost
7. Set dm[i][j] = cost and dm[j][i] = cost (bidirectional link)
8. Apply Dijkstra's algorithm:
    1. For each source node s in range(N):
        1. Create dist[N] and set all values to 99999
        2. Create visited[N] and set all values to false
        3. Create prev[N] and set all values to -1
        4. Set dist[s] = 0 (distance from source to itself is 0)
        5. Find the Shortest Path from source s to all other nodes:
            1. For each step (repeat N-1 times):
                1. Find unvisited node u with minimum dist[u] value
                2. If all remaining nodes have distance infinity, break
                3. Mark u as visited (visited[u] = true)
                4. For each neighbor v of node u (where dm[u][v] < 99999):
                    1. If !visited[v] && dist[u] + dm[u][v] < dist[v]:
                        1. Update dist[v] = dist[u] + dm[u][v]
                        2. Update prev[v] = u
        6. Print the routing table for s
            - Display the destination node, next hop, and cost
9. End

# Example
Let's consider a network with 4 nodes (0, 1, 2, 3) and the following links:
- Link between Node 0 and Node 1: Cost = 1
- Link between Node 0 and Node 2: Cost = 3
- Link between Node 1 and Node 2: Cost = 1
- Link between Node 2 and Node 3: Cost = 2

## Initial Distance Matrix
```
    | 0  | 1  | 2  | 3  |
---|----|----|----|----|
 0 | 0  | 1  | 3  | ∞  |
 1 | 1  | 0  | 1  | ∞  |
 2 | 3  | 1  | 0  | 2  |
 3 | ∞  | ∞  | 2  | 0  |
```

## Dijkstra's Algorithm from Source Node 0

### Initialization:
- dist[0] = 0, dist[1] = ∞, dist[2] = ∞, dist[3] = ∞
- All nodes are unvisited

### Iteration 1:
- Select node 0 (min distance = 0)
- Mark node 0 as visited
- Update distances:
  - dist[1] = min(∞, 0+1) = 1
  - dist[2] = min(∞, 0+3) = 3
  - dist[3] = min(∞, 0+∞) = ∞
- Current dist array: [0, 1, 3, ∞]
- Previous node array: [-1, 0, 0, -1]

### Iteration 2:
- Select node 1 (min distance = 1)
- Mark node 1 as visited
- Update distances:
  - dist[2] = min(3, 1+1) = 2
  - dist[3] = min(∞, 1+∞) = ∞
- Current dist array: [0, 1, 2, ∞]
- Previous node array: [-1, 0, 1, -1]

### Iteration 3:
- Select node 2 (min distance = 2)
- Mark node 2 as visited
- Update distances:
  - dist[3] = min(∞, 2+2) = 4
- Current dist array: [0, 1, 2, 4]
- Previous node array: [-1, 0, 1, 2]

### Iteration 4:
- Select node 3 (min distance = 4)
- Mark node 3 as visited
- No more nodes to visit

## Final Routing Table for Node 0

```
Destination | Next Hop | Cost
------------|----------|-----
1           | 1        | 1
2           | 1        | 2
3           | 1        | 4
```

The routing table shows that from Node 0:
- To reach Node 1: Go directly to Node 1 (cost = 1)
- To reach Node 2: Go to Node 1 first (cost = 2)
- To reach Node 3: Go to Node 1, then to Node 2, then to Node 3 (cost = 4)