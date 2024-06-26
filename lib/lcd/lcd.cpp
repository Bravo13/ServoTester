#include "lcd.h"
#include <Adafruit_TFTLCD.h>

unsigned long testText(Adafruit_TFTLCD *tft) {
  tft->fillScreen(tColor::BLACK_COLOR);
  unsigned long start = micros();
  tft->setCursor(0, 0);
  tft->setTextColor(tColor::WHITE_COLOR);  tft->setTextSize(1);
  tft->println("Hello World!");
  tft->setTextColor(tColor::YELLOW_COLOR); tft->setTextSize(2);
  tft->println(1234.56);
  tft->setTextColor(tColor::RED_COLOR);    tft->setTextSize(3);
  tft->println(0xDEADBEEF, HEX);
  tft->println();
  tft->setTextColor(tColor::GREEN_COLOR);
  tft->setTextSize(5);
  tft->println("Groop");
  tft->setTextSize(2);
  tft->println("I implore thee,");
  tft->setTextSize(1);
  tft->println("my foonting turlingdromes.");
  tft->println("And hooptiously drangle me");
  tft->println("with crinkly bindlewurdles,");
  tft->println("Or I will rend thee");
  tft->println("in the gobberwarts");
  tft->println("with my blurglecruncheon,");
  tft->println("see if I don't!");
  return micros() - start;
}

unsigned long testLines(Adafruit_TFTLCD *tft, uint16_t color) {
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = tft->width(),
                h = tft->height();

  tft->fillScreen(tColor::BLACK_COLOR);

  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft->drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft->drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  tft->fillScreen(tColor::BLACK_COLOR);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft->drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft->drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft->fillScreen(tColor::BLACK_COLOR);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft->drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) tft->drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft->fillScreen(tColor::BLACK_COLOR);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) tft->drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) tft->drawLine(x1, y1, x2, y2, color);

  return micros() - start;
}

// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;
unsigned long testFillScreen(Adafruit_TFTLCD *tft) {
  unsigned long start = micros();
  tft->fillScreen(tColor::BLACK_COLOR);
  tft->fillScreen(tColor::RED_COLOR);
  tft->fillScreen(tColor::GREEN_COLOR);
  tft->fillScreen(tColor::BLUE_COLOR);
  tft->fillScreen(tColor::BLACK_COLOR);
  return micros() - start;
}

unsigned long testFastLines(Adafruit_TFTLCD *tft, uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = tft->width(), h = tft->height();

  tft->fillScreen(tColor::BLACK_COLOR);
  start = micros();
  for(y=0; y<h; y+=5) tft->drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) tft->drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

unsigned long testRects(Adafruit_TFTLCD *tft, uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = tft->width()  / 2,
                cy = tft->height() / 2;

  tft->fillScreen(tColor::BLACK_COLOR);
  n     = min(tft->width(), tft->height());
  start = micros();
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    tft->drawRect(cx-i2, cy-i2, i, i, color);
  }

  return micros() - start;
}

unsigned long testFilledRects(Adafruit_TFTLCD *tft, uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft->width()  / 2 - 1,
                cy = tft->height() / 2 - 1;

  tft->fillScreen(tColor::BLACK_COLOR);
  n = min(tft->width(), tft->height());
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    start = micros();
    tft->fillRect(cx-i2, cy-i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft->drawRect(cx-i2, cy-i2, i, i, color2);
  }

  return t;
}

unsigned long testFilledCircles(Adafruit_TFTLCD *tft, uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = tft->width(), h = tft->height(), r2 = radius * 2;

  tft->fillScreen(tColor::BLACK_COLOR);
  start = micros();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      tft->fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testCircles(Adafruit_TFTLCD *tft, uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                w = tft->width()  + radius,
                h = tft->height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      tft->drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testTriangles(Adafruit_TFTLCD *tft) {
  unsigned long start;
  int           n, i, cx = tft->width()  / 2 - 1,
                      cy = tft->height() / 2 - 1;

  tft->fillScreen(tColor::BLACK_COLOR);
  n     = min(cx, cy);
  start = micros();
  for(i=0; i<n; i+=5) {
    tft->drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      tft->color565(0, 0, i));
  }

  return micros() - start;
}

unsigned long testFilledTriangles(Adafruit_TFTLCD *tft) {
  unsigned long start, t = 0;
  int           i, cx = tft->width()  / 2 - 1,
                   cy = tft->height() / 2 - 1;

  tft->fillScreen(tColor::BLACK_COLOR);
  start = micros();
  for(i=min(cx,cy); i>10; i-=5) {
    start = micros();
    tft->fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft->color565(0, i, i));
    t += micros() - start;
    tft->drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      tft->color565(i, i, 0));
  }

  return t;
}

unsigned long testRoundRects(Adafruit_TFTLCD *tft) {
  unsigned long start;
  int           w, i, i2,
                cx = tft->width()  / 2 - 1,
                cy = tft->height() / 2 - 1;

  tft->fillScreen(tColor::BLACK_COLOR);
  w     = min(tft->width(), tft->height());
  start = micros();
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    tft->drawRoundRect(cx-i2, cy-i2, i, i, i/8, tft->color565(i, 0, 0));
  }

  return micros() - start;
}

unsigned long testFilledRoundRects(Adafruit_TFTLCD *tft) {
  unsigned long start;
  int           i, i2,
                cx = tft->width()  / 2 - 1,
                cy = tft->height() / 2 - 1;

  tft->fillScreen(tColor::BLACK_COLOR);
  start = micros();
  for(i=min(tft->width(), tft->height()); i>20; i-=6) {
    i2 = i / 2;
    tft->fillRoundRect(cx-i2, cy-i2, i, i, i/8, tft->color565(0, i, 0));
  }

  return micros() - start;
}