/*
 * Ship.h
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#ifndef SRC_OBJECTS_SHIP_H_
#define SRC_OBJECTS_SHIP_H_
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include "gImage.h"
#include "objects/AShipBase.h"
#include "datatypes/AnimatedFrames.h"

class Ship : public AShipBase {
public:
	Ship() = delete;
	Ship(const AnimatedFrames* animatedFrames, const glm::vec2& targetPos, const glm::vec2& sourceSize, float targetSizeScale = 1.0f);
	~Ship() = default;

public:
	glm::vec2 getPosition() const;
	glm::vec2 getMidPosition() const;
	glm::vec2 getSize() const;
	void draw() const;

private:
	const glm::vec2 pos;
	const glm::vec2 size;
};

#endif /* SRC_OBJECTS_SHIP_H_ */
