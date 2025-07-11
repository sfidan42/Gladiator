#include "objects/AnimatedShip.h"

AnimatedShip::AnimatedShip(Ship& ship) : AShipBase(ship.getAnimatedFrames()) {
	this->size = ship.getSize();
	this->pos = ship.getPosition();
	this->animator = new SpriteAnimator();
	auto* anim = new SpriteAnimation(AShipBase::animatedframes);
	this->animator->addAnimation(anim);
}

AnimatedShip::~AnimatedShip() {
	delete this->animator;
}

void AnimatedShip::changeCurrentFps(int fps) {
	this->animator->changeCurrentFps(fps);
}

void AnimatedShip::update(float deltaTime) {
	this->animator->update(deltaTime);
}

void AnimatedShip::draw() const {
	this->animator->draw(pos, size);
}

void AnimatedShip::move(const glm::vec2& stepSize, const glm::vec2& minBoundary, const glm::vec2& maxBoundary) {
	pos = glm::clamp(pos + stepSize, minBoundary - size * 0.5f, maxBoundary - size * 0.5f);
}

glm::vec2 AnimatedShip::getSize() const {
	return (size);
}

glm::vec2 AnimatedShip::getPosition() const {
	return (pos);
}

glm::vec2 AnimatedShip::getMidPosition() const {
	return (pos + size * 0.5f);
}
