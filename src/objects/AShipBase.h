/*
 * AShipBase.h
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#ifndef SRC_OBJECTS_SHIPINTERFACE_H_
#define SRC_OBJECTS_SHIPINTERFACE_H_
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "datatypes/AnimatedFrames.h"


class AnimatedShip;

class AShipBase {
public:
	AShipBase(const AnimatedFrames* animatedFrames);
	virtual ~AShipBase() = default;
	virtual void draw() const = 0;
	virtual glm::vec2 getPosition() const = 0;
	virtual glm::vec2 getMidPosition() const = 0;
	virtual glm::vec2 getSize() const = 0;
	const AnimatedFrames* getAnimatedFrames() const;
	bool collision(float& outMarginLen, const glm::vec2& clickPos) const;
	AnimatedShip* isAnimated();

protected:
	const AnimatedFrames* animatedframes;
};

using ShipListType = std::vector<AShipBase*>;
using ShipIterType = ShipListType::iterator;

ShipIterType shipSelect(ShipListType& ships, const glm::vec2& pos);

#endif /* SRC_OBJECTS_SHIPINTERFACE_H_ */
