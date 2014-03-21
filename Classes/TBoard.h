/*
 * TBoard.h
 *
 *  Created on: 2014-3-8
 *      Author: dendong
 */

#ifndef T_BOARD_H_
#define T_BOARD_H_

#include "TPiece.h"
#include "TBlock.h"
#include "TPosition.h"

namespace tetris {

class TPiece;

class TBoard {
public:
	void reset();
	void dropDownPiece(TPiece* p);
	bool isEmpty(int x, int y);
	void setBlock(int x, int y, TBlock* block);
	TBoard();
	~TBoard();
private:
	TBlock* blocks[10][20];
	void init();
	int height(int x, int y);
	void eliminateFull(TPosition* pos);
	bool isFull(int y);
};

}
#endif /* T_BOARD_H_ */
