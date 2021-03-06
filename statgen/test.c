/*
  LibRCD tools - test utility

  Copyright (C) 2005-2018 Suren A. Chilingaryan <csa@suren.me>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License version 2.1 or later
  as published by the Free Software Foundation.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License 
  for more details.

  You should have received a copy of the GNU Lesser General Public License 
  along with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <stdio.h>
#include "librcd.tmp.c"

main(int argc, char *argv[]) {
    FILE *f;
    int len,st;
    char word[256],phrase[8192];
    unsigned long a[4]={0,0,0,0};
    int i,max,mw;


    if ((argc!=2)&&(argc!=3)) {
	printf("Usage: %s <file name> [<max words>]\n",argv[0]);
	exit(0);
    }

    if (argc==3) mw=atoi(argv[2]);
    else mw=1;
    
    f=fopen(argv[1],"r");
    if (!f) {
	printf("Failed to open specified file. Check permissions!\n");
	exit(1);
    }
    
    while(!feof(f)) {
	strcpy(phrase,"");
	for (i=0;i<mw;i++) {
	    if (i) strcat(phrase," ");
	    fscanf(f,"%s",&word);
	    for(st=0;word[st]=='"'||word[st]=='\''||word[st]=='(';st++);
	    if (strlen(word)<1) continue;
	    for(len=strlen(word)-1;word[len]==','||word[len]=='.'||word[len]=='!'||word[len]=='?'||word[len]==';'||word[len]=='-'||word[len]==':'||word[len]=='"'||word[len]=='\''||word[len]==')';len--);
	    if (strlen(word)<1) continue;
	    else word[len+1]=0;
	    strcat(phrase,word+st);
	}
	if (strlen(phrase)<5) continue;

	a[rcdGetRussianCharset(phrase,0)]++;
    }

    printf("Win: %lu, Koi: %lu, Alt: %lu, UTF: %lu\n",a[0],a[1],a[3],a[2]);
    fclose(f);
    if (a[0]>a[1]) {
	if (a[0]>a[2]) max=0;
	else max=2;
    } else {
	if (a[1]>a[2]) max=1;
	else max=2;
    }
    if (a[3]>max) max=3;

    f=fopen(argv[1],"r");
    while(!feof(f)) {
	strcpy(phrase,"");
	for (i=0;i<mw;i++) {
	    if (i) strcat(phrase," ");
	    fscanf(f,"%s",&word);
	    for(st=0;word[st]=='"'||word[st]=='\''||word[st]=='(';st++);
	    if (strlen(word)<1) continue;
	    for(len=strlen(word)-1;word[len]==','||word[len]=='.'||word[len]=='!'||word[len]=='?'||word[len]==';'||word[len]=='-'||word[len]==':'||word[len]=='"'||word[len]=='\''||word[len]==')';len--);
	    if (strlen(word)<1) continue;
	    else word[len+1]=0;
	    strcat(phrase,word+st);
	}
	if (strlen(phrase)<5) continue;

	i=rcdGetRussianCharset(phrase,0);
	if (i!=max) {
	    if (i==0) printf("Win: %s\n",phrase);
	    else if (i==1) printf("Koi: %s\n",phrase);
	    else if (i==2) printf("UTF: %s\n",phrase);
	    else if (i==3) printf("ALT: %s\n",phrase);
	}
    }
    fclose(f);
}
