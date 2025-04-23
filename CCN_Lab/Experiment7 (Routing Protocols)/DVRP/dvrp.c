#include <stdio.h>

struct Node {
    int dist[20]; // Store distances
    int from[20]; // Store previous nodes
}route[10]; // Store routing information

int main(){
    int dm[20][20], no; // Distance matrix and number of nodes

    // Input number of nodes
    printf("Enter the number of nodes: ");
    scanf("%d", &no);

    // Input distance matrix
    printf("Enter the distance matrix:\n");
    for(int i = 0; i < no; i++){
        for(int j = 0; j < no; j++){
            scanf("%d", &dm[i][j]);
            if (i == j){
                dm[i][j] = 0; // Distance to self is 0
            }

            // Initialize routing table with direct distances
            route[i].dist[j] = dm[i][j];
            route[i].from[j] = j; // Previous node is itself
        }
    }
    int flag;

    // Apply the Bellman-Ford algorithm
    do{
        flag = 0; // Reset flag for each iteration
        for(int i = 0; i < no; i++){ // For each source node
            for(int j = 0; j < no; j++){ // For each destination node
                for(int k = 0; k < no; k++){ // For each intermediate node
                    if(route[i].dist[j] > (route[i].dist[k] + route[k].dist[j])){ // Check if path through k is shorter
                        route[i].dist[j] = route[i].dist[k] + route[k].dist[j]; // Update distance
                        route[i].from[j] = route[i].from[k]; // Update previous node
                        flag = 1; // Set flag to indicate a change
                    }
                }
            }
        }
    }while(flag); // Repeat until no changes

    // Print the routing table
    for(int i = 0; i < no; i++){
        printf("\nRouter info for router : %c\n", i + 65); // Print router info
        printf("To Router\tNext Hop\tDistance\n");
        for(int j = 0; j < no; j++){
            printf("%c\t\t%c\t\t%d\n", j + 65, route[i].from[j] + 65, route[i].dist[j]); // Print routing info
        }
    }
    return 0;
}