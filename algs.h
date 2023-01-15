#include <stdio.h>
#include <stdlib.h>

void free_edges_to_node(pnode *head, int nodeId);
void delete_node(pnode *head, int nodeId);
void print_graph(pnode *head);
void reset_node(pnode *head, int nodeId);
int read_num(char *c);
void add_edge(pnode *head, pnode from_node, int to_node, int weight);
int get_max_id(pnode *head);
pnode find_prev(pnode *head, int id);
int dijkstra(pnode *head, int start_node, int end_node, int highest_node_id);