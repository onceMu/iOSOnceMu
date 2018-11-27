//
//  ArraySort.c
//  Sort
//
//  Created by onceMu on 2018/10/31.
//  Copyright © 2018 le. All rights reserved.
//

#include "ArraySort.h"
#include <stdlib.h>
#include <stdio.h>

//从有序的二维数组中找到x对应的值
//从数组的第一行的最后一个元素开始遍历，每次删除掉一行或者一列，缩小排序位置
//因为数组是有序的，所以key 要么比数组第一行最后一列的值大、或者小、或者相等
int findKeyInArray(int *matrix,int columes,int rows,int key) {
    int find = 0;
    if (matrix != NULL && columes >0 && rows > 0) {
        int row = 0;
        int cloume = columes - 1;
        while (row < rows && cloume > 0) {
            if (matrix[row * columes + cloume] == key) {
                find = 1;
                break;
            }else if(matrix[row * columes + cloume] > key) {
                -- cloume;
            }else {
                ++ row;
            }
        }
    }
    return find;
}


//移除有序数组中的重复元素，并且返回新数组的大小
//数组有序，所以从头开始遍历，判断当前元素与下一个元素的大小
int revemoDuplicatesFromSortedArray(int *nums,int numsSize) {
    int countNumber = 0;
    int countSize = numsSize;
    for (int i = 0; i < countSize - 1; i++) {
        if (nums[i] == nums[i+1]) {
            countNumber ++;
            countSize --;
        }else {
            nums[i + 1 - countNumber] = nums[i+1];
        }
    }
    return countSize;
}


//移除数组中给定的元素，比如数组[1,2,3,4,5,5,6,7],给定5,输出6,[1,2,3,4,6,7]
//思路，直接遍历，上面的思路是 --，这个题目的思路是 ++；
//遍历数组，如果值不等于给定的值，就直接重新复制
int removeElement(int *nums,int numsSize,int val) {
    int length = 0;
    for (int i = 0; i< numsSize; i++) {
        if (nums[i] != val) {
            nums[length] = nums[i];
            length ++;
        }
    }
    return length;
}

//给定数组，和一个值，判断值插入数组的位置
//[1,3,5,6],5 输出2，O(n)算法
int searchInsertPosition(int *nums,int numsSize,int target) {
    int position = 0;
    for (int i = 0; i<numsSize; i++) {
        if (nums[i] >= target) {
            position = i;
            break;
        }else {
            if (i == numsSize - 1) {
                position = numsSize;
            }
        }
    }
    return position;
}


//二分查找方法
int binarySearchPosition(int *nums,int numsSize,int target) {
    int left = 0;
    int right = numsSize - 1;
    if (numsSize == 1) {
        if(nums[0] >= target) {
            return 0;
        }else {
            return 1;
        }
    }
    if (nums[0] > target) {
        return 0;
    }
    if (nums[numsSize - 1] < target) {
        return numsSize;
    }
    while (left <= right) {
        if (nums[left] == target) {
            return left;
        }else if(nums[right] == target) {
            return right;
        }else if (nums[left] > target && nums[left - 1] < target) {
            return left;
        }else if(nums[right] < target && nums[right + 1] > target) {
            return right + 1;
        }else {
            right --;
            left ++;
        }
    }
    return left;
}


//给定一个数组，找出数组中和值最大的子序列
//最简单的思路，两层循环遍历,顺序j把数组中每一个元素相加，记录最大值，最后返回最大值
//时间复杂度O(n^2)
int maxSubArray(int *nums, int numsSize) {
    int max = nums[0];
    int sum = 0;
    for (int i = 0; i < numsSize; i++) {
        sum = 0;
        for (int j = i; j < numsSize; j ++) {
            sum += nums[j];
            if (max < sum) {
                max = sum;
            }
        }
    }
    return max;
}

//O(n)解法
int maxSubArray2(int *nums, int numsSize) {
    int max = nums[0];
    int local = nums[0];
    for (int i = 1; i< numsSize; i++) {
        local = (local > 0) ? local + nums[i] : nums[i];
        max = (max < local) ? local : max;
    }
    return max;
}


