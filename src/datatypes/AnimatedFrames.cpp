//
// Created by sadettin on 10.07.2025.
//

#include "AnimatedFrames.h"

AnimatedFrames::~AnimatedFrames() {
	for(auto frame : frames) {
		delete frame;
	}
}

AnimatedFrames::AnimatedFrames(AnimatedFrames&& other) noexcept {
	frames = std::move(other.frames);
	other.frames.clear();
}

AnimatedFrames& AnimatedFrames::operator=(AnimatedFrames&& other) noexcept {
	if(this != &other) {
		frames = std::move(other.frames);
		other.frames.clear();
	}
	return *this;
}

AnimatedFrames loadAnimatedFrames(const std::vector<std::string>& framePaths) {
	AnimatedFrames animatedFrames;
	animatedFrames.frames.reserve(framePaths.size());
	for(const auto& path : framePaths) {
		auto img = new gImage();
		img->loadImage(path);
		animatedFrames.frames.push_back(img);
	}
	return animatedFrames;
}
