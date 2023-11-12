#define WIN32_LEAN_AND_MEAN   // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"          // Windows API の機能定義

#include <stdio.h>            // printf
#include <stdlib.h>           // malloc, free
#include <stdbool.h>          // bool

#include "../include/lib_func.h"

int main()
{
    my_array ar;
    initialize(&ar, 10);

    for (int i = 0; i < size(&ar); i++) {
        set(&ar, i, i);  // 0, 1, 2, ... と値を設定
    }

    // 値を出力（範囲外も含む！）
    for (int i = 0; i < size(&ar); i++) {
        printf("%d, ", get(&ar, i));
    }
    printf("\n");

    resize(&ar, 100);
    for (int i = 10; i < size(&ar); i++) {
        set(&ar, i, i);  // 10, 11, 12, ..., 99 と値を設定
    }

    // 値を出力（全てが範囲内になった！）
    for (int i = 0; i < size(&ar); i++) {
        printf("%d, ", get(&ar, i));
    }
    printf("\n");

    release(&ar);

    return 0;
}
