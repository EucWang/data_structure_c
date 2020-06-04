
#include <stdio.h>
#include <stdlib.h>
#include "../test.h"
#include "../../lib/arr_tool/arrTool.h"
#include "../../lib/mylog/mylog.h"

void arr2_test() {

    int ** arr2 = (int **)createArr2(sizeof(int), 10, 10);
    
    printfArr2(arr2, 10, 10);

    arr2[0][0] = 1;
    arr2[1][1] = 1;
    arr2[2][2] = 1;
    arr2[3][3] = 1;
    arr2[4][4] = 1;
    arr2[5][5] = 1;
    arr2[6][6] = 1;
    arr2[7][7] = 1;
    arr2[8][8] = 1;
    arr2[9][9] = 1;

    printf("after change values. then print arr2\n");
    printfArr2(arr2, 10, 10);
    
    //_LOG(__FILE__, __LINE__, LogLevel[IC_DEBUG_LEVEL], -1, "my log.");

    freeArr2(&arr2, 10, 10);

    if(arr2 == NULL) {
        printf("\nfree done.!\n");
    }
}