// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.

#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

#include <lcd.h>
#include <Button.h>
#include <pins.h>
#include <colors.h>

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

ScreenPoint screen_point = ScreenPoint(&ts, &tft);

Button run_btn = Button(10, 10, 210, 70, "RUN", tColor::GREEN_COLOR, tColor::WHITE_COLOR);
Button stop_btn = Button(10, 10, 210, 70, "STOP", tColor::RED_COLOR, tColor::WHITE_COLOR);

void setup(void) {
  Serial.begin(115200);
  Serial.println(F("TFT LCD test"));

#ifdef USE_ADAFRUIT_SHIELD_PINOUT
  Serial.println(F("Using Adafruit 2.8\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Adafruit 2.8\" TFT Breakout Board Pinout"));
#endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

  uint16_t identifier = tft.readID();

  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    return;
  }

  tft.begin(identifier);
  tft.fillScreen(tColor::BLACK_COLOR);
  tft.setRotation(2);
  tft.drawLine(5, 5, tft.width()-5, 5, tColor::GREEN_COLOR);
  tft.drawLine(5, 5, 5, tft.height()-5, tColor::RED_COLOR);
  tft.setCursor(50, 50);
  tft.setTextColor(tColor::WHITE_COLOR, tColor::BLACK_COLOR);
  tft.setTextSize(1);
  run_btn.render(&tft);
}

void loop(void) {
  tft.setCursor(0, 0);
  if(screen_point.is_touched()){
    screen_point.read_point();
    if(run_btn.is_clicked(screen_point)) {
      Serial.println("Run clicked");
      run_btn.hide(&tft);
      stop_btn.render(&tft);
    } else if( stop_btn.is_clicked(screen_point)){
      Serial.println("Stop clicked");
      stop_btn.hide(&tft);
      run_btn.render(&tft);
    }
    Serial.println(screen_point.z);
    /*
    char str[20];
    sprintf(str, "X=%d, Y=%d", screen_point.x, screen_point.y);
    tft.print(str);
    */
  } else{
    tft.print("Not Touching");
  }

  delay(1000/50);
}