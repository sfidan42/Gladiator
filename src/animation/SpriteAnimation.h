/*
 * SpriteAnimation.h
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#ifndef SRC_SPRITEANIMATION_H_
#define SRC_SPRITEANIMATION_H_
#include <vector>
#include "gImage.h"

class SpriteAnimation {
public:
	SpriteAnimation(int fps = 6);
	~SpriteAnimation(void);
public:
	void update(float deltaTime);
	void setFps(int fps);
	void loadFrame(const std::string& framePath);
	int getId(void);
	gImage *getCurrentFrame(void);
private:
	int id;
	int fps;
	float timer;
	int currentframe;
	std::vector<gImage *> frames;
};

#endif /* SRC_SPRITEANIMATION_H_ */
