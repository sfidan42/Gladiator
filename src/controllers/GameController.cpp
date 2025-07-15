//
// Created by sadettin on 7/15/25.
//

#include "controllers/GameController.h"

GameController::GameController() {
	shipcontroller = new ShipController();
	playerplatformctrl = new PlatformController("silahli_gemi1.png", {{441, 126}, {441, 635}}, {272, 310}, 90.0f);
	enemyplatformctrl = new PlatformController("silahli_dusmangemi1.png", {{1471, 126}, {1471, 635}}, {272, 310}, 90.0f);
}

GameController::~GameController() {
	delete shipcontroller;
	delete playerplatformctrl;
	delete enemyplatformctrl;
}

void GameController::mouseLeftClick(const glm::vec2& clickedPos) {

	auto* previouslySelectedShip = shipcontroller->getSelectedShip();
	shipcontroller->mouseLeftClick(clickedPos);
	auto* currentlySelectedShip = shipcontroller->getSelectedShip();

	auto* previouslySelectedPlatform = playerplatformctrl->getSelectedPlatform();
	playerplatformctrl->mouseLeftClick(clickedPos);
	auto* currentlySelectedPlatform = playerplatformctrl->getSelectedPlatform();

	if (previouslySelectedShip && currentlySelectedPlatform && !currentlySelectedShip) {
		previouslySelectedShip->move(currentlySelectedPlatform);
		previouslySelectedShip->rotate(180.0f);
	}
}

void GameController::mouseRightClick(const glm::vec2& clickedPos) {
	shipcontroller->mouseRightClick(clickedPos);
}
