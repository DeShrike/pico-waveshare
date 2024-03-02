#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_LOGO_CDJ_BELGIUM_TRANSPARENT_100_100
#define LV_ATTRIBUTE_IMG_LOGO_CDJ_BELGIUM_TRANSPARENT_100_100
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST 
    LV_ATTRIBUTE_IMG_LOGO_CDJ_BELGIUM_TRANSPARENT_100_100 

uint8_t logo_cdj_belgium_transparent_100_100_map[] = {
  0xfd, 0xfd, 0xfd, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0x04, 	/*Color of index 1*/
  0x8c, 0x8b, 0x8b, 0xff, 	/*Color of index 2*/
  0x04, 0x03, 0x03, 0xf2, 	/*Color of index 3*/

  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xff, 0xff, 0xdd, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x57, 0xff, 0xee, 0xae, 0xff, 0xfd, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xff, 0xe0, 0x00, 0x00, 0x0f, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2f, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x57, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x7f, 0x00, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xf8, 0x00, 0x00, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x3f, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x57, 0xc0, 0x00, 0x00, 0x00, 0xfa, 0xaa, 0xe0, 0x00, 0x0f, 0xff, 0xfd, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5e, 0x00, 0x00, 0x00, 0x02, 0xf0, 0x02, 0xe0, 0x00, 0x0b, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x78, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0xe0, 0x00, 0x03, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xe0, 0x00, 0x00, 0x00, 0x02, 0xf0, 0x02, 0xe0, 0x00, 0x02, 0xff, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x57, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0xe0, 0x00, 0x02, 0xff, 0xff, 0xfd, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x02, 0xf0, 0x02, 0xe0, 0x00, 0x00, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0xe0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x78, 0x00, 0x00, 0x00, 0x00, 0x02, 0xf0, 0x02, 0xe0, 0x00, 0x00, 0xbf, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0xe0, 0x00, 0x00, 0xbf, 0xff, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xf0, 0x02, 0xe0, 0x00, 0x00, 0xbf, 0xff, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x57, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0xe0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfd, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x57, 0x80, 0x00, 0x00, 0x00, 0x00, 0x02, 0xfa, 0xab, 0xe0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x5e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x5e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0xaa, 0x80, 0x00, 0x02, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0xff, 0xff, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2f, 0xff, 0xff, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x02, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x70, 0x00, 0x00, 0x00, 0x00, 0x0b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x2f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x70, 0x00, 0x00, 0x00, 0x00, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x78, 0x00, 0x00, 0x00, 0x02, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x7c, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x7c, 0x00, 0x00, 0x00, 0x0b, 0xff, 0xff, 0xfb, 0xbb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x5e, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x5e, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xfa, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x57, 0x00, 0x00, 0x00, 0x2f, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x57, 0x80, 0x00, 0x00, 0x2f, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0xe0, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x78, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x7c, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x5e, 0x00, 0x00, 0x2f, 0xff, 0xff, 0xff, 0xc3, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x57, 0x80, 0x00, 0x2f, 0xff, 0xff, 0xff, 0xc3, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x57, 0xe0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xc3, 0x83, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xf8, 0x00, 0x0b, 0xff, 0xff, 0xff, 0xc3, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x7e, 0x00, 0x0b, 0xff, 0xff, 0xea, 0x82, 0x83, 0xff, 0xff, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5f, 0x80, 0x02, 0xff, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x57, 0xe0, 0x00, 0xff, 0xff, 0xfa, 0xaa, 0xaf, 0xff, 0xff, 0xff, 0xfd, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x7e, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5f, 0x80, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x57, 0xf8, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x7f, 0xc0, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x57, 0xfe, 0x8b, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5f, 0xff, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x57, 0x77, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x75, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x75, 0x55, 0x55, 0x55, 
  0x55, 0x5f, 0xf5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x7d, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xdd, 0x55, 0x55, 0x55, 0x55, 0x57, 0xfd, 0x55, 0x55, 0x55, 
  0x57, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5f, 0xff, 0xfd, 0x55, 0x55, 0x55, 0x55, 0xfd, 0x55, 0x55, 0x55, 
  0x5f, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 0xfd, 0x55, 0x55, 0x55, 0x55, 0x55, 0x7f, 0xff, 0xff, 0x55, 0x55, 0x55, 0x55, 0xfd, 0x55, 0x55, 0x55, 
  0x5f, 0xfd, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 0xff, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5f, 0xff, 0xff, 0xd5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x7f, 0xd5, 0x55, 0x57, 0xff, 0xd5, 0x57, 0xff, 0xfd, 0x55, 0xff, 0xd5, 0x5f, 0x7f, 0x7f, 0xd5, 0x7f, 0xd5, 0x5f, 0xfd, 0x55, 0xf5, 0x57, 0xff, 0xd5, 
  0x7f, 0xd5, 0x55, 0x5f, 0xff, 0xfd, 0x5f, 0xff, 0xff, 0x57, 0xff, 0xfd, 0x7f, 0xff, 0x7f, 0xd5, 0x5f, 0xf5, 0xff, 0xff, 0xd5, 0xfd, 0x5f, 0xff, 0xf5, 
  0x7f, 0x55, 0x55, 0x5f, 0xff, 0xfd, 0x5f, 0xff, 0xfd, 0x5f, 0xf7, 0xfd, 0x5f, 0xff, 0x7f, 0xd5, 0x5f, 0xf5, 0xff, 0xff, 0xd7, 0xfd, 0x7f, 0xff, 0xfd, 
  0x7f, 0x55, 0x55, 0x7f, 0xd5, 0xff, 0x7f, 0xd5, 0xff, 0x5f, 0xd5, 0x7f, 0x7f, 0xf5, 0x5f, 0xd5, 0x5f, 0xf7, 0xfd, 0x5f, 0xf5, 0xfd, 0x7f, 0xd5, 0xfd, 
  0x7f, 0x55, 0x55, 0x7f, 0x55, 0xff, 0x7f, 0x55, 0xfd, 0x7f, 0xff, 0xff, 0x5f, 0xd5, 0x7f, 0xd5, 0x5f, 0xf7, 0xf5, 0x5f, 0xf7, 0xfd, 0x7f, 0x55, 0xff, 
  0x7f, 0xd5, 0x55, 0x7f, 0x55, 0xff, 0x7f, 0x55, 0xff, 0x7f, 0xff, 0xff, 0x7f, 0xd5, 0x5f, 0xd5, 0x5f, 0xf7, 0xf5, 0x57, 0xf5, 0xfd, 0x7f, 0x55, 0xff, 
  0x7f, 0xd5, 0x55, 0x7f, 0x55, 0xff, 0x7f, 0x55, 0xfd, 0x7f, 0xd5, 0x55, 0x5f, 0xd5, 0x7f, 0xd5, 0x7f, 0xd7, 0xf5, 0x5f, 0xf7, 0xfd, 0x7f, 0x55, 0xfd, 
  0x7f, 0xf5, 0x57, 0x7f, 0xd5, 0xfd, 0x7f, 0xd5, 0xff, 0x5f, 0xd5, 0x5d, 0x7f, 0xd5, 0x5f, 0xd5, 0xff, 0xd7, 0xfd, 0x5f, 0xf5, 0xfd, 0x7f, 0xd5, 0xfd, 
  0x5f, 0xff, 0xff, 0x5f, 0xff, 0xfd, 0x5f, 0xff, 0xfd, 0x5f, 0xff, 0xff, 0x5f, 0xd5, 0x7f, 0xff, 0xff, 0x55, 0xff, 0xff, 0xd7, 0xfd, 0x7f, 0xff, 0xfd, 
  0x57, 0xff, 0xff, 0x5f, 0xff, 0xfd, 0x5f, 0xff, 0xff, 0x57, 0xff, 0xfd, 0x7f, 0xd5, 0x5f, 0xff, 0xfd, 0x55, 0xff, 0xff, 0xd5, 0xfd, 0x5f, 0xff, 0xf5, 
  0x55, 0xff, 0xfd, 0x57, 0xff, 0xd5, 0x57, 0xff, 0x7d, 0x55, 0xff, 0xf5, 0x5f, 0x55, 0x5f, 0xff, 0xf5, 0x55, 0x5f, 0xfd, 0x57, 0xfd, 0x57, 0xff, 0xd5, 
  0x55, 0x57, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xfd, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x57, 0xfd, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xfd, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0xfd, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x57, 0x75, 0x55, 0x55, 0x5d, 0x55, 0x55, 0x75, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5f, 0x7d, 0x55, 0x55, 0x5d, 0x55, 0x55, 0x75, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5d, 0x57, 0x55, 0x55, 0x5d, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5f, 0x57, 0x57, 0xfd, 0x5d, 0x5f, 0xfd, 0x75, 0xd5, 0x75, 0xff, 0x5f, 0xd5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5d, 0x5d, 0x57, 0x5f, 0x5d, 0x75, 0x7d, 0x75, 0xd5, 0x75, 0xd5, 0xf5, 0x75, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5f, 0xff, 0x5d, 0x57, 0xdd, 0x75, 0x5d, 0x75, 0xd5, 0x75, 0xd5, 0xf5, 0x75, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5d, 0x57, 0x5d, 0xdd, 0xdd, 0xf5, 0x5d, 0x75, 0xd5, 0x75, 0xd5, 0x75, 0x75, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5f, 0x55, 0xdf, 0x77, 0x5d, 0x75, 0x5d, 0x75, 0xd5, 0x75, 0xd5, 0xf5, 0x75, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5d, 0x57, 0x5d, 0x55, 0x5d, 0xf5, 0x5d, 0x75, 0xd5, 0x75, 0xd5, 0x75, 0x75, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5f, 0x57, 0x57, 0x57, 0x5d, 0x7d, 0x7d, 0x75, 0xf5, 0xf5, 0xd5, 0xf5, 0x75, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x57, 0xfd, 0x57, 0xfd, 0x5d, 0x5f, 0xdd, 0x75, 0x7f, 0x55, 0xd5, 0x55, 0x75, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5d, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x75, 0x75, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x5f, 0xf5, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
  0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 
};

const lv_img_dsc_t logo_cdj_belgium_transparent_100_100 = {
  .header.cf = LV_IMG_CF_INDEXED_2BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 100,
  .header.h = 100,
  .data_size = 2516,
  .data = logo_cdj_belgium_transparent_100_100_map,
};
