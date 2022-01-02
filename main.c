#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "graph.h"
#include "Queue.h"

#define BIG_NUM 99999999

ptrNode lastNode;
int graphSize;
int shortestPathWeight = BIG_NUM;

int main() {
    printf("START!\n");
    char input;
    int DONE = 0;
    int amount_of_nodes = 0;
    ptrNode ptrGraph = NULL;
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
                int ans = shortestPath(queue, dest);
                freeQueue(&queue);
                printf("Shortest Path from %d to %d is: %d", source, dest, ans);
                break;
            }
            case 'T':
            {
                int amount_of_cities, num;
                scanf("%d", &amount_of_cities);
                int *cities;
                cities = (int*)malloc(sizeof(int) * amount_of_cities);
                if(cities == NULL){
                    printf("Memory didn't allocated!\n");
                    exit(0);
                }
                for(int i = 0; i < amount_of_cities; i++){
                    scanf("%d", &num);
                   *(cities + i) =  num;
                }
                heapPermuteTSP(ptrGraph, cities, amount_of_cities, amount_of_cities);
                printf("TSP shortest path: %d \n", shortestPathWeight);
                free(cities);
                break;
            }
            case 'E': {
                exit(0);
            }
            default:{
                break;
            }
        }
    }
    freeGraph(&ptrGraph);
    return 0;
}


