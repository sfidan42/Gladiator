/*
 * Ship.cpp
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#include "objects/Ship.h"
#include "datatypes/AnimatedFrames.h"

Ship::Ship(const AnimatedFrames* animatedFrames, const glm::vec2& targetPos, const glm::vec2& sourceSize, float targetSizeScale)
	: AShipBase(animatedFrames), pos(targetPos), size(sourceSize * targetSizeScale) {}

void Ship::draw() const {
	if (AShipBase::animatedframes->frames.empty()) {
		gLoge("Ship::draw") << "Animated frames are empty!";
		return;
	}
	auto* frame = AShipBase::animatedframes->frames.front();
	frame->draw(pos.x, pos.y, size.x, size.y);
}

glm::vec2 Ship::getPosition() const {
	return (pos);
}

glm::vec2 Ship::getMidPosition() const {
	return (pos + size * 0.5f);
}

glm::vec2 Ship::getSize() const {
	return (size);
}
