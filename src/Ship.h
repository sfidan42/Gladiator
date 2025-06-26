/*
 * Ship.h
 *
 *  Created on: Jun 26, 2025
 *      Author: sadettin
 */

#ifndef SRC_SHIP_H_
#define SRC_SHIP_H_
#include "gSpriteAnimation.h"
#include "gSpriteAnimator.h"
#include "glm/glm.hpp"

class Ship
{
private:
	gSpriteAnimation *idleAnim;
	gSpriteAnimator *animator;
	glm::vec<2, int> pos;
private:
	Ship(void);
public:
	Ship(int shipIdx, int lastFrameIdx, std::string framePath, glm::vec<2, int> pos);
	~Ship(void);
public:
	void update(void);
	void draw(void);
	void setIdleFps(int fps);
};

#endif /* SRC_SHIP_H_ */
