#ifndef _SPRITE_H
#define _SPRITE_H

#include "List.h"
#include <math.h>

struct Position {
	int x;
	int y;

	Position() {
		x = 0;
		y = 0;
	}

	Position(int _x, int _y) {
		x = _x;
		y = _y;
	}
};

struct Pixel {
	Position pos;
	bool state;

	Pixel() {
		this->pos = Position();
		this->state = false;
	}

	Pixel(Position _pos, bool _state) {
		pos = _pos;
		state = _state;
	}
};

struct Rectangle {
	Position pos1;
	Position pos2;

	Rectangle() {
		pos1 = Position();
		pos2 = Position();
	}

	Rectangle(Position _pos1, Position _pos2) {
		pos1 = _pos1;
		pos2 = _pos2;
	}

	int getArea() {
		return ((pos1.x - pos2.x) * (pos1.y - pos2.y));
	}
};

class Sprite {
	private:
		
	public:
		Position pos;
		List<Pixel> spriteData;

		Rectangle boundingBox;

		Sprite();
		Sprite(Position _pos, List<Pixel> _data);

		void draw();
		void move();

		void recalcBoundingBox();
};

#endif