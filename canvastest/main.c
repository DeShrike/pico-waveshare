#include <stdio.h>
#include "pico/stdlib.h"
#include "device.h"
#include "canvas.h"

uint16_t colors[] = { 
        BLACK, WHITE, BLUE, LIME, GREEN, EMERALD, TEAL, CYAN,
        COBALT, INDIGO, VIOLET, PINK, MAGENTA, CRIMSON, RED,
        ORANGE, YELLOW, BROWN, OLIVE, STEEL, MAUVE, TAUPE, GRAY1, GRAY2, GRAY3 };
int color_count = sizeof(colors) / sizeof(colors[0]);

input_t touch;
int w = 10;
int h = 10;
uint16_t counter = 0;
uint16_t tx = CANVAS_WIDTH / 2;
uint16_t ty = CANVAS_HEIGHT / 2;
bool stopped = false;

uint16_t counter91 = 0;
uint16_t counter92 = 0;
uint16_t counter93 = 0;

uint16_t angle1 = 0;
uint16_t angle2 = 0;
uint16_t angle3 = 0;
uint16_t angle4 = 0;
uint16_t angle5 = 0;
uint16_t anglestep1 = 10;
uint16_t anglestep2 = 8;
uint16_t anglestep3 = 6;
uint16_t anglestep4 = 4;
uint16_t anglestep5 = 2;

#define SCREEN_COUNT   10
int screen = 0;

#define LINE_COUNT  40
int16_t lx1[LINE_COUNT] = { CANVAS_WIDTH / 2 };
int16_t ly1[LINE_COUNT] = { 10 };
int16_t lx2[LINE_COUNT] = { 20 };
int16_t ly2[LINE_COUNT] = { CANVAS_HEIGHT / 3 };
int16_t ldx1 = 4;
int16_t ldy1 = -4;
int16_t ldx2 = 6;
int16_t ldy2 = 5;

#define VEHICLE_COUNT   50

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
    device_getinput(&touch);
    switch (touch.gesture)
    {
        case GESTURE_UP:
            screen = (screen + 1) % SCREEN_COUNT;
            break;
        case GESTURE_DOWN:
            screen = (screen - 1 + SCREEN_COUNT) % SCREEN_COUNT;
            break;
        case GESTURE_LEFT:
            screen = (screen - 1 + SCREEN_COUNT) % SCREEN_COUNT;
            break;
        case GESTURE_RIGHT:
            screen = (screen + 1) % SCREEN_COUNT;
            break;
        case GESTURE_CLICK:
            printf("%dx%d\n", touch.x, touch.y);
            tx = touch.x;
            ty = touch.y;
            stopped = !stopped;
            break;
    }

    if (stopped)
    {
        return;
    }
    
    counter++;

    if (screen == 3)
    {
        for (int i = LINE_COUNT - 2; i >=  0; --i)
        {
            lx1[i + 1] = lx1[i];
            lx2[i + 1] = lx2[i];
            ly1[i + 1] = ly1[i];
            ly2[i + 1] = ly2[i];
        }
        
        lx1[0] += ldx1;
        lx2[0] += ldx2;
        ly1[0] += ldy1;
        ly2[0] += ldy2;

        if (lx1[0] < 0)
        {
            lx1[0] = 0;
            ldx1 = -ldx1;
        }

        if (lx2[0] < 0)
        {
            lx2[0] = 0;
            ldx2 = -ldx2;
        }

        if (ly1[0] < 0)
        {
            ly1[0] = 0;
            ldy1 = -ldy1;
        }

        if (ly2[0] < 0)
        {
            ly2[0] = 0;
            ldy2 = -ldy2;
        }

        if (lx1[0] >= CANVAS_WIDTH)
        {
            lx1[0] = CANVAS_WIDTH - 1;
            ldx1 = -ldx1;
        }

        if (lx2[0] >= CANVAS_WIDTH)
        {
            lx2[0] = CANVAS_WIDTH - 1;
            ldx2 = -ldx2;
        }

        if (ly1[0] >= CANVAS_HEIGHT)
        {
            ly1[0] = CANVAS_HEIGHT - 1;
            ldy1 = -ldy1;
        }

        if (ly2[0] >= CANVAS_HEIGHT)
        {
            ly2[0] = CANVAS_HEIGHT - 1;
            ldy2 = -ldy2;
        }
    } // Screen 3

    if (screen == 1)
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
    } // Screen 1

    if (screen == 8)
    {
        angle1 += anglestep1;
        angle2 += anglestep2;
        angle3 += anglestep3;
        angle4 += anglestep4;
        angle5 += anglestep5;
        if (angle1 > 360)
        {
            angle1 = 0;
        }

        if (angle2 > 360)
        {
            angle2 = 0;
        }

        if (angle3 > 360)
        {
            angle3 = 0;
        }

        if (angle4 > 360)
        {
            angle4 = 0;
        }

        if (angle5 > 360)
        {
            angle5 = 0;
        }
    } // Screen 8

    if (screen == 9)
    {
        counter91 += 6;
        if (counter91 > 360)
        {
            counter91 = 0;
            counter92 += 6;
            if (counter92 > 360)
            {
                counter92 = 0;
                counter93 += 6;
                if (counter93 > 360)
                {
                    counter93 = 0;
                }
            }
        }
    } // Screen 9
}

