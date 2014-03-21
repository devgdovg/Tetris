/*
 * TPiece.cpp
 *
 *  Created on: 2014-3-8
 *      Author: dendong
 */

#include "TPiece.h"

using namespace tetris;

TPiece* TPiece::createI() {
	TPiece* p = new TPiece();
	p->blocks[0] = new TBlock(4, 0);
	p->blocks[1] = new TBlock(3, 0);
	p->blocks[2] = new TBlock(5, 0);
	p->blocks[3] = new TBlock(6, 0);
	return p;
}

TPiece* TPiece::createJ() {
	TPiece* p = new TPiece();
	p->blocks[0] = new TBlock(4, 0);
	p->blocks[1] = new TBlock(3, 0);
	p->blocks[2] = new TBlock(5, 0);
	p->blocks[3] = new TBlock(5, 1);
	return p;
}

TPiece* TPiece::createL() {
	TPiece* p = new TPiece();
	p->blocks[0] = new TBlock(4, 0);
	p->blocks[1] = new TBlock(4, 1);
	p->blocks[2] = new TBlock(5, 0);
	p->blocks[3] = new TBlock(6, 0);
	return p;
}

TPiece* TPiece::createO() {
	TPiece* p = new TPiece();
	p->blocks[0] = new TBlock(4, 0);
	p->blocks[1] = new TBlock(4, 1);
	p->blocks[2] = new TBlock(5, 0);
	p->blocks[3] = new TBlock(5, 1);
	return p;
}

TPiece* TPiece::createS() {
	TPiece* p = new TPiece();
	p->blocks[0] = new TBlock(4, 0);
	p->blocks[1] = new TBlock(3, 1);
	p->blocks[2] = new TBlock(4, 1);
	p->blocks[3] = new TBlock(5, 0);
	return p;
}

TPiece* TPiece::createT() {
	TPiece* p = new TPiece();
	p->blocks[0] = new TBlock(4, 0);
	p->blocks[1] = new TBlock(3, 0);
	p->blocks[2] = new TBlock(4, 1);
	p->blocks[3] = new TBlock(5, 0);
	return p;
}

TPiece* TPiece::createZ() {
	TPiece* p = new TPiece();
	p->blocks[0] = new TBlock(4, 0);
	p->blocks[1] = new TBlock(3, 0);
	p->blocks[2] = new TBlock(5, 0);
	p->blocks[3] = new TBlock(5, 1);
	return p;
}

void TPiece::appear() {
	for (int i = 0; i < 4; i++) {
		blocks[i]->appear();
	}
}

void TPiece::moveRight() {
	for (int i = 0; i < 4; i++) {
		blocks[i]->move(1, 0);
	}
}

void TPiece::moveLeft() {
	for (int i = 0; i < 4; i++) {
		blocks[i]->move(-1, 0);
	}
}

void TPiece::moveDown(int step) {
	for (int i = 0; i < 4; i++) {
		blocks[i]->move(0, step);
	}
}

void TPiece::rotate() {
	for (int i = 0; i < 4; i++) {
		blocks[i]->move(
				blocks[0]->getX() + blocks[0]->getY() - blocks[i]->getX()
						- blocks[i]->getY(),
				blocks[i]->getX() - blocks[i]->getY() + blocks[0]->getY()
						- blocks[0]->getX());
	}
}

void TPiece::getPositions(TPosition* positions) {
	for (int i = 0; i < 4; i++) {
		positions[i].x = blocks[i]->getX();
		positions[i].y = blocks[i]->getY();
	}
}

void TPiece::setToField(TBoard* field) {
	for (int i = 0; i < 4; i++) {
		field->setBlock(blocks[i]->getX(), blocks[i]->getY(), blocks[i]);
	}
}

TPiece::~TPiece() {
	for (int i = 0; i < 4; i++) {
		delete blocks[i];
	}
}
