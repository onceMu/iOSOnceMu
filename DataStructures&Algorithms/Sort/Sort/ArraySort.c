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
bool findKeyInArray(int *matrix,int columes,int rows,int key) {
    bool find = false;
    if (matrix != NULL && columes >0 && rows > 0) {
        int row = 0;
        int cloume = columes - 1;
        while (row < rows && cloume > 0) {
            if (matrix[row * columes + cloume] == key) {
                find = true;
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
