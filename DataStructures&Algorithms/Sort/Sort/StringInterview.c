//
//  StringInterview.c
//  Sort
//
//  Created by le on 2018/7/11.
//  Copyright © 2018年 le. All rights reserved.
//

#include "StringInterview.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Size_Bin_Table 256
#define UNIQUE_CHARACTER 0
#define MARK_USED 1
#define Is_NUMERIC_STRING(d) (*(char*)d >= 48) && (*(char*)d<= 57)

//给定一个string，删除所有重复的字符串
//比如：
//输入：silence is a source of great strength
//输出：silenc aourfgth

//第一种解决办法，字符串只有256种，所以额外申请一个256大小的char 数组，
//时间复杂度N，空间复杂度，额外申请256
char *removeDupliceString(char *pString) {
    short binTable[Size_Bin_Table] = {0};
    int startIndex = 0;
    int resultIndex = 0;
    unsigned char binTableIndex = 0;
    while (*(pString + startIndex)) {//循环直到输入为空
        binTableIndex = *(pString + startIndex); //获取从startIndex 开始的字符串
        if (binTable[binTableIndex] == UNIQUE_CHARACTER) {
            binTable[binTableIndex] = MARK_USED;
            *(pString + resultIndex) = *(pString + startIndex);//将字符复制到结果中
            resultIndex ++;
        }
        startIndex ++;
    }
    *(pString +resultIndex) = '\0';
    return pString;
}

//第二种解法，暴力循环


//翻转字符串
void revString(char *pBegin,char *pEnd) {
    char temp;
    while (pBegin < pEnd) {
        temp = * pBegin;
        *pBegin ++ = *pEnd;
        *pEnd -- = temp;
    }
}

void reverWord(char *pString) {
    char *pBegin = NULL;
    char *word_bounday = pString;
    while (*word_bounday) {
        //保证pBegin 是从一个合法的字符串开始的
        if ((pBegin == NULL) && (*word_bounday != ' ')) {
            pBegin = word_bounday;
        }
        if(pBegin && ((*(word_bounday+1) == ' ') || (*(word_bounday+1) == '\0')))
        {
            revString(pBegin, word_bounday);
            
            pBegin = NULL;
        }
        word_bounday ++;
    }
}


//在字符串中查找特定的字符串所在的位置
//比如：
//输入：How are you
//样式：are
//输出：4

void searchPatternString(char *pString,char *pPattern) {
    int lenpString = (int)strlen(pString);
    int lenpPattern = (int)strlen(pPattern);
    int pIndex = 0;
    for (pIndex = 0; pIndex < lenpString - lenpPattern; ++ pIndex) {
        int patternIndex;
        for (patternIndex = 0; patternIndex < lenpPattern; ++patternIndex) {
            if (pString[pIndex + patternIndex] != pPattern[patternIndex]) {
                break;
            }
            if (patternIndex == lenpPattern) {
                printf("zhaodao le 起点位置是%d\n",pIndex);
            }
        }
    }
}


//字符串转整型 1 对应的ascii 是48
int stringToInt (const char *pszBuffer) {
    int result = 0;
    int sign = 1;
    if (pszBuffer == NULL) {
        return 0;
    }
    if ((*pszBuffer) =='-') {
        sign = -1;
    }
    ++pszBuffer;
    while (Is_NUMERIC_STRING(pszBuffer)) {//检查输入的是否是合法的字符串
        result = (result * 10) + (*pszBuffer - 48);
        pszBuffer ++;
    }
    return (sign * result);
}

//不用库函数，翻转字符串
//字符串是否是回文字符串
//查找字符串的全部组合
//如何计算一个字符串中元音和辅音的数量
//如何计算给定字符串中某个字符出现的频次
//如何查找字符串中出现频次最多的字符
//通过递归的方式翻转字符串
//如何将给定字符串中某个字符替换成另外一个字符
//左旋或者右旋一个字符串
//检查一个字符串是否是另外一个字符串的翻转字符串 如S1 = ABCD,S2 = CDAB return true，或者 S1 = ABCD,S2 = ACBD return false
//计算给定字符串中的所有number的和 例如：1abc23 返回24  1abc2x30yz67  返回100 123abc 返回123
