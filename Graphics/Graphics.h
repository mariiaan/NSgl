/*
	NSgl
    Graphics.h / Graphics.c
    Basic graphic libary for drawing and filling rectangles, drawing lines
    and drawing text. Uses Display.h libary.

    (C) Copyright 2020, Marian W.
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdbool.h>
#include "Display.h"
#include "Fonts/Fonts.h"

extern bool m_graphics_background_transparent;
extern unsigned short m_graphics_background_color;
extern Fonts_Font m_graphics_font;
extern int m_graphics_font_width;
extern int m_graphics_font_height;
extern char** m_graphics_font_data;
extern int m_graphics_text_spacing;

/* Basic shapes */
extern void Graphics_fillRect_RGB(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b); /* Fills a rectangle at XY with dimensions WH with a color generated from specified RGB values */
extern void Graphics_fillRect_Color(int x, int y, int w, int h, unsigned short color); /* Fills a rectangle at XY with dimensions WH and color */
extern void Graphics_drawRect_RGB(int x, int y, int w, int h, int t, uint8_t r, uint8_t g, uint8_t b); /* Draws a rectangle at XY with dimensions WH with thickness t and a color generated from specified RGB values */
extern void Graphics_drawRect_Color(int x, int y, int w, int h, int t, unsigned short color); /* Draws a rectangle at XY with dimensions WH with thickness t and color */
extern void Graphics_drawLine_RGB(int x1, int y1, int x2, int y2, uint8_t r, uint8_t g, uint8_t b); /* Draws a line from (x1, y1) to (x2, y2) with a color generated from specified RGB values */
extern void Graphics_drawLine_Color(int x1, int y1, int x2, int y2, unsigned short color); /* Draws a line from (x1, y1) to (x2, y2) with a color generated from specified RGB values */

/* Text rendering */
extern void Graphics_drawCharacter_RGB(int x, int y, char c, uint8_t r, uint8_t g, uint8_t b); /* Draws a character at XY with size and a color generated from specified RGB values */
extern void Graphics_drawCharacter_Color(int x, int y, char c, unsigned short color); /* Draws a character at XY with size and color */
extern void Graphics_drawString_RGB(int x, int y, const char* s, uint8_t r, uint8_t g, uint8_t b); /* Draws a string at XY with size and a color generated from specified RGB values */
extern void Graphics_drawString_Color(int x, int y, const char* s, unsigned short color); /* Draws a string at XY with size and color */
extern void Graphics_textBackground_RGB(bool transparent, uint8_t r, uint8_t g, uint8_t b); /* Sets text render background color and transparency */
extern void Graphics_textBackground_Color(bool transparent, unsigned short color); /* Sets text render background color and transparency */
extern void Graphics_textFont(Fonts_Font font); /* Sets the text render font */
extern void Graphics_textSpacing(int s); /* Sets the spacing between characters for DrawString */

#endif
