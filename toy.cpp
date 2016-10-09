//
//  main.cpp
//  toy
//
//  Created by muchuanyun on 16/10/6.
//  Copyright © 2016 muchuanyun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 40320  // 8! = 40320
#define QLEN 42000

int val_base[8] = {5040, 720, 120, 24, 6, 2, 1, 1};

typedef struct vertex* vPtr;

typedef struct vertex {
    bool isValid;
    
    char s[8];
    int len ;
    vPtr child[3];
    bool visited;
    vertex()
    {
        isValid = false;
        visited = false;
        len = 65535;
    }
    
    //vPtr child0; // exchange
    //vPtr child1; // shift
    //vPtr child2; // rotate
} vNode;

vPtr Graph;

vPtr queue[QLEN];
int head = 0;
int tail = 0;

int hash(char* s)
{
    int val = 0;
    
    for (int i = 0; i < 7; i++) {
        int cnt = 0;
        for (int j = i+1; j < 8; j++) {
            if (s[j] < s[i])
                cnt++;
        }
        val += cnt * val_base[i];
    }
    
    return val;
}


char* exchange(char* s)
{
    char* t = new char[8];
    for (int i = 0; i < 8; i++)
        t[i] = s[8-i-1];
    
    return t;
}

char* shift(char* s)
{
    char* t = new char[8];
    t[0] = s[3];
    t[1] = s[0];
    t[2] = s[1];
    t[3] = s[2];
    t[4] = s[5];
    t[5] = s[6];
    t[6] = s[7];
    t[7] = s[4];
    return t;
}

char* rotate(char* s)
{
    char* t = new char[8];
    t[0] = s[0];
    t[3] = s[3];
    t[4] = s[4];
    t[7] = s[7];
    t[1] = s[6];
    t[2] = s[1];
    t[5] = s[2];
    t[6] = s[5];
    
    return t;
}


vPtr childnode_init(char* s, int val)
{
    if ( Graph[val].isValid == false) {
        memcpy(Graph[val].s, s, 8 * sizeof(char));
        Graph[val].isValid = true;
        
        queue[(tail++) % QLEN] = &Graph[val];

    }
    return (&Graph[val]);
}

void graph_init(char* s_init)
{
    int root_val = hash(s_init);
    vPtr root = &Graph[root_val];
    root->isValid = true;
    memcpy(root->s, s_init, 8 * sizeof(char));
    
    queue[tail++] = root;
    
    vPtr curNode;
    
    while (head - tail != 0) {
        curNode = queue[(head++) % QLEN];
        
        char* s0 = exchange(curNode->s);
        int val0 = hash(s0);
        char* s1 = shift(curNode->s);
        int val1 = hash(s1);
        char* s2 = rotate(curNode->s);
        int val2 = hash(s2);
        
        curNode->child[0] = childnode_init(s0, val0);
        curNode->child[1] = childnode_init(s1, val1);
        curNode->child[2] = childnode_init(s2, val2);
    }
}

inline int min(int a, int b)
{
    return a < b? a:b;
}

void BFS(vPtr startNode)
{
    startNode->len = 0;
    
    int curLen;
    vPtr curNode;
    
    head = 0;
    tail = 0;
    queue[tail++] = startNode;
    startNode->visited = true;
    
    while ((head - tail) != 0)
    {
        curNode = queue[(head++) % QLEN];
        curLen = curNode->len;

        if (curNode == &Graph[0]) {
            break;
        }
        
        curNode->child[0]->len = min(curNode->child[0]->len, curLen + 1);
        curNode->child[1]->len = min(curNode->child[1]->len, curLen + 1);
        curNode->child[2]->len = min(curNode->child[2]->len, curLen + 1);
        
        
        if(!(curNode->child[0]->visited))
        {
            queue[(tail++) % QLEN] = curNode->child[0];
            curNode->child[0]->visited = true;
        }
        if(!(curNode->child[1]->visited))
        {
            queue[(tail++) % QLEN] = curNode->child[1];
            curNode->child[1]->visited = true;
        }
        if(!(curNode->child[2]->visited))
        {
            queue[(tail++) % QLEN] = curNode->child[2];
            curNode->child[2]->visited = true;
        }
    }
}


int main() {
    #ifndef _OJ_
        freopen("/Users/muchuanyun/Documents/001-Research/03-Moocs/DS_THU/dsa_pa/pa2/toy/toy/input.in", "r", stdin);
        //freopen("/Users/muchuanyun/Documents/001-Research/03-Moocs/DS_THU/dsa_pa/pa2/toy/toy/output.txt", "w", stdout);
    #endif
    
    setvbuf(stdin, (char*)malloc(1 << 18), _IOFBF, 1 << 18);
    setvbuf(stdout, (char*)malloc(1 << 18), _IOFBF, 1 << 18);

    Graph = new vNode[MAXN];
    
    int n;
    scanf("%d\n", &n);
    
    // build the graph
    char s_init[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    
    graph_init(s_init);
    
    
    char a[8];
    for (int i = 0; i < n; i++) {
        
        for (int j = 0; j < 8; j++) {
            scanf("%c ", &a[j]);
        }
      
        vPtr startNode = &Graph[hash(a)];
        
        BFS(startNode);
        
        if(Graph[0].visited)
        {
            printf("%d\n", Graph[0].len);
        }
        else{
            printf("-1\n");
        }
        
        for(int i = 0; i < MAXN; i++)
        {
            Graph[i].len = 65535;
            Graph[i].visited = false;
        }
        
}
    delete [] Graph;
    return 0;
}
