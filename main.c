#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "graph.h"
//char input = NULL;
//Node graph;
//ptrNode ptrGraph = &graph;
int k = 0;
void printGraph_cmd(ptrNode head);
void addEdge(ptrNode head, int *source, int *dest, int *weight);

int main() {
    printf("START!\n");
    char input = NULL;
    Node graph;
    ptrNode ptrGraph = &graph;
    ptrGraph = (ptrNode *) malloc(sizeof(ptrNode));
    while (true)
    {
        scanf("%c", &input);
        switch (input)
        {
            case 'A':
            {
                // initiating the Graph nodes.
                while (input != 'n')
                {
                    int amount_of_nodes = 0;
                    scanf("%c", &input);
                    if (input > 47 && input < 58)
                    {
                        amount_of_nodes = input - '0';
                        ptrNode arr[amount_of_nodes];
                        for (int i = 0; i < amount_of_nodes; ++i) {
                            arr[i] = (ptrNode ) malloc(sizeof(ptrNode));
                            if (arr[i] == NULL)
                            {
                                printf("Memory didn't allocated!\n");
                                exit(0);
                            }
                            arr[i]->node_num = i;
                            arr[i]->next = NULL;
                            arr[i]->edges = NULL;
                            if (i > 0)
                            {
                                arr[i - 1]->next = arr[i];
                            }
                        }
                        ptrGraph->next = arr[0];
//                        printGraph_cmd(ptrGraph);
                    }
                }
                if(input == 'n')
                {
                    int src = -1;
                    int dest = -1;
                    int weight = -1;
                    scanf("%c", &input);
                    while (input != 'A'
                           && input != 'B' && input != 'D'
                           && input != 'S' && input != 'T'
                           && input != 'E' && input != '\n')
                    {
                        scanf("%c", &input);
                        if (input > 47 && input < 58 && src == -1)
                        {
                            src = input - '0';
                        }
                        else if (input > 47 && input < 58 && dest == -1)
                        {
                            dest = input - '0';
                        }
                        else if (input > 47 && input < 58 && weight == -1)
                        {
                            weight = input - '0';
                        }
                        if(src != -1 && dest != -1 && weight != -1)
                        {
                            addEdge(ptrGraph, &src, &dest, &weight);
                            dest = -1;
                            weight = -1;
                        }
                        if(input == 'n')
                        {
                            src = -1;
                            dest = -1;
                            weight = -1;
                        }
                    }
                }
                printGraph_cmd(ptrGraph);
            }
            case 'E':
            {
                free(ptrGraph);
                break;
            }
//            case 'B':
//            {
//
//            }
//            case 'D':
//            {
//
//            }
//            case 'S':
//            {
//
//            }
//            case 'T':
//            {
//
//            }
        }
    }
//    printGraph_cmd(arr);
    free(ptrGraph);
    return 0;
}

void addEdge(ptrNode head, int *source, int *dest, int *weight){
    ptrNode curr, temp;
    ptrNode end = NULL;

    curr = head->next;
    while(curr != NULL && curr->node_num != *source)
    {
        if(curr->node_num == *dest)
        {
            end = curr;
        }
        curr = curr->next;
    }

    temp = head->next;
    while(end == NULL)
    {
        if(temp->node_num == *dest)
        {
            end = temp;
        }
        temp = temp->next;
    }
    if(curr->edges_s == 0)
    {
        ptrEdge e = curr->edges;
        e = (ptrEdge) malloc(sizeof(ptrEdge));
        if (e == NULL) {
            printf("Memory didn't allocated!\n");
            exit(0);
        }
        e->endpoint = end;
        e->weight = *weight;
        e->next = NULL;
        curr->edges_s++;
    }
    else
    {
        ptrEdge e = (curr->edges);
        int size = curr->edges_s + 1;
        e = (ptrEdge) realloc(e, sizeof(ptrEdge) * size);
        if (e == NULL) {
            printf("Memory didn't allocated!\n");
            exit(0);
        }
        (e + size -1)->endpoint = end;
        (e + size -1)->weight = *weight;
        (e + size -1)->next = NULL;
        (e + size -2)->next = (e + size -1);
        curr->edges_s = size;
    }
}


void printGraph_cmd(ptrNode head){
    printf("[");
    ptrNode temp;
    temp = head->next;
    while(temp != NULL)
    {
        int id = temp->node_num;
        printf("(ID: %d,\n [", id);
        ptrEdge e = temp->edges;
        while(e->next != NULL)
        {
            int dest = e->endpoint->node_num;
            int weight = e->weight;
           printf("E(%d->%d,%d) ",id, dest, weight);
        }
        printf("],\n");
        printf("next -> %d)", temp->next->node_num);
        temp = temp->next;
    }
    printf("]\n");
}