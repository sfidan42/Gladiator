/*
 * AShipBase.cpp
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#include "objects/AnimatedShip.h"

AShipBase::AShipBase(const AnimatedFrames* animatedFrames)
	: animatedframes(animatedFrames) {
	if(animatedframes->frames.empty()) {
		gLoge("AShipBase::AShipBase") << "Animated frames are empty!";
	}
}

AnimatedShip* AShipBase::isAnimated() {
	return (dynamic_cast<AnimatedShip*>(this));
}

const AnimatedFrames* AShipBase::getAnimatedFrames() const {
	return animatedframes;
}

bool AShipBase::collision(float& outMarginLen, const glm::vec2& clickPos) const {
	outMarginLen = glm::length(clickPos - getMidPosition());
	return (outMarginLen <= glm::length(getSize() * 0.5f));
}

ShipIterType shipSelect(ShipListType& ships, const glm::vec2& pos) {
	auto selectedShipIter = ships.end();
	float marginLen;
	float smallestMarginLen = FLT_MAX;
	for(auto shipIter = ships.begin(); shipIter != ships.end(); shipIter++) {
		if((*shipIter)->collision(marginLen, pos)) {
			if(marginLen <= smallestMarginLen) {
				smallestMarginLen = marginLen;
				selectedShipIter = shipIter;
			}
		}
	}
	return selectedShipIter;
}
