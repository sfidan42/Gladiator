/*
 * ShipController.cpp
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#include "controllers/ShipController.h"

ShipController::ShipController()
	: speed(0.0f, 0.0f), speedmul(1.0f), selectedship(nullptr),
	  minboundary(0.0f), maxboundary(0.0f) {
	fixedships = new Object2D<Type2D::VECTOR, Pos2D::FIXED, Tex2D::SPRITE>;
	for(int i = 1; i <= 4; ++i) {
		auto* texture = new AnimatedFrames();
		for(int j = 1; ; ++j) {
			std::string path = "gemiler/ship_" + gToStr(i) + "/ship_" + gToStr(i) + "_" + gToStr(j) + ".png";
			auto* img = new gImage();
			if (!gFile::doesFileExist(gFile::gGetImagesDir() + path) || !img->loadImage(path)) {
				gLogw("ShipController::ShipController") << "No more frames found for: " << path;
				delete img;
				break;
			}
			texture->frames.push_back(img);
		}
		fixedships->addTexture(texture);
	}
	fixedships->addObject2D(0, {60, 20}, {0.0f, 0.0f}, 0.0f, {242, 239});
	fixedships->addObject2D(1, {90, 310}, {0.0f, 0.0f}, 0.0f, {170, 193});
	fixedships->addObject2D(2, {47, 557}, {0.0f, 0.0f},0.0f, {255, 250});
	fixedships->addObject2D(3, {110, 900}, {0.0f, 0.0f}, 0.0f, {130, 97});
	movableships = new Object2D<Type2D::VECTOR, Pos2D::MOVING, Tex2D::SPRITE>();
	animator = new SpriteAnimator();
	bullets = new Object2D<Type2D::VECTOR, Pos2D::MOVING, Tex2D::IMAGE>;
	const std::string bulletPath = "oyuncu_bullet_1_04.png";
	if(!bulletframe.loadImage(bulletPath)) {
		gLoge("ShipController::ShipController") << "Failed to load bullet frame from: " << bulletPath;
	}
}

ShipController::~ShipController() {
	delete fixedships;
	delete movableships;
	delete animator;
	delete bullets;
}

void ShipController::FPressed() {
	if (selectedship) {
		const float bulletDrawAngle = selectedship->getAngle();
		const float bulletSpeedAngle = bulletDrawAngle + 90.0f; // The angle bullets travel

		const glm::vec2 direction = glm::rotate(glm::vec2(1.0f, 0.0f), glm::radians(bulletSpeedAngle));

		const glm::vec2 shipSize = selectedship->getSize();
		const float shipRadius = glm::length(shipSize) * 0.5f;

		const glm::vec2 bulletSpeed = direction * 100.0f; // Already rotated
		const glm::vec2 bulletFrameSize = glm::vec2(bulletframe.getWidth(), bulletframe.getHeight());

		const glm::vec2 spawnPos = selectedship->getMidPosition() + direction * shipRadius - bulletFrameSize * 0.5f;

		const glm::vec2 bulletSize = bulletFrameSize;

		auto* newBullet = new Object2D<Type2D::NODE, Pos2D::MOVING, Tex2D::IMAGE>(&bulletframe, spawnPos, bulletSpeed, bulletDrawAngle, bulletSize);
		bullets->push_back(newBullet);
	} else {
		gLogw("ShipController::FPressed") << "No ship selected to fire!";
	}
}
void ShipController::mouseLeftRelease(const glm::vec2& clickedPos) {
	selectedship = nullptr;
	// Try selecting a MOVING ship first
	auto movableIt = movableships->selectObject2D(clickedPos);
	if (movableIt != movableships->end()) {
		selectedship = *movableIt;
		gLogi("ShipController::mouseLeftRelease")
			<< "Selected movable ship with id " << selectedship->getId()
			<< " at position: " << clickedPos.x << ", " << clickedPos.y;
		return;
	}
	// If not found, check template (FIXED) ships
	auto fixedIt = fixedships->selectObject2D(clickedPos);
	if (fixedIt != fixedships->end()) {
		auto* movingShipCopy = new Object2D<Type2D::NODE, Pos2D::MOVING, Tex2D::SPRITE>(**fixedIt);
		movableships->push_back(movingShipCopy);
		selectedship = movingShipCopy;
		gLogi("ShipController::mouseLeftRelease")
			<< "Selected fixed ship with id " << selectedship->getId()
			<< " at position: " << clickedPos.x << ", " << clickedPos.y;
	}
}

void ShipController::mouseRightRelease(const glm::vec2& clickedPos) {
	auto movableIt = movableships->selectObject2D(clickedPos);
	if(movableIt == movableships->end()) {
		return;
	}
	Object2D<Type2D::INTERFACE, Pos2D::MOVING, Tex2D::SPRITE>* selectedMovable = *movableIt;
	if(selectedMovable == selectedship) {
		selectedship = nullptr;
	}
	delete selectedMovable;
	*movableIt = movableships->back();
	movableships->pop_back();
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
	movableships->setup(minBoundary, maxBoundary);
	bullets->setup(minBoundary, maxBoundary);
}

void ShipController::update(float deltaTime) {
	movableships->update(deltaTime);
	animator->update(deltaTime);
	if(selectedship) {
		auto* movableShip = selectedship->getMovable();
		if(movableShip) {
			glm::vec2 stepSize = speed * speedmul * deltaTime;
			movableShip->move(stepSize, minboundary, maxboundary);
		} else {
			gLoge("ShipController::update") << "Selected ship is not movable!";
			selectedship = nullptr;
		}
	}
	bullets->update(deltaTime);
}

void ShipController::draw() const {
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
	fixedships->draw();
	movableships->draw();
	bullets->draw();
}
