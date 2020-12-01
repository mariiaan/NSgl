/*
	NSgl
    Display.h / Display.c
    Basic library to display a framebuffer on Ndless modified TI-Nspire handhelds,
    convert RGB color values to 2-byte-color and set pixels.

    (C) Copyright 2020, Marian W.
*/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>
#include <os.h>

/* Define some defines for frame buffer */
#define DISPLAY_MODE SCR_320x240_565 /* Pixel mode used for lcd_blit() */
#define DISPLAY_WIDTH 320 /* Display width */
#define DISPLAY_HEIGHT 240 /* Display height */
#define DISPLAY_BPP 2 /* Display bytes per pixel */
#define DISPLAY_BYTES_TOTAL DISPLAY_WIDTH * DISPLAY_HEIGHT * DISPLAY_BPP /* Total size of the framebuffer */

extern char m_display_framebuffer[DISPLAY_BYTES_TOTAL]; /* Framebuffer used for lcd_blit() */
extern bool m_display_initialized; /* Variable used to check if already initialized */

extern void Display_init(void); /* Initialized LCD */
extern void Display_clearBuffer(void); /* Clears the current framebuffer */
extern void Display_finishFrame(void); /* Blits the framebuffer to the screen */

extern unsigned short Display_getColor(uint8_t r, uint8_t g, uint8_t b); /* Gets the 2-byte color from RGB values */
extern void Display_setPixel_RGB(int x, int y, uint8_t r, uint8_t g, uint8_t b); /* Sets the pixel at XY to a color generated from specified RGB values */
extern void Display_setPixel_Color(int x, int y, unsigned short color); /* Sets the pixel at XY to color */

#endif
