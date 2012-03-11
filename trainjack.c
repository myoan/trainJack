#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACKSIZE 1024

struct Stack {
    int stack[STACKSIZE];
    int top;
};

typedef struct Stack stack;

int searchBegin(const char* src, int i) {
	//printf("i : %d\n", i);
	char c;
	while ((c = src[i]) != '[') {
        //printf("begin i: %lu(%c)\n", i, c);
        if (c == ']') {
            i = searchBegin(src, --i);
        }
		i--;
	}
	//printf("ret : %d\n", i);
	return i;
}

int searchEnd(const char* src, int i) {
	//printf("i : %d\n", i);
	char c = src[i];
	while ((c = src[i]) != ']') {
        //printf("end i: %lu(%c)\n", i, c);
        if (c == ']') {
            i = searchEnd(src, --i);
        }
		i++;
	}
	//printf("ret : %d\n", i);
	return i;
}

int exec(const char* src) {
    int stack[STACKSIZE];
    int top = 0;
	size_t i;
	memset(stack, '\0', STACKSIZE * sizeof(int));
	for (i = 0; i < strlen(src); i++) {
		char token = src[i];
        //printf("stacktop: %d, read: \"%c\"(%d)\n", top, token, i);
        //printf("src: %s\n", src);
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
			case '\0':
				return 0;
            default: 
                break;
		}
	}
	return -1;
}

#define BUFSIZE 64
#define READSIZE 1024 * 32
char* readFile(const char* file) {
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

/*----------- main ----------*/

int main(int argc, char const* argv[])
{
    if (argc <= 1) {
        fprintf(stderr, "ERROR: No Input file.\n");
        exit(0);
    }
    char* src = readFile(argv[1]);
    exec(src);
    printf("\n");
	return 0;
}
