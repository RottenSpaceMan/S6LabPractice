# Aim
Implement and simulate algorithm for Distance Vector Routing Protocol (DVRP) using C

# Theory
Distance Vector Routing Protocol (DVRP) is a routing protocol used in packet-switched networks. It is based on the Bellman-Ford algorithm and is designed to find the shortest path from a source node to all other nodes in the network. The key features of DVRP include:
1. Each node maintains a distance vector, which contains the distance to each destination node in the network.
2. Nodes periodically exchange their distance vectors with their neighbors to update their routing tables.
3. The distance vector is updated based on the received information from neighbors, and the node recalculates its routing table.

# Tip
DRAW A GRAPH AND ASSIGN WEIGHTS TO EACH EDGE. USE THE DISTANCE MATRIX'S VALUES AS THE WEIGHTS OF THE EDGES INITIALLY.

# Algorithm
1. Read the number of nodes in the network(N)
2. Initialize a distance matrix of size N x N as dm[N][N]
3. Set dm[i][i] = 0 for all i in range(N) (distance to itself is 0)
4. Read the distance matrix from the user
    - route[i].dist[j] = dm[i][j] (Initial direct distance)
    - route[i].from[j] = j (Each node assumes its direct neighbours are the best next hop)
5. Apply the Bellman-Ford algorithm:
    1. Repeat until no updates occur
        - Set flag = 0
        for each router i in range(N):
            for each destination router j in range(N):
                for each neighbour k in range(N):
                    if dm[i][j] > dm[i][k] + dm[k][j]:
                        Update route[i].dist[j] = route[i].dist[k] + route[k].dist[j]
                        Update route[i].from[j] = route[i].from[k]
                        Set flag = 1
    2. Stop if flag = 0 (No updates occurred)
6. Print the routing table for each node
    - For each router i, print:
        - Destination router j
        - Next hop router to reach destination router j(route[i].from[j])
        - Shortest distance to destination router j(route[i].dist[j])
7. End
                    