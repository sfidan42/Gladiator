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

class AnimatedShip;

class AShipBase {
public:
	AShipBase(const std::string& pathFmt);
	virtual ~AShipBase();
public:
	virtual glm::vec2 getPosition(void) const = 0;
	virtual glm::vec2 getSize(void) const = 0;
	bool collision(float& outMarginLen, const glm::vec2& clickPos);
	virtual void draw(void) = 0;
	AnimatedShip* isAnimated(void);
protected:
	std::string framepathfmt;
};

using ShipListType = std::vector<AShipBase*>;
using ShipIterType = ShipListType::iterator;

ShipIterType shipSelect(ShipListType& ships, const glm::vec2 pos);

#endif /* SRC_OBJECTS_SHIPINTERFACE_H_ */
