/*
 * AnimatedShip.h
 *
 *  Created on: Jun 26, 2025
 *      Author: sadettin
 */

#ifndef SRC_SHIP_H_
#define SRC_SHIP_H_
#include <glm/glm.hpp>
#include <gFile.h>
#include <string>
#include "objects/Ship.h"
#include "objects/AShipBase.h"
#include "animation/SpriteAnimation.h"
#include "animation/SpriteAnimator.h"

class AnimatedShip : public AShipBase {
private:
	AnimatedShip(void);
public:
	AnimatedShip(const Ship* ship);
	~AnimatedShip(void);
public:
	void addAnimation(const std::string &pathFmt);
	void changeCurrentFps(int fps);
	void update(float deltaTime);
	void draw(void);
	void move(glm::vec2 stepSize);
	glm::vec2 getSize(void) const;
	glm::vec2 getPosition(void) const;
private:
	SpriteAnimator *animator;
	glm::vec2 pos;
	glm::vec2 size;
};

#endif /* SRC_SHIP_H_ */
