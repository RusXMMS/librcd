/*
  LibRCD - Public Interface

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

#ifndef _LIBRCD_H
#define _LIBRCD_H

#ifdef __cplusplus
extern "C" {
#endif

enum rcd_russian_charset_t {
    RUSSIAN_CHARSET_WIN = 0,
    RUSSIAN_CHARSET_KOI,
    RUSSIAN_CHARSET_UTF8,
    RUSSIAN_CHARSET_ALT,
    RUSSIAN_CHARSET_LATIN
};
typedef enum rcd_russian_charset_t rcd_russian_charset;


/*
rcdGetRussianCharset
    Detects encoding of russian text passed in buf variable. Support 
    UTF-8, CP1251, CP866 and KOI8-R encoding.
    
    buf  	String with russian texts
    len  	Number of bytes to use from buf. If zero is passed determined 
		by strlen.
    
    Returns:
	0 - CP1251
	1 - KOI8-R
	2 - UTF8
	3 - CP866
	4 - ISO8859-1
*/

rcd_russian_charset rcdGetRussianCharset(const char *buf, int len);

#ifdef __cplusplus
}
#endif

/* Backward compatibility */
#ifndef _LIBRCD_C
# define russian_charsets rcd_russian_charset_t
# define get_russian_charset rcdGetRussianCharset
#endif /* ! _LIBRCD_C */

#endif /* _LIBRCD_H */