void draw(void)
{
    Canvas_Clear();

    if (screen == 0)
    {
        int o = 10;
        Canvas_Draw_Rect(o, o, CANVAS_WIDTH - 1 - o, CANVAS_HEIGHT - 1 - o, CYAN);
        o = 20;
        Canvas_Draw_Rect(o, o, CANVAS_WIDTH - 1 - o, CANVAS_HEIGHT - 1 - o, YELLOW);
        
        Canvas_Draw_HLine(0, CANVAS_WIDTH - 1, CANVAS_HEIGHT / 2, WHITE);
        Canvas_Draw_VLine(CANVAS_WIDTH / 2, 0, CANVAS_HEIGHT - 1, BLUE);

        Canvas_Draw_Line(0, 0, CANVAS_WIDTH - 1, CANVAS_HEIGHT - 1, RED);
        Canvas_Draw_Line(CANVAS_WIDTH - 1, 0, 0, CANVAS_HEIGHT - 1, GREEN);

        Canvas_Fill_Circle(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, 50, ORANGE);

        Canvas_Fill_Circle(50, 50, 20, COBALT);
        Canvas_Fill_Circle(CANVAS_WIDTH - 50, 50, 20, MAUVE);
        Canvas_Fill_Circle(50, CANVAS_HEIGHT - 50, 20, TEAL);
        Canvas_Fill_Circle(CANVAS_WIDTH - 50, CANVAS_HEIGHT - 50, 20, EMERALD);
    }
    else if (screen == 1)
    {
        for (int i = 0; i < VEHICLE_COUNT; ++i)
        {
            // Canvas_Fill_Rect(vehicles[i].ox, vehicles[i].oy, w, h, BLACK);

            Canvas_Fill_Rect(vehicles[i].x, vehicles[i].y, w, h, colors[vehicles[i].c]);
        }
    }
    else if (screen == 2)
    {
        char temp[20];
        uint16_t x = CANVAS_WIDTH / 2;
        uint16_t y = 50;
        Canvas_Write_Ascii_Centered("CoderDojo", x, y, YELLOW, BLACK);

        sprintf(temp, "%d", counter);
        y += Canvas_Ascii_Height(temp) + 2;
        Canvas_Write_Ascii_Centered(temp, x, y, CRIMSON, BLACK);

        sprintf(temp, "0x%X", counter);
        y += Canvas_Ascii_Height(temp) + 2;
        Canvas_Write_Ascii_Centered(temp, x, y, BROWN, BLACK);

        sprintf(temp, "%d", counter);
        y += Canvas_Ascii_Height(temp) + 2;
        Canvas_Write_Ascii_Centered(temp, x, y, STEEL, BLACK);

        sprintf(temp, "0x%X", counter);
        y += Canvas_Ascii_Height(temp) + 2;
        Canvas_Write_Ascii_Centered(temp, x, y, ORANGE, BLACK);

        sprintf(temp, "%d", counter);
        y += Canvas_Ascii_Height(temp) + 2;
        Canvas_Write_Ascii_Centered(temp, x, y, TAUPE, BLACK);

        sprintf(temp, "0x%x", counter);
        y += Canvas_Ascii_Height(temp) + 2;
        Canvas_Write_Ascii_Centered(temp, x, y, TEAL, BLACK);
    }
    else if (screen == 3)
    {
        for (int i = LINE_COUNT - 1; i >= 0; --i)
        {
            Canvas_Draw_Line(lx1[i], ly1[i], lx2[i], ly2[i], i == 0 ? WHITE : GRAY);
        }
    }
    else if (screen == 4)
    {
        Canvas_Fill_Rect(tx - 15, ty - 15, 30, 30, GREEN);

        char temp[20];
        sprintf(temp, "%dx%d", tx, ty);
        Canvas_Write_Ascii_Centered(temp, CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CRIMSON, BLACK);
    }
    else if (screen == 5)
    {
        int w = CANVAS_WIDTH / 32;
        int x = (CANVAS_WIDTH - (32 * w)) / 2;
        int h = 20;
        int y = (CANVAS_HEIGHT / 2) - h - (h / 2); 
        for (int r = 0; r < 32; ++r)
        {
            Canvas_Fill_Rect(x, y, w, h, GBRG(r, 0, 0));
            x += w;
        }

        w = CANVAS_WIDTH / 64;
        x = (CANVAS_WIDTH - (64 * w)) / 2;
        y += h;
        for (int g = 0; g < 64; ++g)
        {
            Canvas_Fill_Rect(x, y, w, h, GBRG(0, g, 0));
            x += w;
        }

        w = CANVAS_WIDTH / 32;
        x = (CANVAS_WIDTH - (32 * w)) / 2;
        y += h;
        for (int b = 0; b < 32; ++b)
        {
            Canvas_Fill_Rect(x, y, w, h, GBRG(0, 0, b));
            x += w;
        }
    }
    else if (screen == 6)
    {
        int s = 40;
        int g = 5;
        int ox = (CANVAS_WIDTH - (g * s)) / 2;
        int oy = (CANVAS_HEIGHT - (g * s)) / 2;
        for (int i = 0; i < g * g; i++)
        {
            int xi = i % g;
            int yi = i / g;
            int x = ox + (xi * s);
            int y = oy + (yi * s);
            if (i < color_count)
            {
                Canvas_Fill_Rect(x, y, s, s, colors[i]);
            }

            Canvas_Draw_Rect(x, y, x + s - 1, y + s - 1, WHITE);
        }
    }
    else if (screen == 7)
    {
        Canvas_Fill_Round_Rect(40, 80, 110, 50, 10, STEEL);
        Canvas_Draw_Round_Rect(100, 70, 90, 50, 10, WHITE);
        Canvas_Draw_Round_Rect(50, 50, 150, 145, 20, RED);
        Canvas_Draw_Round_Rect(70, 100, 70, 70, 30, YELLOW);
        Canvas_Draw_Circle(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH / 3, COBALT);
    }
    else if (screen == 8)
    {
        uint16_t cx = CANVAS_WIDTH / 2;
        uint16_t cy = CANVAS_HEIGHT / 2;

        float r = 110;
        Canvas_Draw_Arc(cx, cy, 0, angle1, r, INDIGO);
        r -= 10;
        Canvas_Draw_Arc(cx, cy, 0, angle2, r, ORANGE);
        r -= 10;
        Canvas_Draw_Arc(cx, cy, 0, angle3, r, GREEN);
        r -= 10;
        Canvas_Draw_Arc(cx, cy, 0, angle4, r, PINK);
        r -= 10;
        Canvas_Draw_Arc(cx, cy, 0, angle5, r, BROWN);
    }
    else if (screen == 9)
    {
        uint16_t cx = CANVAS_WIDTH / 2;
        uint16_t cy = CANVAS_HEIGHT / 2;

        uint16_t dark = RGB2GBRG(24, 24, 24);
        uint16_t r = 100;
        uint16_t thick = 10;

        Canvas_Draw_Thick_Circle(cx, cy, r, thick, dark);
        Canvas_Draw_Thick_Circle(cx, cy, r - 20, thick, dark);
        Canvas_Draw_Thick_Circle(cx, cy, r - 40, thick, dark);

        Canvas_Draw_Thick_Arc(cx, cy, r, 0, counter91, thick, EMERALD);
        Canvas_Draw_Thick_Arc(cx, cy, r - 20, 0, counter92, thick, ORANGE);
        Canvas_Draw_Thick_Arc(cx, cy, r - 40, 0, counter93, thick, STEEL);

        float w = 55;
        float h = 49;

        //Canvas_Fill_Round_Rect(cx - w / 2, cy - h / 2, w, h, 10, GRAY1);
        //Canvas_Draw_Round_Rect(cx - w / 2, cy - h / 2, w, h, 10, GRAY);
        Canvas_Fill_Rect(cx - w / 2 + 10, cy - h / 2 + 10, w, h, dark);
        Canvas_Fill_Rect(cx - w / 2, cy - h / 2, w, h, GRAY1);

        char temp[20];
        sprintf(temp, "%d", counter91 / 6);
        Canvas_Write_Ascii_Centered(temp, cx, cy, YELLOW, BLACK);
    }
}

bool bl = true;

bool timer_callback(struct repeating_timer *t)
{
    printf("Timer %d  - Delay %ldus\n", t->alarm_id, t->delay_us);
    
    bl = !bl;
    device_backlight(bl);

    return true;
}

int64_t alarm_callback(alarm_id_t id, void *user_data)
{
    printf("Alarm %d\n", id);
    return 2000 * 1000;     // 2000 milliseconds = 2 seconds = 2000000 microseconds
}

int main(void)
{
    device_init();

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
        device_delay(50);
        //tight_loop_contents();

        //at = get_absolute_time();
        //uint32_t time_since_boot = to_ms_since_boot(at);
        //printf("Diff: %d \n", boot_ms - time_since_boot);
    }

    device_cleanup();
    return 0;
}

/*

static uint8_t reverse(uint8_t b) 
{
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

https://github.com/shyd/waveshare-pico-lcd2/blob/main/c/lib/Fonts/font12.c
https://github.com/HEJOK254/Pico-ResTouch-LCD-2.8-Horizontal-Fix/blob/main/lib/font/font8.c


*/
