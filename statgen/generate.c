/*
  LibRCD - Statistic generator

  Copyright (C) 2005-2008 Suren A. Chilingaryan <csa@dside.dyndns.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2 of the GNU General Public License as published
  by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <iconv.h>
#include <langinfo.h>
#include <sys/types.h>
#include <sys/stat.h>

#define first_char 128
#define last_char 255

#define original_first_char 192
#define original_last_char 255

#define chars_number (last_char-first_char+1)
#define array_size (chars_number*chars_number)

struct array_pos {
    int ll;
    int uu;
    int lu;
    int ul;
};

struct pstat {
    unsigned long p;
    unsigned long s;
    unsigned long e;
};

iconv_t icnv=(iconv_t)-1;

int end_symbol(char ch) {
    if (ch=='\r'||ch=='\n'||ch==0||ch==' '||ch=='\t'||ch==','||ch=='.'||ch=='!'||ch=='?'||ch==';'||ch=='-'||ch==':'||ch=='"'||ch=='\''||ch==')') return 1;
    return 0;
}

int start_symbol(char ch) {
    if ((ch=='\t')||ch=='\r'||ch=='\n'||(ch==' ')||(ch=='(')||(ch=='"')||(ch=='\'')) return 1;
    return 0;
}    


unsigned char convert_char(unsigned char c) {
    char r;
    char *pr, *pc;
    size_t lr=1,lc=1;
    pr=&r;pc=&c;
    
    if (icnv == (iconv_t)-1) return c;
    if (iconv(icnv,&pc,&lc,&pr,&lr)<0) {
	printf("Error converting characters!\n");
	exit(1);
    }
    return r;
}

int get_array_pos(struct array_pos *pos, int a, int b) {
    int la,ua,lb,ub;
    if ((a<original_first_char)||(a>original_last_char)) return -1;
    if ((b<original_first_char)||(b>original_last_char)) return -1;
    
    la=tolower(a);
    ua=toupper(a);
    lb=tolower(b);
    ub=toupper(b);

    if ((la<original_first_char)||(la>original_last_char)) la=a;
    if ((lb<original_first_char)||(lb>original_last_char)) lb=b;
    if ((ua<original_first_char)||(ua>original_last_char)) ua=a;
    if ((ub<original_first_char)||(ub>original_last_char)) ub=b;
    
    la=convert_char(la);
    ua=convert_char(ua);
    lb=convert_char(lb);
    ub=convert_char(ub);
    
//    la=a;lb=b;ua=a;ub=b;
    
    pos->ll=(la-first_char)*chars_number+(lb-first_char);
    if (la!=ua) {
	pos->ul=(ua-first_char)*chars_number+(lb-first_char);
    } else {
	pos->ul=-1;
    } 
    if (lb!=ub) {
	pos->lu=(la-first_char)*chars_number+(ub-first_char);
    }
    else {
	pos->lu=-1;
    }
    if ((lb!=ub)&&(la!=ua)) {
	pos->uu=(ua-first_char)*chars_number+(ub-first_char);
    } else {
	pos->uu=-1;
    }
    return 0;
}


struct pstat *analyze(const unsigned char *text, unsigned long length) {
    struct pstat *a;
    unsigned long i;
    struct array_pos pos;
    
    a=(struct pstat*)malloc(array_size*sizeof(struct pstat));
    if (!a) return NULL;

    for (i=0;i<array_size;i++) {
	a[i].p=0;
	a[i].s=0;
	a[i].e=0;
    }
	
    for (i=1;i<length;i++) {
	if (get_array_pos(&pos,text[i-1],text[i])>=0) {
	    if (pos.ll>=0) {
		if ((i==1)||(start_symbol(text[i-2]))) a[pos.ll].s++;
		else if ((i+2==length)||(end_symbol(text[i+1]))) a[pos.ll].e++;
		else a[pos.ll].p++;
	    }
	    if (pos.ul>=0) {
		if ((i==1)||(start_symbol(text[i-2]))) a[pos.ul].s++;
		else if ((i+2==length)||(end_symbol(text[i+1]))) a[pos.ul].e++;
		else a[pos.ul].p++;
	    }
//	    if (pos.lu>=0) {
//		if ((i==1)||(start_symbol(text[i-2]))) a[pos.lu].s++;
//		else if ((i+2==length)||(end_symbol(text[i+1]))) a[pos.lu].e++;
//		else a[pos.lu].p++;
//	    }
	    if (pos.uu>=0) {
		if ((i==1)||(start_symbol(text[i-2]))) a[pos.uu].s++;
		else if ((i+2==length)||(end_symbol(text[i+1]))) a[pos.uu].e++;
		else a[pos.uu].p++;
	    }
	}
    }
    return a;
}


int print(struct pstat *a) {
    int i,j,k,n;
    
    for (i=first_char,k=0,n=0;i<=last_char;i++)
	for (j=first_char;j<=last_char;j++,k++) {
	    if ((a[k].p)||(a[k].s)||(a[k].e)) {
		if ((n)&&(n%8==0)) printf(",\n");
		else if (n) printf(", ");
		printf("{'%c','%c',%lf,%lf,%lf}",i,j,a[k].p?log10(a[k].p):-2,a[k].s?log10(a[k].s):-2,a[k].e?log10(a[k].e):-2);
		n++;
	    }
	}
    if ((n%8)!=1) printf("\n");
    return n;
}


unsigned long npow(unsigned long n) {
    unsigned long res=2;
    while (res<=n) res*=2;
    return res;
}

main(int argc, char *argv[]) {
    FILE *f;
    struct stat st;
    unsigned char *text;
    unsigned long len;
    struct pstat *a;
    int num;
    long i,sum;
    char locale[32];


    if (argc!=3) {
	printf("Usage: %s <file name> <encoding>\n",argv[0]);
	exit(0);
    }

    if (strlen(argv[2])>12) {
	printf("Invalid encoding(%s) specified!\n",argv[2]);
	exit(1);
    }
    
    if ((!strcasecmp(argv[2],"koi"))||(!strcasecmp(argv[2],"koi8"))||(!strcasecmp(argv[2],"koi-8"))||(!strcasecmp(argv[2],"koi8-r")))
    	sprintf(locale,"%s","KOI8-R");
    else if ((!strcasecmp(argv[2],"win"))||(!strcasecmp(argv[2],"cp1251"))||(!strcasecmp(argv[2],"cp-1251"))||(!strcasecmp(argv[2],"win1251"))||(!strcasecmp(argv[2],"win-1251")))
	sprintf(locale,"%s","CP1251");
    else if ((!strcasecmp(argv[2],"alt"))||(!strcasecmp(argv[2],"cp866"))||(!strcasecmp(argv[2],"cp-866"))||(!strcasecmp(argv[2],"ibm866"))||(!strcasecmp(argv[2],"ibm-866")))
	sprintf(locale,"%s","IBM866");
    else
	sprintf(locale,"%s",argv[2]);
    
    if (!setlocale(LC_CTYPE,"")) {
	printf("Can't set locale!\n");
	exit(1);
    }

    if (strcmp(locale,nl_langinfo(CODESET))) {
	if ((icnv=iconv_open(locale,nl_langinfo(CODESET)))<0) {
	    printf("Can't initialize iconv!\n");
	    exit(1);
	}
    }
    
    
    if (stat(argv[1],&st)) {
	printf("Specified file can't be stated!\n");
	iconv_close(icnv);
	exit(1);
    }
    
    if (!S_ISREG(st.st_mode)) {
	printf("Specified file isn't regular file!\n");
	iconv_close(icnv);
	exit(1);
    }
    
    text=(unsigned char*)malloc(st.st_size);
    if (!text) {
	printf("Can't allocate %lu bytes of memory!\n",st.st_size);
	iconv_close(icnv);
	exit(1);
    }
    
    f=fopen(argv[1],"r");
    if (!f) {
	printf("Failed to open specified file. Check permissions!\n");
	free(text);
	iconv_close(icnv);
	exit(1);
    }
    if (fread(text,1,st.st_size,f)!=st.st_size) {
	printf("Problem reading specified file!\n");
	free(text);
	fclose(f);
	iconv_close(icnv);
	exit(1);
    }
    fclose(f);
    
    a=analyze(text,st.st_size);
    if (a) {
	printf("static const lng_stat2 enc_%s[]={\n",argv[2]);
	num=print(a);
	printf("};\n\n");
	free(a);
	fprintf(stderr,"static unsigned int indexes2=%lu;\n",num);
	fprintf(stderr,"static unsigned int npow2=%lu;\n",npow(num));
    } else printf("Failed to allocate %lu bytes of memory!\n",array_size*sizeof(struct pstat));

    free(text);
    iconv_close(icnv);
}
