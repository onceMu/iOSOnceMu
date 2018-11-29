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

void rotateArrayOneByOne(int *nums,int n);
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
        if (prices[i] < prices[i+1]) {
            sum += prices[i+1] - prices[i];
        }
    }
    return sum;
}


//判断数组中是否有重复元素
//思路1. 两层for 循环。时间复杂度O(n^2)
//思路2. 先排序，然后再一次for循环  排序算法时间复杂度 + O(n)
//思路3. map和set 做，
int  findMutable(int *nums, int numsSize) {
    for (int i = 0; i<numsSize; i++) {
        for (int j = i+1; j <numsSize; j++) {
            if (nums[i] == nums[j]) {
                return 1;
            }
        }
    }
    return -1;
}
//先排序、然后再看一次遍历完成


//向右旋转数组k次
//最重要的特征是，每次每次旋转一步之后，原位置i 的新 index = (i + 1)%n;
//同理 旋转k次之后，原位置i的新index = (i+k)%n;
//void rotaArray (int *nums,int n,int k) {
//    int index = 0;
//    int temp = nums[0];
//    int newIndex = 0;
//    for (int i = 0; i<n; ++i) {
//        temp = nums[i];
//        newIndex = (i + k) % n;
//        nums[i] = nums[newIndex];
//        nums[newIndex] = temp;
//        temp = nums[i];
//        index = newIndex;
//    }
//}


//向右旋转数组k次
//可以一个一个进行旋转
void roatArray(int *nums,int n,int k) {
    for (int i = 1; i < k ; i ++) {
        rotateArrayOneByOne(nums, n);
    }
}

void rotateArrayOneByOne (int *nums,int n) {
    int i = 0;
    int last = nums[n-1];
    for ( i = n-1; i >0; i--) {
        nums[i] = nums[i-1];
    }
    nums[0] = last;
}

//下面思路是leetcode 大神解法
void rotate(int *nums, int numsSize, int k) {
    int i;
    int pos;
    int tmp;
    int direction = 1;
    if (!nums) return;
    if (!numsSize) return;
    k %= numsSize; //k = k%numsSize;求出k与数组长度的模，求模的意思是 1%7 = 1;
    if (k == 0) return; //如果是移动k步或者 数组长度的整数倍，则说明不需要移动
    if (k > numsSize / 2) {
        k = numsSize - k;
        direction = -1;
    }
    
    if ((numsSize % k) == 0) {
        int j;
        for (j = 0; j < k; j++) {
            pos = j;
            tmp = nums[pos];
            for (i = 0; i < numsSize/k; i++) {
                int newpos = (pos + direction*k + numsSize) % numsSize;
                int newtmp = nums[newpos];
                nums[newpos] = tmp;
                pos = newpos;
                tmp = newtmp;
                
            }
        }
    } else {
        pos = 0;
        tmp = nums[pos];
        for (i = 0; i < numsSize; i++) {
            int newpos = (pos + direction*k + numsSize) % numsSize;
            int newtmp = nums[newpos];
            nums[newpos] = tmp;
            pos = newpos;
            tmp = newtmp;
            
        }
    }
}

//k = k % numsSize;
//if(k == 0){
//    return;
//}
//int nums[k];
//int loc = 0;
//for(int i=0; i<numsSize ;++i){
//    int j=(k+i) % numsSize;
//    if(i < k){
//        nums[loc] = nums[j];
//        nums[j] = nums[i];
//        loc = (loc+1)%k;
//    }
//    else{
//        int t = nums[j];
//        nums[j] = nums[loc];
//        nums[loc] = t;
//        loc = (loc+1)%k;
//    }
//}

//找出数组中只出现一次的值
//1.按位异 操作。2^2 = 0; 0^2 = 0;最终异出来的值就是单独的那个值
int findSingleNumber(int *nums, int n) {
    int result = 0;
    for (int i = 0; i<n; i++) {
        result ^= nums[i];
    }
    return result;
}

//

//第一个思路
//1.分开判断每一行、每一列是否有重复的
//2.再将数独划分成3*3 的小方块，来判断是否有重复的
int isValidSudoku(char ** board, int boardRowSize, int boardColSize) {
    if (boardRowSize != 9 || boardColSize != 9) {
        return -1;
    }
    int row[9][10] = {0};
    int colum[9][10] = {0};
    int box[9][10] = {0};
    int temp = 0;
    for (int i = 0; i<boardRowSize; i++) {
        for (int j = 0; j<boardColSize; j++) {
            if (board[i][j] != '.') {
                temp = board[i][j] - '0';
                if (row[temp] == 0) {
                    row[i][temp] = 1;
                }else {
                    return -1;
                }
                if (colum[j][temp] == 0) {
                    colum[j][temp] = 1;
                }else {
                    return -1;
                }
                if (box[i/3 * 3 + j/3][temp] == 0) {
                    box[i/3 *3 + j/3][temp] = 1;
                }else {
                    return -1;
                }
                
            }
        }
    }
    return -1;
}


int isValidSudoku2(char ** board, int boardRowSize, int boardColSize) {
    if (boardColSize != 9 || boardRowSize != 9) {
        return -1;
    }
    int row[10];
    int i,j,k,l,num;
    for (i = 0; i < boardRowSize; i++) {
//        memset(row,0,sizeof(row));
        for (j = 0; j < boardColSize; j++) {
            if (board[i][j] == '.') {
                continue;
            }
            if (board[i][j] < '0' || board[i][j] > '9') {
                return -1;
            }
            num = board[i][j] - '0';
            if (row[num] != 0) {
                return -1;
            }
            row[num] = 1;
        }
    }
//    for(i=0;i<9;i+=3){
//        for(j=0;j<9;j+=3){
//            for(k=i;k<i+3;k++){
//                for(l=j;l<j+3;l++){
//                    if(board[k][l]=='.')continue;
//                    num = board[k][l]-'0';
//                    if(box[num]!=0)return false;
//                    box[num]=1;
//                }
//            }
//        }
//    }
    
    return -1;
}
