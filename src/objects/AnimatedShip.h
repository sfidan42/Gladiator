/*
 * AnimatedShip.h
 *
 *  Created on: Jun 26, 2025
 *      Author: sadettin
 */

#ifndef SRC_SHIP_H_
#define SRC_SHIP_H_
#include <glm/glm.hpp>
#include "objects/Ship.h"
#include "objects/AShipBase.h"
#include "animation/SpriteAnimator.h"

class AnimatedShip : public AShipBase {
public:
	AnimatedShip() = delete;
	AnimatedShip(Ship& ship);
	~AnimatedShip();
	void changeCurrentFps(int fps);
	void update(float deltaTime);
	void draw() const;
	void move(const glm::vec2& stepSize, const glm::vec2& minBoundary, const glm::vec2& maxBoundary);
	glm::vec2 getSize() const;
	glm::vec2 getPosition() const;
	glm::vec2 getMidPosition() const;

private:
	SpriteAnimator* animator;
	glm::vec2 pos;
	glm::vec2 size;
};

#endif /* SRC_SHIP_H_ */
