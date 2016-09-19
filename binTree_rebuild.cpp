//
//  binTree_rebuild.cpp
//  binTree_rebuild
//
//  Created by muchuanyun on 16/9/11.
//  Copyright © 2016 muchuanyun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

const int SZ = 1 << 20;  //IO buff
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin, inbuf, _IOFBF, SZ);
        setvbuf(stdout, outbuf, _IOFBF, SZ);
    }
}io;

int find(int *s, int c, int en)
{
    int* tmp;
    tmp = s;
    int i = 0;
    while ((tmp < s + en) && c != *(tmp++))
        i++;
    
    return i;
}

void convert(int* preSeq, int* postSeq, int num)
{
    if (num == 1)
        printf("%d ", *preSeq);
    else if (num == 3)
        printf("%d %d %d ", preSeq[1], preSeq[0], preSeq[2]);
    else {
        int* pre_left;
        int* pre_right;
        int* post_left;
        int* post_right;
    
        int root = *preSeq;
    
        pre_left = preSeq+1;
        post_left = postSeq;
    
        int lc = *pre_left;
    
        int lc_len = find(postSeq, lc, num) + 1;
        int rc_len = num - 1 - lc_len;
    
        pre_right = pre_left + lc_len;
        post_right = post_left + lc_len;
        
        convert(pre_left, post_left, lc_len);
        printf("%d ", root);
        convert(pre_right, post_right, rc_len);
    }
}


int main() {
    int nodeNum;
    
    scanf("%d\n", &nodeNum);
    
    int* preSeq;
    int* postSeq;
    
    preSeq = new int[nodeNum];
    postSeq = new int[nodeNum];
    
    for(int i = 0; i < nodeNum; i++)
    {
        scanf("%d", &(preSeq[i]));
    }

    for(int i = 0; i < nodeNum; i++)
    {
        scanf("%d", &(postSeq[i]));
    }
    
    convert(preSeq, postSeq, nodeNum);
    
    printf("\n");
    
    delete []preSeq;
    delete []postSeq;
    
    return 0;
}
