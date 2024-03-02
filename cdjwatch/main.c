#include "pico/stdlib.h"
#include "lvgl.h"
#include "DEV_Config.h"
#include "LCD_1in28.h"
#include "CST816S.h"
//#include "QMI8658.h"
#include "logo_cdj_belgium_transparent_100_100.h"

#define DISP_HOR_RES 240
#define DISP_VER_RES 240

#define INPUTDEV_TS  1

// LVGL
static lv_disp_draw_buf_t disp_buf;
static lv_color_t buf0[DISP_HOR_RES * DISP_VER_RES / 2];
static lv_color_t buf1[DISP_HOR_RES * DISP_VER_RES / 2];
static lv_disp_drv_t disp_drv;

//static dma_channel_config dma_cc;

static lv_indev_drv_t indev_ts;
static lv_indev_drv_t indev_en;
static lv_group_t *group;

static lv_obj_t *label_imu;

// Input Device 
static int16_t encoder_diff;
static lv_indev_state_t encoder_act;

static uint16_t ts_x;
static uint16_t ts_y;
static lv_indev_state_t ts_act;

// Timer 
static struct repeating_timer lvgl_timer;

/********************************************************************************
function:	Refresh image by transferring the color data to the SPI bus by DMA
parameter:
********************************************************************************/
static void disp_flush_cb(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p)
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
function:	Update encoder input device status
parameter:
********************************************************************************/
static void encoder_read_cb(lv_indev_drv_t * drv, lv_indev_data_t*data)
{
    data->enc_diff = encoder_diff;
    data->state    = encoder_act; 
    /* encoder_diff = 0; */
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
        lv_disp_flush_ready(&disp_drv); /* Indicate you are ready with the flushing*/
    }
}

/********************************************************************************
function:   Update touch screen input device status
parameter:
********************************************************************************/
static void ts_read_cb(lv_indev_drv_t * drv, lv_indev_data_t*data)
{
    data->point.x = ts_x;
    data->point.y = ts_y; 
    data->state = ts_act;
    ts_act = LV_INDEV_STATE_RELEASED;
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
        ts_act = LV_INDEV_STATE_PRESSED;
    }
}

/********************************************************************************
function:   Report the elapsed time to LVGL each 5ms
parameter:
********************************************************************************/
static bool repeating_lvgl_timer_callback(struct repeating_timer *t)
{
    lv_tick_inc(5);
    return true;
}

void LVGL_init(void)
{
    // /*1.Init Timer*/ 
    add_repeating_timer_ms(5, repeating_lvgl_timer_callback, NULL, &lvgl_timer);

    // /*2.Init LVGL core*/
    lv_init();

    // /*3.Init LVGL display*/
    lv_disp_draw_buf_init(&disp_buf, buf0, buf1, DISP_HOR_RES * DISP_VER_RES / 2);
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = disp_flush_cb;
    disp_drv.draw_buf = &disp_buf;
    disp_drv.hor_res = DISP_HOR_RES;
    disp_drv.ver_res = DISP_VER_RES;
    lv_disp_t *disp= lv_disp_drv_register(&disp_drv);

#if INPUTDEV_TS
    // /*4.Init touch screen as input device*/ 
    lv_indev_drv_init(&indev_ts); 
    indev_ts.type = LV_INDEV_TYPE_POINTER;
    indev_ts.read_cb = ts_read_cb;
    lv_indev_t * ts_indev = lv_indev_drv_register(&indev_ts);
    //Enable touch IRQ
    DEV_IRQ_SET(Touch_INT_PIN, GPIO_IRQ_EDGE_RISE, &touch_callback);
#endif

    // /*5.Init imu as input device*/
    lv_indev_drv_init(&indev_en);
    indev_en.type = LV_INDEV_TYPE_ENCODER;
    indev_en.read_cb = encoder_read_cb;
    lv_indev_t * encoder_indev = lv_indev_drv_register(&indev_en);
    group = lv_group_create();
    lv_indev_set_group(encoder_indev, group);

    // /6.Init DMA for transmit color data from memory to SPI
    dma_channel_set_irq0_enabled(dma_tx, true);
    irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
    irq_set_enabled(DMA_IRQ_0, true);
}

