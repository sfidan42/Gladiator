/*
* gCanvas.cpp
*
*  Created on: May 6, 2020
*      Author: noyan
*/


#include "gCanvas.h"

gCanvas::gCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
	ships.resize(4);
	ships[0] = new Ship({60,  20}, {242, 239}, 0.95f);
	ships[1] = new Ship({90, 310}, {170, 193}, 1.05f);
	ships[2] = new Ship({70, 560}, {255, 250}, 0.85f);
	ships[3] = new Ship({90, 870}, {130,  97}, 1.30f);
}

gCanvas::~gCanvas() {
	for(Ship *ship : ships) {
		delete ship;
	}
}

void gCanvas::setup() {
	assert(ships.size() >= 4);
	ships[0]->setupAnim("gemiler/ship_1/ship_1_%d.png", 7);
	ships[1]->setupAnim("gemiler/ship_2/ship_2_%d.png", 8);
	ships[2]->setupAnim("gemiler/ship_3/ship_3_%d.png", 7);
	ships[3]->setupAnim("gemiler/ship_4/ship_4_%d.png");
	background.loadImage("map.png");
}

void gCanvas::update() {
	for(Ship *ship: ships) {
		ship->update();
	}
}

void gCanvas::draw() {
	background.draw(0, 0);
	for(Ship *ship : ships) {
		ship->draw();
	}
}

void gCanvas::keyPressed(int key) {
//	gLogi("gCanvas") << "keyPressed:" << key;
}

void gCanvas::keyReleased(int key) {
//	gLogi("gCanvas") << "keyReleased:" << key;
}

void gCanvas::charPressed(unsigned int codepoint) {
//	gLogi("gCanvas") << "charPressed:" << gCodepointToStr(codepoint);
}

void gCanvas::mouseMoved(int x, int y) {
//	gLogi("gCanvas") << "mouseMoved" << ", x:" << x << ", y:" << y;
}

void gCanvas::mouseDragged(int x, int y, int button) {
	mouseObj.dragTo(glm::vec2(x, y));
//	gLogi("gCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void gCanvas::mousePressed(int x, int y, int button) {
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		mouseObj.selectOne(ships, glm::vec2(x, y), 100);
	}
}

void gCanvas::mouseReleased(int x, int y, int button) {
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		mouseObj.deselect();
	}
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

