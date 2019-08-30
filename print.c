//
// Created by a8398 on 2019/8/29.
//

#include <stdio.h>
#include "print.h"

void DumpBuf(const char *tip, unsigned char *buf, int len)
{
    int i;
    printf("\n%s:", tip);
    for(i = 0; i<len; ++i) {
        if((i&0xf) == 0x0)
            printf("\n%08x : ", i);
        printf(" %02x", buf[i]);
    }
    printf("\n");
}