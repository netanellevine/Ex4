#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "graph.h"
#include "Queue.h"

#define BIG_NUM 99999999



extern int shortestPathWeight;



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


int Qsize(ptrQueue head){
    ptrQueue curr = head;
    int size = 0;
    while(curr){
        size++;
        curr = curr->next;
    }
    return size;
}


void bubbleSort(ptrQueue *head){
    ptrQueue curr = *head, q1, q2;
    int size = Qsize((ptrQueue) head);
    for(int i = 1; i < size - 1; i++){
        ptrQueue prev = curr;
        for(int j = 1; j < size - i - 1 ; j++){
            q1 = getQNodeByInd(curr, j);
            q2 = q1->next;
            if(q1->shortestDist > q2->shortestDist){
                ptrQueue q2_next = q2->next;
                ptrQueue temp;
                temp = q1;
                q1 = q2;
                q2 = temp;
                q1->next = q2;
                q2->next = q2_next;
                prev->next = q1;
            }
            prev = q1;
        }
    }
}


ptrQueue deQueue(ptrQueue *head){
    ptrQueue last, newHead;
    newHead = (*head)->next;
    last = *head;
    *head = newHead;
    return last;
}


ptrQueue getFirstUnvisited(ptrQueue head){
    ptrQueue  curr;
    curr = head;
    while(curr->visited != 0){
        curr = curr->next;
    }
    return curr;
}


ptrQueue getQNode(ptrQueue head, int id){
    ptrQueue curr = head;
    while(curr){
        if(curr->Vertex->node_num == id) {
            break;
        }
        curr = curr->next;
    }
    return curr;
}


ptrQueue getQNodeByInd(ptrQueue head, int ind){
    ptrQueue curr;
    curr = head->next;
    int i = 1;
    while(i != ind){
        i++;
        curr = curr->next;
    }
    return curr;
}


int shortestPath(ptrQueue head, int dest){
    ptrQueue queue;
    int size = Qsize(head);
    queue = head;
    int visited = 0;
    while(visited < size){
        ptrQueue current = getFirstUnvisited(queue);
        current->visited = 1;
        visited++;
        ptrEdge edges = current->Vertex->edges;
        while(edges) {
            ptrQueue adj = getQNode(head, edges->endpoint->node_num);
            if (adj->visited == 0) {
                int new_dist = edges->weight + current->shortestDist;
                int old_dist = adj->shortestDist;
                if (new_dist < old_dist) {
                    adj->shortestDist = new_dist;
                }
            }
            edges = edges->next;
        }
        bubbleSort(&queue);
//        sortQueue(&queue);
    }
    int minDist = getQNode(head, dest)->shortestDist;
//    if (minDist == BIG_NUM){
//        return -1;
//    }
    return minDist;
}


void swap (int *x, int *y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}


void heapPermuteTSP(ptrNode head, int cities_to_visit[], int size, int original_size) {
    int i;
    if (size == 1) {
        calculateTSP(head, cities_to_visit, original_size);
    }
    else {
        for (i = 0; i < size; i++) {
            heapPermuteTSP(head ,cities_to_visit, size-1, original_size);
            if (size % 2 == 1) {
                swap(&cities_to_visit[0], &cities_to_visit[size-1]);
            }
            else {
                swap(&cities_to_visit[i], &cities_to_visit[size-1]);
            }
        }
    }
}


void freeQueue(ptrQueue *head){
    if (head == NULL) {
        return;
    }
    ptrQueue curr_q;
    curr_q = *head;
    while (curr_q) {
        ptrQueue next_q = curr_q->next;
        free(curr_q);
        curr_q = next_q;
    }
}


void calculateTSP(ptrNode head, int *arr, int size){
    int i = 0, j = 1, currentMinDist = 0, currDist, src, dest;
    while(j < size){
        src = *(arr + i);
        dest = *(arr + j);
        ptrQueue queue = initQueue(head, src);
        currDist = shortestPath(queue, dest);
        if(currDist == BIG_NUM){
            currentMinDist = BIG_NUM;
            break;
        }
        currentMinDist += currDist;
        freeQueue(&queue);
        i++;
        j++;
    }
    if(currentMinDist < shortestPathWeight){
        shortestPathWeight = currentMinDist;
    }
}