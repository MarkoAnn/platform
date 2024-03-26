#include <iostream>
#include <vector>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;

class Player {
private:
    int x, y; // ���������� ������
    int size; // ������ ������

public:
    Player(int startX, int startY, int playerSize) : x(startX), y(startY), size(playerSize) {}

    void draw() {
        // Draw head (circle)
        circle(x, y, size / 4);

        // Draw body (rectangle)
        rectangle(x - size / 8, y + size / 4, x + size / 8, y + size / 2);

        // Draw legs (rectangles)
        rectangle(x - size / 8, y + size / 2, x - size / 4, y + size * 3 / 4);
        rectangle(x + size / 8, y + size / 2, x + size / 4, y + size * 3 / 4);

        // Draw arms (lines)
        line(x - size / 4, y + size / 4, x - size / 2, y + size / 2);
        line(x + size / 4, y + size / 4, x + size / 2, y + size / 2);
    }

    void fall() {
        y += 5; // ����������� ���������� Y, ����� ����� �����
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    int getSize() const {
        return size;
    }
};
class Obstacle {
private:
    int x1, y1; // ���������� ������ �����������
    int x2, y2; // ���������� ����� �����������

public:
    Obstacle(int startX1, int startY1, int startX2, int startY2) : x1(startX1), y1(startY1), x2(startX2), y2(startY2) {}

    void draw() {
        // Draw obstacle (line)
        line(x1, y1, x2, y2);
    }

    int getX1() const {
        return x1;
    }

    int getX2() const {
        return x2;
    }

    int getTopY() const {
        return y1; // ���������� Y-���������� ������� ����� �����������
    }

    int getBottomY() const {
        return y2; // ���������� Y-���������� ������ ����� �����������
    }
};

int main() {
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT);

    Player player(100, 50, 30); // ������� ������ � ������ ������ ��� ������������
    Obstacle obstacle(150, 300, 300, 300); // ������� ����������� (�����) ����� (150, 300) � (300, 300)

    while (!kbhit()) { // ���� ����� �����������, ���� �� ������ �������
        cleardevice(); // ������� �����

        // ������ ������ � �����������
        player.draw();
        obstacle.draw();

        // ���������, ���� ������ ������� ������ ��������� ���� ������� ������� ����������� � ������� ������� ������ ���� ������ ������� �����������, �� ����� ������
        if (player.getY() + player.getSize() < obstacle.getTopY() || player.getY() + player.getSize() < WINDOW_HEIGHT) {
            player.fall();
        }
        delay(50); // �������� ��� �������� ��������

        // ��������� �����
        swapbuffers();
    }

    closegraph();
    return 0;
}