/**
 * SSD1306 OLED driver implementation for Raspberry Pi Pico
 */

 #include "ssd1306.h"
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>
 
 // 5x8 ASCII font data
 static const uint8_t font5x8[] = {
     0x00, 0x00, 0x00, 0x00, 0x00, // Space
     0x00, 0x00, 0x5F, 0x00, 0x00, // !
     0x00, 0x07, 0x00, 0x07, 0x00, // "
     0x14, 0x7F, 0x14, 0x7F, 0x14, // #
     0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
     0x23, 0x13, 0x08, 0x64, 0x62, // %
     0x36, 0x49, 0x55, 0x22, 0x50, // &
     0x00, 0x05, 0x03, 0x00, 0x00, // '
     0x00, 0x1C, 0x22, 0x41, 0x00, // (
     0x00, 0x41, 0x22, 0x1C, 0x00, // )
     0x08, 0x2A, 0x1C, 0x2A, 0x08, // *
     0x08, 0x08, 0x3E, 0x08, 0x08, // +
     0x00, 0x50, 0x30, 0x00, 0x00, // ,
     0x08, 0x08, 0x08, 0x08, 0x08, // -
     0x00, 0x60, 0x60, 0x00, 0x00, // .
     0x20, 0x10, 0x08, 0x04, 0x02, // /
     0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
     0x00, 0x42, 0x7F, 0x40, 0x00, // 1
     0x42, 0x61, 0x51, 0x49, 0x46, // 2
     0x21, 0x41, 0x45, 0x4B, 0x31, // 3
     0x18, 0x14, 0x12, 0x7F, 0x10, // 4
     0x27, 0x45, 0x45, 0x45, 0x39, // 5
     0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
     0x01, 0x71, 0x09, 0x05, 0x03, // 7
     0x36, 0x49, 0x49, 0x49, 0x36, // 8
     0x06, 0x49, 0x49, 0x29, 0x1E, // 9
     0x00, 0x36, 0x36, 0x00, 0x00, // :
     0x00, 0x56, 0x36, 0x00, 0x00, // ;
     0x00, 0x08, 0x14, 0x22, 0x41, // <
     0x14, 0x14, 0x14, 0x14, 0x14, // =
     0x41, 0x22, 0x14, 0x08, 0x00, // >
     0x02, 0x01, 0x51, 0x09, 0x06, // ?
     0x32, 0x49, 0x79, 0x41, 0x3E, // @
     0x7E, 0x11, 0x11, 0x11, 0x7E, // A
     0x7F, 0x49, 0x49, 0x49, 0x36, // B
     0x3E, 0x41, 0x41, 0x41, 0x22, // C
     0x7F, 0x41, 0x41, 0x22, 0x1C, // D
     0x7F, 0x49, 0x49, 0x49, 0x41, // E
     0x7F, 0x09, 0x09, 0x01, 0x01, // F
     0x3E, 0x41, 0x41, 0x49, 0x7A, // G
     0x7F, 0x08, 0x08, 0x08, 0x7F, // H
     0x00, 0x41, 0x7F, 0x41, 0x00, // I
     0x20, 0x40, 0x41, 0x3F, 0x01, // J
     0x7F, 0x08, 0x14, 0x22, 0x41, // K
     0x7F, 0x40, 0x40, 0x40, 0x40, // L
     0x7F, 0x02, 0x04, 0x02, 0x7F, // M
     0x7F, 0x04, 0x08, 0x10, 0x7F, // N
     0x3E, 0x41, 0x41, 0x41, 0x3E, // O
     0x7F, 0x09, 0x09, 0x09, 0x06, // P
     0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
     0x7F, 0x09, 0x19, 0x29, 0x46, // R
     0x46, 0x49, 0x49, 0x49, 0x31, // S
     0x01, 0x01, 0x7F, 0x01, 0x01, // T
     0x3F, 0x40, 0x40, 0x40, 0x3F, // U
     0x1F, 0x20, 0x40, 0x20, 0x1F, // V
     0x7F, 0x20, 0x18, 0x20, 0x7F, // W
     0x63, 0x14, 0x08, 0x14, 0x63, // X
     0x03, 0x04, 0x78, 0x04, 0x03, // Y
     0x61, 0x51, 0x49, 0x45, 0x43, // Z
     0x00, 0x00, 0x7F, 0x41, 0x41, // [
     0x02, 0x04, 0x08, 0x10, 0x20, // "\"
     0x41, 0x41, 0x7F, 0x00, 0x00, // ]
     0x04, 0x02, 0x01, 0x02, 0x04, // ^
     0x40, 0x40, 0x40, 0x40, 0x40, // _
     0x00, 0x01, 0x02, 0x04, 0x00, // `
     0x20, 0x54, 0x54, 0x54, 0x78, // a
     0x7F, 0x48, 0x44, 0x44, 0x38, // b
     0x38, 0x44, 0x44, 0x44, 0x20, // c
     0x38, 0x44, 0x44, 0x48, 0x7F, // d
     0x38, 0x54, 0x54, 0x54, 0x18, // e
     0x08, 0x7E, 0x09, 0x01, 0x02, // f
     0x08, 0x14, 0x54, 0x54, 0x3C, // g
     0x7F, 0x08, 0x04, 0x04, 0x78, // h
     0x00, 0x44, 0x7D, 0x40, 0x00, // i
     0x20, 0x40, 0x44, 0x3D, 0x00, // j
     0x00, 0x7F, 0x10, 0x28, 0x44, // k
     0x00, 0x41, 0x7F, 0x40, 0x00, // l
     0x7C, 0x04, 0x18, 0x04, 0x78, // m
     0x7C, 0x08, 0x04, 0x04, 0x78, // n
     0x38, 0x44, 0x44, 0x44, 0x38, // o
     0x7C, 0x14, 0x14, 0x14, 0x08, // p
     0x08, 0x14, 0x14, 0x18, 0x7C, // q
     0x7C, 0x08, 0x04, 0x04, 0x08, // r
     0x48, 0x54, 0x54, 0x54, 0x20, // s
     0x04, 0x3F, 0x44, 0x40, 0x20, // t
     0x3C, 0x40, 0x40, 0x20, 0x7C, // u
     0x1C, 0x20, 0x40, 0x20, 0x1C, // v
     0x3C, 0x40, 0x30, 0x40, 0x3C, // w
     0x44, 0x28, 0x10, 0x28, 0x44, // x
     0x0C, 0x50, 0x50, 0x50, 0x3C, // y
     0x44, 0x64, 0x54, 0x4C, 0x44, // z
     0x00, 0x08, 0x36, 0x41, 0x00, // {
     0x00, 0x00, 0x7F, 0x00, 0x00, // |
     0x00, 0x41, 0x36, 0x08, 0x00, // }
     0x08, 0x04, 0x08, 0x10, 0x08, // ~
     0x00, 0x00, 0x00, 0x00, 0x00
 };
 
 // Send command to SSD1306
 static void ssd1306_command(ssd1306_t *display, uint8_t command) {
     uint8_t buf[2] = {0x00, command}; // Control byte (0x00) for command, then actual command
     i2c_write_blocking(display->i2c_inst, display->address, buf, 2, false);
 }
 
 // Send data to SSD1306
 static void ssd1306_data(ssd1306_t *display, const uint8_t *data, size_t len) {
     uint8_t *buf = malloc(len + 1);
     if (buf) {
         buf[0] = 0x40; // Control byte (0x40) for data
         memcpy(buf + 1, data, len);
         i2c_write_blocking(display->i2c_inst, display->address, buf, len + 1, false);
         free(buf);
     }
 }
 
 // Initialize the OLED display
 void ssd1306_init(ssd1306_t *display, uint8_t width, uint8_t height, uint8_t address, i2c_inst_t *i2c_inst) {
     display->width = width;
     display->height = height;
     display->pages = height / SSD1306_PAGE_HEIGHT;
     display->address = address;
     display->i2c_inst = i2c_inst;
     
     // Allocate buffer
     display->bufsize = (width * height) / 8;
     display->buffer = malloc(display->bufsize);
     if (!display->buffer) {
         printf("Failed to allocate memory for display buffer\n");
         return;
     }
     
     // Clear buffer
     memset(display->buffer, 0, display->bufsize);
     
     // Initialize display
     ssd1306_command(display, SSD1306_DISPLAY_OFF);                    // 0xAE - Display off
     ssd1306_command(display, SSD1306_SET_DISP_CLOCK_DIV);            // 0xD5 - Set clock div
     ssd1306_command(display, 0x80);                                   // Default value
     ssd1306_command(display, SSD1306_SET_MULTIPLEX_RATIO);           // 0xA8 - Set multiplex ratio
     ssd1306_command(display, display->height - 1);                    // Height - 1
     ssd1306_command(display, SSD1306_SET_DISPLAY_OFFSET);            // 0xD3 - Set display offset
     ssd1306_command(display, 0x00);                                   // No offset
     ssd1306_command(display, SSD1306_SET_START_LINE | 0x00);         // 0x40 - Set start line to 0
     ssd1306_command(display, SSD1306_SET_CHARGE_PUMP);               // 0x8D - Set charge pump
     ssd1306_command(display, 0x14);                                   // Enable charge pump
     ssd1306_command(display, SSD1306_SET_MEM_ADDR_MODE);             // 0x20 - Memory addressing mode
     ssd1306_command(display, 0x00);                                   // Horizontal addressing mode
     ssd1306_command(display, SSD1306_SET_SEGMENT_REMAP_1);           // 0xA1 - Flip horizontally
     ssd1306_command(display, SSD1306_SET_COM_SCAN_DIR_REMAP);        // 0xC8 - Flip vertically
     
     // Set COM pins hardware configuration
     ssd1306_command(display, SSD1306_SET_COM_PINS);                  // 0xDA
     if (display->height == 32) {
         ssd1306_command(display, 0x02);                              // Sequential COM, no remap
     } else {
         ssd1306_command(display, 0x12);                              // Alt COM, no remap
     }
     
     ssd1306_command(display, SSD1306_SET_CONTRAST);                  // 0x81 - Set contrast
     ssd1306_command(display, 0xCF);                                   // High contrast
     ssd1306_command(display, SSD1306_SET_PRECHARGE);                 // 0xD9 - Set precharge period
     ssd1306_command(display, 0xF1);                                   // High phase 2
     ssd1306_command(display, SSD1306_SET_VCOM_DESELECT);             // 0xDB - Set VCOMH deselect level
     ssd1306_command(display, 0x40);                                   // Default value
     ssd1306_command(display, SSD1306_DISPLAY_RAM);                   // 0xA4 - Display from RAM
     ssd1306_command(display, SSD1306_DISPLAY_NORMAL);                // 0xA6 - Normal display
     ssd1306_command(display, SSD1306_DEACTIVATE_SCROLL);             // 0x2E - Deactivate scroll
     ssd1306_command(display, SSD1306_DISPLAY_ON);                    // 0xAF - Display on
     
     // Clear display
     ssd1306_clear(display);
     ssd1306_show(display);
 }
 
 // Free resources
 void ssd1306_deinit(ssd1306_t *display) {
     if (display->buffer) {
         free(display->buffer);
         display->buffer = NULL;
     }
 }
 
 // Clear display buffer (fill with black)
 void ssd1306_clear(ssd1306_t *display) {
     memset(display->buffer, 0, display->bufsize);
 }
 
 // Write display buffer to OLED
 void ssd1306_show(ssd1306_t *display) {
     // Set column address range
     ssd1306_command(display, SSD1306_SET_COLUMN_ADDR);
     ssd1306_command(display, 0);                          // Start at column 0
     ssd1306_command(display, display->width - 1);         // End at last column
     
     // Set page address range
     ssd1306_command(display, SSD1306_SET_PAGE_ADDR);
     ssd1306_command(display, 0);                          // Start at page 0
     ssd1306_command(display, display->pages - 1);         // End at last page
     
     // Send the buffer
     ssd1306_data(display, display->buffer, display->bufsize);
 }
 
 // Set a single pixel in the buffer
 void ssd1306_draw_pixel(ssd1306_t *display, uint8_t x, uint8_t y, bool color) {
     if (x >= display->width || y >= display->height) return;
     
     // Calculate buffer position and bit
     uint16_t byte_pos = x + (y / 8) * display->width;
     uint8_t bit_pos = y % 8;
     
     if (color) {
         display->buffer[byte_pos] |= (1 << bit_pos);  // Set bit
     } else {
         display->buffer[byte_pos] &= ~(1 << bit_pos); // Clear bit
     }
 }
 
 // Draw a horizontal line
 void ssd1306_draw_hline(ssd1306_t *display, uint8_t x, uint8_t y, uint8_t w, bool color) {
     for (uint8_t i = 0; i < w; i++) {
         ssd1306_draw_pixel(display, x + i, y, color);
     }
 }
 
 // Draw a vertical line
 void ssd1306_draw_vline(ssd1306_t *display, uint8_t x, uint8_t y, uint8_t h, bool color) {
     for (uint8_t i = 0; i < h; i++) {
         ssd1306_draw_pixel(display, x, y + i, color);
     }
 }
 
 // Draw a line using Bresenham's algorithm
 void ssd1306_draw_line(ssd1306_t *display, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color) {
     int8_t dx = abs(x1 - x0);
     int8_t sx = x0 < x1 ? 1 : -1;
     int8_t dy = -abs(y1 - y0);
     int8_t sy = y0 < y1 ? 1 : -1;
     int16_t err = dx + dy;
     int16_t e2;
     
     while (true) {
         ssd1306_draw_pixel(display, x0, y0, color);
         if (x0 == x1 && y0 == y1) break;
         e2 = 2 * err;
         if (e2 >= dy) {
             if (x0 == x1) break;
             err += dy;
             x0 += sx;
         }
         if (e2 <= dx) {
             if (y0 == y1) break;
             err += dx;
             y0 += sy;
         }
     }
 }
 
 // Draw a rectangle
 void ssd1306_draw_rect(ssd1306_t *display, uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool color) {
     ssd1306_draw_hline(display, x, y, w, color);
     ssd1306_draw_hline(display, x, y + h - 1, w, color);
     ssd1306_draw_vline(display, x, y, h, color);
     ssd1306_draw_vline(display, x + w - 1, y, h, color);
 }
 
 // Draw a filled rectangle
 void ssd1306_draw_filled_rect(ssd1306_t *display, uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool color) {
     for (uint8_t i = 0; i < h; i++) {
         ssd1306_draw_hline(display, x, y + i, w, color);
     }
 }
 
 // Draw a character
 void ssd1306_draw_char(ssd1306_t *display, uint8_t x, uint8_t y, uint8_t scale, char c) {
     // Get ASCII value
     c = (c >= ' ' && c <= '~') ? c - ' ' : 0;
     
     // Get font data
     const uint8_t *char_data = &font5x8[c * 5];
     
     // Draw each column
     for (uint8_t col = 0; col < 5; col++) {
         uint8_t line = char_data[col];
         for (uint8_t row = 0; row < 8; row++) {
             if (line & (1 << row)) {
                 if (scale == 1) {
                     ssd1306_draw_pixel(display, x + col, y + row, true);
                 } else {
                     ssd1306_draw_filled_rect(display, x + col * scale, y + row * scale, scale, scale, true);
                 }
             }
         }
     }
 }
 
 // Draw a string
 void ssd1306_draw_string(ssd1306_t *display, uint8_t x, uint8_t y, uint8_t scale, const char *s) {
     uint8_t x_pos = x;
     
     while (*s) {
         ssd1306_draw_char(display, x_pos, y, scale, *s);
         x_pos += 6 * scale; // 5 pixels for character + 1 pixel spacing
         s++;
     }
 }