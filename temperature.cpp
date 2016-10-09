//
//  main.cpp
//  temperature
//
//  Created by muchuanyun on 16/9/26.
//  Copyright © 2016 muchuanyun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "temperature.h"

#define alongX 1
#define alongY -1

#define inBoth 0
#define inLeft 1
#define inRight 2
#define inAbove 3
#define inDown 4

#define eRR -1

typedef long long int int64;

typedef struct point {
    int x, y;
    int temp;
} pt;

typedef struct boundingbox {
    int x1, y1;
    int x2, y2;
} bbox;

typedef struct treeNode *tPtr;

typedef struct treeNode {
    pt* members;
    int num;
    tPtr lc;
    tPtr rc;
    bool isLeaf;
    int axis;
    pt med;
    int64 temp_sum;
    bbox box;   //bbox
} tnode;


pt find_median(pt* A, int len, int axis)
{
    // using quick_select
    int k = len / 2;
    
    if (axis == alongX) {
        for (int lo = 0, hi = len - 1; lo < hi; ) {
            int i = lo, j = hi;
            pt pivot = A[lo];
            while (i < j) {
                while (i < j && pivot.x <= A[j].x) j--; A[i] = A[j];
                while (i < j && A[i].x <= pivot.x) i++; A[j] = A[i];
            }
            A[i] = pivot;
            if (k <= i) hi = i-1;
            if (i <= k) lo = i+1;
        }
    } else if (axis == alongY) {
        for (int lo = 0, hi = len - 1; lo < hi; ) {
            int i = lo, j = hi;
            pt pivot = A[lo];
            while (i < j) {
                while (i < j && pivot.y <= A[j].y) j--; A[i] = A[j];
                while (i < j && A[i].y <= pivot.y) i++; A[j] = A[i];
            }
            A[i] = pivot;
            if (k <= i) hi = i-1;
            if (i <= k) lo = i+1;
        }
    }
    return A[k];
}


int64 comp_total_temp(pt* A, int len)
{
    int sum_temp = 0;
    for (int i = 0; i < len; i++)
        sum_temp += A[i].temp;
    
    return sum_temp;
}

void get_bbox(pt* A, int len, bbox & pos)
{
    int min_x, min_y, max_x, max_y;
    min_x = max_x = A[0].x;
    min_y = max_y = A[0].y;
    for (int i = 1; i < len; i++) {
        if (A[i].x > max_x)
            max_x = A[i].x;
        if (A[i].y > max_y)
            max_y = A[i].y;
        if (A[i].x < min_x)
            min_x = A[i].x;
        if (A[i].y < min_y)
            min_y = A[i].y;
    }
    pos.x1 = min_x;
    pos.y1 = min_y;
    pos.x2 = max_x;
    pos.y2 = max_y;
}


tPtr tnode_init(pt* A, int len, int axis)
{
    if (len < 1)
        return NULL;
    else {
        tPtr new_node = (tPtr) malloc(sizeof(treeNode));
    
        pt* s = new pt[len];
        memcpy(s, A, len * sizeof(pt));
        new_node->members = s;
        new_node->num = len;
        new_node->axis = axis;
        new_node->isLeaf = false;
        new_node->lc = NULL;
        new_node->rc = NULL;
        new_node->temp_sum = comp_total_temp(A, len);
        
        bbox pos;
        get_bbox(A, len, pos);
        new_node->box = pos;
        
    return new_node;
    }
}

tPtr build_2dTree(pt* A, int len, int axis)
{
    tPtr root = tnode_init(A, len, axis);
    if (len <= 5) {
        root->isLeaf = true;
    } else if (len > 1) {
        pt med = find_median(A, len, axis);
        root->med = med;
        root->lc = build_2dTree(A, len/2, -axis);
        root->rc = build_2dTree(A+len/2, len - len/2, -axis);
        
    }
    return root;
}

bool isBoxInRegion(bbox b1, bbox b2)
{
    // check if b1 is in b2
    if ( (b1.x1 >= b2.x1) && (b1.y1 >= b2.y1) && (b1.x2 <= b2.x2) && (b1.y2 <= b2.y2))
        return true;
    else
        return false;
}

bool isNodeInRegion(pt node, bbox query)
{
    // check if node is in box query
    if ( (node.x >= query.x1) && (node.y >= query.y1) && (node.x <= query.x2) && (node.y <= query.y2))
        return true;
    else
        return false;
}

int check_position(bbox b1, pt med, int axis)
{
    // check the box position
    
    if (axis == alongX) {
        if (med.x >= b1.x1 && med.x <= b1.x2)
            return inBoth;
        else if (med.x > b1.x2)
            return inLeft;
        else if (med.x < b1.x1)
            return inRight;
    } else {
        if (med.y >= b1.y1 && med.y <= b1.y2)
            return inBoth;
        else if (med.y > b1.y2)
            return inAbove;
        else if (med.y < b1.y1)
            return inDown;
    }
    return eRR;
}


int do_query(tPtr root, int N, bbox query)
{
    int64 total_temp = 0;
    int total_num = 0;
    
    tPtr* stack = new tPtr[N];
    tPtr* sp = stack;
    
    *(sp++) = root;
    
    while (sp != stack) {
        tPtr curNode = *(--sp);
        
        if (!curNode->isLeaf) {
            if (isBoxInRegion(curNode->box, query)) {
                total_temp += curNode->temp_sum;
                total_num += curNode->num;
            } else {
                int pos = check_position(query, curNode->med, curNode->axis);
                if (pos == inLeft || pos == inAbove)
                    *(sp++) = curNode->lc;
                else if (pos == inRight || pos == inDown)
                    *(sp++) = curNode->rc;
                else if (pos == inBoth) {
                    *(sp++) = curNode->lc;
                    *(sp++) = curNode->rc;
                }
            }
        } else {
            if (isBoxInRegion(curNode->box, query)) {
                total_temp += curNode->temp_sum;
                total_num += curNode->num;
            } else {
                for (int i = 0; i < curNode->num; i++) {
                    if (isNodeInRegion(curNode->members[i], query)) {
                        total_temp += curNode->members[i].temp;
                        total_num += 1;
                    }
                }
            }
        }
    }
    delete []stack;
    
    if (total_num != 0) {
        int64 temp = total_temp / total_num;
        return (int)temp;
    } else {
        return 0;
    }
}

int main() {
    //#ifndef _OJ_
      // freopen("./temperature.in", "r", stdin);
    //freopen("output.txt", "w", stdout);
    //#endif
    
    int N = GetNumOfStation();
    
    pt* A = new pt[N];
    
    for (int i = 0; i < N; i++) {        
        GetStationInfo(i, &A[i].x, &A[i].y, &A[i].temp);
        // printf("station (%d, %d): %d\n", A[i].x, A[i].y, A[i].temp);
    }
    
    tPtr root = build_2dTree(A, N, alongX);
    
    int x1, y1, x2, y2;

    bbox query;
    while (GetQuery(&x1, &y1, &x2, &y2) != 0) {
        query.x1 = x1;
        query.y1 = y1;
        query.x2 = x2;
        query.y2 = y2;
        
        int avg_temp = do_query(root, N, query);
        //printf("query: (%d, %d) ~ (%d, %d) \t temp: %d\n", x1, y1, x2, y2, avg_temp);
        Response(avg_temp);
    }
    
    delete [] A;
    return 0;
}
