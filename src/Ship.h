/*
 * Ship.h
 *
 *  Created on: Jun 26, 2025
 *      Author: sadettin
 */

#ifndef SRC_SHIP_H_
#define SRC_SHIP_H_
#include <gSpriteAnimation.h>
#include <gSpriteAnimator.h>
#include <glm/glm.hpp>
#include <gFile.h>

class Ship
{
private:
	gSpriteAnimation *idleAnim;
	gSpriteAnimator *animator;
	glm::vec2 pos;
	glm::vec2 size;
private:
	Ship(void);
public:
	Ship(glm::vec2 targetPos, glm::vec2 sourceSize = {200.0f, 200.0f}, float targetSizeScale = 1.0f);
	Ship(int shipIdx, int lastFrameIdx, std::string framePath, glm::vec2 pos);
	~Ship(void);
public:
	void setupAnim(const std::string &pathFmt, int fps = 10, bool isLooped = true);
	void update(void);
	void draw(void);
	void setPosition(glm::vec2 pos);
	glm::vec2 getPosition(void);
};

#endif /* SRC_SHIP_H_ */
