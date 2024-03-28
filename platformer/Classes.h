#ifndef CLASSES_H
#define CLASSES_H
#include <iostream>
#include <vector>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")
const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;
const int PLAYER_SPEED = 5; // Ñêîðîñòü äâèæåíèÿ èãðîêà


const int GRAVITY = 1; // Ускорение свободного падения
const int MAX_FALL_SPEED = 15; // Максимальная скорость падения
class Player {
private:
    int x, y; // Êîîðäèíàòû èãðîêà
    int size; // Ðàçìåð èãðîêà

    int yVelocity;
public:
    bool isGrounded = false; // Ôëàã, óêàçûâàþùèé, ïðèçåìëåí ëè èãðîê
    Player(int startX, int startY, int playerSize) : x(startX), y(startY), size(playerSize), yVelocity(0), isGrounded(false) {}

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

        // Проверяем столкновение с препятствием
        if (y >= obstacleTopY - size / 2) {
            y = obstacleTopY - size / 2 - 8; // Устанавливаем игрока над препятствием
            yVelocity = 0; // Обнуляем вертикальную скорость при столкновении с препятствием
            isGrounded = true; // Игрок приземлился
        }
    }
    bool isOnGround() const {
        return isGrounded;
    }

    void setGrounded(bool grounded) {
        isGrounded = grounded;
    }




    void moveLeft() {
        x -= PLAYER_SPEED; // Óìåíüøàåì êîîðäèíàòó X, ÷òîáû èãðîê äâèãàëñÿ âëåâî
    }

    void moveRight() {
        x += PLAYER_SPEED; // Óâåëè÷èâàåì êîîðäèíàòó X, ÷òîáû èãðîê äâèãàëñÿ âïðàâî
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
            yVelocity = -15; // Устанавливаем вертикальную скорость вверх для прыжка
            isGrounded = false; // Игрок больше не приземлен
        }
    }
};

class Obstacle {
private:
    int x1, y1; // Êîîðäèíàòû íà÷àëà ïðåïÿòñòâèÿ
    int x2, y2; // Êîîðäèíàòû êîíöà ïðåïÿòñòâèÿ

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
        return y1; // Âîçâðàùàåì Y-êîîðäèíàòó âåðõíåé ÷àñòè ïðåïÿòñòâèÿ
    }

    int getBottomY() const {
        return y2; // Âîçâðàùàåì Y-êîîðäèíàòó íèæíåé ÷àñòè ïðåïÿòñòâèÿ
    }
};

#endif // CLASSES_H