#ifndef _DEVICE_H_
#define _DEVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "canvas.h"

#define DEVICE_WIDTH 240
#define DEVICE_HEIGHT 240

typedef struct {
    uint16_t x;
    uint16_t y;
    uint8_t gesture;
    bool touched;
} input_t;

// typedef void (*flush_display_callback)(const area_t* area, color16_t* color_p);

void device_init(void);
void device_cleanup(void);
void device_delay(int ms);
void device_backlight(bool state);
bool device_getinput(input_t* data);
// void Device_Flush_Display(int x, int y, int w, int h, uint16_t* pixels);

#define CANVAS_WIDTH	DEVICE_WIDTH
#define CANVAS_HEIGHT	DEVICE_HEIGHT

#define GESTURE_NONE          0
#define GESTURE_UP            1
#define GESTURE_DOWN          2
#define GESTURE_LEFT          3
#define GESTURE_RIGHT         4
#define GESTURE_CLICK         5
#define GESTURE_DOUBLE_CLICK  11
#define GESTURE_LONG_PRESS    12

#ifdef __cplusplus
}
#endif

#endif  // _DEVICE_H_
