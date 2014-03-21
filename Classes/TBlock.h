/*
 * TBlock.h
 *
 *  Created on: 2014-3-8
 *      Author: dendong
 */

#ifndef TBLOCK_H_
#define TBLOCK_H_

#include "cocos2d.h"

namespace tetris {

class TBlock {
public:
	TBlock(int x, int y);
	void appear();
	void move(int dx, int dy);
	int getX(){return x;}
	int getY(){return y;}
	void destroy();
	~TBlock();
private:
	cocos2d::CCSprite* sprite;
	int x;
	int y;
};
}

#endif /* TBLOCK_H_ */
