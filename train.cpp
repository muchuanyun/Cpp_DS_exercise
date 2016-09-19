//
//  train.cpp
//  Train
//
//  Created by muchuanyun on 16/9/10.
//  Copyright © 2016 muchuanyun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1600010
#define PUSH 1
#define POP 0

//int B[MAXSIZE];
//int S[MAXSIZE];
//int Motion[MAXSIZE];

bool stackEmpty(int* S, int *sp) {
    return (sp - S <= 0)? true : false;
}

int judgePermutation(int N, int M, int* B, int* S, int* Motion) {
    int* sp;
    sp = S;
    
    int j = 1;
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        if ( (!stackEmpty(S, sp)) && (*(sp-1) == B[i]) ) {
            sp--;
            Motion[cnt++] = POP;
        } else if ( sp - S >= M ) {
            return 0; // no
        } else if ( B[i] < j) {
            return 0; // no
        } else {
            while ( (sp - S < M) && j <= B[i] ){
                Motion[cnt++] = PUSH;
                *(sp++) = j++;
            }
            if (j-1 == B[i]) {
                Motion[cnt++] = POP;
                sp--;
            } else {
                return 0; // no
            }
                
        }

    }
    
    return cnt;
}


int main() {
    
    int N, M;
    
    scanf("%d %d\n", &N, &M);
    
    int* B;
    int* S;
    int* Motion;
    B = new int[N];
    S = new int[M];
    Motion = new int[2*N];
    
    for(int i = 0; i < N; i++)
    {
        scanf("%d", &(B[i]));
    }
    
    
    if (M == 0)
        printf("No\n");
    
    int cnt = judgePermutation(N, M, B, S, Motion);
    
    if (cnt == 0)
        printf("No\n");
    else {
        for (int i = 0; i < cnt; i++) {
            (Motion[i] == PUSH)? printf("push\n") : printf("pop\n");
        }
    }
    
    delete []B;
    delete []S;
    delete []Motion;

    return 0;
}
