#include <stdio.h>
#include <stdlib.h>

typedef struct edge_ edge, *pedge;
typedef struct GRAPH_NODE_ node, *pnode;

typedef struct GRAPH_NODE_
{
    int node_num;
    int visited;
    int distance;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

typedef struct edge_
{
    int weight;
    pnode startpoint;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;

char getInput(char* buffer);
char build_graph(pnode *head);
void free_graph(pnode *head);
int is_number(char* buffer);
int insert_edge(pnode start, pnode end, int w);
int create_node_list(pnode *head, int n);
pnode find_node(pnode *head, int nodeInd);
void free_edges(pnode node);
void swap(int* a, int* b);
int factorial(int k);
int** matrix(int k);
void de_matrix(int** arr, int k);
void permute(int *arr, int start, int end, int **mat, int *idx);
int read_number(char *c);
void res_node(pnode *head, int ind, char *c);
int dijkstra_matrix(pnode *head, int **mat, int k);