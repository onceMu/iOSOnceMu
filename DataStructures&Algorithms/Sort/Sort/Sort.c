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
        //从第一个元素开始
        min_idx = i;
        //循环开始
        //第一次循环：以第一个元素为基准元素，游标为0，顺序遍历数组后面的值，如果后面的值比游标对应的值小，则将游标对应的indext交换成当前元素对应的值，直到循环到最后一个元素
        //第一次循环完成之后，交换第一个值和 游标对应的值
        //第二次循环，以第二个值为基准元素，游标为1m，顺序遍历数组后面的值，直到最后一个，然后将游标交换到正确的位置，然后交换基准元素和游标对应的元素
        //第n次循环
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
    //插入排序的思想，是将元素顺序插入到对应的位置
    //默认第0个元素是有序的
    //循环从1开始，然后判断第2个和第1个的大小
    //第一次循环，判断第2个元素和已有序数组中第1个值的大小，然后合适的交换位置
    //第二次循环，判断未排序数组第3个元素在已排序数组的合适位置，如果已排序数组的值大于当前的值，则交换到合适位置
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
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
        for (j = 0; j< n-i-1; j++) {
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

//binary serach
//时间复杂度O(lgn)
int BinarySearch(int *a ,int n,int key) {
    int low,high,middle;
    low = 1;
    high = n;
    while (low <= high) {
        //找到中间节点
        middle = (low + high)/2;
        //如果中间结点比key大，
        if (key < a[middle]) {
            high = middle - 1;
        }else if (key > a[middle]) {
            high = middle +1;
        }else {
            return middle;
        }
    }
    return 0;
}


//递归
//1.一个问题的解可以分解为几个子问题的解
//2.问题与拆解之后的子问题，除了数据规模不同，求解思路一致
//3.存在递归终止条件

//排序
//最好情况、最坏情况、平均时间复杂度
//时间复杂度系数、常数、低阶
//比较次数和移动次数
//稳定性

//冒泡排序是一个稳定的排序、时间复杂度O（n2），空间复杂度O(1),只需要交换就可以
void bulleSort (int arr[],int n) {
    if (n <= 1) {
        return;
    }
    for (int i = 0; i<n ; i++) {
        for (int j = 1; i< n-j-1; j++) {
            if (arr[j] < arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

//插入排序
//默认第一个是已经处于正确位置的，要做的是将后面的数据跟有序数组最后一个比较，插入到合适的位置
//时间复杂度O(n2)
void insertSSort(int arr[],int n) {
    if (n <= 1) {
        return;
    }
    for (int i =1; i<n; i++) {
        int value = arr[i];
        int j = i -1;
        for (; j>=0; j--) {
            if (arr[j] > value) {
                arr[j+1] = arr[j];
            }else {
                break;
            }
        }
        arr[j+1] = value;
    }
}


//插入排序的思想就是从将待排序数组中的第一个元素插入到已排序数组中的合适位置
void insertSSSSort (int arr[],int n) {
    if (n <= 1) {
        return;
    }
    for (int i = 1; i< n ; i++) {
        int value = arr[i];
        int j = i-1;
        //当j == 0 的时候，并且arr[0] 大于 arr[1]
        //将arr[1] = arr[0];
        //j --
        //将arr[0] = value
        while (j>= 0 && arr[j] > value) {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = value;
    }
}

//选择排序
//选择排序的思想是将从未排序数组中找出最小元素对应的index，然后交换合适的index
void selctedSSort(int arr[],int n) {
    if (n <= 1) {
        return;
    }
    for (int i =0; i< n; i++) {
        int midX = i;
        for (int j = 1; j < n - 1; j++) {
            if (arr[j] < arr[midX]) {
                midX = j;
            }
        }
        arr[i] = arr[midX];
    }
}


//冒泡排序
//每一趟冒泡，会将对应的值放在合适的位置
void bubbleSorrrt (int arr[],int n) {
    if (n <= 1) {
        return;
    }
    for (int i = 0; i< n; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int value = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = value;
            }
        }
    }
}




