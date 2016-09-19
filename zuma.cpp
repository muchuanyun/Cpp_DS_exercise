//
//  zuma.cpp
//  Zuma
//
//  Created by muchuanyun on 16/9/13.
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


typedef struct ballnode* ballPtr;

typedef struct ballnode {
    char color;
    ballPtr pred;
    ballPtr succ;
} ball;

ballPtr ball_alloc(char c ='0', ballPtr pre = NULL, ballPtr suc = NULL)
{
    ballPtr new_ball = (ballPtr) malloc(sizeof(ball));
    new_ball->color = c;
    new_ball->pred = pre;
    new_ball->succ = suc;
    return new_ball;
}

int check(ballPtr & cur, ballPtr & next, char clr, int cnt_init)
{
    int cnt = cnt_init;
    
    while (cur->pred != NULL && cur->color == clr) {
        cur = cur->pred;
        cnt++;
        
    }
    while (next->succ != NULL && next->color == clr) {
        next = next->succ;
        cnt++;
    }
    
    return cnt;
}

void eliminate(ballPtr & st, ballPtr & en)
{
    st->succ = en;
    en->pred = st;
}

void bangbangbang(ballPtr head, int idx, char clr)
{
    int cnt_init = 1;
    
    int i = 0;
    ballPtr cur = head;
    while ((cur->succ)->succ != NULL && (i++ < idx))
        cur = cur->succ;    // the new ball should be inserted after cur
    
    ballPtr pos = cur;
    ballPtr pos_next = pos->succ;
    
    ballPtr next = cur->succ;
    int cnt = check(cur, next, clr, cnt_init);
    
    if (cnt < 3) {          // add the new ball
        ballPtr new_ball = ball_alloc(clr, pos, pos_next);
        pos->succ = new_ball;
        pos_next->pred = new_ball;
        return;
    } else {               // don't add new ball, eliminate the adjacent two
        eliminate(cur, next);
        cnt_init = 0;
    }
    
    while (check(cur, next, cur->color, cnt_init) >= 3) {
        eliminate(cur, next);
    }
}

void print_list(ballPtr head)
{
    ballPtr cur = head->succ;
    if (cur->succ == NULL)
        printf("-");
    else {
        while(cur->succ != NULL ) {
            printf("%c", cur->color);
            cur = cur->succ;
        }
    }
    printf("\n");
}

int main()
{
	#ifndef _OJ_
		freopen("/Users/muchuanyun/input.in", "r", stdin);
		//freopen("output.txt", "w", stdout);
	#endif
    
    int c;
    ballPtr header, trailer, cur, next, new_ball;
    header = ball_alloc();
    trailer = ball_alloc();
    
    header->succ = trailer;
    trailer->pred = header;

    // build the list
    
    cur = header;
    while ( (c = getchar()) != '\n' ) {
        next = cur->succ;
        
        new_ball = ball_alloc(c, cur, next);
        
        cur->succ = new_ball;
        next->pred = new_ball;
        
        cur = new_ball;
    }
    
    // get the number of operations
    int n;
    scanf("%d\n", &n);
    
    // start operation
    int idx;
    char clr;
    for (int i = 0; i < n; i++) {
        scanf("%d %c\n", &idx, &clr);
        bangbangbang(header, idx, clr);
        
        print_list(header);
    }
    
    return 0;
}
