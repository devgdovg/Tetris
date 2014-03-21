/*
 * TController.cpp
 *
 *  Created on: 2014-3-8
 *      Author: dendong
 */

#include "TController.h"
#include "ResolutionUtil.h"
#include <string>
#include <android/log.h>

using namespace tetris;
using namespace cocos2d;
using namespace cocos2d::extension;

const float TController::AUTO_DROP_DOWN_INTERVAL = 1.0f;

void TController::onStartButton(CCObject* sender, CCControlEvent event) {
	field->reset();
	if (currentPiece) {
		delete currentPiece;
	}
	__android_log_write(ANDROID_LOG_INFO, "Tcontroller", "creating currentPiece...");
	currentPiece = TPiece::createI();
	if (nextPiece) {
		delete nextPiece;
	}
	__android_log_write(ANDROID_LOG_INFO, "Tcontroller", "creating nextPiece...");
	nextPiece = TPiece::createI();
	__android_log_write(ANDROID_LOG_INFO, "Tcontroller", "currentPiece appear...");
	currentPiece->appear();
	scheduleAutoMoveDown();
}

void TController::onLeftButton(CCObject* sender, CCControlEvent event) {
	__android_log_write(ANDROID_LOG_INFO, "Tcontroller", "left button touched...");
	TPosition pos[4];
	currentPiece->getPositions(pos);
	for (int i = 0; i < 4; i++) {
		if(!field->isEmpty(pos[i].x - 1, pos[i].y)) {
			__android_log_print(ANDROID_LOG_INFO, "Tcontroller", "cannot move to left: %d, %d", pos[i].x, pos[i].y);
			return;
		}
	}
	currentPiece->moveLeft();
}

void TController::onRightButton(CCObject* sender, CCControlEvent event) {
	__android_log_write(ANDROID_LOG_INFO, "Tcontroller", "right button touched...");
	TPosition pos[4];
	currentPiece->getPositions(pos);
	for (int i = 0; i < 4; i++) {
		if (!field->isEmpty(pos[i].x + 1, pos[i].y)) {
			__android_log_print(ANDROID_LOG_INFO, "Tcontroller", "cannot move to right: %d, %d", pos[i].x, pos[i].y);
			return;
		}
	}
	currentPiece->moveRight();
}

void TController::onDownButton(CCObject* sender, CCControlEvent event) {
	__android_log_write(ANDROID_LOG_INFO, "Tcontroller", "down button touched...");
	doMoveDown();
}

void TController::onTimeout(float f) {
	__android_log_write(ANDROID_LOG_INFO, "Tcontroller", "timed out for auto move-down...");
	doMoveDown();
}

void TController::doMoveDown() {
	TPosition pos[4];
	currentPiece->getPositions(pos);
	for (int i = 0; i < 4; i++) {
		if (!field->isEmpty(pos[i].x, pos[i].y + 1)) {
			doDrop();
			return;
		}
	}
	currentPiece->moveDown(1);
	rescheduleAutoMoveDown();
}

void TController::doDrop() {
	field->dropDownPiece(currentPiece);
	if (!newPiece()) {
		endGame();
	} else {
		rescheduleAutoMoveDown();
	}
}

void TController::rescheduleAutoMoveDown() {
	cancelAutoMoveDown();
	scheduleAutoMoveDown();
}

void TController::cancelAutoMoveDown() {
	this->unschedule(schedule_selector(TController::onTimeout));
}

void TController::scheduleAutoMoveDown() {
	this->schedule(schedule_selector(TController::onTimeout), AUTO_DROP_DOWN_INTERVAL);
}

bool TController::newPiece() {
	TPiece* p = TPiece::createI();
	currentPiece = nextPiece;
	nextPiece = p;
	TPosition pos[4];
	currentPiece->getPositions(pos);
	for (int i = 0; i < 4; i++) {
		if (!field->isEmpty(pos[i].x, pos[i].y)) {
			return false;
		}
	}
	__android_log_print(ANDROID_LOG_INFO, "Tcontroller", "new piece should created at: %d, %d", pos[0].x, pos[0].y);
	currentPiece->appear();
	__android_log_write(ANDROID_LOG_INFO, "Tcontroller", "new piece created");
	return true;
}

void TController::endGame() {
	cancelAutoMoveDown();
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			if (field->isEmpty(i, j)) {
				TBlock* block = new TBlock(i, j);
				field->setBlock(i, j, block);
				block->appear();
			}
		}
	}
}

void TController::onDropButton(CCObject* sender, CCControlEvent event) {
	__android_log_write(ANDROID_LOG_INFO, "Tcontroller", "drop button touched...");
	doDrop();
}

