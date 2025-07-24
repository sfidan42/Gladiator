/*
 * gCanvas.cpp
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */

#include "gCanvas.h"

gCanvas::gCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
	font = new gFont();
}

gCanvas::~gCanvas() { delete font; }

void gCanvas::setup() {
	appmanager->setTargetFramerate(165);
	appmanager->enableVsync();
	font->loadFont("FreeSansBold.ttf", 16);
}

void gCanvas::update() {
	const float deltaTime = appmanager->getElapsedTime();
	(void)deltaTime;
}

void gCanvas::draw() {
	font->drawText("fps: " + gToStr(1.0f / appmanager->getElapsedTime()), 0.0f, 16.0f);
}

void gCanvas::keyPressed(int key) {
	//	gLogi("gCanvas::keyPressed") << "keyPressed:" << gKeyToStr(key);
}

void gCanvas::keyReleased(int key) {
	//	gLogi("gCanvas::keyReleased") << "keyReleased:" << gKeyToStr(key);
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
	//	gLogi("gCanvas") << "mousePressed" << ", x:" << x << ", y:" << y << ", button:" << button;
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
