/*
 * TController.h
 *
 *  Created on: 2014-3-8
 *      Author: dendong
 */

#ifndef TCONTOLLER_H_
#define TCONTOLLER_H_

#include "TBoard.h"
#include "TPiece.h"
#include "TBlock.h"
#include "cocos2d.h"
#include "cocos-ext.h"

namespace tetris {

class TController : public cocos2d::CCLayer {
public:
	// methods that will be registered as touch event callback
	void onStartButton(cocos2d::CCObject* sender, cocos2d::extension::CCControlEvent event);
	void onLeftButton(cocos2d::CCObject* sender, cocos2d::extension::CCControlEvent event);
	void onRightButton(cocos2d::CCObject* sender, cocos2d::extension::CCControlEvent event);
	void onDownButton(cocos2d::CCObject* sender, cocos2d::extension::CCControlEvent event);
	void onRotateButton(cocos2d::CCObject* sender, cocos2d::extension::CCControlEvent event);
	void onDropButton(cocos2d::CCObject* sender, cocos2d::extension::CCControlEvent event);

	// method that will be registered as timer callback
	void onTimeout(float f);

	TController();
	virtual bool init();
	CREATE_FUNC(TController);
	~TController();
private:
    TPiece* currentPiece;
    TPiece* nextPiece;
    TBoard* field;
    bool newPiece();
    void endGame();
    void doDrop();
    void doMoveDown();
    void rescheduleAutoMoveDown();
    void cancelAutoMoveDown();
    void scheduleAutoMoveDown();

    static const float AUTO_DROP_DOWN_INTERVAL;
};

}
#endif /* TCONTOLLER_H_ */
