#include <stdio.h>
#include "pico/stdlib.h"
#include "device.h"

uint16_t colors[] = { WHITE, RED, GREEN, BLUE, GRAY, YELLOW, CYAN, MAGENTA };
int color_count = sizeof(colors) / sizeof(colors[0]);

int w = 10;
int h = 10;

#define VEHICLE_COUNT 50

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
            .x = (i * 5) % CANVAS_WIDTH,
            .y = (i * 5) % CANVAS_HEIGHT,
            .dx = i % 4 + 1,
            .dy = i % 5 + 2,
            .c = 0,
            .ox = 0,
            .oy = 0
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

bool bl = true;

bool timer_callback(struct repeating_timer *t)
{
    printf("Timer %d  - Delay %ldus\n", t->alarm_id, t->delay_us);
    
    bl = !bl;
    Device_Backlight(bl);

    return true;
}

int64_t alarm_callback(alarm_id_t id, void *user_data)
{
    printf("Alarm %d\n", id);
    return 2000 * 1000;     // 2000 milliseconds = 2 seconds = 2000000 microseconds
}

int main(void)
{
    Device_Init();

    init();

    struct repeating_timer timer;
    add_repeating_timer_ms(3000, timer_callback, NULL, &timer);
    add_alarm_in_ms(2000, alarm_callback, NULL, false);

    //absolute_time_t at = get_absolute_time();
    //uint32_t boot_ms = to_ms_since_boot(at);

    while (true)
    {
        update();
        draw();

        Canvas_Flush();
        Device_Delay(50);
        // tight_loop_contents();

        //at = get_absolute_time();
        //uint32_t time_since_boot = to_ms_since_boot(at);
        //printf("Diff: %d \n", boot_ms - time_since_boot);

    }

    Device_Cleanup();
    return 0;
}
