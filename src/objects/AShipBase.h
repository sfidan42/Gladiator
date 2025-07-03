/*
 * AShipBase.h
 *
 *  Created on: Jul 3, 2025
 *      Author: sadettin
 */

#ifndef SRC_OBJECTS_SHIPINTERFACE_H_
#define SRC_OBJECTS_SHIPINTERFACE_H_
#include <string>
#include <glm/glm.hpp>

class AShipBase {
public:
	AShipBase(const std::string& pathFmt);
	virtual ~AShipBase();
public:
	virtual glm::vec2 getPosition(void) const = 0;
	virtual glm::vec2 getSize(void) const = 0;
	virtual void draw(void) = 0;
	bool isAnimated(void);
protected:
	std::string framepathfmt;
};

#endif /* SRC_OBJECTS_SHIPINTERFACE_H_ */
