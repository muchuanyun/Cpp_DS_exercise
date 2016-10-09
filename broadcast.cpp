//
//  broadcast.cpp
//  broadcast
//
//  Created by muchuanyun on 16/9/26.
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

#define WHITE 1
#define BLACK -1
#define UNDECIDED 0

typedef struct edge {
    vPtr incV;
    arcPtr nextArc;
    //eType type;
} arcNode;

typedef struct vertex {
    int idx;
    vStatus status;
    int color;
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
        (G->vTab)[i].color = UNDECIDED;
        (G->vTab)[i].firstArc = NULL;
    }
    return G;
}

void add_edge(alGraph* G, int u, int v)
{
    // add edge (u, v)
    vPtr targetNode = &(G->vTab[u-1]);
    
    arcPtr newArc1 = (arcPtr) malloc(sizeof(arcNode));
    newArc1->incV = &(G->vTab[v-1]);
    newArc1->nextArc = NULL;
    //newArc->weight = 1;
    
    if ( targetNode->firstArc == NULL) {
        targetNode->firstArc = newArc1;
    } else {
        arcPtr curArc = targetNode->firstArc;
        while (curArc->nextArc != NULL)
            curArc = curArc->nextArc;
        
        curArc->nextArc = newArc1;
    }
    
    // add edge (v, u)
    targetNode = &(G->vTab[v-1]);
    
    arcPtr newArc2 = (arcPtr) malloc(sizeof(arcNode));
    newArc2->incV = &(G->vTab[u-1]);
    newArc2->nextArc = NULL;
    //newArc->weight = 1;
    
    if ( targetNode->firstArc == NULL) {
        targetNode->firstArc = newArc2;
    } else {
        arcPtr curArc = targetNode->firstArc;
        while (curArc->nextArc != NULL)
            curArc = curArc->nextArc;
        
        curArc->nextArc = newArc2;
    }
    
}

bool BFS(alGraph* G, vPtr cur, int* quene)
{
    // int clock = 0;
    int* head = quene;
    int* tail = quene;
    
    vPtr curNode = cur;
    *(tail++) = curNode->idx;
    curNode->status = DISCOVERED;
    curNode->color = BLACK;
    
    while (head - tail != 0)
    {
        
        curNode = &(G->vTab[(*head++)-1]);
        int curColor = curNode->color;
        
        arcPtr curArc = curNode->firstArc;
        while (curArc != NULL) {
            vPtr neighbor = curArc->incV;
            if (neighbor->color == UNDECIDED) {
                neighbor->color = -(curColor);
                neighbor->status = DISCOVERED;
                *(tail++) = neighbor->idx;
            } else {
                if (neighbor->color != -(curColor))
                    return false;
            }
            curArc = curArc->nextArc;
        }
        curNode->status = VISITED;
    }
    
    return true;
}


int main() {
    
    #ifndef _OJ_
        freopen("/Users/muchuanyun/input2.in", "r", stdin);
        //freopen("output.txt", "w", stdout);
    #endif
    int N, M;
    
    scanf("%d %d\n", &N, &M);
    
    alGraph* G = graph_init(N, M);
    
    int u, v;
    for (int i = 0; i < M; i++) {
        scanf("%d %d\n", &u, &v);
        add_edge(G, u, v);
    }
    
    if (N == 1 || N == 2) {
        printf("1\n");
        return 0;
    }
    
    int* quene = new int[N];
    
    for (int i = 1; i < N; i++) {
        vPtr curNode = &(G->vTab[i-1]);
        if (curNode->status == UNDISCOVERED) {
            bool flag = BFS(G, curNode, quene);
            if (!flag) {
                printf("-1\n");
                delete []quene;
                return 0;
            }
        }
    }
    printf("1\n");
    delete []quene;
    
    return 0;
}
