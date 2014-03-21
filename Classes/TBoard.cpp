/*
 * TBoard.cpp
 *
 *  Created on: 2014-3-8
 *      Author: dendong
 */

#include "TBoard.h"
#include <android/log.h>

using namespace tetris;

void TBoard::reset() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			if (blocks[i][j]) {
				blocks[i][j]->destroy();
				delete blocks[i][j];
			}
			blocks[i][j] = NULL;
		}
	}
}

void TBoard::init() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			blocks[i][j] = NULL;
		}
	}
}

void TBoard::dropDownPiece(TPiece* p) {
	TPosition pos[4];
	p->getPositions(pos);
	int min = 19;
	for (int i = 0; i < 4; i++) {
		int h = height(pos[i].x, pos[i].y);
		if (h < min) {
			min = h;
		}
	}
	__android_log_print(ANDROID_LOG_INFO, "Tcontroller", "piece should drop down: %d", min);
	p->moveDown(min);
	p->getPositions(pos);
	__android_log_print(ANDROID_LOG_INFO, "Tcontroller", "piece moved down to: %d, %d", pos[0].x, pos[0].y);
	p->setToField(this);
	__android_log_write(ANDROID_LOG_INFO, "Tcontroller", "set piece to field");
	eliminateFull(pos);
	__android_log_write(ANDROID_LOG_INFO, "Tcontroller", "full layer eliminated");
}

int TBoard::height(int x, int y) {
	if (x < 0 || x >= 10)
		return -1;
	int h = 0;
	for (int j = y + 1; j < 20; j++) {
		if (blocks[x][j] == NULL) {
			h++;
		} else {
			break;
		}
	}
	return h;
}

bool TBoard::isEmpty(int x, int y) {
	if (x < 0 || x >= 10 || y >= 20)
		return false;
	if (y < 0)
		return true;
	return (blocks[x][y] == NULL);
}

void TBoard::setBlock(int x, int y, TBlock* block) {
	if (x < 0 || x > 10 || y < 0 || y >= 20)
		return;
	blocks[x][y] = block;
}

TBoard::~TBoard() {
	reset();
}

TBoard::TBoard() {
	init();
}

void TBoard::eliminateFull(TPosition* pos) {
	bool full[20] = {false};
	for (int i = 0; i < 4; i++) {
		full[pos[i].y] = isFull(pos[i].y);
	}
	int dy = 0;
	for (int j = 19; j >= 0; j--) {
		if (full[j]) {
			dy++;
		} else if (dy > 0) {
			for (int i = 0; i < 10; i++) {
				if (blocks[i][j]) {
					blocks[i][j]->move(0, dy);
				}
				if (blocks[i][j + dy]) {
					blocks[i][j + dy]->destroy();
					delete blocks[i][j + dy];
				}
				blocks[i][j + dy] = blocks[i][j];
				blocks[i][j] = NULL;
			}
		}
	}
}

bool TBoard::isFull(int y) {
	if (y < 0 || y >= 20)
		return false;
	for (int i = 0; i < 10; i++) {
		if (!blocks[i][y])
			return false;
	}
	__android_log_print(ANDROID_LOG_INFO, "Tcontroller", "detected full layer: %d", y);
	return true;
}


