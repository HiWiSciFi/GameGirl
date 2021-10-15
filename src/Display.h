#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <LedControl.h>
#include "Sprite.h"

namespace Display {
	const byte LCR_COUNT = 3;
	const byte DEVICE_COUNT = 4;

	void init();
	void test();
	void update();
	void update(bool);
	void drawPixel(const int, const int, const bool);
	void drawSprite(Sprite* sprite);
}

#endif