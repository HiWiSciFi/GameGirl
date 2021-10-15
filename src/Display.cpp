#include "Display.h"

namespace Display {
	LedControl lcrs[] = {
		LedControl(4, 5, 6, DEVICE_COUNT),
		LedControl(7, 8, 9, DEVICE_COUNT),
		LedControl(10, 11, 12, DEVICE_COUNT)
	};

	byte displayBuffer[] = {
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,

		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,

		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000,
		B00000000,    B00000000,    B00000000,    B00000000
	};

	byte affectedRows[] = {
		B00000000,
		B00000000,
		B00000000,
		B00000000,

		B00000000,
		B00000000,
		B00000000,
		B00000000,

		B00000000,
		B00000000,
		B00000000,
		B00000000
	};
}

void Display::init() {
	for (int d = 0; d < LCR_COUNT; d++) {
		for(int index = 0; index < DEVICE_COUNT; index++) {
			lcrs[d].shutdown(index, false);
			lcrs[d].setIntensity(index, 0);
			lcrs[d].clearDisplay(index);
    	}
	}
}

void Display::test() {
	for (int x = 0; x < 32; x++) {
		for (int y = 0; y < 24; y++) {
			drawPixel(x, y, true);
		}
	}
}

void Display::update() {
	update(false);
}

void Display::update(bool writeFullBuffer) {
	if (writeFullBuffer) {
		for (int d = 0; d < LCR_COUNT; d++) {
			for (int i = 0; i < 4; i++) {
				for (int r = 0; r < 8; r++) {
					lcrs[d].setRow(i, r, displayBuffer[(32 * d) + (8 * i) + r]);
				}
			}
		}
		for (byte i = 0; i < sizeof(affectedRows); i++) {
			affectedRows[i] = B00000000;
		}

	} else {
		for (int d = 0; d < LCR_COUNT; d++) {

			for (int i = 0; i < 4; i++) {
				
				int affectedRowIndex = (4 * d) + i;
				byte currentRowVal = affectedRows[affectedRowIndex];
				
				if (currentRowVal != B00000000) {
					for (int r = 0; r < 8; r++) {
						if (currentRowVal & (B00000001 << r)) {
							Serial.print("-");
							lcrs[d].setRow(i, r, displayBuffer[(32 * d) + (8 * i) + r]);
						}
					}
					affectedRows[affectedRowIndex] = B00000000;
				}
			}
		}
	}
}

void Display::drawPixel(const int x, const int y, const bool state) {
	int displayRow = y >> 3;
	int displayIndex = x >> 3;

	int localY = y - (displayRow << 3);
	int localX = x - (displayIndex << 3);

	int displayBufferIndex = (32 * displayRow) + (8 * displayIndex) + localY;
	byte currentBufferRowVal = displayBuffer[displayBufferIndex];

	if ((currentBufferRowVal >> localX) != state) {
		if (state)
			displayBuffer[displayBufferIndex] = currentBufferRowVal | (1 << localX);
		else
			displayBuffer[displayBufferIndex] = currentBufferRowVal & (~1 << localX);

		int affectedRowIndex = (4 * displayRow) + displayIndex;
		byte affectedRow = affectedRows[affectedRowIndex];
		affectedRows[affectedRowIndex] = affectedRow | (1 << localY);
	}
}

void Display::drawSprite(Sprite* sprite) {
	int lsize = sprite->spriteData.size();
	for (int i = 0; i < lsize; i++) {
		Pixel px = *(sprite->spriteData.get(i));
		drawPixel(sprite->pos.x + px.pos.x, sprite->pos.y + px.pos.y, px.state);
		Serial.print(sprite->pos.x + px.pos.x);
		Serial.print(":");
		Serial.print(sprite->pos.y + px.pos.y);
		Serial.print(":");
		Serial.println(px.state);
	}
}