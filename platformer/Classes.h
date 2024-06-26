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

class Collider {
protected:
    int x, y; // Координаты объекта
    int width, height; // Размеры объекта

public:
    
    Collider() : x(0), y(0), width(0), height(0) {}

    Collider(int startX, int startY, int objWidth, int objHeight) : x(startX), y(startY), width(objWidth), height(objHeight) {}

    bool IsOverlapping(const Collider& other) const {
        return !(x + width < other.x || other.x + other.width < x || y + height < other.y || other.y + other.height < y);
    }

    bool IsOnCollider(const Collider& other) const {
        return IsOverlapping(Collider(x, y + height, width, 2)); // Проверяем нахождение "под" объектом
    }
};

class Player : public Collider {
private:
    int x, y; // Êîîðäèíàòû èãðîêà
    int size; // Ðàçìåð èãðîêà

    int yVelocity = 0;
    int xVelocity = 0;
    
public:
    bool isGrounded = false; // Ôëàã, óêàçûâàþùèé, ïðèçåìëåí ëè èãðîê
    Player(int startX, int startY, int playerSize) : x(startX), y(startY), size(playerSize), yVelocity(0), isGrounded(false) {}

  
    void draw() {
        // draw player area (for debug)
        rectangle(x, y, x + size, y + size);
        int xc = x + size / 2;
        int yc = y + size / 2;
        // Draw head (circle)
        circle(xc, y, size / 4);

        // Draw body (rectangle)
        rectangle(xc - size / 8, y + size / 4, xc + size / 8, y + size / 2);

        // Draw legs (rectangles)
        rectangle(xc - size / 8, y + size / 2, xc - size / 4, y + size );
        rectangle(xc + size / 8, y + size / 2, xc + size / 4, y + size );

        // Draw arms (lines)
        line(xc - size / 4, y + size / 4, xc - size / 2, y + size / 2);
        line(xc + size / 4, y + size / 4, xc + size / 2, y + size / 2);
    }


    void setBottomOn(int y) {
        this->y = y - size;
    }
    bool isOnGround() const {
        return isGrounded;
    }

    void setGrounded(bool grounded) {
        isGrounded = grounded;
    }

    void addVelocity(int x, int y) {
        xVelocity = xVelocity + x;
        yVelocity =  yVelocity + y;
    }

    void setVelocityY(int y) {
        yVelocity = y;
    }

    void setVelocityX(int x) {
        xVelocity = x;
    }

    void update() {
       
        y = y + yVelocity;
        x = x + xVelocity;
    }


    void moveLeft() {
        xVelocity = -PLAYER_SPEED; // Óìåíüøàåì êîîðäèíàòó X, ÷òîáû èãðîê äâèãàëñÿ âëåâî
    }

    void moveRight() {
        xVelocity = +PLAYER_SPEED; // Óâåëè÷èâàåì êîîðäèíàòó X, ÷òîáû èãðîê äâèãàëñÿ âïðàâî
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

class Obstacle : public Collider {
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