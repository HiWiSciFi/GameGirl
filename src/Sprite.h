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

class Sprite {
	private:
		
	public:
		Position pos;
		List<Pixel> spriteData;

		Sprite();
		Sprite(Position _pos, List<Pixel> _data);

		void draw();
		void move();
};

#endif