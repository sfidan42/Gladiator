/*
 * SpriteAnimation.cpp
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#include "animation/SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(int fps) {
	static int sid;
	this->id = sid++;
	this->fps = fps;
	timer = 0.0f;
	currentframe = 0;
}

SpriteAnimation::~SpriteAnimation(void) {
	for (gImage *frame : frames) {
		delete frame;
	}
}

void SpriteAnimation::update(float deltaTime) {
	static int i;
	timer += deltaTime;
	float frameDuration = 1.0f / fps;
	while (timer >= frameDuration) {
		currentframe = (currentframe + 1) % frames.size();
		timer -= frameDuration;
	}
}

void SpriteAnimation::loadFrame(const std::string &framePath) {
	gImage* img = new gImage();
	img->loadImage(framePath);
	frames.push_back(img);
}

void SpriteAnimation::setFps(int fps) {
	this->fps = fps;
}

int SpriteAnimation::getId(void) {
	return (id);
}

gImage* SpriteAnimation::getCurrentFrame(void) {
	if(frames.empty()) {
		return nullptr;
	}
	return frames[currentframe % frames.size()];
}
