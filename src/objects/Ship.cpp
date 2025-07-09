/*
 * Ship.cpp
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#include "objects/Ship.h"

static std::string formatted(const std::string& format, int num) {
    int size = std::snprintf(nullptr, 0, format.c_str(), num);
    if(size <= 0) {
    	return "";
    }
    std::vector<char> buffer(size + 1);
    std::snprintf(buffer.data(), buffer.size(), format.c_str(), num);
    return std::string(buffer.data());
}

Ship::Ship(const std::string& pathFmt, glm::vec2 targetPos, glm::vec2 sourceSize, float targetSizeScale)
 : AShipBase(pathFmt), pos(targetPos), size(sourceSize * targetSizeScale) {
	frame = new gImage();
	framepathfmt = pathFmt;
	std::string path = formatted(pathFmt, 1);
	if(gFile::doesFileExist(gObject::gGetImagesDir() + path)) {
		frame->loadImage(path);
	} else {
		gLoge("Ship::Ship") << path << " is not correct.";
	}
}

Ship::~Ship(void) {
	delete frame;
}

void Ship::setFrame(const std::string &pathFmt) {
	this->framepathfmt = pathFmt;
}

void Ship::draw(void) {
	static int i;
	static glm::vec2 rnd;

	if (i == 0) {
		rnd = glm::gaussRand(glm::vec2(0.0f, 0.0f), glm::vec2(3.0f, 3.0f));
	}

	i = (i + 1) % 200;

	frame->draw(pos.x + rnd.x, pos.y + rnd.y, size.x, size.y);
}

std::string Ship::getFramePathFmt(void) const {
	return (framepathfmt);
}

glm::vec2 Ship::getPosition(void) const {
	return (this->pos + this->size * 0.5f);
}

glm::vec2 Ship::getSize(void) const {
	return (this->size);
}
