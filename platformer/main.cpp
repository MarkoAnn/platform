#include <iostream>
#include <vector>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;

class Player {
private:
    int x, y; // Координаты игрока
    int size; // Размер игрока

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
        y += 5; // Увеличиваем координату Y, чтобы игрок падал
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
    int x1, y1; // Координаты начала препятствия
    int x2, y2; // Координаты конца препятствия

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

    int getY() const {
        return y1; // Оба конца линии имеют одну и ту же координату Y
    }
};

int main() {
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT);

    Player player(200, 50, 30); // Создаем игрока с координатами (200, 50) и размером 30
    Obstacle obstacle(150, 300, 300, 300);
    while (!kbhit()) { // Цикл будет выполняться, пока не нажата клавиша
        cleardevice(); // Очищаем экран

        // Рисуем игрока
        player.draw();
        obstacle.draw();

        // Проверяем, если игрок не находится на препятствии, то падаем
        if (player.getY() + player.getSize() < obstacle.getY()) {
            player.fall();
        }


        delay(50); // Задержка для плавного движения

        // Обновляем экран
        swapbuffers();
    }

    closegraph();
    return 0;
}