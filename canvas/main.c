#include "pico/stdlib.h"

#include "DEV_Config.h"
#include "LCD_1in28.h"
#include "CST816S.h"

#include "framework.h"
#include "canvas.h"

// Input Device 
static int16_t encoder_diff;

// Touch Position
static uint16_t ts_x;
static uint16_t ts_y;
static int ts_touched = 0;

// Timer 
static struct repeating_timer loop_timer;

/********************************************************************************
function:	Refresh image by transferring the color data to the SPI bus by DMA
parameter:
********************************************************************************/
static void disp_flush_cb(const area_t* area, color16_t* color_p)
{
    LCD_1IN28_SetWindows(area->x1, area->y1, area->x2 , area->y2);
    dma_channel_configure(dma_tx,
                          &c,
                          &spi_get_hw(LCD_SPI_PORT)->dr,
                          color_p, // read address
                          ((area->x2 + 1 - area->x1) * (area->y2 + 1 - area->y1)) * 2,
                          true);
}

/********************************************************************************
function:   Indicate ready with the flushing when DMA complete transmission
parameter:
********************************************************************************/
static void dma_handler(void)
{
    if (dma_channel_get_irq0_status(dma_tx))
    {
        dma_channel_acknowledge_irq0(dma_tx);
    }
}

/********************************************************************************
function:   Touch interrupt handler
parameter:
********************************************************************************/
static void touch_callback(uint gpio, uint32_t events)
{
    if (gpio == Touch_INT_PIN)
    {
        CST816S_Get_Point();
        ts_x = Touch_CTS816.x_point;
        ts_y = Touch_CTS816.y_point;
        ts_touched = 1;
    }
}

/********************************************************************************
function:   Report the elapsed time to LVGL each 5ms
parameter:
********************************************************************************/
static bool repeating_loop_timer_callback(struct repeating_timer *t)
{
    return true;
}

/****************************************************/
/****************************************************/
/****************************************************/

void Framework_Init(void)
{
    // Init Timer
    add_repeating_timer_ms(5, repeating_loop_timer_callback, NULL, &loop_timer);

    // Enable touch IRQ
    DEV_IRQ_SET(Touch_INT_PIN, GPIO_IRQ_EDGE_RISE, &touch_callback);

    // Init DMA for transmit color data from memory to SPI
    dma_channel_set_irq0_enabled(dma_tx, true);
    irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
    irq_set_enabled(DMA_IRQ_0, true);
}

void Framework_Cleanup(void)
{
}

/****************************************************/
/****************************************************/
/****************************************************/

uint16_t colors[] = { WHITE, RED, GREEN, BLUE, GRAY, YELLOW, CYAN, MAGENTA };
int color_count = sizeof(colors) / sizeof(colors[0]);
int tx, ty, x, y;
int otx, oty, ox, oy;
int w, h, dx, dy, cix, tcix;

void init(void)
{
    // Init Canvas
    Canvas_Init(disp_flush_cb);

    w = 30;
    h = 30;
    ox = x = CANVAS_WIDTH / 3;
    oy = y = CANVAS_HEIGHT / 5;
    dx = 3;
    dy = 4;
    tcix = cix = 0;

    otx = tx = CANVAS_WIDTH / 2;
    oty = ty = CANVAS_HEIGHT / 2;
}

void update(void)
{
    ox = x;
    oy = y;
    
    x = x + dx;
    y = y + dy;

    if (x < 0)
    {
        x = 0;
        dx = -dx;
        cix = (cix + 1) % color_count;
    }

    if (y < 0)
    {
        y = 0;
        dy = -dy;
        cix = (cix + 1) % color_count;
    }

    if (x > CANVAS_WIDTH - w)
    {
        x = CANVAS_WIDTH - w - 1;
        dx = -dx;
        cix = (cix + 1) % color_count;
    }

    if (y > CANVAS_HEIGHT - h)
    {
        y = CANVAS_HEIGHT - h - 1;
        dy = -dy;
        cix = (cix + 1) % color_count;
    }
    
    if (ts_touched)
    {
        otx = tx;
        oty = ty;
        tx = ts_x;
        ty = ts_y;
        ts_touched = 0;
        tcix = (tcix + 1) % color_count;
    }
}

void draw(void)
{
    Canvas_Fill_Rect(ox, oy, w, h, BLACK);
    Canvas_Fill_Rect(otx, oty, w, h, BLACK);

    Canvas_Fill_Rect(x, y, w, h, colors[cix]);
    Canvas_Fill_Rect(tx, ty, w, h, colors[tcix]);

    Canvas_Flush();
}

int main(void)
{
    if (DEV_Module_Init() != 0)
    {
        return -1;
    }

    // Init LCD
    LCD_1IN28_Init(HORIZONTAL);
    LCD_1IN28_Clear(YELLOW);
    DEV_SET_PWM(100);

    // Init touch screen
    CST816S_init(CST816S_Point_Mode);

    // Init Canvas
    Framework_Init();


    init();

    while (true)
    {
        update();
        draw();

        DEV_Delay_ms(50);
    }

    Framework_Cleanup();
    DEV_Module_Exit();
    return 0;
}