#if 1
void Widgets_Init(void)
{
    lv_obj_t * label1 = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP); /*Break the long lines*/
    lv_label_set_recolor(label1, true);
    
    lv_label_set_text(label1, "#0000ff Coderdojo Belgium - #ff0000 Roeselare");
    //lv_label_set_text(label1, "#0000ff Re-color# #ff00ff words# #ff0000 of a# label, align the lines to the center "
    //                          "and wrap long text automatically.");

    lv_obj_set_width(label1, 150);  /*Set smaller width to make the lines wrap*/
    lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, -70);

    LV_IMG_DECLARE(logo_cdj_belgium_transparent_100_100);
    lv_obj_t *img1 = lv_img_create(lv_scr_act());
    lv_img_set_src(img1, &logo_cdj_belgium_transparent_100_100);
    lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t * label2 = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL_CIRCULAR); /*Circular scroll*/
    lv_obj_set_width(label2, 150);
    // lv_label_set_recolor(label2, true);
    lv_label_set_text(label2, "Coderdojo Belgium - Roeselare");
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 65);
}
#endif

#if 0
void Widgets_Init(void)
{
    LV_IMG_DECLARE(logo_cdj_belgium);
    lv_obj_t *img1 = lv_img_create(lv_scr_act());
    lv_img_set_src(img1, &logo_cdj_belgium);
    lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);
}
#endif 

#if 0
void Widgets_Init(void)
{
    /*Create a LED and switch it OFF*/
    lv_obj_t * led1  = lv_led_create(lv_scr_act());
    lv_obj_align(led1, LV_ALIGN_CENTER, -80, 0);
    lv_led_set_brightness(led1, 150);
    lv_led_set_color(led1, lv_palette_main(LV_PALETTE_RED));
    //lv_led_off(led1);

    /*Copy the previous LED and set a brightness*/
    lv_obj_t * led2  = lv_led_create(lv_scr_act());
    lv_obj_align(led2, LV_ALIGN_CENTER, 0, 0);
    lv_led_set_brightness(led2, 150);
    lv_led_set_color(led2, lv_palette_main(LV_PALETTE_GREEN));

    /*Copy the previous LED and switch it ON*/
    lv_obj_t * led3  = lv_led_create(lv_scr_act());
    lv_obj_align(led3, LV_ALIGN_CENTER, 80, 0);
    lv_led_set_brightness(led3, 150);
    lv_led_set_color(led3, lv_palette_main(LV_PALETTE_BLUE));
    //lv_led_on(led3);
}
#endif

