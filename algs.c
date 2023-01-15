#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "graph.h"
#include <math.h>
#include <limits.h>
#include "algs.h"

void free_edges_to_node(pnode *head, int nodeId){
    pnode currNode = *head;
    while(currNode != NULL){
        pedge currEdge = currNode->edges;
        pedge prevEdge = NULL;
        while(currEdge != NULL){
            if(currEdge->endpoint->node_num == nodeId)
            {
                if(prevEdge == NULL)
                {
                    currNode->edges = currEdge->next;
                }
                else
                {
                    prevEdge->next = currEdge->next;
                }
                free(currEdge);
                currEdge = prevEdge;
            }
            prevEdge = currEdge;
            if(currEdge != NULL)
            {
                currEdge = currEdge->next;
            }
        }
        currNode = currNode->next;
    }
}

void reset_node(pnode *head, int nodeId){
    pnode currNode = *head;
    if(find_node(head, nodeId) == NULL){
        while (currNode != NULL &&currNode->next != NULL){
            currNode = currNode->next;
        }
        pnode newNode = (pnode)malloc(sizeof(node));
        newNode->node_num = nodeId;
        newNode->edges = NULL;
        newNode->next = NULL;
        currNode->next = newNode;
        return;
    }
    
    while(currNode != NULL){
        if(currNode->node_num == nodeId){
            break;
        }
        currNode = currNode->next;
    }
    // free node edges
    pedge currEdge = currNode->edges;
    while(currEdge != NULL){
        pedge nextEdge = currEdge->next;
        free(currEdge);
        currEdge = nextEdge;
    }
    currNode->edges = NULL;
}

void print_graph(pnode *head){
    pnode currNode = *head;
    while(currNode != NULL){
        printf("node %d: \n",currNode->node_num);
        pedge currEdge = currNode->edges;
        while(currEdge != NULL){
            printf("to node %d ", currEdge->endpoint->node_num);
            printf("weighs %d \n", currEdge->weight);
            currEdge = currEdge->next;
        }
        currNode = currNode->next;
    }
}

int read_num(char *c){// the first char to read should be a number, it will read one char after 
    int num = 0;
    if((*c >= '0' ) && (*c <= '9')){
        // its good
    }
    else{
        // might be space or 'n' or any other capital letter 
        scanf("%c", c);
        return -1;
    }
    while((*c >= '0' ) && (*c <= '9')){
        num = num * 10 + (*c - '0');
        scanf("%c", c);
    }
    return num;
}

char add_node(pnode *head, int nodeId){
    pnode newNode;
    if((newNode = find_node(head, nodeId)) != NULL){
        reset_node(head, nodeId);
    }
    else{
        newNode = (pnode)malloc(sizeof(node));
        newNode->node_num = nodeId;
        newNode->edges = NULL;
        newNode->next = NULL;
        pnode currNode = *head;
        if(currNode == NULL){
            *head = newNode;
        }
        else{
            while(currNode->next != NULL){
                currNode = currNode->next;
            }
            currNode->next = newNode;
        }
    }
    while(1){
        char c = getchar();
        int to_node = read_num(&c);// when i call this, the first char should be a number
        if (to_node == -1){
            return c;
        }
        int weight = read_num(&c);
        add_edge(head, newNode, to_node, weight);
    }
}

void add_edge(pnode *head, pnode from_node, int to_node, int weight){
    pedge newEdge = (pedge)malloc(sizeof(edge));
    newEdge->endpoint = find_node(head, to_node);
    newEdge->weight = weight;
    newEdge->next = NULL;
    pedge currEdge = from_node->edges;
    if(currEdge == NULL){
        from_node->edges = newEdge;
    }
    else{
        while(currEdge->next != NULL){
            currEdge = currEdge->next;
        }
        currEdge->next = newEdge;
    }
}

int get_max_id(pnode *head){
    int max = -1;
    pnode currNode = *head;
    while(currNode != NULL){
        if(currNode->node_num > max){
            max = currNode->node_num;
        }
        currNode = currNode->next;
    }
    return max;
}
/*
int dijkstra(pnode *head, int start_node, int end_node, int max_id)
{
    int dist[max_id + 1];
    int visited[max_id + 1];
    
    for (int i = 0; i <= max_id; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    
    dist[start_node] = 0;
    
    int to_visit[max_id + 1];
    
    for(int i = 0; i <= max_id; i++) { to_visit[i] = i; }
    
    while (to_visit[0] != -1) 
    {
        int curr_node = -1;
        int min = INT_MAX;

        for (int i = 0; i <= max_id; i++) 
        {
            if (visited[to_visit[i]]) { continue; }
            
            if (dist[to_visit[i]] < min) 
            {
                min = dist[to_visit[i]];
                curr_node = to_visit[i];
            }
        }

        if (curr_node == -1) break;

        visited[curr_node] = 1;
        to_visit[curr_node] = -1;

        pnode curr = find_node(head, curr_node);
        
        pedge e = curr->edges;
        
        while (e != NULL) 
        {
            pnode endpoint = e->endpoint;
            
            int new_dist = dist[curr_node] + e->weight;
            if (new_dist < dist[endpoint->node_num]) {
                dist[endpoint->node_num] = new_dist;
            }
            e = e->next;
        }
    }
    
    return dist[end_node];
}
*/
void delete_node(pnode *head, int nodeId)
{
    pnode to_delete = find_node(head, nodeId);
    if(to_delete == NULL)
    { 
        return; 
    }
    if (to_delete == *head){
        if(to_delete->next != NULL){ 
            *head = to_delete->next; 
        }
        free(to_delete);
    }    
    else{
        
        reset_node(head, nodeId);
        // free_edges_to_node(head, nodeId);   
        pnode prev = find_prev(head, nodeId);
        prev->next = to_delete->next;
        free(to_delete);
    }
    
}

pnode find_prev(pnode *head, int id){
    pnode curr = *head;
    if (curr == NULL){
        return NULL;
    }
    while(curr->next != NULL){
        if (curr->next->node_num == id){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void reset_dijkstra(pnode *head){
    pnode currNode = *head;
    while(currNode != NULL){
        currNode->visited = 0;
        currNode->distance = INT_MAX;
        currNode = currNode->next;
    }
}
int dijkstra(pnode *head, int start_node, int end_node)
{
    reset_dijkstra(head);
    pnode start = find_node(head, start_node);
    pnode end = find_node(head, end_node);
    start->distance = 0;
    pnode currNode = find_min(head);
    while(currNode != NULL){
        currNode->visited = 1;
        pedge currEdge = currNode->edges;
        while(currEdge != NULL){
            if(currEdge->endpoint->distance > currNode->distance + currEdge->weight){
                //printf("updating %d to %d\n", currEdge->endpoint->node_num, currNode->distance + currEdge->weight);
                currEdge->endpoint->distance = currNode->distance + currEdge->weight;
            }
            currEdge = currEdge->next;
        }
        currNode = find_min(head);
    }
    return end->distance;
}
pnode find_min(pnode *head){
    pnode currNode = *head;
    pnode minNode = NULL;
    int min = __INT_MAX__;
    while(currNode != NULL){
        if(currNode->visited == 0 && currNode->distance < min){
            min = currNode->distance;
            minNode = currNode;
        }
        currNode = currNode->next;
    }
    return minNode;
}