/*
 * TPosition.cpp
 *
 *  Created on: 2014-3-8
 *      Author: dendong
 */

#include "TPosition.h"

using namespace tetris;

TPosition::TPosition(int x, int y){
	this->x = x;
	this->y = y;
}

TPosition::TPosition() {
	x = 0;
	y = 0;
}


