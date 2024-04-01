#include <iostream>
#include <vector>
#include "Classes.h"
#include "graphics.h"
#include "main.h"
#pragma comment(lib,"graphics.lib")
/* const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;
const int PLAYER_SPEED = 5; // Скорость движения игрока
bool isGrounded = false; // Флаг, указывающий, приземлен ли игрок*/


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

// Функция для перемещения игрока в зависимости от переданного направления
void move(char currentDirection, Player& player) {
    switch (currentDirection) {
    case 'a':
        player.moveLeft();
        break;
    case 'd':
        player.moveRight();
        break;
    case 32: // Код клавиши прыжка
        player.jump();
        break;
    }
}
int main() {
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT);

    Player player(200, 50, 30); // Создаем игрока в центре экрана
    Obstacle obstacle(150, 300, 300, 300); // Создаем препятствие (линию) между (150, 300) и (300, 300)



    mainLoop(player, obstacle);

    closegraph();
    return 0;
}

void mainLoop(Player& player, Obstacle& obstacle)
{
    while (true) { // Цикл будет выполняться, пока не нажата клавиша


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

        // Проверяем нажатие клавиш
        if (checkInput(player) == -1) {
            return;
        }

        player.update();
        // ensure player does not fall through the obstacle
        if (isPlayerInObstacle(player, obstacle)) {
            std::cout << "IN ground" << std::endl;
            player.setBottomOn(obstacle.getTopY());
        }

        // Обновляем экран
        swapbuffers();        
        cleardevice(); // Очищаем экран
        // Рисуем игрока и препятствие
        // ensure player does not fall through the obstacle
        player.draw();
        obstacle.draw(); // Отрисовываем препятствие

        delay(50); // Задержка для плавного движения
    }
}

int checkInput(Player& player)
{
    
    if (kbhit()) {
        char key = getch(); // Получаем код нажатой клавиши
        while (kbhit()) {
            key = getch(); // Получаем код нажатой клавиши
        }


        if (key == 32) {
            player.jump(); // Вызываем метод прыжка для игрока
        }
        std::cout << "Pressed key: " << static_cast<int>(key) << std::endl; // Вывод нажатой клавиши

        // Выход из цикла, если нажата клавиша выхода (Esc)
        if (key == 27)
        {
            return - 1;
        };

        // Вызываем функцию для перемещения игрока
        move(key, player);
    }
    return 0;
}
