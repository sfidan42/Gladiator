//
// Created by sadettin on 10.07.2025.
//

#ifndef ANIMATEDFRAMES_H
#define ANIMATEDFRAMES_H
#include <vector>
#include "gImage.h"

struct AnimatedFrames {
	AnimatedFrames() = default;
	~AnimatedFrames();
	AnimatedFrames(const AnimatedFrames&) = delete;
	AnimatedFrames& operator=(const AnimatedFrames&) = delete;
	AnimatedFrames(AnimatedFrames&& other) noexcept;
	AnimatedFrames& operator=(AnimatedFrames&& other) noexcept;

	std::vector<gImage*> frames;
};

AnimatedFrames loadAnimatedFrames(const std::vector<std::string>& framePaths);

#endif //ANIMATEDFRAMES_H
