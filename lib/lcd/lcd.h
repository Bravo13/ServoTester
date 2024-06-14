#ifndef LCD_H
#define LCD_H

#include <Adafruit_TFTLCD.h>
#include <colors.h>

// Assign human-readable names to some common 16-bit color values:
unsigned long testText(Adafruit_TFTLCD *tft);
unsigned long testLines(Adafruit_TFTLCD *tft, uint16_t color);
unsigned long testFillScreen(Adafruit_TFTLCD *tft);
unsigned long testFastLines(Adafruit_TFTLCD *tft, uint16_t color1, uint16_t color2);
unsigned long testRects(Adafruit_TFTLCD *tft, uint16_t color);
unsigned long testFilledRects(Adafruit_TFTLCD *tft, uint16_t color1, uint16_t color2);
unsigned long testFilledCircles(Adafruit_TFTLCD *tft, uint8_t radius, uint16_t color);
unsigned long testCircles(Adafruit_TFTLCD *tft, uint8_t radius, uint16_t color);
unsigned long testTriangles(Adafruit_TFTLCD *tft);
unsigned long testFilledTriangles(Adafruit_TFTLCD *tft);
unsigned long testRoundRects(Adafruit_TFTLCD *tft);
unsigned long testFilledRoundRects(Adafruit_TFTLCD *tft);

#endif