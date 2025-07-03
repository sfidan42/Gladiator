/*
 * Ship.h
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#ifndef SRC_OBJECTS_SHIP_H_
#define SRC_OBJECTS_SHIP_H_
#include <glm/glm.hpp>
#include <string>
#include "gImage.h"
#include "gFile.h"
#include "objects/AShipBase.h"

class Ship : public AShipBase {
private:
	Ship(void);
public:
	Ship(const std::string& pathFmt, glm::vec2 targetPos, glm::vec2 sourceSize, float targetSizeScale = 1.0f);
	~Ship(void);
public:
	void setFrame(const std::string& framePath);
	std::string getFramePathFmt(void) const;
	glm::vec2 getPosition(void) const;
	glm::vec2 getSize(void) const;
	void draw(void);
private:
	gImage *frame;
	const glm::vec2 pos;
	const glm::vec2 size;
};

#endif /* SRC_OBJECTS_SHIP_H_ */
