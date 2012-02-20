#define VIDEO_MEMORY_ADDRESS 0xb8000;

#define SCREEN_ROWS 25
#define SCREEN_COLUMNS 80

#define BLACK 0x00
#define BLUE 0x01
#define GREEN 0x02
#define CYAN 0x03
#define RED 0x04
#define MAGENTA 0x05
#define BROWN 0x06
#define LIGHT_GREY 0x07
#define DARK_GREY 0x08
#define LIGHT_BLUE 0x09
#define LIGHT_GREEN 0x0A
#define LIGHT_CYAN 0x0B
#define LIGHT_RED 0x0C
#define LIGHT_MAGENTA 0x0D
#define LIGHT_BROWN 0X0E
#define WHITE 0X0F

typedef struct {
	u8int attributes;
	u32int x;
	u32int y;
} console;

console mainConsole;
u16int *videoMemory = (u16int *) VIDEO_MEMORY_ADDRESS;
u8int *u8videoMemory = (u8int *) VIDEO_MEMORY_ADDRESS;
	
/*
 * Calculates the attribute byte for a foreground and a background color.
 */
u8int getTextAttribute(u8int foreground, u8int background){
	return (background << 4) | (foreground & 0x0F);
}

/*
 * Calculates the 16-bit value of a u8intacter and attribute.
 */
u16int getAttributeTextValue(u8int u8intacter, u8int attributes){
	return u8intacter | (attributes << 8);
}

/*
 * Calculates the 16-bit value of a u8intacter, foreground and background.
 */
u16int getTextValue(u8int u8intacter, u8int foreground, u8int background){
	return u8intacter | (getTextAttribute(foreground, background) << 8);
}

/*
 * Clears the screen.
 */
void cls(){
	// Note that we must use short for the pointer so that we can
	// use memsetw.
	u32int i=0;
	
	 // empty text with white text.
	u16int blankCell = getTextValue(' ', WHITE, BLACK);
	
	for (i = 0; i < SCREEN_ROWS; i++)
		memsetw(videoMemory + (i * SCREEN_COLUMNS), blankCell, SCREEN_COLUMNS);
		
	// Clear current console options
	mainConsole.attributes = getTextAttribute(WHITE, BLACK);
	mainConsole.x = 0;
	mainConsole.y = 0;
	updateCursor();
}

/*
 * Scroll the screen up a line.
 */
void scroll(){
	u16int blankCell = getTextValue(' ', WHITE, BLACK);
	
	// If we are not at the end number of rows, then all we must do is move down by one
	if (mainConsole.y >= SCREEN_ROWS){
		// Find the new line 1
		u16int offset = mainConsole.y - SCREEN_ROWS + 1;
		memcpy(u8videoMemory, u8videoMemory + (offset * SCREEN_COLUMNS * 2), (SCREEN_ROWS - offset) * SCREEN_COLUMNS * 2);
		
		// Clear the last row
		memsetw(videoMemory + ((SCREEN_ROWS - offset) * SCREEN_COLUMNS), blankCell, SCREEN_COLUMNS);
		mainConsole.y = SCREEN_ROWS - 1;
	}
}

void putc(u8int c){
	u16int * cellPos;
	
	// Backspace - move cursor back one position.
	if (c == 0x08){
		if (mainConsole.x > 0)
			mainConsole.x--;
	// Tab - move cursor towards next x which is divisible by 8
	} else if (c == 0x09) {
		mainConsole.x = (mainConsole.x + 8) & ~(8 - 1);
	// Carriage return - set x to 0
	} else if (c == '\r'){
		mainConsole.x = 0;
	// New line
	} else if (c == '\n'){
		mainConsole.x = 0;
		mainConsole.y++;
	// Printable u8intacter
	} else if (c >= ' '){
		cellPos = videoMemory + ((mainConsole.y * SCREEN_COLUMNS) + mainConsole.x);
		*cellPos = getAttributeTextValue(c, mainConsole.attributes);
		mainConsole.x++;
	}
	
	// Move line down y 1 if we have reached the edge of the columns
	if (mainConsole.x > SCREEN_COLUMNS){
		mainConsole.x = 0;
		mainConsole.y++;
	}
	
	// Scroll and update cursor.
	scroll();
	updateCursor();
}


/*
 * This prints a string to the current console.
 */
void puts(u8int *str){
	u32int i;
	
	for (i = 0; i < strlen(str); i++)
		putc(str[i]);
}

u8int u8intToHexCharacter(u8int i){
	if (i < 10){
		return '0' + i;
	} else {
		return 'A' + (i - 10);
	}
}

void puthex(u32int i){
	u8int result[11]; // 11 for 0x + 8 characters + '\0'
	result[0] = '0';
	result[1] = 'x';
	result[11] = '\0';
	
	u32int pos = 8;
	u8int current;
	
	while (pos > 0){
		current = (u8int) i & 0x0f;
		result[1 + pos] = u8intToHexCharacter(current);
		i = i >> 4;
		pos--;
	}
	
	puts(result);
}

void putdec(u32int i){
	// TODO.
}

/*
 * Sends a hardware message to make the new cursor position blink.
 */
void updateCursor(){
	u16int offset = (mainConsole.y * SCREEN_COLUMNS) + mainConsole.x;
	outportb(0x3D4, 14);
    outportb(0x3D5, offset >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, offset);
}

/*
 * This updates the current text color and background color of the console.
 */
void setTextColor(u8int foreground, u8int background){
	mainConsole.attributes = getTextAttribute(foreground, background);
}

/*
 * Prints a message starting at a given cell.
 */
 /*
void kernel_printf(u8int *message, u32int line, u32int column){
	u8int *videoMemory = (u8int *) VIDEO_MEMORY_ADDRESS;
	
	// Need to start at right line, and each line is 80 spaces.
	// We also nee to multiply by two as there is two bytes
	// per slot.
	u32int i = (((line * 80) + column) * 2);
	
	while (*message != 0){
		// Special case for new line
		if (*message == '\n'){
			line++;
			i = (((line * 80) + column) * 2);
		// 4 empty spaces for tabs
		} else if (*message == '\t'){
			videoMemory[i++] = ' ';
			videoMemory[i++] = WHITE;
			videoMemory[i++] = ' ';
			videoMemory[i++] = WHITE;
			videoMemory[i++] = ' ';
			videoMemory[i++] = WHITE;
			videoMemory[i++] = ' ';
			videoMemory[i++] = WHITE;
		// Regular u8intacter
		} else {
			videoMemory[i] = *message;
			i++;
			videoMemory[i] = WHITE;
			i++;
		}
		
		*message++;
	}
}
*/
void initializeConsole(){
	cls();
}
