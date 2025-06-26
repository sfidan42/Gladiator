/*
* gCanvas.cpp
*
*  Created on: May 6, 2020
*      Author: noyan
*/


#include "gCanvas.h"


gCanvas::gCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

gCanvas::~gCanvas() {
	for (Ship *ship : ships)
		delete ship;
}

void gCanvas::setup() {
	ships.resize(4);
	ships[0] = new Ship(1, 25, "gemiler/ship_1/", {55, 20});
	ships[1] = new Ship(2, 16, "gemiler/ship_2/", {90, 310});
	ships[2] = new Ship(3, 25, "gemiler/ship_3/", {50, 550});
	ships[3] = new Ship(5, 21, "gemiler/", {90, 850});
	ships[0]->setIdleFps(8);
	ships[1]->setIdleFps(9);
	ships[2]->setIdleFps(8);
	ships[3]->setIdleFps(10);
	background.loadImage("map.png");
}

void gCanvas::update() {
	for (Ship *ship: ships)
		ship->update();
}

void gCanvas::draw() {
	background.draw(0, 0);
	for (Ship *ship : ships)
		ship->draw();
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
//	gLogi("gCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void gCanvas::mousePressed(int x, int y, int button) {
//	gLogi("gCanvas") << "mousePressed" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void gCanvas::mouseReleased(int x, int y, int button) {
//	gLogi("gCanvas") << "mouseReleased" << ", button:" << button;
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

