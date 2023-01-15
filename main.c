#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "graph.h"
#include <math.h>
#include <limits.h>
#include "algs.h"

int main()
{
    char c = 0;
    pnode *head = (pnode*)malloc(sizeof(pnode)); 
    *head = NULL;
    c = getchar();
    while(1){
        
        if(c == 'A'){
            c = getchar();
            c = build_graph(head);
            //printf("char after build graph: (%c)\n",c);
        }

        else if(c == 'B'){
            
            c = getchar();
            int id = read_number(&c);
            //printf("node to reset : (%d)\n", id);
            reset_node(head, id);
            while (c == ' '){// || (c >= '0' && c <= '9')
                int to_node = read_number(&c);
                //printf("char after reading first num: (%c)\n",c);
                if(c != ' '){
                    break;
                }
                int weight = read_number(&c);
                add_edge(head, find_node(head, id), to_node, weight);
                
            }
            //printf("char after node reset: (%c)\n",c);
        }
        
        else if(c == 'D'){
            //printf("inside D: (%c)\n",c);
            c = getchar();
            int id = read_number(&c);
            //printf("id: (%d)\n",id);
            free_edges_to_node(head, id);
            delete_node(head, id);
            //printf("char after node delete: (%c)\n",c);
        }

        else if(c == 'S'){
            c = getchar();
            int src = read_number(&c);
            int dest = read_number(&c);
            int ans = dijkstra(head, src, dest, get_max_id(head));
            if (ans == INT_MAX) { ans = -1; }
            printf("Dijsktra shortest path: %d \n", ans);
        }

        else if(c == 'T')
        {
            c = getchar();
            
            int ans = 0;
            int k = read_number(&c);
            //printf("k = %d\n",k);

            int* arr = (int*)malloc(k*sizeof(int));
            
            //printf("arr: (");
            for(int i = 0; i < k; i++){
                *(arr + i) = read_number(&c);
                //printf("%d, ",*(arr + i));
            }
            //printf(").");
        
            //printf("calling matrix\n");
            int **mat = matrix(k);
            int idx = 0;
            //printf("got to permute\n");
            permute(arr, 0, k-1, mat, &idx);

            ans = dijkstra_matrix(head, mat, k);
            if (ans == INT_MAX) { ans = -1; }
            
            printf("TSP shortest path: %d \n", ans);
            de_matrix(mat, k);
            if(arr != NULL){free(arr);}
        }

        else if(c == ' ')
        {
            
            c = getchar();
            //printf("char was space and now: (%c)\n",c);
        }
        
        else
        {
            break;
        }
        
    }
    //printf("ended on a: (%c)\n",c);
    
    free_graph(head);
    free(head);
    
    return 0;
}