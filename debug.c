/*
 * TRAIN JACK
 * Train Jack is my brain fxxk Virtual Machine.
 * (c) Motoki Yoan
 * 2012/3/11
 */

#include "trainjack.h"

/* -------------------------------------------------------- */

/*
static bool isInst(char i) {
    switch (i) {
        case '+':
        case '-':
        case '<':
        case '>':
        case '.':
        case ',':
        case '[':
        case ']':
             return true;
        default:
             return false;
    }
}
*/

void dbg_stat(int stack[], int top) {
    int i;
    printf("stack(%d): [", top);
    for (i = 0; i < top + 3; i++) {
        printf("%d, ", stack[i]);
    }
    printf("]\n");
    if (stack[6] < 0) {
        asm("int3");
    }
    return;
}

static void printNav(int i)
{
    int j = 0;
    for(j; j < i; j++) {
        printf(" ");
    }
    printf("v\n");
}

static void printLine(const char* src, size_t end) {
    size_t start = 0;
    size_t j;
    if (end == 0) {
        for (j = 0; j < strlen(src); j++) {
            if (src[j] == '\n') {
                break;
            }
        }
        for (start = 0; start < j; start++) {
             printf("%c", src[start]);
        }
    }
    else {
        for (j = 0; j < strlen(src); j++) {
            if (src[j] == '\n' && j < (size_t)end) {
                start = j + 1;
            }
        }
        for (start; start < end; start++) {
             printf("%c", src[start]);
        }

    }
    printf("\n");
}

void dbg_srcNavigator(const char* src, int i) {
    int lineend = 0;
    size_t j;
    for(j = 0; j < strlen(src); j++) {
        if (src[j] == '\n') {
            lineend = j;
        }
        if (j > (size_t)i) {
            printNav(i - lineend);
            printLine(src, (size_t)lineend);
            return;
        }
    }
}
