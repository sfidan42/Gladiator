#include "Ship.h"
#include <sstream>

Ship::Ship(int shipIdx, int lastFrameIdx, std::string framesDir, glm::vec<2, int> pos) {
	this->pos = pos;
	this->idleAnim = new gSpriteAnimation();
	this->idleAnim->setFps(10);
	this->idleAnim->setLoop(true);
	for (int i = 1; i <= lastFrameIdx; i++) {
		std::stringstream framePath;
		framePath << framesDir << "ship_" << shipIdx << "_" << i << ".png";
		this->idleAnim->loadFrame(framePath.str());
	}
	this->animator = new gSpriteAnimator();
	this->animator->addAnimation(0, idleAnim);
	this->animator->changeAnimation(0);
}

Ship::~Ship(void) {
	delete this->animator;
}

void Ship::update() {
	this->animator->update();
}

void Ship::draw(void) {
	this->animator->draw(pos.x, pos.y);
}

void Ship::setIdleFps(int fps) {
	this->idleAnim->setFps(fps);
}
