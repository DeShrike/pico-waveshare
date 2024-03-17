#include "pico/stdlib.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "ascii.h"
#include "canvas.h"

static color16_t canvas_data[CANVAS_WIDTH * CANVAS_HEIGHT] = { 0 };
static float sinus[CIRCLE_STEPS] = { 0 };
static float cosinus[CIRCLE_STEPS] = { 0 };

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
    
    if (y < 0 || y >= CANVAS_HEIGHT)
    {
        return;
    }

    for (uint16_t x = x1; x <= x2; ++x)
    {
        if (x < 0 || x >= CANVAS_WIDTH)
        {
            return;
        }

        canvas_data[INDEX(x, y)] = color;
    }
}

void Canvas_Draw_VLine(uint16_t x, uint16_t y1, uint16_t y2, uint16_t color)
{
    if (y2 < y1)
    {
        return;
    }

    if (x < 0 || x >= CANVAS_WIDTH)
    {
        return;
    }
    
    for (uint16_t y = y1; y <= y2; ++y)
    {
        if (y < 0 || y >= CANVAS_HEIGHT)
        {
            return;
        }
        
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

void Canvas_Draw_Rounded_Corner(uint16_t x0, uint16_t y0, uint16_t r, uint8_t corner, uint16_t color)
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        
        x++;
        ddF_x += 2;
        f += ddF_x;
        
        if (corner & 0x4)
        {
            canvas_data[INDEX(x0 + x, y0 + y)] = color;
            canvas_data[INDEX(x0 + y, y0 + x)] = color;
        }
        else if (corner & 0x2)
        {
            canvas_data[INDEX(x0 + x, y0 - y)] = color;
            canvas_data[INDEX(x0 + y, y0 - x)] = color;
        }
        else if (corner & 0x8)
        {
            canvas_data[INDEX(x0 - y, y0 + x)] = color;
            canvas_data[INDEX(x0 - x, y0 + y)] = color;
        }
        else if (corner & 0x1)
        {
            canvas_data[INDEX(x0 - y, y0 - x)] = color;
            canvas_data[INDEX(x0 - x, y0 - y)] = color;
        }
    }
}

void Canvas_Fill_Circle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color)
{
    int16_t f  = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        
        x++;
        ddF_x += 2;
        f += ddF_x;

        if (cornername & 0x1)
        {
            Canvas_Draw_VLine(x0 + x, y0 - y, y0 - y + 2 * y + 1 + delta, color);
            Canvas_Draw_VLine(x0 + y, y0 - x, y0 - x + 2 * x + 1 + delta, color);
        }
        
        if (cornername & 0x2)
        {
            Canvas_Draw_VLine(x0 - x, y0 - y, y0 - y + 2 * y + 1 + delta, color);
            Canvas_Draw_VLine(x0 - y, y0 - x, y0 - x + 2 * x + 1 + delta, color);
        }
    }
}

void Canvas_Draw_Round_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r, uint16_t color)
{
    uint16_t x2 = (w - 2 * r) + (x + r);
    Canvas_Draw_HLine(x + r, x2, y, color); // Top
    Canvas_Draw_HLine(x + r, x2, y + h - 1, color); // Bottom

    uint16_t y2 = (h - 2 * r) + (y + r);
    Canvas_Draw_VLine(x, y + r, y2, color); // Left
    Canvas_Draw_VLine(x + w - 1, y + r, y2, color); // Right

    // draw four corners
    Canvas_Draw_Rounded_Corner(x + r, y + r, r, 1, color);
    Canvas_Draw_Rounded_Corner(x + w - r - 1, y + r, r, 2, color);
    Canvas_Draw_Rounded_Corner(x + w - r - 1, y + h - r - 1, r, 4, color);
    Canvas_Draw_Rounded_Corner(x + r, y + h - r - 1, r, 8, color);
}

void Canvas_Fill_Round_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r, uint16_t color)
{
  // smarter version
  Canvas_Fill_Rect(x + r, y, w - 2 * r, h, color);
  // draw four corners
  Canvas_Fill_Circle_Helper(x + w - r - 1, y + r, r, 1, h - 2 * r - 1, color);
  Canvas_Fill_Circle_Helper(x + r        , y + r, r, 2, h - 2 * r - 1, color);
}

uint16_t Canvas_RGB_To_GBRG(uint16_t r, uint16_t g, uint16_t b)
{
    r = r * 32 / 256;
    g = g * 64 / 256;
    b = b * 32 / 256;
    
    return 0;
}

float Canvas_Sin(float angle)
{
	int index = angle / (TAU / CIRCLE_STEPS);
	return sinus[index];
}

float Canvas_Cos(float angle)
{
	int index = angle / (TAU / CIRCLE_STEPS);
	return cosinus[index];
}