//void initGraph(ptrNode *head, int size){
//    int amount_of_nodes = size;
//    // initiating the Graph nodes.
//    ptrNode last = NULL;
//    ptrNode node;
//    for (int i = 0; i < amount_of_nodes; ++i) {
//        node = (ptrNode) malloc(sizeof(Node));
//        if (node == NULL) {
//            printf("Memory didn't allocated!\n");
//            exit(0);
//        }
//        node->node_num = i;
//        node->next = NULL;
//        node->edges_s = 0;
//        node->edges = NULL;
//        if (i == 0) {
//            *head = node;
//            last = *head;
//        } else if (i > 0) { // last is not NULL
//            last->next = node;
//            last = node;
//        }
//    }
//    lastNode = last;
//    graphSize = amount_of_nodes;
//}
//
//
//void addEdge(ptrNode *head, int source, int dest, int weight) {
//    ptrNode curr_n, temp;
//    ptrNode end = NULL;
//
//    curr_n = (*head);
//    while (curr_n != NULL && curr_n->node_num != source) {
//        if (curr_n->node_num == dest) {
//            end = curr_n;
//        }
//        curr_n = curr_n->next;
//    }
//
//    temp = (*head);
//    while (end == NULL) {
//        if (temp->node_num == dest) {
//            end = temp;
//        }
//        temp = temp->next;
//    }
//    if (curr_n->edges_s == 0) {
//        ptrEdge e;
//        e = (ptrEdge) malloc(sizeof(Edge));
//        if (e == NULL) {
//            printf("Memory didn't allocated!\n");
//            exit(0);
//        }
//        e->endpoint = end;
//        e->weight = weight;
//        e->next = NULL;
//        curr_n->edges_s++;
//        curr_n->edges = e;
//    } else {
//        ptrEdge curr_e = curr_n->edges;
//        while (curr_e->next != NULL) {
//            curr_e = curr_e->next;
//        }
//        ptrEdge newEdge;
//        newEdge = (ptrEdge) malloc(sizeof(Edge));
//        if (newEdge == NULL) {
//            printf("Memory didn't allocated!\n");
//            exit(0);
//        }
//        newEdge->endpoint = end;
//        newEdge->weight = weight;
//        newEdge->next = NULL;
//        curr_e->next = newEdge;
//        curr_n->edges_s++;
//    }
//}
//
//
//void printGraph_cmd(ptrNode head) {
//    ptrNode temp;
//    temp = head;
//    while (temp != NULL) {
//        int id = temp->node_num;
//        printf("(ID: %d, [", id);
//        ptrEdge e = temp->edges;
//        while (e != NULL) {
//            int dest = e->endpoint->node_num;
//            int weight = e->weight;
//            printf("E(%d->%d,%d) ", id, dest, weight);
//            e = e->next;
//        }
//        int next_id = -1;
//        if(temp->next != NULL) {
//            next_id = temp->next->node_num;
//        }
//        printf("], next -> %d)\n", next_id);
//        temp = temp->next;
//    }
//}
//
//
//bool contains(ptrNode head, int id){
//    ptrNode curr_n = head;
//    while(curr_n != NULL){
//        if(curr_n->node_num == id){
//            return true;
//        }
//        curr_n = curr_n->next;
//    }
//    return false;
//}
//
//
//void freeGraph(ptrNode *head) {
//    if (head == NULL) {
//        return;
//    }
//    ptrNode curr_n;
//    curr_n = *head;
//    while (curr_n) {
//        ptrNode next_node = curr_n->next;
//        freeEdges(&curr_n);
//        free(curr_n);
//        curr_n = next_node;
//    }
//}
//
//
//void freeQueue(ptrQueue *head){
//    if (head == NULL) {
//        return;
//    }
//    ptrQueue curr_q;
//    curr_q = *head;
//    while (curr_q) {
//        ptrQueue next_q = curr_q->next;
//        free(curr_q);
//        curr_q = next_q;
//    }
//}
//
//
//void freeEdges(ptrNode *node) {
//    if (node == NULL) {
//        return;
//    }
//    ptrEdge curr_e = (*node)->edges;
//    while (curr_e != NULL) {
//        ptrEdge next_edge = curr_e->next;
//        free(curr_e);
//        curr_e = next_edge;
//    }
//}
//
//
//void addNode(ptrNode *head, int id){
//    ptrNode newNode;
//    newNode = (ptrNode) malloc(sizeof(Node));
//    if (newNode == NULL) {
//        printf("Memory didn't allocated!\n");
//        exit(0);
//    }
//    newNode->node_num = id;
//    newNode->next = NULL;
//    newNode->edges = NULL;
//    newNode->edges_s = 0;
//    lastNode->next = newNode;
//    lastNode = newNode;
//    graphSize++;
//}
//
//
//ptrNode getNode(ptrNode head, int id){
//    ptrNode curr_n;
//    curr_n = head;
//    while(curr_n->node_num != id){
//        curr_n = curr_n->next;
//    }
//    return curr_n;
//}
//
//
//void removeEdge(ptrNode *node, int dest){
//    ptrEdge edges = (*node)->edges;
//    ptrEdge last = (*node)->edges;
//    if((*node)->edges->endpoint->node_num == dest){
//        (*node)->edges = edges->next;
//        free(edges);
//        (*node)->edges_s--;
//        return;
//    }
//    while(edges != NULL){
//        if(edges->endpoint->node_num == dest){
//            last->next = edges->next;
//            free(edges);
//            (*node)->edges_s--;
//            break;
//        }
//        last = edges;
//        edges = edges->next;
//    }
//}
//
//
//void remove_in_edges(ptrNode *head, int id){
//    ptrNode curr = *head;
//    while(curr != NULL){
//        ptrEdge edges = curr->edges;
//        while(edges != NULL){
//            if(edges->endpoint->node_num == id){
//                removeEdge(&curr, id);
//                break;
//            }
//            edges = edges->next;
//        }
//        curr = curr->next;
//    }
//}
//
//
//void removeNode(ptrNode *head, int id){
//    ptrNode curr = *head;
//    ptrNode last;
//    if(curr->node_num == id){
//        (*head) = curr->next;
//    }
//    else {
//        while (curr->node_num != id) {
//            last = curr;
//            curr = curr->next;
//        }
//        last->next = curr->next;
//    }
//    freeEdges(&curr);
//    remove_in_edges(head, id);
//    free(curr);
//    graphSize++;
//}


