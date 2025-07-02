/*
 * MouseObject.cpp
 *
 *  Created on: Jul 1, 2025
 *      Author: sadettin
 */

#include <MouseObject.h>

MouseObject::MouseObject() {
	leftClicked = false;
	selectedShip = nullptr;
	selectedMarginVec = {0.0f, 0.0f};
}

MouseObject::~MouseObject() {
}

void MouseObject::dragTo(glm::vec2 targetPos) {
	if (leftClicked && selectedShip) {
		selectedShip->setPosition(targetPos - selectedMarginVec);
	}
}

void MouseObject::selectOne(const std::vector<Ship*>& ships, glm::vec2 clickedPos, int marginLimit) {
	leftClicked = true;
	selectedShip = nullptr;
	int smallestMargin = INT_MAX;
	for (Ship* ship : ships) {
		glm::vec2 marginVec = clickedPos - ship->getPosition();
		int margin = glm::length(marginVec);
		if (margin < marginLimit && margin < smallestMargin) {
			smallestMargin = margin;
			selectedShip = ship;
			selectedMarginVec = marginVec;
		}
	}
}

void MouseObject::deselect() {
	leftClicked = false;
	selectedShip = nullptr;
}
