/*
 * SpriteAnimation.h
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#ifndef SRC_SPRITEANIMATION_H_
#define SRC_SPRITEANIMATION_H_
#include "gImage.h"
#include "datatypes/AnimatedFrames.h"


class SpriteAnimation {
public:
	SpriteAnimation(const AnimatedFrames* animatedFrames, int fps = 6);
	~SpriteAnimation();
public:
	void update(float deltaTime);
	void setFps(int fps);
	int getId() const;
	gImage *getCurrentFrame() const;
private:
	int id;
	float frameduration;
	float timer;
	size_t currentframe;
	const AnimatedFrames* animatedframes;
};

#endif /* SRC_SPRITEANIMATION_H_ */
