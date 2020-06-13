/*********************************************************************
This is a library for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

These displays use SPI to communicate, 4 or 5 pins are required to
interface

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/
#ifndef _Adafruit_SSD1306_H_
#define _Adafruit_SSD1306_H_

#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "gpio_api.h"
#include "spi_api.h"
#include "i2c_api.h"
#include "gfxfont.h"

#define BLACK 0
#define WHITE 1
#define INVERSE 2

#define SSD1306_I2C_ADDRESS   0x78  // 011110+SA0+RW - 0x78 or 0x7A
// Address for 128x32 is 0x3C
// Address for 128x64 is 0x3D (default) or 0x3C (if SA0 is grounded)

/*=========================================================================
	SSD1306 Displays
	-----------------------------------------------------------------------
	The driver is used in multiple displays (128x64, 128x32, etc.).
	Select the appropriate display below to create an appropriately
	sized framebuffer, etc.

	SSD1306_128_64  128x64 pixel display

	SSD1306_128_32  128x32 pixel display

	SSD1306_96_16

	-----------------------------------------------------------------------*/
#define SSD1306_128_64
//#define SSD1306_128_32
//   #define SSD1306_96_16
/*=========================================================================*/

#if defined SSD1306_128_64 && defined SSD1306_128_32
#error "Only one SSD1306 display can be specified at once in SSD1306.h"
#endif
#if !defined SSD1306_128_64 && !defined SSD1306_128_32 && !defined SSD1306_96_16
#error "At least one SSD1306 display must be specified in SSD1306.h"
#endif

#if defined SSD1306_128_64
#define SSD1306_LCDWIDTH                  128
#define SSD1306_LCDHEIGHT                 64
#endif
#if defined SSD1306_128_32
#define SSD1306_LCDWIDTH                  128
#define SSD1306_LCDHEIGHT                 32
#endif
#if defined SSD1306_96_16
#define SSD1306_LCDWIDTH                  96
#define SSD1306_LCDHEIGHT                 16
#endif

#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF

#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

#define SSD1306_SETVCOMDETECT 0xDB

#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9

#define SSD1306_SETMULTIPLEX 0xA8

#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10

#define SSD1306_SETSTARTLINE 0x40

#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22

#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SEGREMAP 0xA0

#define SSD1306_CHARGEPUMP 0x8D

#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

typedef struct
{
	uint16_t                _width;		/* 幅ピクセル数 */
	uint16_t				_height;	/* 高さピクセル数 */
	int rotation;
	int8_t _i2caddr, _vccstate;
	gpio_t sid, sclk, dc, rst, cs;
	bool_t hwSPI;
	i2c_t i2c;
	spi_t spi;
} LCD_Handler_t;

void lcd_init1(LCD_Handler_t *lcd, int8_t SID, int8_t SCLK, int8_t DC, int8_t RST, int8_t CS);
void lcd_init2(LCD_Handler_t *lcd, int8_t DC, int8_t RST, int8_t CS);
//void lcd_init3(LCD_Handler_t *lcd, int8_t RST = -1);
void lcd_init3(LCD_Handler_t *lcd, int8_t RST);

//void lcd_begin(LCD_Handler_t *lcd, uint8_t switchvcc = SSD1306_SWITCHCAPVCC, uint8_t i2caddr = SSD1306_I2C_ADDRESS, bool_t reset = true);
void lcd_begin(LCD_Handler_t *lcd, uint8_t switchvcc, uint8_t i2caddr, bool_t reset);
void lcd_command(LCD_Handler_t *lcd, uint8_t c);

void lcd_clearDisplay(LCD_Handler_t *lcd);
void lcd_invertDisplay(LCD_Handler_t *lcd, uint8_t i);
void lcd_display(LCD_Handler_t *lcd);

void lcd_startscrollright(LCD_Handler_t *lcd, uint8_t start, uint8_t stop);
void lcd_startscrollleft(LCD_Handler_t *lcd, uint8_t start, uint8_t stop);

void lcd_startscrolldiagright(LCD_Handler_t *lcd, uint8_t start, uint8_t stop);
void lcd_startscrolldiagleft(LCD_Handler_t *lcd, uint8_t start, uint8_t stop);
void lcd_stopscroll(LCD_Handler_t *lcd);

void lcd_dim(LCD_Handler_t *lcd, bool_t dim);

void lcd_drawPixel(LCD_Handler_t *lcd, int16_t x, int16_t y, uint16_t color);

void lcd_drawFastVLine(LCD_Handler_t *lcd, int16_t x, int16_t y, int16_t h, uint16_t color);
void lcd_drawFastHLine(LCD_Handler_t *lcd, int16_t x, int16_t y, int16_t w, uint16_t color);

void lcd_drawFastVLineInternal(LCD_Handler_t *lcd, int16_t x, int16_t y, int16_t h, uint16_t color);
void lcd_drawFastHLineInternal(LCD_Handler_t *lcd, int16_t x, int16_t y, int16_t w, uint16_t color);

#endif /* _Adafruit_SSD1306_H_ */
