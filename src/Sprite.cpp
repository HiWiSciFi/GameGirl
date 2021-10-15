#include "Sprite.h"

Sprite::Sprite() {
	pos = Position();
	spriteData = List<Pixel>();
}

Sprite::Sprite(Position _pos, List<Pixel> _data) {
	pos = _pos;
	spriteData = _data;
}

void Sprite::recalcBoundingBox() {

}