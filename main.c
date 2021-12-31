#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "graph.h"

#define BIG_NUM 99999999


void freeGraph(ptrNode *head);
void freeEdges(ptrNode *node);
void printGraph_cmd(ptrNode head);
void addEdge(ptrNode *head, int source, int dest, int weight);
void addNode(ptrNode *head, int id);
void initGraph(ptrNode *head, int size);
ptrNode getNode(ptrNode head, int id);
bool contains(ptrNode head, int id);
void removeEdge(ptrNode *node, int dest);
void remove_in_edges(ptrNode *head, int id);
void removeNode(ptrNode *head, int id);
ptrQueue initQueue(ptrNode head, int src);
void sortQueue(ptrQueue *head);
int cmp(const void *a, const void *b);
ptrQueue deQueue(ptrQueue *head);
int shortestPath(ptrQueue head, int src ,int dest, int q_size);
int getShortestDist(ptrQueue head, int id);
void setShortestDist(ptrQueue *head, int id, int dist);

ptrNode lastNode;

int main() {
    printf("START!\n");
    char input;
    int DONE = 0;
    int amount_of_nodes = 0;
    ptrNode ptrGraph;
//    ptrNode lastNode;
    while (DONE != EOF) {
        DONE = scanf("%c", &input);
        switch (input) {
            case 'A': {
                if(ptrGraph != NULL){
                    freeGraph(&ptrGraph);
                }
                // initiating the Graph nodes.
                scanf("%d", &amount_of_nodes);
                initGraph(&ptrGraph, amount_of_nodes);
                break;
            }
            case 'n': {
                // adding the node (the node id that was scanned before the 'n).
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
            case 'B':{
                // add new node, case this node already exist in the graph
                // it will remove his old edges and will update to the new ones given.
                int new_id;
                ptrNode curr_n = NULL;
                bool hasEdges = false;
                scanf("%d", &new_id);
                if(!contains(ptrGraph, new_id)){
                    addNode(&ptrGraph, new_id);
                }
                else{
                    hasEdges = true;
                    curr_n = getNode(ptrGraph, new_id);
                }
                int dest = -1;
                int weight = -1;
                int num = -1;
                while (scanf("%d", &num)) {
                    if (new_id != -1 && dest == -1 && weight == -1) {
                        dest = num;
                    } else if (new_id != -1 && dest != -1 && weight == -1) {
                        weight = num;
                    }
                    if (new_id != -1 && dest != -1 && weight != -1) {
                        if(hasEdges){
                            freeEdges(&curr_n);
                        }
                        addEdge(&ptrGraph, new_id, dest, weight);
                        dest = -1;
                        weight = -1;
                    }
                }
                break;
            }
            case 'D':{
                int id;
                scanf("%d", &id);
                if(contains(ptrGraph, id)){
                    removeNode(&ptrGraph, id);
                }
                break;
            }
            case 'P':{
                printGraph_cmd(ptrGraph);
                break;
            }
            case 'S':{
                int source, dest;
                scanf("%d", &source);
                scanf("%d", &dest);
                ptrQueue queue = initQueue(ptrGraph, source);
                qsort(&queue, ptrGraph->nodes_s, sizeof(Queue), cmp);

            }
//            case 'T':
//            {
//
//            }
        }
    }
    freeGraph(&ptrGraph);
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
    lastNode = last;
    (*head)->nodes_s = amount_of_nodes;
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
    ptrNode temp;
    temp = head;
    while (temp != NULL) {
        int id = temp->node_num;
        printf("(ID: %d, [", id);
        ptrEdge e = temp->edges;
        while (e != NULL) {
            int dest = e->endpoint->node_num;
            int weight = e->weight;
            printf("E(%d->%d,%d) ", id, dest, weight);
            e = e->next;
        }
        int next_id = -1;
        if(temp->next != NULL) {
            next_id = temp->next->node_num;
        }
        printf("], next -> %d)\n", next_id);
        temp = temp->next;
    }
}


bool contains(ptrNode head, int id){
    ptrNode curr_n = head;
    while(curr_n != NULL){
        if(curr_n->node_num == id){
            return true;
        }
        curr_n = curr_n->next;
    }
    return false;
}


void freeGraph(ptrNode *head) {
    if (head == NULL) {
        return;
    }
    ptrNode curr_n;
    curr_n = *head;
    while (curr_n != NULL) {
        ptrNode next_node = curr_n->next;
        freeEdges(&curr_n);
        free(curr_n);
        curr_n = next_node;
    }
}


void freeEdges(ptrNode *node) {
    if (node == NULL) {
        return;
    }
    ptrEdge curr_e = (*node)->edges;
    while (curr_e != NULL) {
        ptrEdge next_edge = curr_e->next;
        free(curr_e);
        curr_e = next_edge;
    }
}


void addNode(ptrNode *head, int id){
    ptrNode newNode;
    newNode = (ptrNode) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory didn't allocated!\n");
        exit(0);
    }
    newNode->node_num = id;
    newNode->next = NULL;
    newNode->edges = NULL;
    newNode->edges_s = 0;
    lastNode->next = newNode;
    lastNode = newNode;
    (*head)->nodes_s++;
}


