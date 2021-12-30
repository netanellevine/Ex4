#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "graph.h"



void freeGraph(ptrNode head);
void printGraph_cmd(ptrNode head);
void addEdge(ptrNode *head, int source, int dest, int weight);
void initGraph(ptrNode *head, int size);

int main() {
    printf("START!\n");
    char input;
    int DONE = 0;
    int amount_of_nodes = 0;
    ptrNode ptrGraph;
    while (DONE != EOF) {
        DONE = scanf("%c", &input);
        switch (input) {
            case 'A': {
                // initiating the Graph nodes.
                scanf("%d", &amount_of_nodes);
                initGraph(&ptrGraph, amount_of_nodes);
                break;
            }
            case 'n': {
                int src = -1;
                int dest = -1;
                int weight = -1;
                int num = -1;
                scanf("%d", &src);
                while (scanf("%d", &num)) {
                    if (src != -1 && dest == -1 && weight == -1) {
                        dest = num;
                    } else if (src != -1 && dest != -1 && weight == -1) {
                        weight = num;
                    }
                     if (src != -1 && dest != -1 && weight != -1) {
                        addEdge(&ptrGraph, src, dest, weight);
                        dest = -1;
                        weight = -1;
                    }
                }
                break;
            }
            case 'E': {
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
    freeGraph(ptrGraph);
    return 0;
}


void initGraph(ptrNode *head, int size){
    int amount_of_nodes = size;
    // initiating the Graph nodes.
    ptrNode last = NULL;
    ptrNode node;
    for (int i = 0; i < amount_of_nodes; ++i) {
        node = (ptrNode) malloc(sizeof(Node));
        if (node == NULL) {
            printf("Memory didn't allocated!\n");
            exit(0);
        }
        node->node_num = i;
        node->next = NULL;
        node->edges_s = 0;
        node->edges = NULL;
        if (i == 0) {
            *head = node;
            last = *head;
        } else if (i > 0) { // last is not NULL
            last->next = node;
            last = node;
        }
    }
}


void addEdge(ptrNode *head, int source, int dest, int weight) {
    ptrNode curr_n, temp;
    ptrNode end = NULL;

    curr_n = (*head);
    while (curr_n != NULL && curr_n->node_num != source) {
        if (curr_n->node_num == dest) {
            end = curr_n;
        }
        curr_n = curr_n->next;
    }

    temp = (*head);
    while (end == NULL) {
        if (temp->node_num == dest) {
            end = temp;
        }
        temp = temp->next;
    }
    if (curr_n->edges_s == 0) {
        ptrEdge e;
        e = (ptrEdge) malloc(sizeof(Edge));
        if (e == NULL) {
            printf("Memory didn't allocated!\n");
            exit(0);
        }
        e->endpoint = end;
        e->weight = weight;
        e->next = NULL;
        curr_n->edges_s++;
        curr_n->edges = e;
    } else {
        ptrEdge curr_e = curr_n->edges;
        while (curr_e->next != NULL) {
            curr_e = curr_e->next;
        }
        ptrEdge newEdge;
        newEdge = (ptrEdge) malloc(sizeof(Edge));
        if (newEdge == NULL) {
            printf("Memory didn't allocated!\n");
            exit(0);
        }
        newEdge->endpoint = end;
        newEdge->weight = weight;
        newEdge->next = NULL;
        curr_e->next = newEdge;
        curr_n->edges_s++;
    }
}


void printGraph_cmd(ptrNode head) {
    printf("[");
    ptrNode temp;
    temp = head->next;
    while (temp != NULL) {
        int id = temp->node_num;
        printf("(ID: %d,\n [", id);
        ptrEdge e = temp->edges;
        while (e->next != NULL) {
            int dest = e->endpoint->node_num;
            int weight = e->weight;
            printf("E(%d->%d,%d) ", id, dest, weight);
        }
        printf("],\n");
        printf("next -> %d)", temp->next->node_num);
        temp = temp->next;
    }
    printf("]\n");
}


void freeGraph(ptrNode head) {
    if (head == NULL) {
        return;
    }
    ptrNode curr_n;
    curr_n = head;
    while (curr_n != NULL) {
        ptrNode next_node = curr_n->next;
        ptrEdge curr_e = curr_n->edges;
        while (curr_e != NULL) {
            ptrEdge next_edge = curr_e->next;
            free(curr_e);
            curr_e = next_edge;
        }
        free(curr_n);
        curr_n = next_node;
    }
}