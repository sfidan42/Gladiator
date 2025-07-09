/*
 * AShipBase.cpp
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#include "objects/AnimatedShip.h"

AShipBase::AShipBase(const std::string& pathFmt) {
	this->framepathfmt = pathFmt;
}

AnimatedShip* AShipBase::isAnimated(void) {
	return (dynamic_cast<AnimatedShip*>(this));
}

AShipBase::~AShipBase() {
}

bool AShipBase::collision(float& outMarginLen, const glm::vec2 &clickPos) {
	outMarginLen = glm::length(clickPos - getPosition());
	return (outMarginLen <= glm::length(getSize() * 0.5f));
}

ShipIterType shipSelect(ShipListType& ships, const glm::vec2 pos) {
	ShipIterType selectedShipIter = ships.end();
	float marginLen;
	float smallestMarginLen = FLT_MAX;
	for (ShipIterType shipIter = ships.begin(); shipIter != ships.end(); shipIter++) {
		if ((*shipIter)->collision(marginLen, pos)) {
			if (marginLen <= smallestMarginLen) {
				smallestMarginLen = marginLen;
				selectedShipIter = shipIter;
			}
		}
	}
	return selectedShipIter;
}
