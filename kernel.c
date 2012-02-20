// Black background with white, non-blinking text.

#define PIC1 0x20
#define PIC2 0xA0

#define ICW1 0x11
#define ICW4 0x01

#include "system.h"
#include "system.c"
#include "string.c"
#include "screen.c"

kernel_main(){
	initialize_console();
	puts("Hello, World!\n");
	set_text_color(RED, LIGHT_GREY);
	puts("\tWelcome to my OS!\n");
	set_text_color(WHITE, BLACK);
	puts("The address for video memory is: ");
	puthex(0xb8000);
	for(;;);
}

