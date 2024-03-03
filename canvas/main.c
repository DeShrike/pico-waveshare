#include "pico/stdlib.h"
#include "device.h"

uint16_t colors[] = { WHITE, RED, GREEN, BLUE, GRAY, YELLOW, CYAN, MAGENTA };
int color_count = sizeof(colors) / sizeof(colors[0]);
int w = 10;
int h = 10;

#define VEHICLE_COUNT 25

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
    int c;
    int ox;
    int oy;
} vehicle;

vehicle vehicles[VEHICLE_COUNT];

void init(void)
{
    for (int i = 0; i < VEHICLE_COUNT; ++i)
    {
        vehicles[i] = (vehicle) { 
            .x = i * 5,
            .y = i* 5,
            .dx = i % 4 + 1,
            .dy = i % 5 + 2,
            .c = 0
        };
    }
}

void update(void)
{
    for (int i = 0; i < VEHICLE_COUNT; ++i)
    {
        vehicles[i].ox = vehicles[i].x;
        vehicles[i].oy = vehicles[i].y;
        
        vehicles[i].x += vehicles[i].dx;
        vehicles[i].y += vehicles[i].dy;

        if (vehicles[i].x < 0)
        {
            vehicles[i].x = 0;
            vehicles[i].dx = -vehicles[i].dx;
            vehicles[i].c = (vehicles[i].c + 1) % color_count;
        }

        if (vehicles[i].y < 0)
        {
            vehicles[i].y = 0;
            vehicles[i].dy = -vehicles[i].dy;
            vehicles[i].c = (vehicles[i].c + 1) % color_count;
        }

        if (vehicles[i].x > CANVAS_WIDTH - w)
        {
            vehicles[i].x = CANVAS_WIDTH - w - 1;
            vehicles[i].dx = -vehicles[i].dx;
            vehicles[i].c = (vehicles[i].c + 1) % color_count;
        }

        if (vehicles[i].y > CANVAS_HEIGHT - h)
        {
            vehicles[i].y = CANVAS_HEIGHT - h - 1;
            vehicles[i].dy = -vehicles[i].dy;
            vehicles[i].c = (vehicles[i].c + 1) % color_count;
        }
    }

    /*
    if (ts_touched)
    {
        otx = tx;
        oty = ty;
        tx = ts_x;
        ty = ts_y;
        ts_touched = 0;
        tcix = (tcix + 1) % color_count;
    }*/
}

void draw(void)
{
    for (int i = 0; i < VEHICLE_COUNT; ++i)
    {
        Canvas_Fill_Rect(vehicles[i].ox, vehicles[i].oy, w, h, BLACK);

        Canvas_Fill_Rect(vehicles[i].x, vehicles[i].y, w, h, colors[vehicles[i].c]);
    }
}

int main(void)
{
    Device_Init();

    init();

    while (true)
    {
        update();
        draw();

        Canvas_Flush();
        Device_Delay(50);
    }

    Device_Cleanup();
    return 0;
}
