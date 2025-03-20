/**
 * SSD1306 OLED driver for Raspberry Pi Pico
 * 
 * Based on Raspberry Pi Pico SDK examples and various SSD1306 implementations
 */

 #ifndef _SSD1306_H_
 #define _SSD1306_H_
 
 #include <stdbool.h>
 #include <stdint.h>
 #include "hardware/i2c.h"
 #include "pico/stdlib.h"
 
 // SSD1306 commands
 #define SSD1306_SET_CONTRAST            0x81
 #define SSD1306_DISPLAY_RAM             0xA4
 #define SSD1306_DISPLAY_ALLON           0xA5
 #define SSD1306_DISPLAY_NORMAL          0xA6
 #define SSD1306_DISPLAY_INVERTED        0xA7
 #define SSD1306_DISPLAY_OFF             0xAE
 #define SSD1306_DISPLAY_ON              0xAF
 #define SSD1306_SET_MEM_ADDR_MODE       0x20
 #define SSD1306_SET_COLUMN_ADDR         0x21
 #define SSD1306_SET_PAGE_ADDR           0x22
 #define SSD1306_SET_START_LINE          0x40
 #define SSD1306_SET_SEGMENT_REMAP_0     0xA0
 #define SSD1306_SET_SEGMENT_REMAP_1     0xA1
 #define SSD1306_SET_MULTIPLEX_RATIO     0xA8
 #define SSD1306_SET_COM_SCAN_DIR_NORMAL 0xC0
 #define SSD1306_SET_COM_SCAN_DIR_REMAP  0xC8
 #define SSD1306_SET_DISPLAY_OFFSET      0xD3
 #define SSD1306_SET_COM_PINS            0xDA
 #define SSD1306_SET_DISP_CLOCK_DIV      0xD5
 #define SSD1306_SET_PRECHARGE           0xD9
 #define SSD1306_SET_VCOM_DESELECT       0xDB
 #define SSD1306_SET_CHARGE_PUMP         0x8D
 #define SSD1306_DEACTIVATE_SCROLL       0x2E
 
 // Display parameters
 #define SSD1306_PAGE_HEIGHT             8
 #define SSD1306_MAX_PAGE                8
 
 // Structure to hold display information
 typedef struct {
     uint8_t width;          // Display width
     uint8_t height;         // Display height
     uint8_t pages;          // Number of pages (height / 8)
     uint8_t address;        // I2C address
     i2c_inst_t *i2c_inst;   // I2C instance
     uint8_t *buffer;        // Display buffer
     size_t bufsize;         // Buffer size
 } ssd1306_t;
 
 /**
  * Initialize the OLED display
  */
 void ssd1306_init(ssd1306_t *display, uint8_t width, uint8_t height, uint8_t address, i2c_inst_t *i2c_inst);
 
 /**
  * Free resources
  */
 void ssd1306_deinit(ssd1306_t *display);
 
 /**
  * Clear display buffer (fill with black)
  */
 void ssd1306_clear(ssd1306_t *display);
 
 /**
  * Write display buffer to OLED
  */
 void ssd1306_show(ssd1306_t *display);
 
 /**
  * Set a single pixel in the buffer
  */
 void ssd1306_draw_pixel(ssd1306_t *display, uint8_t x, uint8_t y, bool color);
 
 /**
  * Draw a horizontal line
  */
 void ssd1306_draw_hline(ssd1306_t *display, uint8_t x, uint8_t y, uint8_t w, bool color);
 
 /**
  * Draw a vertical line
  */
 void ssd1306_draw_vline(ssd1306_t *display, uint8_t x, uint8_t y, uint8_t h, bool color);
 
 /**
  * Draw a line
  */
 void ssd1306_draw_line(ssd1306_t *display, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color);
 
 /**
  * Draw a rectangle
  */
 void ssd1306_draw_rect(ssd1306_t *display, uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool color);
 
 /**
  * Draw a filled rectangle
  */
 void ssd1306_draw_filled_rect(ssd1306_t *display, uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool color);
 
 /**
  * Draw a character
  */
 void ssd1306_draw_char(ssd1306_t *display, uint8_t x, uint8_t y, uint8_t scale, char c);
 
 /**
  * Draw a string
  */
 void ssd1306_draw_string(ssd1306_t *display, uint8_t x, uint8_t y, uint8_t scale, const char *s);
 
 #endif // _SSD1306_H_