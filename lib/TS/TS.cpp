#include <TS.h>

ScreenPoint::ScreenPoint(TouchScreen *pTs, Adafruit_TFTLCD *pTft){
	this->pTs = pTs;
	this->pTft = pTft;
}

bool ScreenPoint::is_touched(){
	TSPoint p = read_point_raw();
	if( !touched && (p.z > PRESS_MIN) ){
		delay(PRESS_DEBOUNSE_MS);
		p = read_point_raw();
		touched = p.z > PRESS_MIN;
	} else {
		if(touched){
			delay(PRESS_DEBOUNSE_MS);
			p = read_point_raw();
			touched = p.z > PRESS_MIN;
		}
	}
	return touched;
}

TSPoint ScreenPoint::read_point_raw() {
	digitalWrite(13, HIGH);
	TSPoint p = pTs->getPoint();
	digitalWrite(13, LOW);
	pinMode(XM, OUTPUT);
	pinMode(YP, OUTPUT);
	x = p.x;
	y = p.y;
	z = p.z;

	return p;
}

void ScreenPoint::read_point(){
	uint8_t rotation = pTft->getRotation();
	int a = x;
	switch(rotation){
		case 0:
			scaled_x = map(x, TS_MINX, TS_MAXX, 0, pTft->width());
			scaled_y = map(y, TS_MINY, TS_MAXY, pTft->height(), 0);
			break;
		case 1:
			x = y;
			y = a;
			scaled_x = map(y, TS_MINY, TS_MAXY, pTft->width(), 0);
			scaled_y = map(x, TS_MINX, TS_MAXX, pTft->height(), 0);
			break;
		case 2:
			scaled_x = map(x, TS_MINY, TS_MAXY, pTft->width(), 0);
			scaled_y = map(y, TS_MINX, TS_MAXX, 0, pTft->height());
			break;
		case 3:
			x = y;
			y = a;
			scaled_x = map(y, TS_MINY, TS_MAXY, 0, pTft->width());
			scaled_y = map(x, TS_MINX, TS_MAXX, 0, pTft->height());
			break;
	}
}