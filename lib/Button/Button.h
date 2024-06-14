#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include <Adafruit_TFTLCD.h>
#include <TS.h>
#include <colors.h>

class Button {
	public:

	int x;
	int y;
	int width;
	int height;
	char *text;
	tColor bgColor;
	tColor textColor;

	bool visible;

	Button();
	Button(int xPos, int yPos, int butWidth, int butHeight, char *butText, tColor bgColor, tColor textColor);

	void initButton(Adafruit_TFTLCD *tft, int xPos, int yPos, int butWidth, int butHeight, char *butText);
	void render(Adafruit_TFTLCD *tft);
	void hide(Adafruit_TFTLCD *tft);
	bool is_clicked(ScreenPoint sp);

};

#endif