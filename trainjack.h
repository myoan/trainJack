/*
 * TRAIN JACK
 * Train Jack is my brain fxxk Virtual Machine.
 * (c) Motoki Yoan
 * 2012/3/11
 */

/* -------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STACKSIZE 1024 * 32
#define BUFSIZE 64
#define READSIZE 1024 * 32

struct Stack {
    int stack[STACKSIZE];
    int top;
};

struct Code {
	int op;
	int label;
};

typedef struct Stack Stack;
typedef struct Code Code;

/* -------------------------------------------------------- */
/* [prototype functions] */
void dbg_srcNavigator(const char* src, int i);
void dbg_stat(int stack[], int top);
