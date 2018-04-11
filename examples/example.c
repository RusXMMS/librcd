/*
  LibRCD - Example application

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
#include <string.h>
#include <librcd.h>

main() {
    rcd_russian_charset res;
    char buf[255];
    int l;
    
    while (fgets(buf,255,stdin)) {
	if (strlen(buf)<2) break;
	
	res = rcdGetRussianCharset(buf,0);
	switch(res) {
	    case RUSSIAN_CHARSET_WIN:
		printf("CP1251: ");
	    break;
	    case RUSSIAN_CHARSET_ALT:
		printf("CP866 : ");
	    break;
	    case RUSSIAN_CHARSET_KOI:
		printf("KOI8-R: ");
	    break;
	    case RUSSIAN_CHARSET_UTF8:
		printf("UTF8  : ");
	    break;
	}
	printf("%s",buf);
	if (buf[strlen(buf)-1]!='\n') printf("\n");
    }
}
