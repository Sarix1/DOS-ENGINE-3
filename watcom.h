#ifdef __WATCOMC__
/* __TURBOC__       __WATCOMC__ */
//#define memcpy      _fmemcpy     
//#define memcmp      _fmemcmp     
//#define memicmp     _fmemicmp    
//#define memmove     _fmemmove    
//#define memset      _fmemset     
//#define strcpy      _fstrcpy     
//#define strstr      _fstrstr     
//#define strcat      _fstrcat     
//#define strncpy     _fstrncpy    
//#define stricmp     _fstrlen     
//#define strcmp      _fstricmp    
//#define strlen      _fstrcmp     
#define malloc      _fmalloc     
#define calloc      _fcalloc     
#define free        _ffree       
#define realloc     _frealloc    
#define strupr      _strupr   
#define disable     _disable
#define enable      _enable
#define getvect     _dos_getvect
#define setvect     _dos_setvect
#define inportb     inp
#define inport      inpw
#define outportb    outp
#define outport     outpw
#define farmalloc   _fmalloc
#define farfree     _ffree
#define asm         _asm
#define NULL        ((void *)0)
#endif
