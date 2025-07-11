/*
 * ShipController.h
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#ifndef SRC_CONTROLLERS_SHIPCONTROLLER_H_
#define SRC_CONTROLLERS_SHIPCONTROLLER_H_
#include <glm/glm.hpp>
#include <vector>
#include <array>
#include "gImage.h"
#include "gFile.h"
#include "objects/Ship.h"
#include "objects/AnimatedShip.h"
#include "animation/SpriteAnimator.h"

class ShipController {
public:
	ShipController();
	~ShipController();
public:
	void WPressed() { speed.y -= 1.0f; }
	void APressed() { speed.x -= 1.0f; }
	void SPressed() { speed.y += 1.0f; }
	void DPressed() { speed.x += 1.0f; }
	void WReleased() { speed.y += 1.0f; }
	void AReleased() { speed.x += 1.0f; }
	void SReleased() { speed.y -= 1.0f; }
	void DReleased() { speed.x -= 1.0f; }
	void mouseLeftClick(const glm::vec2& clickedPos);
	void mouseRightClick(const glm::vec2& clickedPos);
	void setup(float speedMul, const glm::vec2& minBoundary, const glm::vec2& maxBoundary);
	void update(float deltaTime);
	void draw();
private:
	glm::vec2 speed;
	float speedmul;
	AShipBase* selectedship;
	std::array<AnimatedFrames, 4> listofanimatedframes;
	std::vector<AShipBase*> ships;
	glm::vec2 minboundary { 0.0f, 0.0f };
	glm::vec2 maxboundary { FLT_MAX, FLT_MAX };
	SpriteAnimator *animator;
};

#endif /* SRC_CONTROLLERS_SHIPCONTROLLER_H_ */
