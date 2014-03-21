/*
 * ResolutionUtil.h
 *
 *  Created on: 2014-3-9
 *      Author: dendong
 */

#ifndef RESOLUTIONUTIL_H_
#define RESOLUTIONUTIL_H_

#include "cocos2d.h"

namespace tetris {

class ResolutionUtil {
public:
	static void init();
	static cocos2d::CCSprite* createBlockSprite(int x, int y);
	static void setLeftButtonPosition(cocos2d::CCNode* leftButton);
	static void setRightButtonPosition(cocos2d::CCNode* rightButton);
	static void setDownButtonPosition(cocos2d::CCNode* downButton);
	static void setRotateButtonPosition(cocos2d::CCNode* rotateButton);
	static void setStartButtonPosition(cocos2d::CCNode* startButton);
	static void setDropButtonPosition(cocos2d::CCNode* startButton);
	static void appearBlockSprite(cocos2d::CCSprite* sprite);
	static void moveBlockSprite(cocos2d::CCSprite* sprite, int dx, int dy);
	static void destroyBlockSprite(cocos2d::CCSprite* sprite);
private:
	////// normalized resolution. ///////
	static const int SCREEN_WIDTH = 1000;
	static const int LEFT_PADDING = 80;
	static const int FIELD_WIDTH = 500;
	static const int RIGHT_PADDING = 420;

	static const int SCREEN_HEIGHT = 1600;
	static const int UPPER_PADDING = 80;
	static const int FIELD_HEIGHT = 1000;
	static const int BOTTOM_PADDING = 520;

	static const int LEFT_BUTTON_X = 150;
	static const int LEFT_BUTTON_Y = BOTTOM_PADDING - 80;
	static const int RIGHT_BUTTON_X = 350;
	static const int RIGHT_BUTTON_Y = LEFT_BUTTON_Y;
	static const int DOWN_BUTTON_X = 250;
	static const int DOWN_BUTTON_Y = LEFT_BUTTON_Y - 200;
	static const int ROTATE_BUTTON_X = 750;
	static const int ROTATE_BUTTON_Y = LEFT_BUTTON_Y;
	static const int DROP_BUTTON_X = ROTATE_BUTTON_X;
	static const int DROP_BUTTON_Y = DOWN_BUTTON_Y;
	static const int START_BUTTON_X = LEFT_PADDING + FIELD_WIDTH + 80;
	static const int START_BUTTON_Y = SCREEN_HEIGHT - 150;

	static const int BLOCK_SIDE_LEN = 50;
	/////////////////////////////////////

	static const char* BLOCK_RES_IMG;

	static float R_FACTOR; // resolution factor
	static float IMG_FACTOR; // block image factor, should equal to normalized BLOCK_SIDE_LEN divided by IMG_SIDE_LEN
};

}

#endif /* RESOLUTIONUTIL_H_ */
