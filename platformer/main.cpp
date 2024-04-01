#include <iostream>
#include <vector>
#include "Classes.h"
#include "graphics.h"
#include "main.h"
#pragma comment(lib,"graphics.lib")
/* const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;
const int PLAYER_SPEED = 5; // �������� �������� ������
bool isGrounded = false; // ����, �����������, ��������� �� �����*/


bool isPlayerInObstacle(const Player& player, const Obstacle& obstacle) {
    int playerTop = player.getY() ;
    int playerBottom = player.getY() + player.getSize();
    int playerLeft = player.getX() ;
    int playerRight = player.getX() + player.getSize();

    int obstacleTop = obstacle.getTopY();
    int obstacleBottom = obstacle.getBottomY();
    int obstacleLeft = obstacle.getX1();
    int obstacleRight = obstacle.getX2();

    return IsOverlapping(playerLeft, obstacleLeft, playerRight, obstacleRight, playerTop, obstacleTop, playerBottom, obstacleBottom);
}

bool isPlayerOnObstacle(Player& p, Obstacle& o) {
    return IsOverlapping(p.getX(), o.getX1(), p.getX() + p.getSize(), o.getX2(), p.getY() + p.getSize(), o.getTopY(), p.getY() + 2 + p.getSize(), o.getBottomY());
}

bool IsOverlapping(int left1, int left2, int right1, int right2, int top1, int top2, int bottom1, int bottom2)
{
    if (left1 > right2 || left2 > right1 || top1 > bottom2 || top2 > bottom1) {
        return false;
    }
    return true;
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



    mainLoop(player, obstacle);

    closegraph();
    return 0;
}

void mainLoop(Player& player, Obstacle& obstacle)
{
    while (true) { // ���� ����� �����������, ���� �� ������ �������


        // ensure player does not fall through the obstacle
        if (isPlayerInObstacle(player, obstacle)) {
            std::cout << "IN ground" << std::endl;
            player.setBottomOn(obstacle.getTopY());
        }
        // check if player is on the floor
        if (isPlayerOnObstacle(player, obstacle)) {
            std::cout << "onground" << std::endl;
            player.setGrounded(true);
            player.setVelocityY(0);
            player.setVelocityX(0);
        }
        else {
            player.setGrounded(false);
            player.addVelocity(0, 1);
        }

        // ��������� ������� ������
        if (checkInput(player) == -1) {
            return;
        }

        player.update();
        // ensure player does not fall through the obstacle
        if (isPlayerInObstacle(player, obstacle)) {
            std::cout << "IN ground" << std::endl;
            player.setBottomOn(obstacle.getTopY());
        }

        // ��������� �����
        swapbuffers();        
        cleardevice(); // ������� �����
        // ������ ������ � �����������
        // ensure player does not fall through the obstacle
        player.draw();
        obstacle.draw(); // ������������ �����������

        delay(50); // �������� ��� �������� ��������
    }
}

int checkInput(Player& player)
{
    
    if (kbhit()) {
        char key = getch(); // �������� ��� ������� �������
        while (kbhit()) {
            key = getch(); // �������� ��� ������� �������
        }


        if (key == 32) {
            player.jump(); // �������� ����� ������ ��� ������
        }
        std::cout << "Pressed key: " << static_cast<int>(key) << std::endl; // ����� ������� �������

        // ����� �� �����, ���� ������ ������� ������ (Esc)
        if (key == 27)
        {
            return - 1;
        };

        // �������� ������� ��� ����������� ������
        move(key, player);
    }
    return 0;
}
