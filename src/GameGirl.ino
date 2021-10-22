#include "Display.h"
#include "Sprite.h"

void setup() {
	Serial.begin(9600);
	while(!Serial);

	Display::init();
	drawShape();
	Display::update();
}

byte tetrominoL[] = {
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1
};

void drawShape() {
	Sprite* sprite = spriteFromArray(Position(5, 5), tetrominoL, 6, 4);
	Display::drawSprite(sprite);
}

// 0 = alpha | 1 = on  | 2 = off
Sprite* spriteFromArray(Position _pos, byte* _array, unsigned int _width, unsigned int _height) {
	List<Pixel> shapeList = List<Pixel>();
	for (unsigned int x = 0; x < _width; x++) {
		for (unsigned int y = 0; y < _height; y++) {
			byte cv = _array[(_width*y)+x];
			switch(cv) {
				case 0:
					continue;
				case 1:
					shapeList.add(Pixel(Position(x, _height-y-1), true));
					continue;
				case 2:
					shapeList.add(Pixel(Position(x, _height-y-1), false));
					continue;
			}
		}
	}
	return new Sprite(_pos, shapeList);
}

void loop() {
	
}