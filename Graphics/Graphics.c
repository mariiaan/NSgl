/*
	NSgl
    Graphics.h / Graphics.c
    Basic graphic libary for drawing and filling rectangles, drawing lines
    and drawing text. Uses Display.h libary.

    (C) Copyright 2020, Marian W.
*/

#include "Graphics.h"

bool m_graphics_background_transparent = false;
unsigned short m_graphics_background_color = 0x0000;
Fonts_Font m_graphics_font = 0;
int m_graphics_font_width;
int m_graphics_font_height;
char** m_graphics_font_data;
int m_graphics_text_spacing = 1;

void Graphics_fillRect_RGB(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b)
{
    unsigned short color = Display_getColor(r, g, b);

    Graphics_fillRect_Color(x, y, w, h, color);
}

void Graphics_fillRect_Color(int x, int y, int w, int h, unsigned short color)
{
    for(int ix = x; ix < x + w; ++ix) /* Iterate through each pixel and set corresponding color */
    {
        for(int iy = y; iy < y + h; ++iy)
        {
            Display_setPixel_Color(ix, iy, color);
        }
    }
}

void Graphics_drawRect_RGB(int x, int y, int w, int h, int t, uint8_t r, uint8_t g, uint8_t b)
{
    unsigned short color = Display_getColor(r, g, b);

    Graphics_drawRect_Color(x, y, w, h, t, color);
}

void Graphics_drawRect_Color(int x, int y, int w, int h, int t, unsigned short color)
{
    for(int ix = x; ix < x + w; ++ix)                   /* Draw horizontal lines */
    {  
        for(int iy = y; iy < y + t; ++iy)               /* Draw top line */
            Display_setPixel_Color(ix, iy, color);     
        
        for(int iy = y + h - 1; iy >= y + h - t; --iy)  /* Draw bottom line */
            Display_setPixel_Color(ix, iy, color);
    }
    
    for(int iy = y; iy < y + h; ++iy)                   /* Draw vertical lines */
    {
        for(int ix = x; ix < x + t; ++ix)               /* Draw left line */
            Display_setPixel_Color(ix, iy, color); 
        
        for(int ix = x + w - 1; ix >= x + w - t; --ix)  /* Draw right line */
            Display_setPixel_Color(ix, iy, color); 
    }
}

void Graphics_drawLine_RGB(int x1, int y1, int x2, int y2, uint8_t r, uint8_t g, uint8_t b)
{
    unsigned short color = Display_getColor(r, g, b);

    Graphics_drawLine_Color(x1, y1, x2, y2, color);
}

void Graphics_drawLine_Color(int x1, int y1, int x2, int y2, unsigned short color)
{
    /* 
        Using Bresenham algorithm 
        TODO: Add right to left and bottom to top support
    */

    int dx, dy, p, x, y;
    dx = x2 - x1;
    dy = y2- y1;

    x = x1;
    y = y1;
    p = 2 * dy - dx;

    while(x <= x2)
    {
        Display_setPixel_Color(x, y, color);

        if(p >= 0)
        { 
            y = y + 1;
            p = p + 2 * dy - 2 * dx;
        }
        else
        {
            p = p + 2 * dy;
        }

        x = x + 1;
    }
}

void Graphics_drawCharacter_RGB(int x, int y, char c, uint8_t r, uint8_t g, uint8_t b)
{
    unsigned short color = Display_getColor(r, g, b);

    Graphics_drawCharacter_Color(x, y, c, color);
}

void Graphics_drawCharacter_Color(int x, int y, const char c, unsigned short color)
{
    char* charToDraw = m_graphics_font_data[(int)c];

    if(m_graphics_background_transparent)
    {  
        for(int ix = 0; ix < m_graphics_font_width; ++ix)
        {
            for(int iy = 0; iy < m_graphics_font_height; ++iy)
            {
                if(charToDraw[iy * m_graphics_font_width + ix] == 'x')
                {
                    Display_setPixel_Color(x + ix, y + iy, color);
                }
            }
        }
    }
    else
    {
        for(int ix = 0; ix < m_graphics_font_width; ++ix)
        {
            for(int iy = 0; iy < m_graphics_font_height; ++iy)
            {
                if(charToDraw[iy * m_graphics_font_width + ix] == 'x')
                {
                    Display_setPixel_Color(x + ix, y + iy, color);
                }
                else
                {
                    Display_setPixel_Color(x + ix, y + iy, m_graphics_background_color);
                }              
            }
        }
    }
    
}

void Graphics_drawString_RGB(int x, int y, const char* s, uint8_t r, uint8_t g, uint8_t b)
{
    unsigned short color = Display_getColor(r, g, b);

    Graphics_drawString_Color(x, y, s, color);
}

void Graphics_drawString_Color(int x, int y, const char* s, unsigned short color)
{
    int index = 0;
    int offsetX = 0;
    int offsetY = 0;
    bool continueLoop = true;

    while(continueLoop)
    {
        char c = s[index];

        switch(c)
        {
            case '\0':
            {
                continueLoop = false;
                break;
            }
            case '\n':
            {
                offsetX = 0;
                offsetY += m_graphics_font_height + 1;
                break;
            }
            default:
            {
                Graphics_drawCharacter_Color(x + offsetX, y + offsetY, s[index], color);

                offsetX += m_graphics_font_width + m_graphics_text_spacing;
                break;
            }
        }

        index++;
    }
}

void Graphics_textBackground_RGB(bool transparent, uint8_t r, uint8_t g, uint8_t b)
{
    unsigned short color = Display_getColor(r, g, b);

    Graphics_textBackground_Color(transparent, color);
}

void Graphics_textBackground_Color(bool transparent, unsigned short color)
{
    m_graphics_background_transparent = transparent;
    m_graphics_background_color = color;
}

void Graphics_textFont(Fonts_Font font)
{
    m_graphics_font = font;

    switch(m_graphics_font)
    {
        case Font_F5x7:
            m_graphics_font_data = F5x7_m_font;
            m_graphics_font_width = F5x7_m_width;
            m_graphics_font_height = F5x7_m_height;
            break;
        default: break;
    }
}

void Graphics_textSpacing(int s)
{
    m_graphics_text_spacing = s;
}
