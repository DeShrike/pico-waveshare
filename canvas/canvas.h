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

#define BLACK       0x0000
#define WHITE       0xFFFF
#define RED         0x00F8
#define GREEN       0xE007
#define BLUE        0x1F00
#define GRAY        0x1084
#define YELLOW      0xE0FF
#define CYAN        0xFF07
#define MAGENTA     0x1FF8

void Canvas_Init();
void Canvas_Flush();
void Canvas_Fill_Rect(int x, int y, int w, int h, uint16_t color);
void Canvas_Fill_Rect_R(rect_t* area, uint16_t color);
void Canvas_Set_Pixel(size_t x, size_t y, uint16_t color);
void Canvas_Write_Ascii(const char* str, int x, int y, uint16_t fgcolor, uint16_t bgcolor);

extern void display_flush(const area_t* area, color16_t* color_p);

#ifdef __cplusplus
}
#endif

#endif  // _CANVAS_H_