void TController::onRotateButton(CCObject* sender, CCControlEvent event) {
	__android_log_write(ANDROID_LOG_INFO, "Tcontroller", "rotate button touched...");
	TPosition pos[4];
	currentPiece->getPositions(pos);
	for (int i = 0; i < 4; i++) {
		// pos[0] as anchor. check if all other rotated positions are empty.
		if (!field->isEmpty(pos[0].x + pos[0].y - pos[i].y,
				pos[0].y + pos[i].x - pos[0].x)) {
			return;
		}
	}
	currentPiece->rotate();
}

TController::TController():currentPiece(NULL), nextPiece(NULL) {
	__android_log_write(ANDROID_LOG_INFO, "Tcontroller", "TController construct...");
	field = new TBoard();
}

bool TController::init() {
	__android_log_write(ANDROID_LOG_INFO, "Tcontroller", "TController init...");
	if (!CCLayer::init()) {
		return false;
	}
	ResolutionUtil::init();

	std::string left("left");
	CCControlButton* leftButton = CCControlButton::create(left, "Arial", 48);
	ResolutionUtil::setLeftButtonPosition(leftButton);
	leftButton->addTargetWithActionForControlEvents(this,
				cccontrol_selector(TController::onLeftButton),
				CCControlEventTouchUpInside);

	std::string right("right");
	CCControlButton* rightButton = CCControlButton::create(right, "Arial", 48);
	ResolutionUtil::setRightButtonPosition(rightButton);
	rightButton->addTargetWithActionForControlEvents(this,
				cccontrol_selector(TController::onRightButton),
				CCControlEventTouchUpInside);

	std::string down("down");
	CCControlButton* downButton = CCControlButton::create(down, "Arial", 48);
	ResolutionUtil::setDownButtonPosition(downButton);
	downButton->addTargetWithActionForControlEvents(this,
				cccontrol_selector(TController::onDownButton),
				CCControlEventTouchUpInside);

	std::string rotate("rotate");
	CCControlButton* rotateButton = CCControlButton::create(rotate, "Arial", 48);
	ResolutionUtil::setRotateButtonPosition(rotateButton);
	rotateButton->addTargetWithActionForControlEvents(this,
				cccontrol_selector(TController::onRotateButton),
				CCControlEventTouchUpInside);

	std::string start("start");
	CCControlButton* startButton = CCControlButton::create(start, "Arial", 48);
	ResolutionUtil::setStartButtonPosition(startButton);
	startButton->addTargetWithActionForControlEvents(this,
			cccontrol_selector(TController::onStartButton),
			CCControlEventTouchUpInside);

	std::string drop("drop");
	CCControlButton* dropButton = CCControlButton::create(drop, "Arial", 48);
	ResolutionUtil::setDropButtonPosition(dropButton);
	dropButton->addTargetWithActionForControlEvents(this,
			cccontrol_selector(TController::onDropButton),
			CCControlEventTouchUpInside);

	this->addChild(leftButton);
	this->addChild(rightButton);
	this->addChild(downButton);
	this->addChild(rotateButton);
	this->addChild(startButton);
	this->addChild(dropButton);

	CCScene* scene = CCScene::create();
	this->setTag(0);
	scene->addChild(this);
	CCDirector::sharedDirector()->runWithScene(scene);

//	onStartButton(this, CCControlEventTouchUpInside);
	__android_log_write(ANDROID_LOG_INFO, "Tcontroller", "TController init done...");

	const CCPoint p = dropButton->getPosition();
	__android_log_print(ANDROID_LOG_INFO, "Tcontroller",
			"drop button position: %f, %f", p.x, p.y);
	const CCPoint p2 = leftButton->getPosition();
	__android_log_print(ANDROID_LOG_INFO, "Tcontroller",
			"left button position: %f, %f", p2.x, p2.y);
	const CCPoint p3 = rightButton->getPosition();
	__android_log_print(ANDROID_LOG_INFO, "Tcontroller",
			"right button position: %f, %f", p3.x, p3.y);
	const CCPoint p4 = downButton->getPosition();
	__android_log_print(ANDROID_LOG_INFO, "Tcontroller",
			"down button position: %f, %f", p4.x, p4.y);
	const CCPoint p5 = startButton->getPosition();
	__android_log_print(ANDROID_LOG_INFO, "Tcontroller",
			"start button position: %f, %f", p5.x, p5.y);


	return true;
}

TController::~TController() {
	if (currentPiece) {
		delete currentPiece;
		currentPiece = NULL;
	}
	if (nextPiece) {
		delete nextPiece;
		nextPiece = NULL;
	}
	if (field) {
		delete field;
		field = NULL;
	}
}