ptrNode getNode(ptrNode head, int id){
    ptrNode curr_n;
    curr_n = head;
    while(curr_n->node_num != id){
        curr_n = curr_n->next;
    }
    return curr_n;
}


void removeEdge(ptrNode *node, int dest){
    ptrEdge edges = (*node)->edges;
    ptrEdge last = (*node)->edges;
    if((*node)->edges->endpoint->node_num == dest){
        (*node)->edges = edges->next;
        free(edges);
        (*node)->edges_s--;
        return;
    }
    while(edges != NULL){
        if(edges->endpoint->node_num == dest){
            last->next = edges->next;
            free(edges);
            (*node)->edges_s--;
            break;
        }
        last = edges;
        edges = edges->next;
    }
}


void remove_in_edges(ptrNode *head, int id){
    ptrNode curr = *head;
    while(curr != NULL){
        ptrEdge edges = curr->edges;
        while(edges != NULL){
            if(edges->endpoint->node_num == id){
                removeEdge(&curr, id);
                break;
            }
            edges = edges->next;
        }
        curr = curr->next;
    }
}


void removeNode(ptrNode *head, int id){
    ptrNode curr = *head;
    ptrNode last;
    if(curr->node_num == id){
        (*head) = curr->next;
    }
    else {
        while (curr->node_num != id) {
            last = curr;
            curr = curr->next;
        }
        last->next = curr->next;
    }
    freeEdges(&curr);
    remove_in_edges(head, id);
    free(curr);
    (*head)->nodes_s++;
}


ptrQueue initQueue(ptrNode head, int src){
    ptrQueue queue;
    queue = (ptrQueue) malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory didn't allocated!\n");
        exit(0);
    }
    queue->visited = 0;
    queue->shortestDist =0;
    queue->Vertex = getNode(head, src);
    ptrNode curr;
    ptrQueue last = NULL;
    bool firstTime = false;
    curr = head;
    while(curr != NULL) {
        if (curr->node_num != src) {
            ptrQueue q = (ptrQueue) malloc(sizeof(Queue));
            if (q == NULL) {
                printf("Memory didn't allocated!\n");
                exit(0);
            }
            q->visited = 0;
            q->shortestDist = BIG_NUM;
            q->Vertex = curr;
            q->next = NULL;
            if (!firstTime) {
                queue->next = q;
                last = q;
                firstTime = true;
            } else {
                last->next = q;
                last = q;
            }
        }
        curr = curr->next;
    }
    return queue;
}


void sortQueue(ptrQueue *head){
//Node q1 will point to head
    ptrQueue q1 = *head, q2 = NULL;
    int temp_dist;

    if(*head == NULL) {
        return;
    }
    else {
        while(q1 != NULL) {
            //Node q2 will point to node next to q1
            q2 = q1->next;

            while(q2 != NULL) {
                //If q1 node's data is greater than q2's node data, swap the data between them
                if(q1->shortestDist > q2->shortestDist) {
                    temp_dist = q1->shortestDist;
                    q1->shortestDist = q2->shortestDist;
                    q2->shortestDist = temp_dist;
                }
                q2 = q2->next;
            }
            q1 = q1->next;
        }
    }
}


int cmp(const void *a, const void *b ){
    const ptrQueue q1 = (const ptrQueue)a;
    const ptrQueue q2 = (const ptrQueue)b;

    if (q1->shortestDist > q2->shortestDist && q2->visited == 0)
    {
        return -1;
    }
    else if (q1->shortestDist <= q2->shortestDist && q1->visited == 0)
    {
        return 1;
    }
    return 1;
}


ptrQueue deQueue(ptrQueue *head){
    ptrQueue last, newHead;
    newHead = (*head)->next;
    last = *head;
    *head = newHead;
    return newHead;
    // NEED TO FREE QUEUE HEAD

}


int getShortestDist(ptrQueue head, int id){
    ptrQueue curr = head;
    while(curr->Vertex->node_num != id){
        curr = curr->next;
    }
    return curr->shortestDist;
}


void setShortestDist(ptrQueue *head, int id, int dist){
    ptrQueue curr = *head;
    while(curr->Vertex->node_num != id){
        curr = curr->next;
    }
    curr->shortestDist = dist;
}


int shortestPath(ptrQueue head, int src ,int dest, int q_size){
    ptrQueue queue = head;
    int size = q_size;
    while(queue){
        ptrQueue current = deQueue(&queue);
        size--;
        ptrEdge edges = current->Vertex->edges;
        while(edges){
            int new_dist = edges->weight + current->shortestDist;
            int old_dist = getShortestDist(head, edges->endpoint->node_num);
            if(new_dist < old_dist){
                setShortestDist(&head, edges->endpoint->node_num, new_dist);
            }
            edges = edges->next;
        }
    }
    return 0;
}