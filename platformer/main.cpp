#include <iostream>
#include <vector>
#include "Classes.h"
#include "graphics.h"
#pragma comment(lib,"graphics.lib")
/* const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;
const int PLAYER_SPEED = 5; // �������� �������� ������
bool isGrounded = false; // ����, �����������, ��������� �� �����*/


bool isPlayerOnObstacle(const Player& player, const Obstacle& obstacle) {
    int playerTop = player.getY() - player.getSize() / 2;
    int playerBottom = player.getY() + player.getSize() / 2;
    int playerLeft = player.getX() - player.getSize() / 2;
    int playerRight = player.getX() + player.getSize() / 2;

    int obstacleTop = obstacle.getTopY();
    int obstacleBottom = obstacle.getBottomY();
    int obstacleLeft = obstacle.getX1();
    int obstacleRight = obstacle.getX2();

    // ��������� ����������� �� ����������� � ���������
    bool horizontalOverlap = playerRight >= obstacleLeft && playerLeft <= obstacleRight;
    bool verticalOverlap = playerBottom >= obstacleTop && playerTop <= obstacleBottom;

    return horizontalOverlap && verticalOverlap;
}

// ������� ��� ����������� ������ � ����������� �� ����������� �����������
void move(char currentDirection, Player& player) {
    switch (currentDirection) {
    case 'a':
        player.moveLeft();
        break;
    case 'd':
        player.moveRight();
        break;
    case 32: // ��� ������� ������
        player.jump();
        break;
    }
}
int main() {
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT);

    Player player(200, 50, 30); // ������� ������ � ������ ������
    Obstacle obstacle(150, 300, 300, 300); // ������� ����������� (�����) ����� (150, 300) � (300, 300)

    while (true) { // ���� ����� �����������, ���� �� ������ �������
        cleardevice(); // ������� �����
        // ������ ������ � �����������
        player.draw();
        obstacle.draw(); // ������������ �����������
       
        bool isGrounded = (player.getY() >= obstacle.getTopY() - player.getSize() / 2);
        if (isPlayerOnObstacle(player, obstacle)) {
            player.fall(obstacle.getTopY()); // ������������� �������� �������, ���� ����� �� �����������
        }
        else {
            player.fall(WINDOW_HEIGHT); // ����� ������ ������ ����
        }
        
    // ��������� ������� ������
        if (kbhit()) {
            char key = getch(); // �������� ��� ������� �������

         
            if (key == 32) { 
                player.jump(); // �������� ����� ������ ��� ������
            }
            std::cout << "Pressed key: " << static_cast<int>(key) << std::endl; // ����� ������� �������

            // ����� �� �����, ���� ������ ������� ������ (Esc)
            if (key == 27)
                break;

            // �������� ������� ��� ����������� ������
            move(key, player);
        }
   
        // ��������� �����
        swapbuffers();

        delay(50); // �������� ��� �������� ��������
    }

    closegraph();
    return 0;
}