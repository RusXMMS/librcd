#include <stdio.h>
#define _AUTO_DEBUG
#include "librcd.tmp.c"


main(int argc, char *argv[]) {
    FILE *f;
    int len,st;
    char word[256];


    if (argc!=2) {
	printf("Usage: %s <file name>\n",argv[0]);
	exit(0);
    }

    f=fopen(argv[1],"r");
    if (!f) {
	printf("Failed to open specified file. Check permissions!\n");
	exit(1);
    }
    
    while(!feof(f)) {
	fscanf(f,"%s",&word);
//	len=strlen(word)-1;
	for(st=0;word[st]=='"'||word[st]=='\''||word[st]=='(';st++);
	for(len=strlen(word)-1;word[len]==','||word[len]=='.'||word[len]=='!'||word[len]=='?'||word[len]==';'||word[len]=='-'||word[len]==':'||word[len]=='"'||word[len]=='\''||word[len]==')';len--);
	if (len<5) continue;
	else word[len+1]=0;

	rcdGetRussianCharset(word+st,len+1-st);
    }
}
