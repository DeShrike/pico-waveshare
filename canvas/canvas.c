#include "pico/stdlib.h"
#include <string.h>
#include <stdlib.h>

#include "ascii.h"
#include "canvas.h"

static color16_t canvas_data[CANVAS_WIDTH * CANVAS_HEIGHT] = { 0 };

static area_t fullarea = {
    .x1 = 0,
    .y1 = 0,
    .x2 = CANVAS_WIDTH - 1,
    .y2 = CANVAS_HEIGHT - 1
};

void Canvas_Clear()
{
    memset(canvas_data, 0, sizeof(canvas_data));
}

void Canvas_Flush()
{
    display_flush(&fullarea, canvas_data);
}

void Canvas_Set_Pixel(uint16_t x, uint16_t y, uint16_t color)
{
    if (y >= 0 && y < CANVAS_HEIGHT)
    {
        if (x >= 0 && x < CANVAS_WIDTH)
        {
            canvas_data[INDEX(x, y)] = color;
        }
    }
}

void Canvas_Fill_Rect_R(rect_t* rect, uint16_t color)
{
    for (uint16_t y = rect->y; y < rect->y + rect->h; ++y)
    {
        if (y >= 0 && y < CANVAS_HEIGHT)
        {
            for (uint16_t x = rect->x; x < rect->x + rect->w; ++x)
            {
                if (x >= 0 && x < CANVAS_WIDTH)
                {
                    canvas_data[INDEX(x, y)] = color;
                }
            }
        }
    } 
}

void Canvas_Fill_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
{
    rect_t r = {
        .x = x,
        .y = y,
        .w = w,
        .h = h
    };
    Canvas_Fill_Rect_R(&r, color);
}

void Canvas_Write_Ascii_Char(const char str, uint16_t x, uint16_t y, uint16_t fgcolor, uint16_t bgcolor)
{
    const uint16_t index = (uint16_t)str - 32;
    for (uint16_t col = 0; col < ASCII_WIDTH; ++col)
    {
        for (uint16_t bit = 0; bit < 8; ++bit)
        {
            uint16_t xx = x + (col * ASCII_ZOOM);
            uint16_t yy = y + (bit * ASCII_ZOOM);
            if ((ascii[index][col] & (1 << bit)) != 0)
            {
                Canvas_Fill_Rect(xx, yy, ASCII_ZOOM, ASCII_ZOOM, fgcolor);
            }
            else if (bgcolor != BLACK)
            {
                Canvas_Fill_Rect(xx, yy, ASCII_ZOOM, ASCII_ZOOM, bgcolor);
            }
        }
    }
}

void Canvas_Write_Ascii(const char* str, uint16_t x, uint16_t y, uint16_t fgcolor, uint16_t bgcolor)
{
    while (*str)
    {
        Canvas_Write_Ascii_Char(*str++, x, y, fgcolor, bgcolor);
        x += ASCII_WIDTH * ASCII_ZOOM;
    }
}

void Canvas_Write_Ascii_Centered(const char* str, uint16_t x, uint16_t y, uint16_t fgcolor, uint16_t bgcolor)
{
    uint16_t width = strlen(str);
    uint16_t nx = x - ((width * ASCII_WIDTH * ASCII_ZOOM) / 2);
    uint16_t ny = y - (ASCII_HEIGHT * ASCII_ZOOM / 2);
    Canvas_Write_Ascii(str, nx, ny, fgcolor, bgcolor);
}

uint16_t Canvas_Ascii_Width(const char* str)
{
    return strlen(str) * ASCII_WIDTH * ASCII_ZOOM;
}

uint16_t Canvas_Ascii_Height(const char* str)
{
    return ASCII_HEIGHT * ASCII_ZOOM;
}

void Canvas_Draw_HLine(uint16_t x1, uint16_t x2, uint16_t y, uint16_t color)
{
    if (x2 < x1)
    {
        return;
    }
    
    for (uint16_t x = x1; x <= x2; ++x)
    {
        canvas_data[INDEX(x, y)] = color;
    }
}

void Canvas_Draw_VLine(uint16_t x, uint16_t y1, uint16_t y2, uint16_t color)
{
    if (y2 < y1)
    {
        return;
    }

    for (uint16_t y = y1; y <= y2; ++y)
    {
        canvas_data[INDEX(x, y)] = color;
    }
}

