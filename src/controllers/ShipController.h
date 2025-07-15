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
#include "animation/SpriteAnimator.h"
#include "datatypes/Object2DNode.h"


class ShipController {
public:
	ShipController();
	~ShipController();
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

	Object2D<Type2D::NODE, Pos2D::MOVING, Tex2D::SPRITE>* getSelectedShip() const {
		return dynamic_cast<Object2D<Type2D::NODE, Pos2D::MOVING, Tex2D::SPRITE>*>(selectedship);
	}

private:
	glm::vec2 speed;
	float speedmul;

	Object2D<Type2D::INTERFACE, Pos2D::MOVING, Tex2D::SPRITE>* selectedship;
	Object2D<Type2D::VECTOR, Pos2D::FIXED, Tex2D::SPRITE>* fixedships;
	Object2D<Type2D::VECTOR, Pos2D::MOVING, Tex2D::SPRITE>* movableships;
	glm::vec2 minboundary;
	glm::vec2 maxboundary;
	SpriteAnimator *animator;
};

#endif /* SRC_CONTROLLERS_SHIPCONTROLLER_H_ */
