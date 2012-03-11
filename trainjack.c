#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACKSIZE 64

void readFile(char* str)
{
	FILE *fp;
	char s[64], tmp[256];
	char* line = tmp;
	memset(s, 0, 64);
	memset(line, 0, 256);
	int parenth = 0;
	if ((fp = fopen(str, "r")) == NULL){
		fprintf(stderr, "ERROR: cannot open file %s\n", str);
		exit(0);
	}

	while (fgets(s, 64, fp) != NULL){
		strcat(line, s);
		Node_t* head = new_node();
		parenth += getParenth(s);
		if (parenth == 0){
			parse(head, &line);
			eval(head);
			memset(line, 0, 256);
		}
	}
	if (parenth != 0){
		fprintf(stderr, "ERROR: sytax error\n");
		exit(0);
	}
	fclose(fp);
}

int searchBegin(const char* src, int i) {
	//printf("i : %d\n", i);
	char c;
	while ((c = src[i]) != '[') {
		i--;
	}
	//printf("ret : %d\n", i);
	return i;
}

int searchEnd(const char* src, int i) {
	//printf("i : %d\n", i);
	char c = src[i];
	while ((c = src[i]) != ']') {
		printf("c: %c\n", c);
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
				//p = getchar();
				break;
			case '[':
				if (stack[top] == 0) {
					i = searchEnd(src, i);
				}
				break;
			case ']':
				if (stack[top] != 0) {
					i = searchBegin(src, i);
				}
				break;
			case '\0':
				return 0;
		}
	}
	return -1;
}

/*- test -*/
int main(int argc, char const* argv[])
{
	const char* src = ">+++++++++[<++++++++>-]<.>+++++++[<++++>-]<+.+++++++..+++.[-]>++++++++[<++ ++>-]<.>+++++++++++[<+++++>-]<.>++++++++[<+++>-]<.+++.------.--------.[-]> ++++++++[<++++>-]<+.[-]++++++++++.\0"; // HELLO WORLD;
	printf("\n");
	exec(src);
	return 0;
}