//plus one
//对于给定的数组，返回数组对应的值+1;[1,2,3],返回124
//需要注意进位的问题；以及重新申请数组长度
int *plusOne(int *digits, int digitsSize, int *returnSize) {
    int i = 0;
    //如果最后一位不是9，就意味着不需要进位
    if (digits[digitsSize - 1] != 9) {
        digits[digitsSize - 1] ++;
    }else {
        //考虑进位的情况
        for (i = digitsSize - 1; i >= 0; i--) {
            if (digits[i] == 9) {
                //如果第i个值是9，则将当前位置进一位，置为0
                digits[i] = 0;
            }else {
                digits[i]++;
                
                //没有这个break 也是可以的
                break;
            }
        }
    }
    //如果第一位是0，意味着第一位也产生了进位，这个时候需要重新分配内存地址
    if (digits[0] == 0) {
        *returnSize = digitsSize + 1;
    }else {
        *returnSize = digitsSize;
        return digits;
    }
    int *array = (int *)malloc(sizeof(int) *(*returnSize));
    for (i = *returnSize - 1; i >= 1; i--) {
        array[i] = digits[i-1];
    }
    array[0] = 1;
    return array;
}


//合并两个有序数组
//两种思路，1是开辟新空间，然后比较两个数组
//2.从后往前进行插入，可以不用开辟新空间

//1.开辟新空间
void merge(int* nums1, int m, int* nums2, int n) {
    int *temp = (int *)malloc(sizeof(int) *(m +n));
    
    int num1Index = 0;
    int num2Index = 0;
    int tempIndex = 0;
    //先将一个数组遍历到结尾
    while (num1Index < m && num2Index <n) {
        if (nums1[num1Index] < nums2[num2Index]) {
            temp[tempIndex ++] = nums1[num1Index++];
        }else {
            temp[tempIndex ++] = nums2[num2Index++];
        }
    }
    //再处理没有遍历到结尾的数组
    if (num1Index == m) {
        for (int i = num2Index; i<n; i++) {
            temp[tempIndex ++] = nums2[i];
        }
    }else if (num2Index == n) {
        for (int i = num1Index; i< m; i++) {
            temp[tempIndex ++] = nums1[i];
        }
    }
    for (int i = 0; i < m+n; i ++) {
        nums1[i] = temp[i];
    }
    free(temp);
}

//从尾部开始插入
void mergeTwoArray(int* nums1, int m, int* nums2, int n) {
    int i,j;
    int k = m+n-1;
    for (i = m-1, j = n-1; (j>=0) && (i >= 0); ) {
        if (nums1[i] >= nums2[j]) {
            nums1[k] = nums1[i];
            i--;
            k--;
        }
        if (nums1[i] < nums2[j]) {
            nums1[k] = nums2[j];
            j--;
            k--;
        }
    }
    if (i == -1) {
        for (; j>0; j--,k--) {
            nums1[k] = nums2[j];
        }
    }
}


//找出最合适的卖出股票机会，只能操作一次，计算最大收益
//卖出价要大于买入价
//如果找不到，返回0
//时间复杂度 O(n^2)
int maxPorfit(int * prices, int pricesSize) {
    int max = 0;
    int sum = 0;//默认值是是0
    //从第二天开始遍历
    for (int i = 0; i< pricesSize; i++) {
        max = prices[i];
        for (int j = i+1; j<pricesSize; j++) {
            int income = prices[j] - max;
            if (income > sum) {
                sum = income;
            }
        }
    }
    return sum;
}

//彩票买卖变种，你可以多次买卖操作
//但是需要满足先买再卖
int maxProfit2(int * prices, int pricesSize) {
    int sum = 0;
    for (int i = 0; i<pricesSize -1; i++) {
        if (pricesSize[i] < pricesSize[i+1]) {
            sum += prices[i+1] - prices[i];
        }
    }
    return sum;
}
