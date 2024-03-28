#include <iostream>
#include <vector>
#include "Classes.h"
#include "graphics.h"
#pragma comment(lib,"graphics.lib")
/* const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;
const int PLAYER_SPEED = 5; // Скорость движения игрока
bool isGrounded = false; // Флаг, указывающий, приземлен ли игрок*/


bool isPlayerOnObstacle(const Player& player, const Obstacle& obstacle) {
    int playerTop = player.getY() - player.getSize() / 2;
    int playerBottom = player.getY() + player.getSize() / 2;
    int playerLeft = player.getX() - player.getSize() / 2;
    int playerRight = player.getX() + player.getSize() / 2;

    int obstacleTop = obstacle.getTopY();
    int obstacleBottom = obstacle.getBottomY();
    int obstacleLeft = obstacle.getX1();
    int obstacleRight = obstacle.getX2();

    // Проверяем пересечение по горизонтали и вертикали
    bool horizontalOverlap = playerRight >= obstacleLeft && playerLeft <= obstacleRight;
    bool verticalOverlap = playerBottom >= obstacleTop && playerTop <= obstacleBottom;

    return horizontalOverlap && verticalOverlap;
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

    while (true) { // Цикл будет выполняться, пока не нажата клавиша
        cleardevice(); // Очищаем экран
        // Рисуем игрока и препятствие
        player.draw();
        obstacle.draw(); // Отрисовываем препятствие
       
        bool isGrounded = (player.getY() >= obstacle.getTopY() - player.getSize() / 2);
        if (isPlayerOnObstacle(player, obstacle)) {
            player.fall(obstacle.getTopY()); // Пересчитываем скорость падения, если игрок на препятствии
        }
        else {
            player.fall(WINDOW_HEIGHT); // Иначе просто падаем вниз
        }
        
    // Проверяем нажатие клавиш
        if (kbhit()) {
            char key = getch(); // Получаем код нажатой клавиши

         
            if (key == 32) { 
                player.jump(); // Вызываем метод прыжка для игрока
            }
            std::cout << "Pressed key: " << static_cast<int>(key) << std::endl; // Вывод нажатой клавиши

            // Выход из цикла, если нажата клавиша выхода (Esc)
            if (key == 27)
                break;

            // Вызываем функцию для перемещения игрока
            move(key, player);
        }
   
        // Обновляем экран
        swapbuffers();

        delay(50); // Задержка для плавного движения
    }

    closegraph();
    return 0;
}