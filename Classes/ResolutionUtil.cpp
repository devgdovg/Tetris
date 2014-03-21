/*
 * ResolutionUtil.cpp
 *
 *  Created on: 2014-3-9
 *      Author: dendong
 */

#include "ResolutionUtil.h"
#include "cocos2d.h"
#include <android/log.h>

using namespace tetris;
using namespace cocos2d;

const char* ResolutionUtil::BLOCK_RES_IMG = "block.png";
float ResolutionUtil::R_FACTOR;
float ResolutionUtil::IMG_FACTOR;

void ResolutionUtil::init() {
	__android_log_write(ANDROID_LOG_INFO, "ResolutionUtil", "ResolutionUtil init...");
	CCDirector* director = CCDirector::sharedDirector();
	CCSize size = director->getVisibleSize();
	R_FACTOR = size.height / SCREEN_HEIGHT;
	IMG_FACTOR = 1.0 * ResolutionUtil::R_FACTOR;
	__android_log_print(ANDROID_LOG_INFO, "ResolutionUtil",
			"getVisibleSize: %f * %f; R_FACTOR: %f; IMG_FACTOR: %f",
			size.height, size.width, R_FACTOR, IMG_FACTOR);
}

CCSprite* ResolutionUtil::createBlockSprite(int x, int y) {
	CCSprite* sprite = CCSprite::create(BLOCK_RES_IMG);
	sprite->setScale(IMG_FACTOR);
	sprite->setPositionX((LEFT_PADDING + x * BLOCK_SIDE_LEN) * R_FACTOR);
	sprite->setPositionY((SCREEN_HEIGHT - UPPER_PADDING - (1 + y) * BLOCK_SIDE_LEN) * R_FACTOR);
	return sprite;
}

void ResolutionUtil::appearBlockSprite(CCSprite* sprite) {
	CCNode* parent = sprite->getParent();
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
		CCLayer* layer = (CCLayer*) (scene->getChildByTag(0));
	layer->addChild(sprite);
}

void ResolutionUtil::moveBlockSprite(CCSprite* sprite, int dx, int dy) {
	CCMoveBy* move = CCMoveBy::create(0,
			ccp(BLOCK_SIDE_LEN*R_FACTOR*dx, -BLOCK_SIDE_LEN*R_FACTOR*dy));
	sprite->runAction(move);
}

void ResolutionUtil::destroyBlockSprite(CCSprite* sprite) {
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	CCLayer* layer = (CCLayer*) scene->getChildByTag(0);
	layer->removeChild(sprite);
}

void ResolutionUtil::setLeftButtonPosition(cocos2d::CCNode* leftButton) {
	leftButton->setPositionX(LEFT_BUTTON_X * R_FACTOR);
	leftButton->setPositionY(LEFT_BUTTON_Y * R_FACTOR);
}
void ResolutionUtil::setRightButtonPosition(cocos2d::CCNode* rightButton) {
	rightButton->setPositionX(RIGHT_BUTTON_X * R_FACTOR);
	rightButton->setPositionY(RIGHT_BUTTON_Y * R_FACTOR);
}
void ResolutionUtil::setDownButtonPosition(cocos2d::CCNode* downButton) {
	downButton->setPositionX(DOWN_BUTTON_X * R_FACTOR);
	downButton->setPositionY(DOWN_BUTTON_Y * R_FACTOR);
}
void ResolutionUtil::setRotateButtonPosition(cocos2d::CCNode* rotateButton) {
	rotateButton->setPositionX(ROTATE_BUTTON_X * R_FACTOR);
	rotateButton->setPositionY(ROTATE_BUTTON_Y * R_FACTOR);
}
void ResolutionUtil::setStartButtonPosition(cocos2d::CCNode* startButton) {
	startButton->setPositionX(START_BUTTON_X * R_FACTOR);
	startButton->setPositionY(START_BUTTON_Y * R_FACTOR);
}
void ResolutionUtil::setDropButtonPosition(cocos2d::CCNode* dropButton) {
	dropButton->setPositionX(DROP_BUTTON_X * R_FACTOR);
	dropButton->setPositionY(DROP_BUTTON_Y * R_FACTOR);
}
