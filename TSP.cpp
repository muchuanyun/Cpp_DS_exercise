//
//  TSP.cpp
//  TSP
//
//  Created by muchuanyun on 16/9/16.
//  Copyright © 2016 muchuanyun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

const int SZ = 1<<20;
struct fastio{   //fast io
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;


typedef struct edge* arcPtr;
typedef struct vertex* vPtr;

typedef enum {UNDISCOVERED, DISCOVERED, VISITED} vStatus;
//typedef enum {UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD} eType;

typedef struct edge {
    vPtr incV;
    arcPtr nextArc;
    //eType type;
} arcNode;

typedef struct vertex {
    int idx;
    vStatus status;
    int inDegree;
    int outDegree;
    int dTime;
    arcPtr firstArc;
} vNode;

typedef struct {
    int V;      // number of vertices
    int E;      // number of edges
    vPtr vTab;
} alGraph;


alGraph* graph_init(int N, int M)
{
    // create al-graph
    alGraph* G;
    G = (alGraph*) malloc(sizeof(alGraph));
    
    // initialize
    G->V = N;
    G->E = M;
    G->vTab = new vNode[N];
    
    for (int i = 0; i < N; i++) {
        (G->vTab)[i].idx = i+1;
        (G->vTab)[i].status = UNDISCOVERED;
        (G->vTab)[i].inDegree = 0;
        (G->vTab)[i].outDegree = 0;
        (G->vTab)[i].dTime = 0;
        (G->vTab)[i].firstArc = NULL;
    }
    return G;
}

void add_edge(alGraph* G, int u, int v)
{
    // add edge (u, v)
    vPtr targetNode = &(G->vTab[u-1]);
    targetNode->outDegree += 1;
    
    arcPtr newArc = (arcPtr) malloc(sizeof(arcNode));
    newArc->incV = &(G->vTab[v-1]);
    newArc->incV->inDegree += 1;
    newArc->nextArc = NULL;
    //newArc->weight = 1;
    
    if ( targetNode->firstArc == NULL) {
        targetNode->firstArc = newArc;
    } else {
        arcPtr curArc = targetNode->firstArc;
        while (curArc->nextArc != NULL)
            curArc = curArc->nextArc;
        
        curArc->nextArc = newArc;
    }
}

void print_graph(alGraph* G)
{
    int N = G->V;
    // int M = G->E;
    for (int i = 0; i < N; i++) {
        vNode curNode = (G->vTab)[i];
        printf("Node %d: %d %d %d -\t", curNode.idx, curNode.inDegree, curNode.outDegree, curNode.dTime);
        
        arcPtr curArc = curNode.firstArc;
        if (curArc == NULL) {
            printf("\n");
        } else {
            while (curArc != NULL) {
                printf("%d ", curArc->incV->idx);
                curArc = curArc->nextArc;
            }
            printf("\n");
        }
    }
}

int visit(alGraph* G, int* stack, int* sp)
{
    // int clock = 0;
    int curDepth = 1;
    int maxDepth = curDepth;
    
    while (sp != stack) {
        vPtr curNode = &(G->vTab[*(--sp)-1]);
        curNode->status = VISITED;
        // printf("pop node %d from stack\n", curNode->idx);
        
        arcPtr curArc = curNode->firstArc;
        while (curArc != NULL) {
            curDepth = curNode->dTime + 1;
            vPtr neighbor = curArc->incV;
            
            if (neighbor->status != VISITED) {
                
                if (neighbor->dTime < curDepth)
                    neighbor->dTime = curDepth;
                
                (neighbor->inDegree)--;
                if (neighbor->inDegree > 0) {
                    neighbor->status = DISCOVERED;
                } else {
                    *(sp++) = neighbor->idx;
                    // printf("push node %d to stack\n", neighbor->idx);
                }
            }
            curArc = curArc->nextArc;
        }
        maxDepth = curDepth > maxDepth ? curDepth : maxDepth;
    }
    
    return maxDepth;
}


int topo_visit(alGraph* G, int* stack)
{
    int N = G->V;
    int maxDepth = 0;
    int* sp = stack;

    for (int i = 0; i < N; i++){
        vPtr curNode = &(G->vTab[i]);
        if (curNode->inDegree == 0) {
            *(sp++) = curNode->idx;
            curNode->dTime = 1;
        }
    }
    maxDepth = visit(G, stack, sp);
    
    return maxDepth;
}


int main() {
    
    #ifndef _OJ_
        freopen("/Users/muchuanyun/input1.in", "r", stdin);
        //freopen("output.txt", "w", stdout);
    #endif
    
    int N, M;  // N ~ number of nodes, M ~ number of edges
    scanf("%d %d\n", &N, &M);
    
    int* stack;
    stack = new int[N];
    
    alGraph* G = graph_init(N, M);
    
    int u, v;
    for (int i = 0; i < M; i++) {
        scanf("%d %d\n", &u, &v);
        add_edge(G, u, v);
    }
    
    // print_graph(G);
    
    int finDepth = topo_visit(G, stack);
    printf("%d\n", finDepth);
    
    delete []stack;
    
    return 0;
}
