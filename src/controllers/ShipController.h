/*
 * ShipController.h
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#ifndef SRC_CONTROLLERS_SHIPCONTROLLER_H_
#define SRC_CONTROLLERS_SHIPCONTROLLER_H_
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include "gImage.h"
#include "gFile.h"
#include "animation/SpriteAnimator.h"
#include "datatypes/Object2D.h"


class ShipController {
public:
	ShipController();
	~ShipController();
	void WPressed() { speedptr->y -= 1000.0f; }
	void APressed() { speedptr->x -= 1000.0f; }
	void SPressed() { speedptr->y += 1000.0f; }
	void DPressed() { speedptr->x += 1000.0f; }
	void FPressed();
	void GPressed();
	void WReleased() { speedptr->y += 1000.0f; }
	void AReleased() { speedptr->x += 1000.0f; }
	void SReleased() { speedptr->y -= 1000.0f; }
	void DReleased() { speedptr->x -= 1000.0f; }
	void mouseLeftRelease(const glm::vec2& clickedPos);
	void mouseRightRelease(const glm::vec2& clickedPos);

	std::string getLogMessages() const {
		return "number of bullets: " + gToStr(bullets->size()) +
		       ", number of fixed ships: " + gToStr(fixedships->size()) +
		       ", number of moving ships: " + gToStr(movableships->size());
	}

	void setup(const glm::vec2& minBoundary, const glm::vec2& maxBoundary);
	void update(float deltaTime);
	void draw() const;

	Object2D<Type2D::NODE, Pos2D::MOVING, Tex2D::SPRITE>* getSelectedShip() const {
		return dynamic_cast<Object2D<Type2D::NODE, Pos2D::MOVING, Tex2D::SPRITE>*>(selectedship);
	}

private:
	glm::vec2 speed = glm::vec2(0.0f);
	glm::vec2* speedptr = &speed;

	Object2D<Type2D::VECTOR, Pos2D::FIXED, Tex2D::SPRITE>* fixedships = nullptr;
	Object2D<Type2D::VECTOR, Pos2D::MOVING, Tex2D::SPRITE>* movableships = nullptr;
	Object2D<Type2D::INTERFACE, Pos2D::MOVING, Tex2D::SPRITE>* selectedship = nullptr;

	Object2D<Type2D::VECTOR, Pos2D::MOVING, Tex2D::IMAGE>* bullets;
	gImage bulletframe;

	SpriteAnimator *animator = nullptr;
};

#endif /* SRC_CONTROLLERS_SHIPCONTROLLER_H_ */
