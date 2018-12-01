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

//动态规划
//打家窃舍，不能抢劫相邻的房子
//思路就是不断的找出当前最大值与上一次最大值进行比较
//[2,1,1,2,2]
//上上次最大值 2、上次最大值2
//当前最大值3、上次最大值2 //第一次循环
//当前最大值4、上次最大值3 //第二次循环
//当前最大值5、上次最大值4 //第三次循环
int rob(int* nums, int numsSize) {
    if (numsSize <= 1) {
        return numsSize ==0 ? 0 : nums[0];
    }
    //记录一个上一次的最大值，和上上次最大值
    //分别用上上次最大值+当前值  与 上一次最大值进行比较
    
    //最初的最大值
    int maxA = nums[0];
    int maxB = (nums[0] > nums[1]) ? nums[0] : nums[1];
    for (int i = 2;i <numsSize;i++) {
        int temp = maxB;
        maxB = ((nums[i] + maxA) > maxB) ? (nums[i] + maxA) : maxB;
        maxA = temp;
    }
    return maxB;
}

//数组中 和值最大的连续子序列和值是多少
//思路
//从0 开始遍历、记录一个max、同时记录一个sum
//max = nums[0];sum = nums[0];
//遍历，当sum > 0的时候，sum 就加上当前的nums[i],判断sum与max大小，如果sum > max 就重新给max赋值
//如果sum < 0就丢弃掉上一次的sum，重新复制
int maxSubArray(int *nums,int numsSize) {
    int max = nums[0];
    int sum = nums[0];
    for (int i = 1; i<numsSize ; i ++) {
        sum = (sum > 0) ? (sum + nums[i]) : sum;
        max = (max > sum) ? max : sum;
    }
    return max;
}
