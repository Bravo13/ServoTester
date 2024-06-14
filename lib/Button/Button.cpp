#include <Button.h>

Button::Button() {}

Button::Button(int xPos, int yPos, int butWidth, int butHeight, char *butText, tColor iBgColor, tColor iTextColor){
	x = xPos;
	y = yPos;
	width = butWidth;
	height = butHeight;
	text = butText;
	visible = false;
	bgColor = iBgColor;
	textColor = iTextColor;
}

void Button::render(Adafruit_TFTLCD *tft){
	tft->fillRect(x,y,width,height, bgColor); // draw rectangle
	tft->setCursor(x+5,y+5);
	tft->setTextSize(2);
	tft->setTextColor(textColor);
	tft->print(text);
	visible = true;
}

void Button::hide(Adafruit_TFTLCD *tft) {
	visible = false;
	tft->fillRect(x,y,width,height, tColor::BLACK_COLOR); // draw rectangle
}

bool Button::is_clicked(ScreenPoint sp){
	if(!visible) return false;
	if (
		(sp.scaled_x >= x)
		&& (sp.scaled_x <= (x+width))
		&& (sp.scaled_y >= y)
		&& (sp.scaled_y <= (y+height))
	){
		return true;
	}
	else {
		return false;
	}
}