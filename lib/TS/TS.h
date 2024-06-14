#ifndef TS_H
#define TS_H

#include <Arduino.h>
#include <TouchScreen.h>
#include <Adafruit_TFTLCD.h>
#include <pins.h>

#define TS_MINX 120
#define TS_MAXX 910

#define TS_MINY 120
#define TS_MAXY 910

#define PRESS_MIN 150
#define PRESS_DEBOUNSE_MS 50

class ScreenPoint {
	public:
		int16_t x;
		int16_t y;

		int16_t scaled_x;
		int16_t scaled_y;

		int16_t z;

		bool touched;

		ScreenPoint(TouchScreen *pTs, Adafruit_TFTLCD *pTft);
		bool is_touched();
		TSPoint read_point_raw();
		void read_point();

	private:
		TouchScreen *pTs;
		Adafruit_TFTLCD *pTft;
};

#endif