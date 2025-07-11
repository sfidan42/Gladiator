/*
 * ShipController.cpp
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#include "controllers/ShipController.h"

ShipController::ShipController()
	: speed(0.0f, 0.0f), selectedship(nullptr), speedmul(1000.0f),
	  minboundary(0.0f, 0.0f), maxboundary(200.0f, 150.0f) {
	for(int i = 1; i <= 4; ++i) {
		AnimatedFrames animatedFrames;
		for(int j = 1; ; ++j) {
			std::string path = "gemiler/ship_" + gToStr(i) + "/ship_" + gToStr(i) + "_" + gToStr(j) + ".png";
			if(!gFile::doesFileExist(gObject::gGetImagesDir() + path)) {
				gLogw("ShipController::ShipController") << "No more frames found for: " << path;
				break;
			}
			auto* img = new gImage();
			img->loadImage(path);
			animatedFrames.frames.push_back(img);
		}
		listofanimatedframes[i - 1] = std::move(animatedFrames);
	}
	ships.reserve(4);
	ships.push_back(new Ship(&listofanimatedframes[0], {60, 20}, {242, 239}));
	ships.push_back(new Ship(&listofanimatedframes[1], {90, 310}, {170, 193}));
	ships.push_back(new Ship(&listofanimatedframes[2], {47, 557}, {255, 250}));
	ships.push_back(new Ship(&listofanimatedframes[3], {110, 900}, {130, 97}));
	animator = new SpriteAnimator();
}

ShipController::~ShipController() {
	for(AShipBase* ship : ships) {
		delete ship;
	}
	delete animator;
}

void ShipController::mouseLeftClick(const glm::vec2& clickedPos) {
	selectedship = nullptr;
	auto selectedShipIter = shipSelect(ships, clickedPos);
	if(selectedShipIter == ships.end()) {
		return;
	}
	AShipBase* newSelectedShip = *selectedShipIter;
	if(newSelectedShip->isAnimated()) {
		selectedship = newSelectedShip;
		return;
	}
	Ship* ship = dynamic_cast<Ship*>(newSelectedShip);
	auto* animship = new AnimatedShip(*ship);
	animship->changeCurrentFps(12);
	newSelectedShip = dynamic_cast<AShipBase*>(animship);
	ships.push_back(newSelectedShip);
	selectedship = newSelectedShip;
}

void ShipController::mouseRightClick(const glm::vec2& clickedPos) {
	auto selectedShipIter = shipSelect(ships, clickedPos);
	if(selectedShipIter == ships.end()) {
		return;
	}
	AShipBase* selectedShip = *selectedShipIter;
	if(!selectedShip->isAnimated()) {
		return;
	}
	if(selectedShip == selectedship) {
		selectedship = nullptr;
	}
	delete selectedShip;
	*selectedShipIter = ships.back();
	ships.pop_back();
}

void ShipController::setup(const float speedMul, const glm::vec2& minBoundary, const glm::vec2& maxBoundary) {
	this->speedmul = speedMul;
	this->minboundary = minBoundary;
	this->maxboundary = maxBoundary;
	auto *animatedFrames = new AnimatedFrames();
	const std::string& baseDir = gObject::gGetImagesDir();
	for(int i = 1; ; i++) {
		std::string path = "platform_anim/platform_" + gToStr(i) + ".png";
		if(gFile::doesFileExist(baseDir + path)) {
			auto* img = new gImage();
			img->loadImage(path);
			animatedFrames->frames.push_back(img);
		} else {
			break;
		}
	}
	auto* selectionAnim = new SpriteAnimation(animatedFrames, 25);
	animator->addAnimation(selectionAnim);
	animator->changeAnimation(selectionAnim->getId());
}

void ShipController::update(float deltaTime) {
	for(AShipBase* ship : ships) {
		AnimatedShip* animShip = ship->isAnimated();
		if(animShip) {
			animShip->update(deltaTime);
		}
	}
	animator->update(deltaTime);
	if(selectedship) {
		AnimatedShip* animShip = selectedship->isAnimated();
		if(animShip) {
			animShip->move(speed * speedmul * deltaTime, this->minboundary, this->maxboundary);
		}
	}
}

void ShipController::draw() {
	if(selectedship) {
		const gImage* curFrame = animator->getCurrentFrame();
		glm::vec2 curPos = selectedship->getMidPosition();
		glm::vec2 curFrameSize {
			static_cast<float>(curFrame->getWidth()),
			static_cast<float>(curFrame->getHeight())
		};
		curPos -= curFrameSize * 0.5f;
		animator->draw(curPos, curFrameSize, 30.0f);
	}
	for(AShipBase* ship : ships) {
		ship->draw();
	}
}