//ptrQueue initQueue(ptrNode head, int src){
//    ptrQueue queue;
//    queue = (ptrQueue) malloc(sizeof(Queue));
//    if (queue == NULL) {
//        printf("Memory didn't allocated!\n");
//        exit(0);
//    }
//    queue->visited = 0;
//    queue->shortestDist =0;
//    queue->Vertex = getNode(head, src);
//    ptrNode curr;
//    ptrQueue last = NULL;
//    bool firstTime = false;
//    curr = head;
//    while(curr != NULL) {
//        if (curr->node_num != src) {
//            ptrQueue q = (ptrQueue) malloc(sizeof(Queue));
//            if (q == NULL) {
//                printf("Memory didn't allocated!\n");
//                exit(0);
//            }
//            q->visited = 0;
//            q->shortestDist = BIG_NUM;
//            q->Vertex = curr;
//            q->next = NULL;
//            if (!firstTime) {
//                queue->next = q;
//                last = q;
//                firstTime = true;
//            } else {
//                last->next = q;
//                last = q;
//            }
//        }
//        curr = curr->next;
//    }
//    return queue;
//}
//
//
//void sortQueue(ptrQueue *head){
////Node q1 will point to head
//    ptrQueue prev = NULL, q1 = *head, q2 = NULL;
//
//    if(*head == NULL) {
//        return;
//    }
//    else {
//        while(q1 != NULL) {
//            //Node q2 will point to node next to q1
//            q2 = q1->next;
//
//            while(q2 != NULL) {
//                //If q1 node's data is greater than q2's node data, swap the data between them
//                if(q1->shortestDist > q2->shortestDist && q2->visited == 0) {
//                    ptrQueue temp;
//                    ptrQueue q2_next;
//                    q2_next = q2->next;
//                    temp = q1;
//                    q1 = q2;
//                    q2 = temp;
//                    q2->next = q2_next;
//                    q1->next = q2;
//                    if(prev != NULL) {
//                        prev->next = q1;
//                    }
//                    else{
//                        (*head) = q1;
//                    }
//                }
//                q2 = q2->next;
//            }
//            prev = q1;
//            q1 = q1->next;
//        }
//    }
//}
//
//
//ptrQueue deQueue(ptrQueue *head){
//    ptrQueue last, newHead;
//    newHead = (*head)->next;
//    last = *head;
//    *head = newHead;
//    return last;
//}
//
//
//ptrQueue getFirstUnvisited(ptrQueue head){
//    ptrQueue  curr;
//    curr = head;
//    while(curr->visited != 0){
//        curr = curr->next;
//    }
//    return curr;
//}
//
//
//ptrQueue getQNode(ptrQueue head, int id){
//    ptrQueue curr = head;
//    while(curr){
//        if(curr->Vertex->node_num == id) {
//            break;
//        }
//        curr = curr->next;
//    }
//    return curr;
//}
//
//
//int shortestPath(ptrQueue head, int dest){
//    ptrQueue queue;
//    queue = head;
//    int visited = 0;
//    int *distArray = NULL;
//    while(visited < graphSize){
//        ptrQueue current = getFirstUnvisited(queue);
//        current->visited = 1;
//        visited++;
//        ptrEdge edges = current->Vertex->edges;
//        while(edges) {
//            ptrQueue adj = getQNode(head, edges->endpoint->node_num);
//            if (adj->visited == 0) {
//                int new_dist = edges->weight + current->shortestDist;
//                int old_dist = adj->shortestDist;
//                if (new_dist < old_dist) {
//                    adj->shortestDist = new_dist;
//                }
//            }
//                edges = edges->next;
//        }
//        sortQueue(&queue);
//    }
//    shortestPathWeight = getQNode(head, dest)->shortestDist;
//    if (shortestPathWeight == BIG_NUM){
//        shortestPathWeight = -1;
//    }
//    return shortestPathWeight;
//}
//
//
//void swap (int *x, int *y){
//    int temp;
//    temp = *x;
//    *x = *y;
//    *y = temp;
//}
//
//
//void heapPermuteTSP(ptrNode head, int cities_to_visit[], int size, int original_size) {
//    int i;
//    if (size == 1) {
//        calculateTSP(head, cities_to_visit, original_size);
//    }
//    else {
//        for (i = 0; i < size; i++) {
//            heapPermuteTSP(head ,cities_to_visit, size-1, original_size);
//            if (size % 2 == 1) {
//                swap(&cities_to_visit[0], &cities_to_visit[size-1]);
//            }
//            else {
//                swap(&cities_to_visit[i], &cities_to_visit[size-1]);
//            }
//        }
//    }
//}
//
//
//void calculateTSP(ptrNode head, int *arr, int size){
//    int i = 0, j = 1, currentMinDist = 0, src, dest;
//    while(j < size){
//        src = *(arr + i);
//        dest = *(arr + j);
//        ptrQueue queue = initQueue(head, src);
//        currentMinDist += shortestPath(queue, dest);
//        freeQueue(&queue);
//        i++;
//        j++;
//    }
//    if(currentMinDist < shortestPathWeight){
//        shortestPathWeight = currentMinDist;
//    }
//}

