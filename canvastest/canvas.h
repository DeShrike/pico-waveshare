#ifndef _CANVAS_H_
#define _CANVAS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
typedef union {
    struct {
        uint16_t green_l : 3;
        uint16_t blue : 5;
        uint16_t red : 5;
        uint16_t green_h : 3;
    } ch;
    uint16_t full;
} color16_t;
*/

typedef uint16_t color16_t;
typedef int16_t coord_t;

typedef struct {
    coord_t x;
    coord_t y;
} point_t;

/** Represents an area of the screen.*/
typedef struct {
    coord_t x1;
    coord_t y1;
    coord_t x2;
    coord_t y2;
} area_t;

typedef struct {
    coord_t x;
    coord_t y;
    uint16_t w;
    uint16_t h;
} rect_t;

#include "device.h"

#define CANVAS_WIDTH	DEVICE_WIDTH
#define CANVAS_HEIGHT	DEVICE_HEIGHT

#define CIRCLE_STEPS	180
#define PI				3.141592654
#define TAU				(PI * 2.0)

#define RGB2GBRG(r, g, b) ((((r) * 32 / 256) & 0x001F) << 3) |  \
                          ((((b) * 32 / 256) & 0x001F) << 8) |  \
                          ((((g) * 64 / 256) & 0x0007) << 13) | \
                          ((((g) * 64 / 256) & 0x0038) >> 3)

// r: 0 - 31, b: 0 - 31, g: 0 - 63
#define GBRG(r, g, b) (((r) & 0x001F) << 3) |  \
                      (((b) & 0x001F) << 8) |  \
                      (((g) & 0x0007) << 13) | \
                      (((g) & 0x0038) >> 3)

#define BLACK       0x0000
#define WHITE       0xFFFF
//#define RED         0x00F8
//#define GREEN       0xE007
#define BLUE        0x1F00
//#define YELLOW      0xE0FF
//#define CYAN        0xFF07
//#define MAGENTA     0x1FF8

#define GRAY    0x1084
#define GRAY1   0x0842
#define GRAY2   0x1084
#define GRAY3   0x18C6

#define LIME    0x20A6
#define GREEN   0x4265
#define EMERALD 0x4004
#define TEAL    0x5505
#define CYAN    0x1C1D
#define COBALT  0x9D02
#define INDIGO  0x1F68
#define VIOLET  0x1FA8
#define PINK    0x9AF3
#define MAGENTA 0x0ED8
#define CRIMSON 0x04A0
#define RED     0xA0E0
#define ORANGE  0x40FB
#define YELLOW  0x40E6
#define BROWN   0xC582
#define OLIVE   0x2C6C
#define STEEL   0xB063
#define MAUVE   0x1173
#define TAUPE   0xC983

#define INDEX(x, y) ((y) * CANVAS_WIDTH + (x))

void Canvas_Init();
void Canvas_Clear();
void Canvas_Flush();

float Canvas_Sin(float angle);
float Canvas_Cos(float angle);

void Canvas_Set_Pixel(uint16_t x, uint16_t y, uint16_t color);

void Canvas_Fill_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void Canvas_Fill_Rect_R(rect_t* area, uint16_t color);
void Canvas_Draw_Rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void Canvas_Draw_Round_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r, uint16_t color);
void Canvas_Fill_Round_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r, uint16_t color);

void Canvas_Write_Ascii(const char* str, uint16_t x, uint16_t y, uint16_t fgcolor, uint16_t bgcolor);
void Canvas_Write_Ascii_Centered(const char* str, uint16_t x, uint16_t y, uint16_t fgcolor, uint16_t bgcolor);
uint16_t Canvas_Ascii_Width(const char* str);
uint16_t Canvas_Ascii_Height(const char* str);

void Canvas_Draw_HLine(uint16_t x1, uint16_t y2, uint16_t y, uint16_t color);
void Canvas_Draw_VLine(uint16_t x, uint16_t y1, uint16_t y2, uint16_t color);
void Canvas_Draw_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

void Canvas_Draw_Circle(uint16_t xc, uint16_t yc, uint16_t r, uint16_t color);
void Canvas_Fill_Circle(uint16_t xc, uint16_t yc, uint16_t r, uint16_t color);

void Canvas_Draw_Arc(int16_t xc, int16_t yc, int16_t sa, int16_t ea, int16_t r, uint16_t color);

//uint16_t Canvas_RGB_To_GBRG(uint16_t r, uint16_t g, uint16_t b);

extern void display_flush(const area_t* area, color16_t* color_p);

#ifdef __cplusplus
}
#endif

#endif  // _CANVAS_H_
