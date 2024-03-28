#include <iostream>
#include "Classes.h"
#include <vector>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")
/* const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;
const int PLAYER_SPEED = 5; // �������� �������� ������
bool isGrounded = false; // ����, �����������, ��������� �� �����*/


// ������� ��� �������� ����������� ���� ���������������
bool isRectangleIntersecting(int x1, int y1, int width1, int height1,
    int x2, int y2, int width2, int height2) {
    // ��������� ����������� ���� ���������������
    if (x1 > x2 + width2 || x2 > x1 + width1 ||
        y1 > y2 + height2 || y2 > y1 + height1) {
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
        // ��������� ������ ����������� ��������, ���� �����
    }
}
int main() {
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT);

    Player player(200, 50, 30); // ������� ������ � ������ ������ ��� ������������
    Obstacle obstacle(150, 300, 300, 300); // ������� ����������� (�����) ����� (150, 300) � (300, 300)

    while (true) { // ���� ����� �����������, ���� �� ������ �������
        cleardevice(); // ������� �����

        // ������ ������ � �����������
        player.draw();
        obstacle.draw();

        // ��������� ������������ � ������
        if (!isGrounded) {
            player.fall(obstacle.getTopY());

        }
        // ��������� ������������ � ������������
        if (isRectangleIntersecting(player.getX() - player.getSize() / 2, player.getY() + player.getSize() / 2, player.getSize(), 1,
            obstacle.getX1(), obstacle.getTopY(), obstacle.getX2() - obstacle.getX1(), 1))
            player.setGrounded(true);

        // ���� ����� �� �����, �� ������ ������
        if (!isGrounded)
            player.fall(obstacle.getTopY());


        // ��������� ������� ������
        if (kbhit()) {
            char key = getch(); // �������� ��� �������
            std::cout << "Pressed key: " << static_cast<int>(key) << std::endl; // ����� ������� �������
            if (key == ' ') {
                player.jump();
            }
            // ����� �� �����, ���� ������ ������� ������ (Esc)
            if (key == 27)
                break;

            // �������� ������� ��� ����������� ������
            move(key, player);
        }

        delay(50); // �������� ��� �������� ��������

        // ��������� �����
        swapbuffers();
    }

    closegraph();
    return 0;
}