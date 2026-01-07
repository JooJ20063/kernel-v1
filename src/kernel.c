#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000

void put_char_at(char c, int x, int y, uint8_t color) {
	volatile uint16_t* vga = (volatile uint16_t*)VGA_ADDRESS;
	uint16_t value = ((uint16_t)color << 8) | (uint8_t)c;
	vga[y * VGA_WIDTH + x] = ((uint16_t)color << 8) | c;
}

void kprint(const char* str, int x, int y, uint8_t color) {
	for (int i = 0; str[i] != '\0'; i++) {
		put_char_at(str[i], x + i, y, color);
	}
}

void kernel_main(void) {
	kprint("HELLO KERNEL", 0, 0, 0x0F);

	for (;;) {
		__asm__ volatile("hlt");
	}
}
