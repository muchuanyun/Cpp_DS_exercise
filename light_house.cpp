//
//  light_house.cpp
//  light_house
//
//  Created by muchuanyun on 16/9/14.
//  Copyright © 2016 muchuanyun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef long long unsigned int int64;

const int SZ = 1<<20;
struct fastio{   //fast io
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;

typedef struct pt {
    int x;
    int y;
} point;

void swap(point A[], int i, int j)
{
    point tmp;
    tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

void quickSort(point* const arr, int lo, int hi)
{
    // quick sort according to x axis
    int i = lo;
    int j = hi;
    
    point pivot = arr[(lo + hi) / 2];
    
    while (i <= j) {
        while (arr[i].x < pivot.x)
            i++;
        while (arr[j].x > pivot.x)
            j--;
        if (i <= j) {
            swap(arr, i, j);
            i++;
            j--;
        }
    }
    
    if (lo < j)
        quickSort(arr, lo, j);
    if (i < hi)
        quickSort(arr, i, hi);
    
}

int binSearch(int* s, int c, int lo, int hi)
{
    
    while (lo < hi) {
        int mi = (lo + hi) >> 1;
        c < s[mi] ? hi = mi : lo = mi + 1;
        
    }
    
    return lo;  // the index of the smallest elem larger than c
}



int64 inversion(int* const arr, int lo, int mi, int hi)
{
    int64 cnt = 0;
    int* A = arr+lo;
    int lb = mi - lo;
    int* B = new int[lb];
    
    for (int i = 0; i < lb; i++)
        B[i] = A[i];
    
    int lc = hi - mi;
    int* C = arr+mi;
    
    int idx = 0;
    for (int l = 0; l < lc; l++) {
        idx = binSearch(B, C[l], 0, lb);
        cnt += idx;
    }

    for (int i = 0, j = 0, k = 0; j < lb; ) {
        if (k < lc && C[k] < B[j]) {
            A[i++] = C[k++];
        }
        if (lc <= k || B[j] <= C[k]) {
            A[i++] = B[j++];
        }
    }
    
    delete []B;
    return cnt;
}

int64 count_inversion(int* const arr, int lo, int hi)
{
    int64 cnt_left, cnt_right, cnt_in;
    if (hi - lo < 2)
        return 0;
    int mi = (lo+hi) >> 1;
    cnt_left = count_inversion(arr, lo, mi);
    cnt_right = count_inversion(arr, mi, hi);
    cnt_in = inversion(arr, lo, mi, hi);
    
    return (cnt_left+cnt_right+cnt_in);
}

int main()
{
    #ifndef _OJ_
        freopen("/Users/muchuanyun/input4.in", "r", stdin);
        //freopen("output.txt", "w", stdout);
    #endif
    
    int N;   // the number of lighthouses
    scanf("%d\n", &N);
    
    point* A = new point[N];
    
    int tmpX, tmpY;
    for (int i = 0; i < N; i++) {
        scanf("%d %d\n", &tmpX, &tmpY);
        A[i].x = tmpX;
        A[i].y = tmpY;
    }
    
    if (N <= 1) {
        printf("0\n");
        return 0;
    }
    
    quickSort(A, 0, N-1);
    
    /*
    printf("Sorted:\n");
    for (int i = 0; i < N; i++)
        printf("%d %d\n", A[i].x, A[i].y);
    */
    
    int* B;
    B = new int[N];
    for (int i = 0; i < N; i++)
        B[i] = A[i].y;
    
    int64 cnt = count_inversion(B, 0, N);
    
    printf("%llu\n",  cnt);
    
    delete []A;
    delete []B;
    
    return 0;
}
