#ifndef CLASSES_H
#define CLASSES_H
#include <iostream>
#include <vector>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")
const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;
const int PLAYER_SPEED = 5; // Скорость движения игрока
bool isGrounded = false; // Флаг, указывающий, приземлен ли игрок
class Player {
private:
    int x, y; // Координаты игрока
    int size; // Размер игрока
    float vertical_velocity;
    int yVelocity;
public:
    Player(int startX, int startY, int playerSize) : x(startX), y(startY), size(playerSize), yVelocity(0) {}

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

    void fall(int obstacleTopY) {
        y += yVelocity; // Обновляем вертикальную координату игрока
        yVelocity += 1; // Увеличиваем скорость падения

        // Если игрок достигает верхней части препятствия, обнуляем вертикальную скорость
        if (y >= obstacleTopY - size / 2) {
            y = obstacleTopY - size / 2;
            yVelocity = 0;
            isGrounded = true;
        }
        else {
            isGrounded = false;
        }
    }
    void setGrounded(bool grounded) {
        if (grounded)
            vertical_velocity = 0; // Обнуляем вертикальную скорость при приземлении
        isGrounded = grounded;
    }

    void moveLeft() {
        x -= PLAYER_SPEED; // Уменьшаем координату X, чтобы игрок двигался влево
    }

    void moveRight() {
        x += PLAYER_SPEED; // Увеличиваем координату X, чтобы игрок двигался вправо
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

    void jump() {
        if (isGrounded) {
            yVelocity = -15; // Устанавливаем скорость вверх для прыжка
            isGrounded = false; // Отмечаем, что игрок больше не на земле
        }
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

#endif // CLASSES_H
