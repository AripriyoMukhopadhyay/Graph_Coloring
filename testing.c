#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 50000
#define POOL_SIZE 6

typedef struct Graph_t {
    int V;
    bool adj[MAX_VERTICES][MAX_VERTICES];
} Graph;

Graph* Graph_create(int V) {
    Graph* g = malloc(sizeof(Graph));
    g->V = V;

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            g->adj[i][j] = false;
        }
    }

    return g;
}

void Graph_destroy(Graph* g) {
    free(g);
}

void Graph_addEdge(Graph* g, int v, int w) {
    g->adj[v][w] = true;
}

int GraphSize(Graph* g, int s) {
    bool visited[MAX_VERTICES];
    int count = 0;
    for (int i = 0; i < g->V; i++) {
        visited[i] = false;
    }

    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[s] = true;
    queue[rear++] = s;

    while (front != rear) {
        s = queue[front++];
        count++;

        for (int adjacent = 0; adjacent < g->V; adjacent++) {
            if (g->adj[s][adjacent] && !visited[adjacent]) {
                visited[adjacent] = true;
                queue[rear++] = adjacent;
            }
        }
    }
    return count;
}

int** generateArray(int rows, int cols) {
    int** myArray = (int**)malloc(rows * sizeof(int*));

    for (int i = 0; i < rows; i++) {
        myArray[i] = (int*)malloc(cols * sizeof(int));
    }

    srand(time(0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            myArray[i][j] = rand() % 7 + 1;
        }
    }

    return myArray;
}

void swap(int arr[][6], int r1, int c, int r2) {
    int temp = arr[r1][c];
    arr[r1][c] = arr[r2][c];
    arr[r2][c] = temp;
}

int randomIndex(int chromosome[][6]) {
    int col = sizeof(chromosome[0]) / sizeof(chromosome[0][0]);
    int num;
    num = rand() % col;
    return num;
}

int randomChrom() {
    int num;
    num = rand() % (POOL_SIZE);
    return num;
}

void Crossover(int chromosome[][4])
{
    int col = sizeof(chromosome[0])/sizeof(chromosome[0][0]);
    int c1, c2, index1, index2;
    double probablity;
    
    for(int i=0; i<POOL_SIZE/2; i++)
    {
        probablity = (double)rand()/ (double)RAND_MAX;
        if(probablity < 0.7)
        {
            int start, end;
            c1 = randomChrom();
            do {
                c2 = randomChrom();
            } while (c1 == c2);
            
            index1 = randomIndex(chromosome);
            do {
                index2 = randomIndex(chromosome);
            } while (index1 == index2);
            
            if (index1 > index2)
            {
                start = index2;
                end = index1;
            }
            else
            {
                start = index1;
                end = index2;
            }
            printf("\n%d %d %d %d %0.3f\n", c1, c2, index1, index2, probablity);
    
            for(int x=start; x<=end; x++)
            {
                swap(chromosome, c1, x, c2);
            }
        }
    }
}

int main() {
    Graph* g = Graph_create(6);
    Graph_addEdge(g, 0, 1);
    Graph_addEdge(g, 1, 2);
    Graph_addEdge(g, 2, 3);
    Graph_addEdge(g, 3, 3);
    Graph_addEdge(g, 4, 3);
    Graph_addEdge(g, 2, 4);
    Graph_addEdge(g, 5, 3);
    Graph_addEdge(g, 4, 5);

    int cols = GraphSize(g, 0);
    printf("%d\n", cols);
    int rows = 6;

    int** myArray = generateArray(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%2d ", myArray[i][j]);
        }
        printf("\n");
    }

    int chromosome[POOL_SIZE][6];
    for (int i = 0; i < POOL_SIZE; i++) {
        for (int j = 0; j < 6; j++) {
            chromosome[i][j] = myArray[i][j];
        }
    }

    Crossover(chromosome);

    printf("Array Contents after Crossover:\n");
    for (int i = 0; i < POOL_SIZE; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%2d ", chromosome[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        free(myArray[i]);
    }
    free(myArray);
    Graph_destroy(g);

    return 0;
}
