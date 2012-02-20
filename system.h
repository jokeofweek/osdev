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

/*  GDT */
//extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

/* Strings */
extern u8int getTextAttribute(u8int foreground, u8int background);
extern u16int getAttributeTextValue(u8int u8intacter, u8int attributes);
extern u16int getTextValue(u8int u8intacter, u8int foreground, u8int background);
extern void cls();
extern void scroll();
extern void putc(u8int c);
extern void puts(u8int *str);
extern u8int u8intToHexCharacter(u8int i);
extern void puthex(u32int i);
extern void putdec(u32int i);
extern void updateCursor();

/* Strings */
extern size_t strlen(const u8int *str);
extern int strcmp(const u8int *str1, const u8int *str2);


#endif