#if 0
void Widgets_Init(void)
{
    // /*Style Config*/
    static lv_style_t style_base;
    lv_style_init(&style_base);
    lv_style_set_bg_color(&style_base, lv_palette_main(LV_PALETTE_LIGHT_GREEN));
    lv_style_set_border_color(&style_base, lv_palette_darken(LV_PALETTE_LIGHT_GREEN, 3));
    lv_style_set_border_width(&style_base, 2);
    lv_style_set_radius(&style_base, 10);
    lv_style_set_shadow_width(&style_base, 10);
    lv_style_set_shadow_ofs_y(&style_base, 5);
    lv_style_set_shadow_opa(&style_base, LV_OPA_50);
    lv_style_set_text_color(&style_base, lv_color_white());
    lv_style_set_width(&style_base, 100);
    lv_style_set_height(&style_base, LV_SIZE_CONTENT);

    static lv_style_t style_press;
    lv_style_init(&style_press);
    lv_style_set_bg_color(&style_press, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_border_color(&style_press, lv_palette_darken(LV_PALETTE_GREEN, 3));
    lv_style_set_border_width(&style_press, 2);
    lv_style_set_radius(&style_press, 10);
    lv_style_set_shadow_width(&style_press, 10);
    lv_style_set_shadow_ofs_y(&style_press, 5);
    lv_style_set_shadow_opa(&style_press, LV_OPA_50);
    lv_style_set_text_color(&style_press, lv_color_white());
    lv_style_set_width(&style_press, 100);
    lv_style_set_height(&style_press, LV_SIZE_CONTENT);

    static lv_style_t style_slider;
    lv_style_set_bg_color(&style_slider, lv_palette_main(LV_PALETTE_ORANGE));
    lv_style_set_border_color(&style_slider, lv_palette_darken(LV_PALETTE_ORANGE, 3));

    static lv_style_t style_indic;
    lv_style_init(&style_indic);
    lv_style_set_bg_color(&style_indic, lv_palette_lighten(LV_PALETTE_DEEP_ORANGE, 3));
    lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_DEEP_ORANGE));
    lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_HOR);

    static lv_style_t style_indic_pr;
    lv_style_init(&style_indic_pr);
    lv_style_set_shadow_color(&style_indic_pr, lv_palette_main(LV_PALETTE_DEEP_ORANGE));
    lv_style_set_shadow_width(&style_indic_pr, 10);
    lv_style_set_shadow_spread(&style_indic_pr, 3);

    static lv_style_t style_sw;
    lv_style_init(&style_sw);
    lv_style_set_bg_opa(&style_sw, LV_OPA_COVER);
    lv_style_set_bg_color(&style_sw, lv_palette_lighten(LV_PALETTE_RED, 1));
    lv_style_set_shadow_width(&style_sw, 55);
    lv_style_set_shadow_color(&style_sw, lv_palette_main(LV_PALETTE_PINK));

    static lv_style_t style_roller;
    lv_style_init(&style_roller);
    lv_style_set_border_color(&style_roller, lv_palette_darken(LV_PALETTE_BLUE, 3));
    lv_style_set_shadow_width(&style_roller, 55);
    lv_style_set_shadow_color(&style_roller, lv_palette_main(LV_PALETTE_BLUE_GREY));
    static lv_style_t style_list;
    lv_style_set_shadow_width(&style_list, 55);
    lv_style_set_shadow_color(&style_list, lv_palette_main(LV_PALETTE_GREY));

    static lv_style_t style_imu_label;
    lv_style_init(&style_imu_label);
    lv_style_set_text_color(&style_imu_label, lv_palette_main(LV_PALETTE_PURPLE));;

    // /*Create tileview*/
    lv_obj_t *tv = lv_tileview_create(lv_scr_act());
    lv_obj_set_scrollbar_mode(tv, LV_SCROLLBAR_MODE_OFF);
    lv_group_add_obj(group, tv);

    // /*Tile1: Just a pic*/
    #if 1
    {
        lv_obj_t *tile1 = lv_tileview_add_tile(tv, 0, 0, LV_DIR_BOTTOM);
        
        LV_IMG_DECLARE(logo_cdj_belgium_transparent_100_100);
        lv_obj_t *img1 = lv_img_create(tile1);
        lv_img_set_src(img1, &logo_cdj_belgium_transparent_100_100);
        lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);
    }
    #endif

    // /*Tile2: Some widgets*/
    #if 1
    {
        lv_obj_t *tile2 = lv_tileview_add_tile(tv, 0, 1, LV_DIR_TOP);

        lv_obj_t *btn = lv_btn_create(tile2);
        lv_obj_set_size(btn, 60, 30);
        lv_obj_align(btn, LV_ALIGN_CENTER, -50, -50);
        lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);
        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text(label, "Toggle");
        lv_obj_center(label);
        lv_group_add_obj(group, btn);
        lv_obj_add_style(btn,&style_base, 0);
        lv_obj_add_style(btn,&style_press, LV_STATE_CHECKED);

        lv_obj_t *sw = lv_switch_create(tile2);
        lv_obj_set_size(sw, 60, 30);
        lv_obj_align(sw, LV_ALIGN_CENTER, 50, -50);
        lv_group_add_obj(group, sw);
        lv_obj_add_style(sw, &style_sw, LV_STATE_CHECKED | LV_PART_INDICATOR);

        lv_obj_t *roller = lv_roller_create(tile2);
        const char * opts = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10";
        lv_roller_set_options(roller, opts, LV_ROLLER_MODE_NORMAL);
        lv_roller_set_visible_row_count(roller, 2);
        lv_obj_align(roller, LV_ALIGN_CENTER, -50, 50);
        lv_roller_set_selected(roller, 5, LV_ANIM_OFF);
        lv_group_add_obj(group, roller);
        lv_obj_add_style(roller, &style_roller,0);

        lv_obj_t *slider = lv_slider_create(tile2);
        lv_obj_set_size(slider, 10, 80);
        lv_obj_align(slider, LV_ALIGN_CENTER, 50, 50);
        lv_group_add_obj(group, slider);
        lv_obj_add_style(slider, &style_slider, 0);
        lv_obj_add_style(slider, &style_indic, LV_PART_INDICATOR);
        lv_obj_add_style(slider, &style_indic_pr, LV_PART_INDICATOR | LV_STATE_PRESSED);
        lv_obj_add_style(slider, &style_slider, LV_PART_KNOB);
    }
    #endif

    // /*Tile2: Show IMU data*/
    #if 0
    {
        lv_obj_t *tile3 = lv_tileview_add_tile(tv, 0, 2, LV_DIR_TOP|LV_DIR_BOTTOM);
      
        lv_obj_t *list = lv_list_create(tile3);
        lv_obj_set_size(list, 80, 120);
        lv_obj_align(list,LV_ALIGN_LEFT_MID, 20, 0);
        lv_obj_clear_flag(list, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_t *label = lv_label_create(list);
        lv_obj_add_style(list, &style_list, 0);
        lv_label_set_text(label, "ACC_X\nACC_Y\nACC_Z\n\nGYRO_X\nGYRO_Y\nGYRO_Z");
        lv_obj_add_style(label, &style_imu_label,0);

        list = lv_list_create(tile3);
        lv_obj_set_size(list, 70, 120);
        lv_obj_align(list, LV_ALIGN_CENTER, 15, 0);
        lv_obj_clear_flag(list, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_add_style(list,&style_list,0 );
        label_imu = lv_label_create(list);
        lv_label_set_text(label_imu, "0\n0\n0\n\n0\n0\n0");

        list = lv_list_create(tile3);
        lv_obj_set_size(list, 50, 120);
        lv_obj_align(list,LV_ALIGN_RIGHT_MID, -20, 0);
        lv_obj_clear_flag(list, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_add_style(list,&style_list, 0);
        label = lv_label_create(list);
        lv_label_set_text(label, "mg\nmg\nmg\n\ndps\ndps\ndps");
        lv_obj_add_style(label, &style_imu_label,0);
    }
    #endif
}
#endif

#if 0
void Widgets_Init(void)
{
#define CANVAS_WIDTH  150
#define CANVAS_HEIGHT  150

    lv_draw_rect_dsc_t rect_dsc;
    lv_draw_rect_dsc_init(&rect_dsc);
    rect_dsc.radius = 10;
    rect_dsc.bg_opa = LV_OPA_COVER;
    rect_dsc.bg_grad_dir = LV_GRAD_DIR_HOR;
    rect_dsc.bg_color = lv_palette_main(LV_PALETTE_RED);
    rect_dsc.bg_grad_color = lv_palette_main(LV_PALETTE_BLUE);
    rect_dsc.border_width = 2;
    rect_dsc.border_opa = LV_OPA_90;
    rect_dsc.border_color = lv_color_white();
    rect_dsc.shadow_width = 5;
    rect_dsc.shadow_ofs_x = 5;
    rect_dsc.shadow_ofs_y = 5;

    lv_draw_label_dsc_t label_dsc;
    lv_draw_label_dsc_init(&label_dsc);
    label_dsc.color = lv_palette_main(LV_PALETTE_YELLOW);

    static lv_color_t cbuf[LV_CANVAS_BUF_SIZE_TRUE_COLOR(CANVAS_WIDTH, CANVAS_HEIGHT)];

    lv_obj_t * canvas = lv_canvas_create(lv_scr_act());
    lv_canvas_set_buffer(canvas, cbuf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_IMG_CF_TRUE_COLOR);
    lv_obj_center(canvas);
    lv_canvas_fill_bg(canvas, lv_palette_lighten(LV_PALETTE_GREY, 3), LV_OPA_COVER);

    lv_canvas_draw_rect(canvas, 70, 60, 100, 70, &rect_dsc);

    lv_canvas_draw_text(canvas, 40, 20, 100, &label_dsc, "Some text on text canvas");
}
#endif

int main(void)
{
    if (DEV_Module_Init() != 0)
    {
        return -1;
    }

    // /*Init LCD*/
    LCD_1IN28_Init(HORIZONTAL);
    LCD_1IN28_Clear(YELLOW);
    DEV_SET_PWM(100);

    // /*Init touch screen*/ 
    CST816S_init(CST816S_Point_Mode);

    // /*Init IMU*/
    // QMI8658_init();

    // /*Init LVGL*/
    LVGL_init();
    Widgets_Init();

    /*
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_put(LED_PIN, 1);
    */
    
    while (true)
    {
        lv_task_handler();

        /*
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(2000);
        */

        DEV_Delay_ms(5); 
    }

    DEV_Module_Exit();
	return 0;
}
