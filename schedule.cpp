//
//  main.cpp
//  schedule
//
//  Created by muchuanyun on 16/10/2.
//  Copyright © 2016 muchuanyun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long unsigned int int64;

typedef struct treeNode* tPtr;

typedef struct treeNode {
    char name[9];
    int64 val;
} tnode;


const int64 MAXVAL = 4294967296;//  (int64)1 << (int64)32

const int MAXN = 4000000;

tnode heap_nodes[MAXN];

#define InHeap(n, i)  ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) )
#define Parent(i) ((i-1) >> 1)
#define LChild(i) (1 + ((i) << 1))  // odd
#define RChild(i) ((1 + (i)) << 1)  // even

int cnt = 0;


int tnode_cmp(tPtr node1, tPtr node2)
{
    if (node1->val < node2->val)
        return 1;
    else if (node1->val > node2->val)
        return -1;
    else {
        if ( strcmp(node2->name, node1->name) > 0)
            return 1;
        else
            return -1;
    }
}

int properPapa(tPtr* heap, int i)
{
    int j, tmp;
    
    int lc_idx = LChild(i);
    int rc_idx = RChild(i);
    bool lc_valid, rc_valid;
    lc_valid = (InHeap(cnt, lc_idx)) ? true : false;
    rc_valid = (InHeap(cnt, rc_idx)) ? true : false;
    
    if (lc_valid && rc_valid) {
        tmp = (tnode_cmp(heap[i], heap[lc_idx]) > 0) ? i : lc_idx;
        j = (tnode_cmp(heap[tmp], heap[rc_idx]) > 0) ? tmp : rc_idx;
    } else if (lc_valid && !rc_valid) {
        j = (tnode_cmp(heap[i], heap[lc_idx]) > 0) ? i : lc_idx;
    } else if (!lc_valid && rc_valid) {
        j = (tnode_cmp(heap[i], heap[rc_idx]) > 0) ? i : rc_idx;
    } else {
        j = i;
    }
        
    return j;
}

int percolateDown(tPtr* heap, int n, int i)
{
    int j;
    //tPtr tmp;
    tnode tmp;
    while ( i != (j = properPapa(heap, i)) ) {
        //swap heap_nodes[i], heap_nodes[j];
        tmp = heap_nodes[i];
        heap_nodes[i] = heap_nodes[j];
        heap_nodes[j] = tmp;
        
        i = j;
    }
    return i;
}

int main() {
    #ifndef _OJ_
        freopen("/Users/muchuanyun/Documents/001-Research/03-Moocs/DS_THU/dsa_pa/pa2/schedule/schedule/input1.in", "r", stdin);
        //freopen("output.txt", "w", stdout);
    #endif
    setvbuf(stdin, (char*)malloc(1 << 20), _IOFBF, 1 << 20);
    setvbuf(stdout, (char*)malloc(1 << 20), _IOFBF, 1 << 20);
    
    int n, m;
    scanf("%d %d\n", &n, &m);
    
    tPtr* heap = new tPtr[n];
    cnt = n;
    
    for (int i = 0; i < n; i++) {
        scanf("%lld %s\n", &(heap_nodes[i].val), (heap_nodes[i].name));
        heap[i] = &(heap_nodes[i]);
    }
    
    // construct the heap
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        percolateDown(heap, n, i);
    }

    
    for (int i = 0; i < m; i++) {
        
        /*
        if (cnt > 0) {
            printf("current heap:\n");
            for (int t = 0; t < cnt; t++) {
                printf("%s (val: %llu) ||", heap[t]->name, heap[t]->val);
            }
            printf("\n");
        }
        */
        
        if (cnt >= 1) {
            printf("%s\n", heap_nodes[0].name);
        
            if (heap_nodes[0].val * 2 < MAXVAL)
                heap_nodes[0].val *= 2;
            else
                heap_nodes[0] = heap_nodes[--cnt];
            
            percolateDown(heap, cnt, 0);
        } else {
            break;
        }
        
    }
    
    delete [] heap;
    return 0;
}
