#pragma once

bool IsOverlapping(int playerRight, int obstacleLeft, int playerLeft, int obstacleRight, int playerBottom, int obstacleTop, int playerTop, int obstacleBottom);

void mainLoop(Player& player, Obstacle& obstacle);

int checkInput(Player& player);
