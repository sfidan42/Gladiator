/*
 * SpriteAnimator.h
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#ifndef SRC_SPRITEANIMATOR_H_
#define SRC_SPRITEANIMATOR_H_
#include "animation/SpriteAnimation.h"
#include <vector>
#include <glm/glm.hpp>

class SpriteAnimator {
public:
	SpriteAnimator();
	~SpriteAnimator();
public:
	void addAnimation(SpriteAnimation *anim);
	void changeAnimation(int id);
	void changeCurrentFps(int fps);
	void update(float deltaTime);
	void draw(int x, int y);
	void draw(int x, int y, int w, int h);
	void draw(const glm::vec2& pos);
	void draw(const glm::vec2& pos, const glm::vec2& size);
private:
	std::vector<SpriteAnimation*> animations;
	SpriteAnimation* currentanim;
};

#endif /* SRC_SPRITEANIMATOR_H_ */
