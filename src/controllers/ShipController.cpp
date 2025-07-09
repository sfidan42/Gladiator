/*
 * ShipController.cpp
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#include "controllers/ShipController.h"

ShipController::ShipController(void) {
	selectedship = nullptr;
	ships.resize(4);
	ships[0] = new Ship("gemiler/ship_1/ship_1_%d.png", {60,  20}, {242, 239}, 0.95f);
	ships[1] = new Ship("gemiler/ship_2/ship_2_%d.png", {90, 310}, {170, 193}, 1.05f);
	ships[2] = new Ship("gemiler/ship_3/ship_3_%d.png", {70, 560}, {255, 250}, 0.85f);
	ships[3] = new Ship("gemiler/ship_4/ship_4_%d.png", {90, 870}, {130,  97}, 1.30f);
	animator = new SpriteAnimator();
}

ShipController::~ShipController() {
	for(AShipBase *ship : ships) {
		delete ship;
	}
	delete animator;
}

void ShipController::mouseLeftClick(const glm::vec2& clickedPos) {
	selectedship = nullptr;
	ShipIterType selectedShipIter = shipSelect(ships, clickedPos);
	if (selectedShipIter == ships.end()) {
		return;
	}
	AShipBase* newSelectedShip = *selectedShipIter;
	if (newSelectedShip->isAnimated()) {
		selectedship = newSelectedShip;
		return;
	}
	const Ship* ship = dynamic_cast<const Ship*>(newSelectedShip);
	AnimatedShip* animship = new AnimatedShip(ship);
	animship->changeCurrentFps(12);
	newSelectedShip = dynamic_cast<AShipBase*>(animship);
	ships.push_back(newSelectedShip);
	selectedship = newSelectedShip;
}

void ShipController::mouseRightClick(const glm::vec2& clickedPos) {
	ShipIterType selectedShipIter = shipSelect(ships, clickedPos);
	if (selectedShipIter == ships.end()) {
		return;
	}
	AShipBase* selectedShip = *selectedShipIter;
	if (!selectedShip->isAnimated()) {
		return;
	}
	if (selectedShip == selectedship) {
		selectedship = nullptr;
	}
	delete selectedShip;
	*selectedShipIter = ships.back();
	ships.pop_back();
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

void ShipController::setup(const float speedMul, const glm::vec2& minBoundary, const glm::vec2& maxBoundary) {
	this->speedmul = speedMul;
	this->minboundary = minBoundary;
	this->maxboundary = maxBoundary;
	SpriteAnimation* selectionAnim = new SpriteAnimation(25);
	std::string pathFmt("platform_anim/platform_%d.png");
	const std::string &baseDir = gObject::gGetImagesDir();
		for(int i = 1; ;i++) {
			std::string path = formatted(pathFmt, i);
			if(gFile::doesFileExist(baseDir + path)) {
				selectionAnim->loadFrame(path);
			} else {
				break;
			}
		}
	animator->addAnimation(selectionAnim);
	animator->changeAnimation(selectionAnim->getId());
}

void ShipController::update(float deltaTime) {
	for(AShipBase *ship : ships) {
		AnimatedShip* animship = ship->isAnimated();
		if (animship) {
			animship->update(deltaTime);
		}
	}
	animator->update(deltaTime);
	if (selectedship) {
		AnimatedShip* animship = selectedship->isAnimated();
		if (animship) {
			animship->move(speed * speedmul * deltaTime, minboundary, maxboundary);
		}
	}
}

void ShipController::draw(void) {
	if (selectedship) {
		glm::vec2 pos = selectedship->getPosition();
		glm::vec2 size = selectedship->getSize();
		animator->draw(pos - size * 0.5f, size);
	}
	for(AShipBase *ship : ships) {
		ship->draw();
	}
}
