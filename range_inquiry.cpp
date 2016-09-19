//
//  range_inquiry.cpp
//  range_inquiry
//
//  Created by muchuanyun on 16/9/13.
//  Copyright © 2016 muchuanyun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int cmpfunc (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

int binSearch(int* s, int c, int lo, int hi, bool& flag)
{

    while (lo < hi) {
        int mi = (lo + hi) >> 1;
        c < s[mi] ? hi = mi : lo = mi + 1;
        
    }
    
    flag = false;
    
	// make sure the index exists
    if (--lo >= 0 && s[lo] == c)
        flag = true;

    return lo;
}


int main()
{
#ifndef _OJ_
    freopen("/Users/muchuanyun/input.in", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
    int N, M, a, b, ans;
    bool flag_a, flag_b;
    scanf("%d %d\n", &N, &M);
    
    int* A;
    A = new int[N];
    for (int i = 0; i < N; i++)
        scanf("%d", &(A[i]));
    
    qsort(A, N, sizeof(int), cmpfunc);
    
    
    for (int j = 0; j < M; j++) {
        scanf("%d %d", &a, &b);
        int idx_a = binSearch(A, a, 0, N, flag_a);
        //printf("%d's idx_a = %d, A[idx_a] = %d\n", a, idx_a, A[idx_a]);
        if (a == b) {
            ans = (flag_a ? 1 : 0);
            printf("%d\n", ans);
            continue;
        } else {
            int idx_b =binSearch(A, b, idx_a, N, flag_b);
            if ( flag_a )
                printf("%d\n", idx_b - idx_a + 1);
            else
                printf("%d\n", idx_b - idx_a);
        }
    }
    
    delete []A;
    return 0;
}
