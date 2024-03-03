#ifndef _DEVICE_H_
#define _DEVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define DEVICE_WIDTH 240
#define DEVICE_HEIGHT 240

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

#define INPUT_MODE_NONE 0
#define INPUT_MODE_TAP 1
#define INPUT_MODE_HOLD 2

typedef struct {
    uint16_t x;
    uint16_t y;
    int mode;
} input_t;

// typedef void (*flush_display_callback)(const area_t* area, color16_t* color_p);

void Device_Init(void);
void Device_Cleanup(void);
void Device_Delay(int ms);
void Device_Backlight(bool state);
bool Device_GetInput(input_t* data);
// void Device_Flush_Display(int x, int y, int w, int h, uint16_t* pixels);

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

#ifdef __cplusplus
}
#endif

#endif  // _DEVICE_H_
