// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.

#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
#include <Servo.h>

#include <lcd.h>
#include <Button.h>
#include <pins.h>
#include <colors.h>

#define OPEN_SRV_POS 1500
#define CLOSE_SRV_POS 1000

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

ScreenPoint screen_point = ScreenPoint(&ts, &tft);

Button open_btn = Button(10, 10, 210, 70, "OPEN", tColor::GREEN_COLOR, tColor::BLACK_COLOR);
Button close_btn = Button(10, 90, 210, 70, "CLOSE", tColor::RED_COLOR, tColor::WHITE_COLOR);
Button opnrls_btn = Button(10, 180, 210, 120, "DROP", tColor::YELLOW_COLOR, tColor::BLACK_COLOR);

Servo srv;

uint8_t open_release_state = 0;

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
  open_btn.render(&tft);
  close_btn.render(&tft);
  opnrls_btn.render(&tft);

  srv.attach(SRV_PIN);
  srv.write(CLOSE_SRV_POS);
}

void loop(void) {
  tft.setCursor(0, 0);
  if(
    screen_point.is_touched()
    && open_release_state == 0
  ){
    screen_point.read_point();
    if( open_btn.is_clicked(screen_point)){
      Serial.println("Open clicked");
      srv.write(OPEN_SRV_POS);
    } else if( close_btn.is_clicked(screen_point)){
      Serial.println("Close clicked");
      srv.write(CLOSE_SRV_POS);
    } else if( opnrls_btn.is_clicked(screen_point)){
      Serial.println("Single Drop");
      srv.write(OPEN_SRV_POS);
      open_release_state = 30;
    }
  } else {
      if(
        open_release_state
        && --open_release_state == 0
      ){
        srv.write(CLOSE_SRV_POS);
      }
  }

  delay(1000/50);
}