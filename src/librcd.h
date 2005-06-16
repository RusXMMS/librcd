#ifndef _LIBRCD_H
#define _LIBRCD_H

#ifdef __cplusplus
extern "C" {
#endif

enum russian_charsets {
    RUSSIAN_CHARSET_WIN = 0,
    RUSSIAN_CHARSET_KOI,
    RUSSIAN_CHARSET_UTF8,
    RUSSIAN_CHARSET_ALT
};


/*
get_russian_charset
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
*/

enum russian_charsets get_russian_charset(const char *buf,int len);

#ifdef __cplusplus
}
#endif

#endif /* _LIBRCD_H */