void Canvas_Init()
{
	float a = 0;

	for (int i = 0; i < CIRCLE_STEPS; ++i)
	{
		a += TAU / CIRCLE_STEPS;
		sinus[i] = sin(a);
		cosinus[i] = cos(a);
	}
}

/********************************/
#define NOT_DRAWN 0
#define STARTS_HERE 1
#define ALL_DRAWN 2
#define ENDS_HERE 3
#define STARTS_ENDS_HERE 4

//Radian to degree conversion value.
#define R_TO_D 57.29578

int arc_sector[8];

void PositiveSectorPoint (int16_t x, int16_t y, int16_t s, int16_t sp, int16_t ep, uint16_t color)
{
    if (arc_sector[s] == NOT_DRAWN) return;

    if (arc_sector[s] == ALL_DRAWN)
    {
        //draw all points of this sector
        canvas_data[INDEX(x, y)] = color;
        return;
    }

    if (arc_sector[s] == STARTS_HERE)
    {
        //draw all points flowing to right
        if (x >=sp)
        {
            canvas_data[INDEX(x, y)] = color;
            return;
        }
    }

    if (arc_sector[s] == ENDS_HERE)
    {
        //draw all points flowing from left
        if (x <= ep)
        {
            canvas_data[INDEX(x, y)] = color;
            return;
        }
    }

    if (arc_sector[s] == STARTS_ENDS_HERE) 
    {
        //fill only sections of this sector. 
        if ((x >= sp) && (x <= ep))
        {
            canvas_data[INDEX(x, y)] = color;
        }
    }
}

void NegativeSectorPoint(int16_t x, int16_t y, int16_t s, int16_t sp, int16_t ep, uint16_t color)
{
    if (arc_sector[s] == NOT_DRAWN) return;
    if (arc_sector[s] == ALL_DRAWN)
    {
        //Draw all points in this sector
        canvas_data[INDEX(x, y)] = color;
        return;
    }

    if (arc_sector[s] == STARTS_HERE)
    {
        //Draw all points flowing to the left
        if (x <= sp)
        {
            canvas_data[INDEX(x, y)] = color;
            return;
        }
    }

    if (arc_sector[s] == ENDS_HERE)
    {
        //Draw all points flowing from the right
        if (x >= ep)
        {
            canvas_data[INDEX(x, y)] = color;
            return;
        }
    }

    if (arc_sector[s] == STARTS_ENDS_HERE)
    {
        //fill only sections of this sector.
        if ((x >= ep) && (x <= sp))
        {
            canvas_data[INDEX(x, y)] = color;
        }
    }
}

// sa : start angle in degrees
// ea : end angle in degrees
void Canvas_Draw_Arc(int16_t xc, int16_t yc, int16_t sa, int16_t ea, int16_t r, uint16_t color)
{
    int16_t start_sector,end_sector;
    int16_t i;
    int16_t x, y;
    int16_t ep, sp, d;
    
    //Clear all the arc sector flags,
    for (i = 0; i< 8; i++)
    {
        arc_sector[i] = NOT_DRAWN;
    }
    
    //Calculate the start and end Arc sectors
    start_sector = sa / 45;
    end_sector = ea / 45;
    if (start_sector == end_sector)
    {
        arc_sector[start_sector] = STARTS_ENDS_HERE;
    }
    else
    {
        for (i = start_sector; i < end_sector; i++)
        {
            arc_sector[i] = ALL_DRAWN; 
        }

        arc_sector[start_sector] = STARTS_HERE; 
        arc_sector[end_sector] = ENDS_HERE;
    }

    /*''Calculate the Start and End Points*/
    /*''Calculate points in first sector and translate*/ 
    x = 0; y = r;
    sp = ((double)xc + (double)r * cos((double)sa/R_TO_D));
    ep = ((double)xc + (double)r * cos((double)ea/R_TO_D));
    d = 2 * (1 - r);
    while (y > x)
    {
        NegativeSectorPoint(xc + y, yc + x, 0, sp, ep, color);
        NegativeSectorPoint(xc + x, yc + y, 1, sp, ep, color);
        NegativeSectorPoint(xc - x, yc + y, 2, sp, ep, color);
        NegativeSectorPoint(xc - y, yc + x, 3, sp, ep, color);
        PositiveSectorPoint(xc - y, yc - x, 4, sp, ep, color);
        PositiveSectorPoint(xc - x, yc - y, 5, sp, ep, color);
        PositiveSectorPoint(xc + x, yc - y, 6, sp, ep, color);
        PositiveSectorPoint(xc + y, yc - x, 7, sp, ep, color);
        if (d + y > 0)
        {
            y = y - 1;
            d = d - 2 * y + 1;
        }
        else
        {
            if (x > d)
            {
                x = x + 1;
                d = d + 2 * x + 1;
            }
        }
    }
}