void Canvas_Draw_Rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    Canvas_Draw_HLine(x1, x2, y1, color);
    Canvas_Draw_HLine(x1, x2, y2, color);
    Canvas_Draw_VLine(x1, y1, y2, color);
    Canvas_Draw_VLine(x2, y1, y2, color);
}

static void draw_line_low(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    int16_t dx = x1 - x0;
    int16_t dy = y1 - y0;
    int16_t yi = 1;
    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }
    
    int16_t D = (2 * dy) - dx;
    uint16_t y = y0;

    for (uint16_t x = x0; x <= x1; ++x)
    {
        canvas_data[INDEX(x, y)] = color;

        if (D > 0)
        {
            y = y + yi;
            D = D + (2 * (dy - dx));
        }
        else
        {
            D = D + 2 * dy;
        }
    }
}

static void draw_line_high(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    int16_t dx = x1 - x0;
    int16_t dy = y1 - y0;
    int16_t xi = 1;
    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }
    
    int16_t D = (2 * dx) - dy;
    uint16_t x = x0;

    for (uint16_t y = y0; y <= y1; ++y)
    {
        canvas_data[INDEX(x, y)] = color;

        if (D > 0)
        {
            x = x + xi;
            D = D + (2 * (dx - dy));
        }
        else
        {
            D = D + 2 * dx;
        }
    }
}

void Canvas_Draw_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    if (abs(y1 - y0) < abs(x1 - x0))
    {
        if (x0 > x1)
        {
            draw_line_low(x1, y1, x0, y0, color);
        }
        else
        {
            draw_line_low(x0, y0, x1, y1, color);
        }
    }
    else
    {
        if (y0 > y1)
        {
            draw_line_high(x1, y1, x0, y0, color);
        }
        else
        {
            draw_line_high(x0, y0, x1, y1, color);
        }
    }
}

static void draw_circle_part(int16_t xc, int16_t yc, int16_t x, int16_t y, uint16_t color)
{
    canvas_data[INDEX(xc + x, yc + y)] = color;
    canvas_data[INDEX(xc - x, yc + y)] = color;

    canvas_data[INDEX(xc + x, yc - y)] = color;
    canvas_data[INDEX(xc - x, yc - y)] = color;

    canvas_data[INDEX(xc + y, yc + x)] = color;
    canvas_data[INDEX(xc - y, yc + x)] = color;
        
    canvas_data[INDEX(xc + y, yc - x)] = color;
    canvas_data[INDEX(xc - y, yc - x)] = color;
} 

static void fill_circle_part(int16_t xc, int16_t yc, int16_t x, int16_t y, uint16_t color)
{
    Canvas_Draw_HLine(xc - x, xc + x, yc + y, color);
    Canvas_Draw_HLine(xc - x, xc + x, yc - y, color);
    Canvas_Draw_HLine(xc - y, xc + y, yc + x, color);
    Canvas_Draw_HLine(xc - y, xc + y, yc - x, color);
} 

void Canvas_Draw_Circle(uint16_t xc, uint16_t yc, uint16_t r, uint16_t color)
{
    int16_t x = 0, y = r;
    int16_t d = 3 - 2 * r;
    draw_circle_part(xc, yc, x, y, color);
    while (y >= x)
    { 
        x++;
        if (d > 0)
        { 
            y--;
            d = d + 4 * (x - y) + 10;
        } 
        else
        {
            d = d + 4 * x + 6;
        }

        draw_circle_part(xc, yc, x, y, color);
    }
}

void Canvas_Fill_Circle(uint16_t xc, uint16_t yc, uint16_t r, uint16_t color)
{
    int16_t x = 0, y = r;
    int16_t d = 3 - 2 * r;
    fill_circle_part(xc, yc, x, y, color);
    while (y >= x)
    { 
        x++;
        if (d > 0)
        { 
            y--;
            d = d + 4 * (x - y) + 10;
        } 
        else
        {
            d = d + 4 * x + 6;
        }

        fill_circle_part(xc, yc, x, y, color);
    }
}

uint16_t Canvas_RGB_To_GBRG(uint16_t r, uint16_t g, uint16_t b)
{
    r = r * 32 / 256;
    g = g * 64 / 256;
    b = b * 32 / 256;
    
    return 0;
}

void Canvas_Init()
{
}
