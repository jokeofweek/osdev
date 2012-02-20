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
extern u8int inportb (u16int _port);
extern void outportb (u16int _port, u8int _data);

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

/* We will use this later on for reading from the I/O ports to get data
*  from devices such as the keyboard. We are using what is called
*  'inline assembly' in these routines to actually do the work */
u8int inportb (u16int _port){
    u8int rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/* We will use this to write to I/O ports to send bytes to devices. This
*  will be used in the next tutorial for changing the textmode cursor
*  position. Again, we use some inline assembly for the stuff that simply
*  cannot be done in C */
void outportb (u16int _port, u8int _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

#endif