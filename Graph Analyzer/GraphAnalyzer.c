#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define help 0
#define read 1
#define minpath 2
#define mst 3
#define MAXNODE 100

typedef struct { char *key; int val; } t_transition_table;

static t_transition_table transition_table[] = {
    {"help", help},
    {"read", read},
    {"minpath", minpath},
    {"mst", mst}
};

int tranform_cmd(char *cmd)
{
    for(int i = 0; i < 4; i++)
    {
        t_transition_table *cmp = &transition_table[i];
        if(strcmp(cmd, cmp->key) == 0)
        {
            return cmp->val;
        }
    }
    return -1;
}

int main()
{
    char cmd[100];
    int num = 0; // vertex number
    int **graph;
    int openFile = 0;
    puts("Enter command: ");
    fgets(cmd, sizeof(cmd), stdin);
    cmd[strcspn(cmd, "\n")] = 0;

    while(strcmp(cmd, "quit") != 0){ // maybe need to trim space at the beginning and end of cmd
        char *token = strtok(cmd, " ");
        // printf("Command: %s\n", token);
        switch (tranform_cmd(token))
        {
        case 0:
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                printf("COMMANDS:\n1. read: To read in a file.\nUSAGE: read <filename>\n2. minpath: To calculate the minimum path between two vertex.\nUSAGE: minpath <v1> <v2>\n3. mst: To find minimum spanning tree.\nUSAGE: mst\n");
            }
            else
            {
                switch (tranform_cmd(token))
                {
                case 1:
                    printf("To read in a file.\nUSAGE: read <filename>\n");
                    break;
                case 2:
                    printf("To calculate the minimum path between two vertex.\nUSAGE: minpath <v1> <v2>\n");
                    break;
                case 3:
                    printf("To find minimum spanning tree.\nUSAGE: mst\n");
                    break;
                }
            }
            break;
        case 1:
            token = strtok(NULL, " ");
            // printf("File name: %s\n", token);
            FILE *fp = fopen(token, "r");
            if (fp == NULL)
            {
                printf("File not found\n");
                return 1;
            }
            char ch = getc(fp);
            num = atoi(&ch);
            // printf("Number of vertex: %d\n", num);
            graph = (int **)malloc(num * sizeof(int *));
            for (int i = 0; i < num; i++)
            {
                graph[i] = (int *)malloc(num * sizeof(int));
            }
            for (int i = 0; i < num; i++)
            {
                for (int j = 0; j < num; j++)
                {
                    ch = getc(fp);
                    if (ch == ' ' || ch == '\n')
                    {
                        ch = getc(fp);
                    }
                    graph[i][j] = atoi(&ch);
                }
            }
            // check input
            // for (int i = 0; i < num; i++)
            // {
            //     for (int j = 0; j < num; j++)
            //     {
            //         printf("%d ", graph[i][j]);
            //     }
            //     printf("\n");
            // }
            fclose(fp);
            printf("Reading File: %s Success!\n", token);
            openFile = 1;
            break;
        case 2:
            // SP
            if (openFile == 0)
            {
                printf("Please read in a file first\n");
                break;
            }
            token = strtok(NULL, " ");
            int src = atoi(token);
            token = strtok(NULL, " ");
            int dest = atoi(token);
            // printf("%d\t%s", src, dest);
            // dijkstra's algorithm
            int dist[MAXNODE]; // assuming max number of nodes is 100
            int visited[MAXNODE]; // assuming max number of nodes is 100
            for (int i = 0; i < num; i++) 
            {
                dist[i] = graph[src][i];
                visited[i] = 0;
            }
            dist[src] = 0;
            visited[src] = 1;
            
            for (int i = 0; i < num - 1; i++) 
            {
                int min = 999, u;
                for (int j = 0; j < num; j++) 
                {
                    if (!visited[j] && dist[j] <= min) 
                    {
                        min = dist[j];
                        u = j;
                    }
                }
                visited[u] = 1;
                //relax
                for (int v = 0; v < num; v++) 
                {
                    if (!visited[v] && graph[u][v] && dist[u] != 999 && dist[u] + graph[u][v] < dist[v]) 
                    {
                        dist[v] = dist[u] + graph[u][v];
                    }
                }
                if (u == dest)
                {
                    printf("Minimum path from %d to %d is %d\n", src, dest, dist[dest]);
                }
            }
            break;
        case 3:
            if (openFile == 0)
            {
                printf("Please read in a file first\n");
                break;
            }
            // MST
            int parent[MAXNODE];
            // printf("MST");
            for (int i = 0; i < num; i++)
            {
                parent[i] = i;
            }
            int edge = 0;
            int weight_sum = 0;
            while( edge != num - 1 )
            {
                int min = 999, a = -1, b = -1;
                for (int i = 0; i < num; i++)
                {
                    for (int j = i + 1; j < num; j++)
                    {
                        int parent_i = i, parent_j = j;
                        while (parent[parent_i] != parent_i)
                        {
                            parent_i = parent[parent_i];
                        }
                        while (parent[parent_j] != parent_j)
                        {
                            parent_j = parent[parent_j];
                        }
                        if (parent_i != parent_j && graph[i][j] < min)
                        {
                            
                            min = graph[i][j];
                            a = i;
                            b = j;
                        }
                    }
                }
                // disjoint set operation
                // a
                int parent_a = a, parent_b = b;
                while (parent[parent_a] != parent_a)
                {
                    parent_a = parent[parent_a];
                }
                while (parent[parent_b] != parent_b)
                {
                    parent_b = parent[parent_b];
                }
                if (parent_a != parent_b)
                {
                    printf("Edge %d: (%d, %d) = %d\n", ++edge, a, b, min);
                    weight_sum += min;
                    parent[parent_a] = parent_b; // union
                }
                
            }
            printf("Weight sum: %d\n", weight_sum);
            break;
        
        default:
            printf("Invalid command\n");
            break;
        }
        puts("Enter command: ");
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strcspn(cmd, "\n")] = 0;
    }
}