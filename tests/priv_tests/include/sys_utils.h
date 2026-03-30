#include <stdlib.h>

/*  
 *  -----------------------------------------------
 *                   Memory utils
 *  -----------------------------------------------
 */

void* memcpy(void* dest, const void* src, size_t len);
void* memset(void* dest, int byte, size_t len);

/*  
 *  -----------------------------------------------
 *                   String utils
 *  -----------------------------------------------
 */

size_t strlen(const char *s);
size_t strnlen(const char *s, size_t n);
int strcmp(const char* s1, const char* s2);
char* strcpy(char* dest, const char* src);
long atol(const char* str);


/*  
 *  -----------------------------------------------
 *                   Print utils
 *  -----------------------------------------------
 */

int puts(const char* s);
int putchar(int ch);
int printf(const char* fmt, ...);
int sprintf(char* str, const char* fmt, ...);


/*  
 *  -----------------------------------------------
 *                   System utils
 *  -----------------------------------------------
 */

void exit(int code);

