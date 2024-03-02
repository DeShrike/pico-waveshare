#include <stdint.h>
#include "canvas.h"

static color16_t canvas_data[CANVAS_WIDTH * CANVAS_HEIGHT] = {0};
static flush_display_callback flush_display_cb;

void Canvas_Flush()
{
    area_t area = {
        .x1 = 0,
        .y1 = 0,
        .x2 = CANVAS_WIDTH - 1,
        .y2 = CANVAS_HEIGHT - 1
    };

    /*
    uint16_t colors[] = { WHITE, RED, GREEN, BLUE, GRAY, YELLOW, CYAN, MAGENTA };
    int color_count = sizeof(colors) / sizeof(colors[0]);
    
    for (int x = 0; x <= CANVAS_WIDTH; x += 20)
    {
        for (int y = 0; y <= CANVAS_HEIGHT; y += 20)
        {
            rect_t r = {
                .x = x - 1,
                .y = y - 1,
                .w = 3,
                .h = 3
            };
            Canvas_Fill_Rect_R(&r, colors[ (x * y) % color_count]);
        }
    }
    */
    
    flush_display_cb(&area, canvas_data);
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

void Canvas_Init(flush_display_callback flush_display)
{
    flush_display_cb = flush_display;
}
