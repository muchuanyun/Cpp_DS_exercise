//
//  main.cpp
//  cycle
//
//  Created by muchuanyun on 16/10/4.
//  Copyright © 2016 muchuanyun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 100005

char s1[MAXLEN];
char s2[MAXLEN];

bool isCycle(char* s1, char* s2)
{
    int len1 = (int) strlen(s1);
    int len2 = (int) strlen(s2);
    
    bool flag = false;
    
    if ( len1 != len2)
        return false;
    
    int i = 0;  // standard s1
    int j = 0;  // pattern s2
    while ( j < len2 && i < len1) {
        
       if (s1[i] == s2[j]) {

           if (i == len1 - 1) { 
                int l = 0;
                int k = j+1;
                while (l < i - j && k < len2) {
                    if (s1[l++] != s2[k++]) {
                        flag = false;
                        return flag;
                    }
                }
                flag = true;
            }
            i++;
            j++;
            
        } else {
            i = (i - j + 1);
            j = 0;
        }
    }
    
    return flag;
}



int main() {
    #ifndef _OJ_
        freopen("/Users/muchuanyun/Documents/001-Research/03-Moocs/DS_THU/dsa_pa/pa2/cycle/cycle/input.in", "r", stdin);
    //freopen("output.txt", "w", stdout);
    #endif
    setvbuf(stdin, (char*)malloc(1 << 20), _IOFBF, 1 << 20);
    setvbuf(stdout, (char*)malloc(1 << 20), _IOFBF, 1 << 20);

    while (scanf("%s %s\n", s1, s2) == 2) {
        //printf("%s %s\n", s1, s2);
        if (isCycle(s1, s2)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}
