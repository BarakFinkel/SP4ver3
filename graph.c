#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "graph.h"
#include <math.h>
#include <limits.h>
#include "algs.h"

/* THE FUNCTIIONSS */

char build_graph(pnode *head)
{
    if (*head != NULL)
    {
        free_graph(head);
    }

    char temp; // A temporary char variable to store getInput()'s return value.
    int k;

    k = read_number(&temp);

    int listMade = create_node_list(head, k); // We create a list of nodes.
    if (listMade == -1)
    {
        printf("Allocating memory failed. Exiting Program..."); // If allocating space for the graph's nodes fails, we exit the program.
        exit(-1);
    }

    k = read_number(&temp);
    temp = getchar();

    pnode start; // Initializing pointers for nodes.
    pnode end;

    while (1)
    {

        k = read_number(&temp);     // Here we expect to get the index of the starting node of an edge.
        start = find_node(head, k); // Here we find the node with the given index, and store it's pointer in the variable 'start'.

        while (1)
        {
            k = read_number(&temp); // Here we expect to get the index of the ending node of an edge.

            if (temp != ' ')
            {
                break;
            } // If the next char is not a space, we break out of the loop.

            end = find_node(head, k); // Here we find the node with the given index, and store it's pointer in the variable 'end'.

            k = read_number(&temp); // Here we expect to get the weight of the edge.

            int edgeMade = insert_edge(start, end, k);
            if (edgeMade == -1)
            {
                printf("Allocating memory failed. Exiting Program..."); // If allocating space for an edge fails, we exit the program.
                exit(-1);
            }
        }

        if (temp != 'n')
        {
            return temp;
        }
        else
        {
            temp = getchar();
        }
    }

    return temp;
}

////////////////////

int read_number(char *c)
{

    // If the first character read is not a digit, store it to &c and return -1;
    // Else, read chars as long as they're adjacent digits and return their value in int format.
    // If the latter occurs, we expect a ' ' to be stored in &c when the function ends.

    int num = 0;
    scanf("%c", c);
    if (!((*c >= '0') && (*c <= '9')))
    {
        return -1;
    }
    while ((*c >= '0') && (*c <= '9'))
    {
        num = num * 10 + (*c - '0');
        scanf("%c", c);
    }
    return num;
}

////////////////////

char getInput(char *buffer)
{
    char c;
    int i = 0;

    while (1)
    {
        c = getchar();

        if (c == 'n')
        {
            buffer[i] = c;
            buffer[i + 1] = '\0';
            i = 0;
            return c;
        }
        else if ((c >= '0') && (c <= '9'))
        {
            buffer[i++] = c;
        }
        else
        {
            buffer[i] = '\0';
            i = 0;
            return c;
        }
    }

    return c;
}

////////////////

int create_node_list(pnode *head, int numOfNodes)
{

    pnode curr = (pnode)malloc(sizeof(node));
    if (curr == NULL)
    {
        return -1;
    }

    curr->node_num = 0;
    curr->edges = NULL;
    curr->next = NULL;

    *head = curr;

    for (int i = 1; i < numOfNodes; i++)
    {
        pnode next = (pnode)malloc(sizeof(node));
        if (next == NULL)
        {
            return -1;
        }

        next->node_num = i;
        next->edges = NULL;
        next->next = NULL;

        curr->next = next;

        curr = next;
    }

    return 0;
}

//////////////////

int insert_edge(pnode start, pnode end, int w)
{
    pedge new_edge = (pedge)malloc(sizeof(edge));
    if (new_edge == NULL)
    {
        return -1;
    }

    new_edge->weight = w;
    new_edge->startpoint = start;
    new_edge->endpoint = end;
    new_edge->next = NULL;

    pedge curr_edge = start->edges;

    if (curr_edge == NULL)
    {
        start->edges = new_edge;
    }
    else
    {
        while (curr_edge->next != NULL)
        {
            curr_edge = curr_edge->next;
        }
        curr_edge->next = new_edge;
    }

    // printf("(%d)--%d-->(%d)\n",start->node_num,new_edge->weight,end->node_num);

    return 0;
}

//////////////////

