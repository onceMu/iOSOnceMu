//
//  Search.c
//  Sort
//
//  Created by le on 2018/11/26.
//  Copyright © 2018 le. All rights reserved.
//

#include "Search.h"


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
    return left - 1;
}
