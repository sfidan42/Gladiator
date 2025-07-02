/*
 * MouseObject.h
 *
 *  Created on: Jul 1, 2025
 *      Author: sadettin
 */

#ifndef SRC_MOUSEOBJECT_H_
#define SRC_MOUSEOBJECT_H_
#include "Ship.h"

class MouseObject {
public:
	MouseObject();
	virtual ~MouseObject();
public:
	void dragTo(glm::vec2 targetPos);
	void selectOne(const std::vector<Ship*>& ships, glm::vec2 clickedPos, int marginLimit);
	void deselect(void);
private:
	Ship *selectedShip;
	bool leftClicked;
	glm::vec2 selectedMarginVec;
};

#endif /* SRC_MOUSEOBJECT_H_ */
