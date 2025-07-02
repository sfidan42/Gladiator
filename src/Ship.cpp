#include "Ship.h"

Ship::Ship(glm::vec2 targetPos, glm::vec2 sourceSize, float targetSizeScale) {
	this->pos = targetPos;
	this->size = sourceSize * targetSizeScale;
	this->idleAnim = new gSpriteAnimation();
	this->animator = new gSpriteAnimator();
}

static std::string formatted(const std::string& format, int num) {
    int size = std::snprintf(nullptr, 0, format.c_str(), num);
    if(size <= 0) {
    	return "";
    }
    std::vector<char> buffer(size + 1);
    std::snprintf(buffer.data(), buffer.size(), format.c_str(), num);
    return std::string(buffer.data());
}

void Ship::setupAnim(const std::string &pathFmt, int fps, bool isLooped) {
	this->idleAnim->setFps(fps);
	this->idleAnim->setLoop(isLooped);
	const std::string &baseDir = gObject::gGetImagesDir();
	for(int i = 1; ;i++) {
		std::string path = formatted(pathFmt, i);
		if(gFile::doesFileExist(baseDir + path)) {
			this->idleAnim->loadFrame(path);
		} else {
			break;
		}
	}
	this->animator->addAnimation(0, idleAnim);
	this->animator->changeAnimation(0);
}

Ship::~Ship(void) {
	delete this->animator;
	delete this->idleAnim;
}

void Ship::update() {
	this->animator->update();
}

void Ship::draw(void) {
	this->animator->draw(pos.x, pos.y, size.x, size.y);
}

void Ship::setPosition(glm::vec2 pos) {
	this->pos = pos - this->size * 0.5f;
}

glm::vec2 Ship::getPosition(void) {
	return (this->pos + this->size * 0.5f);
}
