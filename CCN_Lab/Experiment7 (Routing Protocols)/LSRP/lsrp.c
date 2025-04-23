#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 10
#define INF 99999

int numNodes;
typedef struct{
    int cost;
    bool exists;
}Edge;
Edge graph[MAX_NODES][MAX_NODES]; // Adjacency matrix
bool visited[MAX_NODES]; // Visited nodes

// Function to perform Dijkstra
void dijkstra(int start){
    int distance[MAX_NODES]; // Stores shortest distance from start to each node
    int previous[MAX_NODES]; // Stores previous node in the shortest path

    // Initialize distances as infinity and visited[] nodes as false
    for(int i = 0; i < numNodes; i++){
        distance[i] = INF;
        visited[i] = false;
        previous[i] = -1;
    }
    distance[start] = 0; // Distance to start node is 0

    // Loop to find the shortest path
    for(int count = 0; count < numNodes - 1; count++){
        int minDistance = INF, minNode = -1;

        // Find the unvisited node with the smallest distance
        for(int i = 0; i < numNodes; i++){
            if(!visited[i] && distance[i] < minDistance){
                minDistance = distance[i]; // Update minDistance
                minNode = i; // Update minNode
            }
        }
        if(minNode == -1) break; // All reachable nodes visited
        visited[minNode] = true; // Mark the node as visited
        
        // Update distances to neighbors
        for(int i = 0; i < numNodes; i++){
            if(!visited[i] && graph[minNode][i].exists
                && distance[minNode] + graph[minNode][i].cost < distance[i]){
                distance[i] = distance[minNode] + graph[minNode][i].cost; // Update distance
                previous[i] = minNode; // Update previous node
            }
        }
    }

    // Print the routing table for the node
    printf("Routing table for node %d:\n", start);
    printf("Destination\tNext Hop\nCost\n");
    for(int i = 0; i < numNodes; i++){
        if(i != start){
            printf("%d\t\t%d\t\t%d\n", i, (previous[i] != -1 ? previous[i] : -1), distance[i]);
        }
    }
}

int main(){
    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    // Initialize the graph with no links(infinite cost)
    for(int i = 0; i < numNodes; i++){
        for(int j = 0; j < numNodes; j++){
            graph[i][j].cost = INF;
            graph[i][j].exists = false;
        }
    }

    int numLinks; // Number of links
    printf("Enter the number of links: ");
    scanf("%d", &numLinks);

    // Read user input for graph links
    for(int i = 0; i < numLinks; i++){
        int src, dest, cost;
        printf("Enter source, destintion and cost of link %d: ", i+1);
        scanf("%d %d %d", &src, &dest, &cost);
        
        graph[src][dest].cost = cost; // Set cost for the link
        graph[src][dest].exists = true; // Mark the link as existing
        graph[dest][src].cost = cost; // Set cost for the reverse link
        graph[dest][src].exists = true; // Mark the reverse link as existing
    }

    // Perform Dijkstra for each node
    for(int i = 0; i < numNodes; i++){
        dijkstra(i);
    }
    return 0;
}