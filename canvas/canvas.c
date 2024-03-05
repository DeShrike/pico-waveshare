#include "pico/stdlib.h"

#include "ascii.h"
#include "canvas.h"

static color16_t canvas_data[CANVAS_WIDTH * CANVAS_HEIGHT] = {0};
// static flush_display_callback flush_display_cb;

void Canvas_Flush()
{
    area_t area = {
        .x1 = 0,
        .y1 = 0,
        .x2 = CANVAS_WIDTH - 1,
        .y2 = CANVAS_HEIGHT - 1
    };

    display_flush(&area, canvas_data);
}

void Canvas_Set_Pixel(size_t x, size_t y, uint16_t color)
{
    if (y >= 0 && y < CANVAS_HEIGHT)
    {
        if (x >= 0 && x < CANVAS_WIDTH)
        {
            int ix = y * CANVAS_WIDTH + x;
            canvas_data[ix] = color;
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
                    int ix = y * CANVAS_WIDTH + x;
                    // canvas_data[ix].full = color;
                    canvas_data[ix] = color;
                }
            }
        }
    } 
}

void Canvas_Fill_Rect(int x, int y, int w, int h, uint16_t color)
{
    rect_t r = {
        .x = x,
        .y = y,
        .w = w,
        .h = h
    };
    Canvas_Fill_Rect_R(&r, color);
}

#define ASCII_ZOOM 3
void Canvas_Write_Ascii_Char(const char str, int x, int y, uint16_t fgcolor, uint16_t bgcolor)
{
    const int index = (int)str - 32;
    for (size_t col = 0; col < ASCII_WIDTH; ++col)
    {
        for (size_t bit = 0; bit < 8; ++bit)
        {
            int xx = x + (col * ASCII_ZOOM);
            int yy = y + (bit * ASCII_ZOOM);
            if ((ascii[index][col] & (1 << bit)) != 0)
            {
                Canvas_Fill_Rect(xx, yy, ASCII_ZOOM, ASCII_ZOOM, fgcolor);
            }
            else
            {
                Canvas_Fill_Rect(xx, yy, ASCII_ZOOM, ASCII_ZOOM, bgcolor);
            }
        }
    }
}

void Canvas_Write_Ascii(const char* str, int x, int y, uint16_t fgcolor, uint16_t bgcolor)
{
    while (*str)
    {
        Canvas_Write_Ascii_Char(*str++, x, y, fgcolor, bgcolor);
        x += (ASCII_WIDTH + 1) * ASCII_ZOOM;
    }
}

void Canvas_Init()
{
}
