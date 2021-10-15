#include "Display.h"
#include "Sprite.h"

void setup() {
	Serial.begin(9600);
	while(!Serial);

	Display::init();
	Serial.println("DInfo1");
	drawShape();
	Serial.println("DInfo2");
	Display::update();
	Serial.println("DInfo3");
}

void drawShape() {
	List<Pixel> shape = List<Pixel>();
	shape.add(Pixel(Position(0, 0), true));
	shape.add(Pixel(Position(0, 1), true));
	shape.add(Pixel(Position(1, 0), true));
	shape.add(Pixel(Position(1, 1), true));

	Sprite* sprite = new Sprite(Position(5, 5), shape);
	Display::drawSprite(sprite);
}

void loop() {
	
}