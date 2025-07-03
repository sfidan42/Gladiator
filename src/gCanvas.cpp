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
}

gCanvas::~gCanvas() {
	delete shipcontroller;
}

void gCanvas::setup() {
	background.loadImage("map.png");
	shipcontroller->setup();
//	shipcontroller->changesSpeedMul(10.0f);
}

void gCanvas::update() {
	float deltaTime = appmanager->getElapsedTime();
	shipcontroller->update(deltaTime);
}

void gCanvas::draw() {
	background.draw(0, 0);
	shipcontroller->draw();
}

void gCanvas::keyPressed(int key) {
	shipcontroller->WASDPressed(key);
}

void gCanvas::keyReleased(int key) {
	shipcontroller->WASDReleased(key);
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
	switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			shipcontroller->mouseLeftClick(glm::vec2(x, y), 100.0f);
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			shipcontroller->mouseRightClick(glm::vec2(x, y), 100.0f);
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

