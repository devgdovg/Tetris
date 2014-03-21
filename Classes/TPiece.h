/*
 * TPiece.h
 *
 *  Created on: 2014-3-8
 *      Author: dendong
 */

#ifndef TPIECE_H_
#define TPIECE_H_

#include "TBoard.h"
#include "TBlock.h"
#include "TPosition.h"

namespace tetris {

class TBoard;

class TPiece {
public:
	static TPiece* createI();
	static TPiece* createJ();
	static TPiece* createL();
	static TPiece* createO();
	static TPiece* createS();
	static TPiece* createT();
	static TPiece* createZ();
	void appear();
	void moveLeft();
	void moveRight();
	void rotate();
	void moveDown(int step);
	void getPositions(TPosition* positions);
	void setToField(TBoard* field);
	~TPiece();
private:
	TPiece(){};
	TBlock* blocks[4];
};

}

#endif /* TPIECE_H_ */