int is_number(char *buffer)
{
    int i = 0;
    while (buffer[i] != '\0')
    {
        if (!isdigit(buffer[i]))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

///////////////

void free_graph(pnode *head)
{
    if (*head == NULL)
    {
        return;
    }
    else
    {
        pnode curr = *head;

        while (curr != NULL)
        {
            pedge curr_edge = curr->edges;

            while (curr_edge != NULL)
            {
                pedge next_edge = curr_edge->next;
                free(curr_edge);
                curr_edge = next_edge;
            }

            pnode next = curr->next;
            free(curr);
            curr = next;
        }
    }
}

///////////////

pnode find_node(pnode *head, int nodeInd)
{
    pnode curr = *head;

    while (curr != NULL)
    {
        if (curr->node_num == nodeInd)
        {
            return curr;
        }
        else
        {
            curr = curr->next;
        }
    }

    return NULL;
}

///////////////

void free_edges(pnode node) // *node isnt NULL
{
    pedge curr = node->edges;
    pedge next = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }

    node->edges = NULL;
}

void res_node(pnode *head, int ind, char *c)
{
    pnode mynode = find_node(head, ind);
    free_edges(mynode);
    pnode end;
    int end_id;
    int weight;

    getchar(); // Here we expect a space after the node ind in the input, so we read it.

    while (*c != ' ' && (*c >= '0' && *c <= '9'))
    {
        end_id = read_number(c);
        if (end_id == -1)
        {
            return;
        }

        end = find_node(head, end_id);

        weight = read_number(c);

        insert_edge(mynode, end, weight);
    }
}

///////////////

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

///////////////

int factorial(int k)
{
    int fact = 1;

    for (int i = 1; i <= k; i++)
    {
        fact *= i;
    }

    return fact;
}

///////////////

// This function will allocate factorial(k) lines of memory, and will return a pointer to the first line.

int **matrix(int k)
{
    int numOfLines = factorial(k); // We calculate the number of lines of the matrix.

    int **mat = (int **)malloc(numOfLines * sizeof(int *)); // We allocate memory for the lines of the matrix.
    if (mat == NULL)
    {
        exit(-1);
    } // If the allocation fails, we exit the program.

    for (int i = 0; i < numOfLines; i++) // We allocate memory for the columns of the matrix.
    {
        mat[i] = (int *)malloc(k * sizeof(int));
        if (mat[i] == NULL)
        {
            exit(-1);
        } // If the allocation fails, we exit the program.
    }

    return mat;
}

///////////////

void de_matrix(int **arr, int k)
{
    int numOfLines = factorial(k); // We calculate the number of lines of the matrix.

    for (int i = 0; i < numOfLines; i++)
    {
        free(arr[i]);
    }          // We free the memory of the columns of the matrix.
    free(arr); // We free the memory of the lines of the matrix.
}

///////////////

/*
    This method will get an array of integers representing IDs of nodes, and will return a pointer to the first line of a matrix
    containing all the permutations of the array.

    1) *arr       - The array of integers we want to permute (the IDs of the nodes).
    2) start, end - The start and end indexes of the array.
    3) **mat      - The matrix we want to fill with the permutations of *arr.
    4) *idx       - The index of the line we want to fill in the matrix.
*/

void permute(int *arr, int start, int end, int **mat, int *idx)
{
    if (start == end)
    {
        // printf("(");
        for (int i = 0; i <= end; i++)
        {
            mat[*idx][i] = arr[i]; // We copy the permutation to the matrix to a line with index *idx.
            // printf("%d, ",mat[*idx][i]);
        }
        // printf(")\n");
        (*idx)++;
    }
    else
    {
        for (int i = start; i <= end; i++)
        {
            swap(&arr[start], &arr[i]);
            permute(arr, start + 1, end, mat, idx);
            swap(&arr[start], &arr[i]);
        }
    }
}

///////////////

// This function will go over the matrix's lines and will run dijkstra's algorithm on each line.

int dijkstra_matrix(pnode *head, int **mat, int k)
{
    int numOfLines = factorial(k); // We calculate the number of lines of the matrix.
    int min = INT_MAX;             // We initialize the minimum sum of the weights of the edges in the path to INT_MAX.
    int max_id = get_max_id(head); // We get the maximum ID of the nodes in the graph.
    for (int i = 0; i < numOfLines; i++)
    {
        int sum = 0; // We initialize the sum of the weights of the edges in the path to 0.

        for (int j = 0; j < k - 1; j++)
        {
            pnode start = find_node(head, mat[i][j]);                       // We find the node with ID mat[i][j].
            pnode end = find_node(head, mat[i][j + 1]);                     // We find the node with ID mat[i][j+1].
            int w = dijkstra(head, start->node_num, end->node_num, max_id); // We run dijkstra's algorithm on the nodes we found.
            if (w == INT_MAX)
            {
                sum = w;
                break;
            } // If dijkstra's algorithm failed, we return -1.

            sum += w; // We add the weight of the edge to the sum.
        }

        if (sum < min) // If the sum is smaller than the current minimum, we update the minimum.
        {
            min = sum;
        }
    }

    return min;
}

///////////////

// int traveling_agent(pnode *head, char *c)
// {
//                                 // We initialize a temporary char which will hold the return value of getInput().

//     c = getInput(buffer);                         // Here, we expect to get the number of nodes IDs from the graph we want to permute.
//     int k = atoi(buffer);                         // We convert the string to an integer.
//     memset(buffer, 0, strlen(buffer)+1);          // We clear the buffer.

//     int arr[k];                                   // We create an array to hold the IDs of the nodes we want to permute.

//     int i;
//     for (i = 0; i<k; i++)
//     {
//         c = getInput(buffer);                     // Here, we expect to get the IDs of the nodes we want to permute, one by one.
//         arr[i] = atoi(buffer);                    // We convert the string to an integer, and input the value in the array.
//         memset(buffer, 0, strlen(buffer)+1);      // We clear the buffer.
//     }

//     int** mat = matrix(k);                        // We allocate memory for the matrix.

//     int* idx;                                     // We initialize a pointer that will hold index of each line returned from the permute function.
//     *idx = 0;

//     permute(arr, 0, k-1, mat, idx);               // We fill the matrix with all the permutations of the the array of nodes IDs.

//     int min = dijkstra_matrix(head, mat, k);      // We run dijkstra's algorithm on each line of the matrix, and return the minimum sum of the weights of the edges in the path.

//     de_matrix(mat, k);                            // We free the memory of the matrix.

//     return min;
// }