/*
 * ShipController.h
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#ifndef SRC_CONTROLLERS_SHIPCONTROLLER_H_
#define SRC_CONTROLLERS_SHIPCONTROLLER_H_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "objects/Ship.h"
#include "objects/AnimatedShip.h"

class ShipController {
public:
	ShipController();
	~ShipController();
public:
	void WASDPressed(int key);
	void WASDReleased(int key);
	void mouseLeftClick(glm::vec2 clickedPos, float marginLimit);
	void mouseRightClick(glm::vec2 clickedPos, float marginLimit);
	void setup(float speedMul = 1000.0f);
	void update(float deltaTime);
	void draw(void);
private:
	glm::vec2 speed;
	float speedmul;
	AShipBase* selectedship;
	glm::vec2 selectedmargin;
	std::vector<AShipBase*> ships;
};

#endif /* SRC_CONTROLLERS_SHIPCONTROLLER_H_ */
