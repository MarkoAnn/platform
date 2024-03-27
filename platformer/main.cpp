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

    int getTopY() const {
        return y1; // Возвращаем Y-координату верхней части препятствия
    }

    int getBottomY() const {
        return y2; // Возвращаем Y-координату нижней части препятствия
    }
};
// Функция для проверки пересечения двух прямоугольников
bool isRectangleIntersecting(int x1, int y1, int width1, int height1,
    int x2, int y2, int width2, int height2) {
    // Проверяем, что прямоугольники не пересекаются
    if (x1 > x2 + width2 || x2 > x1 + width1 ||
        y1 > y2 + height2 || y2 > y1 + height1) {
        return false;
    }
    return true;
}

int main() {
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT);

    Player player(200, 50, 30); // Создаем игрока в центре экрана над препятствием
    Obstacle obstacle(150, 300, 300, 300); // Создаем препятствие (линию) между (150, 300) и (300, 300)

    while (!kbhit()) { // Цикл будет выполняться, пока не нажата клавиша
        cleardevice(); // Очищаем экран

        // Рисуем игрока и препятствие
        player.draw();
        obstacle.draw();

        // Проверяем, если препятствие под игроком, то игрок падает
        if (!isRectangleIntersecting(player.getX() - player.getSize() / 2, player.getY() - player.getSize() / 2, player.getSize(), player.getSize(),
            obstacle.getX1(), obstacle.getTopY(), obstacle.getX2() - obstacle.getX1(), obstacle.getBottomY() - obstacle.getTopY())) {
            player.fall();
        }

        delay(50); // Задержка для плавного движения

        // Обновляем экран
        swapbuffers();
    }

    closegraph();
    return 0;
}