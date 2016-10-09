//
//  main.cpp
//  deduplicate
//
//  Created by muchuanyun on 16/10/1.
//  Copyright © 2016 muchuanyun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SZ = 1<<20;
struct fastio{   //fast io
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;

#define HASHSIZE 60001

struct nlist {
    char* name;
    unsigned cnt;
    struct nlist* next;
    /*
    nlist()
    {
        name = null;
        cnt = 0;
        next = null;
    }
     */
};

struct nlist* hashtab[HASHSIZE];

unsigned hash(char* s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return (hashval % HASHSIZE);
}

struct nlist* lookup(char* s)
{
    struct nlist* np;
    int idx = hash(s);
    for (np = hashtab[idx]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np; // found
        }
    }
    return NULL;    // not found
}

void install(char* name)
{
    struct nlist* np;
    unsigned hashval;
    
    if ( (np = lookup(name)) == NULL) {
        np = (struct nlist*) malloc(sizeof(nlist));
        np->name = strdup(name);
        np->cnt = 1;
        np->next = NULL;
        if (np == NULL || np->name == NULL)
            return;
        
        hashval = hash(name);
        
        if (hashtab[hashval] != NULL) {
            struct nlist* cur = hashtab[hashval];
            while ( cur->next != NULL) {
                cur = cur->next;
            }
            cur->next = np;
        } else {
            hashtab[hashval] = np;
        }
    } else {
        np->cnt++;
        if (np->cnt == 2)
            printf("%s\n", name);
    }
    return;
}

int main() {
    #ifndef _OJ_
        freopen("/Users/muchuanyun/Documents/001-Research/03-Moocs/DS_THU/dsa_pa/pa2/deduplicate/deduplicate/input.in", "r", stdin);
        //freopen("output.txt", "w", stdout);
    #endif
    
    for (int i = 0; i < HASHSIZE; i++) {
        hashtab[i] = NULL;
    }
    int N;
    scanf("%d\n", &N);      // number of strings

    
    char s[41];
    for (int i = 0; i < N; i++) {
        scanf("%s\n", s);
        install(s);
        // printf("out: %s\n", s);
    }
    
    return 0;
}
