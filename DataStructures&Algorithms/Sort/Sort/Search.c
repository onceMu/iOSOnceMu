//
//  Search.c
//  Sort
//
//  Created by le on 2018/11/26.
//  Copyright © 2018 le. All rights reserved.
//

#include "Search.h"
#include <stdlib.h>
#include <stdio.h>


//返回x的平方根
int mySqrt(int x) {
    long right = (x/2) + 1;
    long left = 0;
    while (left <= right) {
        long m = left + (right - left) / 2;
        if (m * m > x) {
            right = m - 1;
        } else {
            left = m + 1;
        }
    }
    return (int)left - 1;
}


//给定字符串数组，查找数组中存在的字符串C，查找字符串数组中每个字符串离C 最近的距离数组
//字符串数组中离给定字符串最小的距离
//需要考虑的是这个值可能在前面，也可能在后面
//遍历数组，然后分别从当前值查找左边和右边第一个符合的位置，然后比较大小。
//时间复杂度 O(n^2)
/*
int* shortestToChar(char* S, char C, int* returnSize) {
    int length = strlen(S);
    *returnSize = length;
    int *array = (int*)malloc(sizeof(int) *(*returnSize));
    for(int i = 0;i < *returnSize;i ++) {
        array[i] = -1;
    }
    for(int i = 0;i < *returnSize;i ++) {
        if(S[i] == C) {
            array[i] = 0;
        }else {
            //找出
            int leftIndex = -1;
            int rightIndex = -1;
            
            int leftRight = i;
            int rightLeft = i+1;
            while(leftRight >= 0) {
                if(S[leftRight] == C) {
                    leftIndex = i - leftRight;
                    break;
                }
                leftRight --;
            }
            while(rightLeft <= *returnSize -1) {
                if(S[rightLeft] == C) {
                    rightIndex = rightLeft - i;;
                    break;
                }
                rightLeft ++;
            }
            if(leftIndex >0 || rightIndex > 0) {
                if (leftIndex > 0 && rightIndex > 0) {
                    if (leftIndex > rightIndex && rightIndex) {
                        array[i] = rightIndex;
                    }else {
                        array[i] = leftIndex;
                    }
                }else if(leftIndex > 0 && rightIndex < 0) {
                    array[i] = leftIndex;
                }else {
                    array[i] = rightIndex;
                }
            }
        }
    }
    return array;
}
 */
