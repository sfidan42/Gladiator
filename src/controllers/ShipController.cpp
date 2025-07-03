/*
 * ShipController.cpp
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#include "controllers/ShipController.h"

ShipController::ShipController(void) {
	ships.resize(4);
	ships[0] = new Ship("gemiler/ship_1/ship_1_%d.png", {60,  20}, {242, 239}, 0.95f);
	ships[1] = new Ship("gemiler/ship_2/ship_2_%d.png", {90, 310}, {170, 193}, 1.05f);
	ships[2] = new Ship("gemiler/ship_3/ship_3_%d.png", {70, 560}, {255, 250}, 0.85f);
	ships[3] = new Ship("gemiler/ship_4/ship_4_%d.png", {90, 870}, {130,  97}, 1.30f);
}

ShipController::~ShipController() {
	for(AShipBase *ship : ships) {
		delete ship;
	}
}

void ShipController::WASDPressed(int key) {
	switch (key) {
		case GLFW_KEY_W: speed.y -= 1.0f; break;
		case GLFW_KEY_S: speed.y += 1.0f; break;
		case GLFW_KEY_A: speed.x -= 1.0f; break;
		case GLFW_KEY_D: speed.x += 1.0f; break;
	}
}

void ShipController::WASDReleased(int key) {
	switch (key) {
		case GLFW_KEY_W: speed.y += 1.0f; break;
		case GLFW_KEY_S: speed.y -= 1.0f; break;
		case GLFW_KEY_A: speed.x += 1.0f; break;
		case GLFW_KEY_D: speed.x -= 1.0f; break;
	}
}

void ShipController::mouseLeftClick(glm::vec2 clickedPos, float marginLimit) {
	selectedship = nullptr;
	int smallestMargin = 2147483647;
	for (AShipBase* ship : ships) {
		glm::vec2 shipPos = ship->getPosition();
		glm::vec2 marginVec = clickedPos - shipPos;
		int margin = glm::length(marginVec);
		if (margin < marginLimit && margin <= smallestMargin) {
			smallestMargin = margin;
			selectedship = ship;
			selectedmargin = marginVec;
		}
	}
	if (!selectedship) {
		return;
	}
	if (selectedship->isAnimated()) {
		return;
	}
	const Ship* ship = dynamic_cast<const Ship *>(selectedship);
	selectedship = dynamic_cast<AShipBase*>(new AnimatedShip(ship));
	ships.push_back(selectedship);
}

void ShipController::mouseRightClick(glm::vec2 clickedPos, float marginLimit) {
	std::vector<AShipBase*>::iterator selectedShipIter = ships.end();
	int smallestMargin = 2147483647;
	for (auto shipIter = ships.begin(); shipIter < ships.end(); shipIter++) {
		glm::vec2 shipPos = (*shipIter)->getPosition();
		int margin = glm::length(clickedPos - shipPos);
		if (margin < marginLimit && margin <= smallestMargin) {
			smallestMargin = margin;
			selectedShipIter = shipIter;
		}
	}
	if (selectedShipIter == ships.end()) {
		return;
	}
	if ((*selectedShipIter)->isAnimated()) {
		gLogi("ShipController::mouseRightClick") << "an animated ship is selected";
		ships.erase(selectedShipIter);
		return;
	}
}

void ShipController::setup(float speedMul) {
	this->speedmul = speedMul;
}

void ShipController::update(float deltaTime) {
	for(AShipBase *ship : ships) {
		if (ship->isAnimated()) {
			dynamic_cast<AnimatedShip*>(ship)->update(deltaTime);
		}
	}
	if (selectedship) {
		dynamic_cast<AnimatedShip*>(selectedship)->move(speed * speedmul * deltaTime);
	}
}

void ShipController::draw(void) {
	for(AShipBase *ship : ships) {
		ship->draw();
	}
}
