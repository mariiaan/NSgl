/*
	NSgl
    Display.h / Display.c
    Basic library to display a framebuffer on Ndless modified TI-Nspire handhelds,
    convert RGB color values to 2-byte-color and set pixels.

    (C) Copyright 2020, Marian W.
*/

#include "Display.h"

char m_display_framebuffer[DISPLAY_BYTES_TOTAL];
bool m_display_initialized = false;

void Display_init(void)
{
    if(m_display_initialized) // Return if already initialized
    {
        return;
    }

    lcd_init(DISPLAY_MODE); /* Initialize the nspire LCD */
    m_display_initialized = true;

    Display_clearBuffer(); /* Clear framebuffer */
    Display_finishFrame(); /* Blit framebuffer to the screen */
}

void Display_clearBuffer(void)
{
    for(int i = 0; i < DISPLAY_BYTES_TOTAL; i++) /* Set every byte to 0 */
    {
        m_display_framebuffer[i] = 0;
    }
}

void Display_finishFrame(void)
{
    lcd_blit(m_display_framebuffer, DISPLAY_MODE);
}

unsigned short Display_getColor(uint8_t r, uint8_t g, uint8_t b)
{
    return (r / 8 << 12) | (g / 4 << 6) | b / 8; /* Convert RGB to 2 bytes color */
}

void Display_setPixel_RGB(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    if(x < 0 || y < 0 || x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT) /* Bounds check */
    {
        return;
    }
    int pixelAddr = 2 * (y * DISPLAY_WIDTH + x);
    unsigned short color = (r / 8 << 12) | (g / 4 << 6) | b / 8;

    m_display_framebuffer[pixelAddr] = color;
    m_display_framebuffer[pixelAddr + 1] = color >> 8;
}

void Display_setPixel_Color(int x, int y, unsigned short color)
{
    if(x < 0 || y < 0 || x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT) /* Bounds check */
    {
        return;
    }
    int pixelAddr = 2 * (y * DISPLAY_WIDTH + x);

    m_display_framebuffer[pixelAddr] = color;
    m_display_framebuffer[pixelAddr + 1] = color >> 8;
}
