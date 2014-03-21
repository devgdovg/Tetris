/*
 * TBlock.cpp
 *
 *  Created on: 2014-3-8
 *      Author: dendong
 */

#include "TBlock.h"
#include "ResolutionUtil.h"

using namespace tetris;

TBlock::TBlock(int x, int y) {
	this->x = x;
	this->y = y;
	sprite = ResolutionUtil::createBlockSprite(x, y);
	sprite->retain();
}

void TBlock::appear() {
	ResolutionUtil::appearBlockSprite(sprite);
}

void TBlock::move(int dx, int dy) {
	this->x += dx;
	this->y += dy;
	ResolutionUtil::moveBlockSprite(sprite, dx, dy);
}

void TBlock::destroy() {
	ResolutionUtil::destroyBlockSprite(sprite);
}

TBlock::~TBlock() {
	sprite->release();
}

