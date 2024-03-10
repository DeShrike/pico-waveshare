#include "pico/stdlib.h"

#include "DEV_Config.h"
#include "LCD_1in28.h"
#include "CST816S.h"

#include "device.h"

// Input Device
static int16_t encoder_diff;

// Touch Position
static uint16_t ts_x;
static uint16_t ts_y;
static uint8_t ts_gesture;
static int ts_touched = 0;

// Timer
static struct repeating_timer loop_timer;

/********************************************************************************
function:	Refresh image by transferring the color data to the SPI bus by DMA
parameter:
********************************************************************************/
/*static*/ void display_flush(const area_t* area, color16_t* color_p)
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
static uint32_t last_touch_ms = 0xFFFFFFFF; 
static void touch_callback(uint gpio, uint32_t events)
{
    if (gpio == Touch_INT_PIN)
    {
        absolute_time_t at = get_absolute_time();
        uint32_t tt = to_ms_since_boot(at);
        if (tt - last_touch_ms > 150)
        {
            uint8_t g =  CST816S_Get_Gesture();
            ts_gesture = g;
            // printf("Gesture: %d    %d    %d  Diff: %d Events: %d \n", g, last_touch_ms, tt, tt - last_touch_ms, events);

            if (g == GESTURE_CLICK)
            {
                CST816S_Get_Point();
                ts_x = Touch_CTS816.x_point;
                ts_y = Touch_CTS816.y_point;

                CST816S_Mode mode = Touch_CTS816.mode;

                // printf("Touch: (%d,%d)  %d    %d    %d  Diff: %d Events: %d \n", ts_x, ts_y, mode, last_touch_ms, tt, tt - last_touch_ms, events);
            }

            ts_touched = 1;
            last_touch_ms = tt;
        }
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

static int init_devices() 
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
    // CST816S_init(CST816S_Point_Mode);
    CST816S_init(CST816S_Gesture_Mode);

    return 0;
}

/********************************************************************************
function:   Initialize
parameter:
********************************************************************************/
void device_init(void)
{
    init_devices();

    // Init Timer
    // add_repeating_timer_ms(5, repeating_loop_timer_callback, NULL, &loop_timer);

    // Enable touch IRQ
    DEV_IRQ_SET(Touch_INT_PIN, GPIO_IRQ_EDGE_RISE, &touch_callback);

    // Init DMA for transmit color data from memory to SPI
    dma_channel_set_irq0_enabled(dma_tx, true);
    irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
    irq_set_enabled(DMA_IRQ_0, true);

    Canvas_Init();
}

void device_backlight(bool state)
{
    DEV_SET_PWM(state ? 100 : 25);
}

/********************************************************************************
function:   Cleanup
parameter:
********************************************************************************/
void device_cleanup(void)
{
    DEV_Module_Exit();
}

/********************************************************************************
function:   Delay
parameter:
********************************************************************************/
void device_delay(int ms)
{
    DEV_Delay_ms(ms);
}

bool device_getinput(input_t* data)
{
    data->x = ts_x;
    data->y = ts_y;
    data->touched = ts_touched == 1;

    data->gesture = ts_touched ? ts_gesture : GESTURE_NONE;
    /*
    if (ts_gesture == GESTURE_CLICK)
    {
        data->gesture = ts_touched ? ts_gesture : GESTURE_NONE;
    }
    else
    {
        data->gesture = ts_gesture;
    }*/

    ts_touched = 0;
}

/*
void Device_Flush_Display(int x, int y, int w, int h, uint16_t* pixels)
{
}*/



/*
static void delay_loop(volatile uint32_t count)
{
	asm volatile(
		"1: sub %0, %0, #1\n"
		"bne 1b\n"
		: "+r" (count)
		:
		: "cc"
	);
}
*/
/***********************************************************************/

