//
// Created by sadettin on 7/13/25.
//

#include "controllers/PlatformController.h"

#include "datatypes/AnimatedFrames.h"
#include "datatypes/AnimatedFrames.h"
#include "datatypes/AnimatedFrames.h"
#include "datatypes/AnimatedFrames.h"
#include "datatypes/AnimatedFrames.h"
#include "datatypes/AnimatedFrames.h"
#include "datatypes/AnimatedFrames.h"
#include "datatypes/AnimatedFrames.h"
#include "datatypes/Object2DNode.h"
#include "datatypes/Object2DNode.h"
#include "datatypes/Object2DNode.h"
#include "datatypes/Object2DNode.h"
#include "datatypes/Object2DNode.h"
#include "datatypes/Object2DNode.h"
#include "datatypes/Object2DNode.h"
#include "datatypes/Object2DNode.h"

PlatformController::PlatformController(const std::string& path, std::initializer_list<glm::vec2> positions, const glm::vec2& platformSize, float angle)
	: selectedplatform(nullptr) {
	platforms = new Object2D<Type2D::VECTOR, Pos2D::FIXED, Tex2D::IMAGE>();
	size_t index = 0;
	for (const auto& pos : positions) {
		auto* texture = new gImage();
		if (!texture->loadImage(path)) {
			gLoge("PlatformController::PlatformController") << "Failed to load platform image from: " << path;
			delete texture;
			break;
		}
		platforms->addTexture(texture);
		platforms->addObject2D(index, pos, platformSize, 1.0f, angle);
		index++;
	}
}

PlatformController::~PlatformController() {
	delete platforms;
}

void PlatformController::mouseLeftClick(const glm::vec2& clickedPos) {
	selectedplatform = nullptr;
	auto selectionIter = platforms->selectObject2D(clickedPos);
	if (selectionIter != platforms->end()) {
		gLogi("PlatformController::mouseLeftClick") << "Platform selected at position: " << clickedPos.x << ", " << clickedPos.y;
		selectedplatform = *selectionIter;
	}
}

void PlatformController::draw() const {
	platforms->draw();
}
