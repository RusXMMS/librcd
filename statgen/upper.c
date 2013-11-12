/*
  LibRCD tools - change a case of words in text files

  Copyright (C) 2005-2008 Suren A. Chilingaryan <csa@dside.dyndns.org>

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
#include <unistd.h>
#include <ctype.h>
#include <locale.h>
#include <sys/types.h>
#include <sys/stat.h>


main(int argc, char *argv[]) {
    FILE *f;
    struct stat st;
    unsigned char *text;
    char locale[32];
    int i;


    if (argc!=3) {
	printf("Usage: %s <file name> <encoding>\n",argv[0]);
	exit(0);
    }

    if (strlen(argv[2])>12) {
	printf("Invalid encoding(%s) specified!\n",argv[2]);
	exit(1);
    }
    
    if ((!strcasecmp(argv[2],"koi"))||(!strcasecmp(argv[2],"koi8"))||(!strcasecmp(argv[2],"koi-8"))||(!strcasecmp(argv[2],"koi8-r")))
    	sprintf(locale,"ru_RU.%s","KOI8-R");
    else if ((!strcasecmp(argv[2],"win"))||(!strcasecmp(argv[2],"cp1251"))||(!strcasecmp(argv[2],"cp-1251"))||(!strcasecmp(argv[2],"win1251"))||(!strcasecmp(argv[2],"win-1251")))
	sprintf(locale,"ru_RU.%s","CP1251");
    else
	sprintf(locale,"ru_RU.%s",argv[2]);
    if (!setlocale(LC_CTYPE,locale)) {
	printf("Can't set locale %s!\n",argv[2]);
	exit(1);
    }
    
    if (stat(argv[1],&st)) {
	printf("Specified file can't be stated!\n");
	exit(1);
    }
    
    if (!S_ISREG(st.st_mode)) {
	printf("Specified file isn't regular file!\n");
	exit(1);
    }
    
    text=(unsigned char*)malloc(st.st_size);
    if (!text) {
	printf("Can't allocate %lu bytes of memory!\n",st.st_size);
	exit(1);
    }
    
    f=fopen(argv[1],"r");
    if (!f) {
	printf("Failed to open specified file. Check permissions!\n");
	free(text);
	exit(1);
    }
    if (fread(text,1,st.st_size,f)!=st.st_size) {
	printf("Problem reading specified file!\n");
	free(text);
	fclose(f);
	exit(1);
    }
    fclose(f);
    
    for (i=0;i<st.st_size;i++) 
	text[i]=toupper(text[i]);
    
    f=fopen("UPPED.OUT","w");
    fwrite(text,1,st.st_size,f);
    fclose(f);
    free(text);
}
