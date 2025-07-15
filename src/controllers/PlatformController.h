//
// Created by sadettin on 7/13/25.
//

#ifndef PLATFORMCONTROLLER_H
#define PLATFORMCONTROLLER_H
#include <string>
#include <glm/glm.hpp>
#include "datatypes/Object2DNode.h"


class PlatformController {
public:
	PlatformController(const std::string& path, std::initializer_list<glm::vec2> positions, const glm::vec2& platformSize, float angle);
	~PlatformController();
	void draw() const;
private:
	Object2D<Type2D::VECTOR, Pos2D::FIXED, Tex2D::IMAGE>* platforms;
};



#endif //PLATFORMCONTROLLER_H
