/*
 * AShipBase.cpp
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#include "objects/AnimatedShip.h"
#include "objects/AShipBase.h"

AShipBase::AShipBase(const std::string& pathFmt) {
	this->framepathfmt = pathFmt;
}

bool AShipBase::isAnimated(void) {
	return (dynamic_cast<AnimatedShip*>(this));
}

AShipBase::~AShipBase() {
}
