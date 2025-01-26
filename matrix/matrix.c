/*
 * MAX7219 Led Matrix Module
 * https://github.com/kevinboone/Pico7219
 * https://kevinboone.me/pico7219.html
 */

#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>
#include "pico7219.h"
#include "font8.h"
#include "hardware/adc.h"

// MOSI pin, also called "TX" in the Pico pinout. Connects to the "DIN" pin on the MAX7219
#define MOSI 19

// SCK pin. Connects to the "CLOCK" pin on the MAX7219
#define SCK 18

// Chip-select pin. The same name is used on the Pico and the MAX7219
#define CS 17

// Number of 8x8 modules in the display chain
#define CHAIN_LEN 1

// SPI channel can be 0 or 1, and depends on the pins you've wired to MOSI, etc (see pinout diagram)
#define SPI_CHAN 0

#define LED1_PIN   16

typedef struct Pico7219 Pico7219;

#define ADC_NUM 0
#define ADC_PIN (26 + ADC_NUM)
#define ADC_VREF 3.3
#define ADC_RANGE (1 << 12)
#define ADC_CONVERT (ADC_VREF / (ADC_RANGE - 1))

#define SENSOR_PIN 1

// Draw a character to the library. Note that the width of the "virtual
// display" can be much longer than the physical module chain, and
// off-display elements can later be scrolled into view. However, it's
// the job of the application, not the library, to size the virtual
// display sufficiently to fit all the text in.
//
// chr is an offset in the font table, which starts with character 32 (space).
// It isn't an ASCII character.
void draw_character (Pico7219 *pico7219, uint8_t chr, int x_offset, BOOL flush)
{
	for (int i = 0; i < 8; i++) // row
    {
    	// The font elements are one byte wide even though, as its an 8x5 font,
    	//   only the top five bits of each byte are used.
    	uint8_t v = font8_table[8 * chr + i];
    	for (int j = 0; j < 8; j++) // column
      	{
      		int sel = 1 << j;
      		if (sel & v)
			{
        		pico7219_switch_on(pico7219, 7 - i, 7- j + x_offset, FALSE);
      		}
    	}
	}

  	if (flush)
	{
    	pico7219_flush (pico7219);
	}
}

void draw_number(Pico7219 *pico7219, int number)
{
	char num[10];
	sprintf(num, "%d", number);
	int l = strlen(num);
	for (int i = 0; i < l; ++i)
	{
		pico7219_switch_off_all(pico7219, FALSE);
		draw_character (pico7219, num[i] - ' ', 1, TRUE);
        sleep_ms(300);
	}

	pico7219_switch_off_all(pico7219, FALSE);
}

int main()
{
    gpio_init(LED1_PIN);

    gpio_set_dir(LED1_PIN, GPIO_OUT);

  	// Create the Pico7219 object, specifying the connected pins and
  	// baud rate. The last parameter indicates whether the column order
  	// should be reversed -- this depends on how the LED matrix is wired
  	// to the MAX7219, and isn't easy to determine except by trying.
	Pico7219 *pico7219 = pico7219_create(SPI_CHAN, 1500 * 1000,
    				MOSI, SCK, CS, CHAIN_LEN, FALSE);

  	pico7219_switch_off_all(pico7219, FALSE);
	pico7219_set_intensity(pico7219, 1);

	//adc_init();
    //adc_gpio_init(ADC_PIN);
    //adc_select_input(ADC_NUM);

    gpio_set_dir(SENSOR_PIN, GPIO_IN);

    while (true)
	{
        gpio_put(LED1_PIN, 1);
        sleep_ms(50);

		pico7219_switch_off_all (pico7219, FALSE);
		draw_character (pico7219, 'p' - ' ', 1, TRUE);
        sleep_ms(500);

		pico7219_switch_off_all(pico7219, FALSE);
		draw_character (pico7219, 'i' - ' ', 1, TRUE);
        sleep_ms(500);

		pico7219_switch_off_all(pico7219, FALSE);
		draw_character (pico7219, 'c' - ' ', 1, TRUE);
        sleep_ms(500);

		pico7219_switch_off_all(pico7219, FALSE);
		draw_character (pico7219, 'o' - ' ', 1, TRUE);
        sleep_ms(500);

		pico7219_switch_off_all(pico7219, TRUE);
        sleep_ms(100);

        gpio_put(LED1_PIN, 0);
        sleep_ms(150);

		for (int x = 0; x < 8; ++x)
		{
			for (int y = 0; y < 8; ++y)
			{
				pico7219_switch_off_all(pico7219, FALSE);
        		pico7219_switch_on(pico7219, x, y, TRUE);
		        sleep_ms(50);
			}
		}

		//uint adc_raw = (float)adc_read() * (float)ADC_CONVERT; // raw voltage from ADC
		//draw_number(pico7219, adc_raw);
		draw_number(pico7219, 2025);
        sleep_ms(500);

		pico7219_switch_off_all(pico7219, TRUE);
        sleep_ms(100);
    }

	// For completeness, but we never get here...
  	pico7219_destroy(pico7219, FALSE);
}

int mainX()
{
    gpio_init(LED1_PIN);

    gpio_set_dir(LED1_PIN, GPIO_OUT);

	Pico7219 *pico7219 = pico7219_create(SPI_CHAN, 1500 * 1000,
    				MOSI, SCK, CS, CHAIN_LEN, FALSE);

  	pico7219_switch_off_all(pico7219, FALSE);
	pico7219_set_intensity(pico7219, 1);

    gpio_set_dir(SENSOR_PIN, GPIO_IN);

    while (true)
	{
        gpio_put(LED1_PIN, 1);
        sleep_ms(50);
        gpio_put(LED1_PIN, 0);
        sleep_ms(50);

		pico7219_switch_off_all(pico7219, TRUE);

		int p = gpio_get(SENSOR_PIN);

		draw_number(pico7219, p);
        sleep_ms(100);

		pico7219_switch_off_all(pico7219, TRUE);
        sleep_ms(100);
    }

  	pico7219_destroy(pico7219, FALSE);
}
