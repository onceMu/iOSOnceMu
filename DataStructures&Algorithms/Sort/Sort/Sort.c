//
//  Sort.c
//  Sort
//
//  Created by le on 2018/7/11.
//  Copyright © 2018年 le. All rights reserved.
//

#include "Sort.h"


//交换两个函数
void swap (int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//选择排序思想，找到数组中最小的值，与数组中第一个进行比较，然后交换 不会访问索引左边
void selectionSort(int arr[],int n ) {
    int i,j,min_idx;
    for (i = 0; i< n-1; i++) {
        min_idx = i;
        for (j = i +1; j <n; j ++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
    }
}

//插入排序 不会访问索引右边，将每次需要插入的数据，插入到索引左边合适的位置
void insertSort(int arr[],int n) {
    int i,j,key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j > 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }
}


//递归插入排序
void insertSortRecursive(int arr[],int n) {
    if (n <= 1) {
        return;
    }
    insertSortRecursive(arr, n-1);
    int last = arr[n-1];
    int j = n-2;
    while (j >=0 && arr[j] > last) {
        arr[j+1] = arr[j];
        j--;
    }
    arr[j+1] = last;
}

//冒泡排序  每一次循环把索引的值插入到合适的位置，也就是第一次循环，把第一个值插入到最合适的位置，
//下面的做法是从小到大去找
void bubbleSort(int arr[],int n) {
    int i,j;
    for (i = 0; i<n; i++) {
        for (j = 0; j<n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

//递归冒泡排序，每一趟找到最大值。
void bubbleSortRecursive(int arr[],int n ){
    if (n == 1) {
        return;
    }
    //找到最大值
    for (int i = 0; i<n; i++) {
        if (arr[i] > arr[i+1]) {
            swap(&arr[i], &arr[i+1]);
        }
    }
    bubbleSortRecursive(arr, n-1);
}

//希尔排序 i++与 ++i 的区别，i++ 是先用再自增1， ++i是先自增1再用
void shellSort(int arr[],int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = 0; i <n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; i>gap && arr[j-gap] > temp; j -= gap) {
                arr[j] = arr[j-gap];
            }
            arr[j] = temp;
        }
    }
}

void swipTwoNumber(int *xp,int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//冒泡排序，从头开始往后进行比较，如果前一个比后一个大，则交换两个值，这样一趟之后最大值会排在最后位置
void bubbleCurrentSort(int arr[],int n) {
    int i,j;
    for (i = 0; i<n; i++) {
        for (j = 1; j< n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swipTwoNumber(&arr[j], &arr[j+1]);
            }
        }
    }
}

//链表数据进行冒泡排序，除了需要比较值之外，还要改变链表指针的改变
void bubbleSSSSS (int arr[],int n ){
    for (int i = 0; i< n; i++) {
        for (int j = 0; j< n-1-i; j++) {
            if (arr[j] > arr[j+1]) {
                swipTwoNumber(&arr[j], &arr[j+1]);
            }
        }
    }
}

//选择排序，最核心思想是每次找到未排序序列中的最大（最小）值所在的index，然后交换位置
void selectedSSSSS (int arr[],int n ) {
    int i ,j,min_idx;
    for (i = 0;  i < n ; i ++) {
        min_idx = i;
        for (j = 1 ; j < n-1; j++) {
            if (arr[min_idx] > arr[j]) {
                min_idx = j;
            }
        }
        swipTwoNumber(&arr[i], &arr[min_idx]);
    }
}

//插入排序,将未排序的数列中第一个元素，插入到已排序数列中的合适位置，从已排序的数列中最后一个元素往前开始遍历
void insertSSSSSS (int arr[],int n) {
    int preIndex,currentIndex;
    for (int i = 1; i<n ; i++) {
        preIndex = i - 1;
        currentIndex = arr[i];
        while (preIndex >=0 && arr[preIndex] > currentIndex) {
            arr[preIndex + 1] = arr[preIndex];
            preIndex --;
        }
        arr[preIndex + 1] = currentIndex;
    }
}



//选择排序
void selctedSorted(int arr[],int n){
    int i,j,min_idx;
    for (i = 0; i< n; i++) {
        min_idx = i;
        for (j = 1; j< n-1; j++) {
            if (arr[min_idx] > arr[j]) {
                min_idx = j;
            }
        }
        swipTwoNumber(&arr[i], &arr[min_idx]);
    }
}

//冒泡排序  19861209wanxiONCE
void bubbleSortedss(int arr[],int n ) {
    int i,j;
    for (i = 0; i< n; i++) {
        for (j = 0; j<n-1-i; j++) {
            if (arr[j] > arr[j+1]) {
                swipTwoNumber(&arr[j], &arr[j+1]);
            }
        }
    }
}

//void quickSort(int arr[],)







