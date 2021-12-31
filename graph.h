#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH *ptrNode;

typedef struct edge_ {
    int weight;
    ptrNode endpoint;
    struct edge_ *next;
} Edge, *ptrEdge;


typedef struct GRAPH {
    int node_num;
    int edges_s;
    int nodes_s;
    ptrEdge edges;
    struct GRAPH *next;
} Node, *ptrNode;

typedef struct QUEUE {
    ptrNode Vertex;
    int shortestDist;
    int visited;
    struct QUEUE *next;
}Queue, *ptrQueue;

void build_graph_cmd(ptrNode *head);
void insert_node_cmd(ptrNode *head);
void delete_node_cmd(ptrNode *head);
void printGraph_cmd(ptrNode head); //for self debug
void deleteGraph_cmd(ptrNode* head);
void shortsPath_cmd(ptrNode head);
void TSP_cmd(ptrNode head);

#endif
