/*
  LibRCD tools - Debugging information

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
