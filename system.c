#ifndef __SYSTEM_H
#define __SYSTEM_H

// Standardized typedefs.
typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;
typedef u32int         size_t;

extern u8int *memcpy(u8int *dest, const u8int *src, size_t count);
extern u8int *memset(u8int *dest, u8int val, size_t count);
extern u16int *memsetw(u16int *dest, u16int val, size_t count);
extern u8int inportb (u16int port);
extern void outportb (u16int port, u8int data);
extern u16int inportw (u16int port);

/*
 * Copies 'count' bytes from src to dest.
 *
 */
u8int *memcpy(u8int *dest, const u8int *src, size_t count){
	char* dstPtr = (char *)dest;
	const char* srcPtr = (const char *)src;

    for (; count != 0; count--) *dstPtr++ = *srcPtr++;
	
	return dest;
}

/*
 * Sets 'count' bytes of dst to val.
 */
u8int *memset(u8int *dest, u8int val, size_t count){
	char* dstPtr = (char *)dest;

    for (; count != 0; count--) *dstPtr++ = val;
	
	return dest;
}

/*
 * Sets 'count' 16-bit bytes of dst to val.
 */
u16int *memsetw(u16int *dest, u16int val, size_t count){
	u16int* dstPtr = (u16int *)dest;

    for (; count != 0; count--) *dstPtr++ = val;
	
	return dest;
}

/*
 * Reads a byte from a given port.
 */
u8int inportb (u16int port){
    u8int rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (port));
    return rv;
}

/*
 * Reads a short from a given port.
 */
u16int inportw(u16int port){
   u16int ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

/* 
 * Writes a byte to a given port.
 */
void outportb (u16int port, u8int data){
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}

#endif