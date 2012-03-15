/*
 * TRAIN JACK
 * Train Jack is my brainfxxk Virtual Machine.
 * (c) Motoki Yoan
 * 2012/3/11
 */

#include "trainjack.h"

/* -------------------------------------------------------- */

static int searchBegin(const char* src, int i) {
	char c;
	while ((c = src[i]) != '[') {
        if (c == ']') {
            i = searchBegin(src, i-1);
        }
		i--;
	}
	return i;
}

static int searchEnd(const char* src, int i) {
	char c = src[i];
	while ((c = src[i]) != ']') {
        if (c == '[') {
            i = searchEnd(src, i+1);
        }
		i++;
	}
	return i;
}

static int exec(const char* src) {
    int stack[STACKSIZE];
    int top = 0;
	size_t i;
	memset(stack, '\0', STACKSIZE * sizeof(int));
	for (i = 0; i < strlen(src); i++) {
		char token = src[i];
        if (top < 0) {
            printf("ERROR: stack is out of bound.\n");
            exit(1);
        }
		switch(token) {
			case '+':
				stack[top]++;
				break;
			case '-':
				stack[top]--;
				break;
			case '<':
				top--;
				break;
			case '>':
				top++;
				break;
			case '.':
				putchar(stack[top]);
				break;
			case ',':
				stack[top] = getchar();
				break;
			case '[':
				if (stack[top] == 0) {
					i = searchEnd(src, i+1);
				}
				break;
			case ']':
				if (stack[top] != 0) {
					i = searchBegin(src, i-1);
				}
				break;
			//case '\\':   // original instructioin.
            //            // when / is called, trainjack displayes stack info.
            //    dbg_srcNavigator(src, i);
            //    dbg_stat(stack, top);
            //    break;
			case '\0':
				return 0;
            default: 
                break;
		}
	}
	return -1;
}

static char* readFile(const char* file) {
    FILE* fp;
    char s[BUFSIZE];
    if ((fp = fopen(file, "r")) == NULL){
    	fprintf(stderr, "ERROR: cannot open file %s\n", file);
    	exit(0);
    }
    char* ret = (char*)malloc(sizeof(char) * READSIZE);
    while(fgets(s, BUFSIZE, fp) != NULL) {
        strcat(ret, s);
    }
	fclose(fp);
    return ret;
}

char* parse(char* src)
{
    char* ret = (char*)malloc(sizeof(char) * READSIZE);
    size_t i, j = 0;
    for (i = 0; i < strlen(src); i++) {
        switch (src[i]) {
            case '+':
            case '-':
            case '<':
            case '>':
            case '.':
            case ',':
            case '[':
            case ']':
            //case '\\':
                ret[j++] = src[i];
                break;
            default:
                break;
        }
    }
    free(src);
    ret[j] = '\0';
    printf("parsed: %s\n", ret);
    return ret;
}

/* -------------------------------------------------------- */
/* [main] */

int main(int argc, char const* argv[])
{
    if (argc <= 1) {
        fprintf(stderr, "ERROR: No Input file.\n");
        exit(0);
    }
    char* src = readFile(argv[1]);
    exec(parse((char*)src));
    printf("\n");
	return 0;
}
