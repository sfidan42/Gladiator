/*
* gCanvas.cpp
*
*  Created on: May 6, 2020
*      Author: noyan
*/


#include "gCanvas.h"

gCanvas::gCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
	shipcontroller = new ShipController();
	playerplatformctrl = new PlatformController("silahli_gemi1.png", {{441, 126}, {441, 635}}, {272, 310}, 90.0f);
	enemyplatformctrl = new PlatformController("silahli_dusmangemi1.png", {{1471, 126}, {1471, 635}}, {272, 310}, 90.0f);
}

gCanvas::~gCanvas() {
	delete shipcontroller;
	delete playerplatformctrl;
	delete enemyplatformctrl;
}

void gCanvas::setup() {
	std::string backgroundImg = "map.png";
	if (!background.loadImage(backgroundImg)) {
		gLoge("gCanvas::setup") << "Failed to load background image.";
	} else {
		gLogi("gCanvas::setup") << "Background image loaded from " << backgroundImg;
	}
	glm::vec2 windowSize = {
		renderer->getUnitWidth(),
		renderer->getUnitHeight()
	};
	shipcontroller->setup(1000.0f, glm::vec2(0.0f), windowSize);
}

void gCanvas::update() {
	float deltaTime = appmanager->getElapsedTime();
	shipcontroller->update(deltaTime);
}

void gCanvas::draw() {
	background.draw(0, 0);
	playerplatformctrl->draw();
	enemyplatformctrl->draw();
	shipcontroller->draw();
}

void gCanvas::keyPressed(int key) {
	switch(key) {
	case G_KEY_W: shipcontroller->WPressed();
		break;
	case G_KEY_A: shipcontroller->APressed();
		break;
	case G_KEY_S: shipcontroller->SPressed();
		break;
	case G_KEY_D: shipcontroller->DPressed();
		break;
	default: break;
	}
}

void gCanvas::keyReleased(int key) {
	switch(key) {
	case G_KEY_W: shipcontroller->WReleased();
		break;
	case G_KEY_A: shipcontroller->AReleased();
		break;
	case G_KEY_S: shipcontroller->SReleased();
		break;
	case G_KEY_D: shipcontroller->DReleased();
		break;
	default: break;
	}
}

void gCanvas::charPressed(unsigned int codepoint) {
	//	gLogi("gCanvas") << "charPressed:" << gCodepointToStr(codepoint);
}

void gCanvas::mouseMoved(int x, int y) {
	//	gLogi("gCanvas") << "mouseMoved" << ", x:" << x << ", y:" << y;
}

void gCanvas::mouseDragged(int x, int y, int button) {
	//	gLogi("gCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void gCanvas::mousePressed(int x, int y, int button) {
	switch(button) {
	case GLFW_MOUSE_BUTTON_LEFT:
		shipcontroller->mouseLeftClick(glm::vec2(x, y));
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		shipcontroller->mouseRightClick(glm::vec2(x, y));
		break;
	default:
		break;
	}
}

void gCanvas::mouseReleased(int x, int y, int button) {
	//	gLogi("gCanvas") << "mouseReleased" << ", x:" << x << ", y:" << y << ", button:" << button;
}

void gCanvas::mouseScrolled(int x, int y) {
	//	gLogi("gCanvas") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void gCanvas::mouseEntered() {
}

void gCanvas::mouseExited() {
}

void gCanvas::windowResized(int w, int h) {
}

void gCanvas::showNotify() {
}

void gCanvas::hideNotify() {
}
