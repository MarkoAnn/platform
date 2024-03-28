#include <iostream>
#include "Classes.h"
#include <vector>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")
/* const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;
const int PLAYER_SPEED = 5; // Скорость движения игрока
bool isGrounded = false; // Флаг, указывающий, приземлен ли игрок*/


// Функция для проверки пересечения двух прямоугольников
bool isRectangleIntersecting(int x1, int y1, int width1, int height1,
    int x2, int y2, int width2, int height2) {
    // Проверяем пересечение двух прямоугольников
    if (x1 > x2 + width2 || x2 > x1 + width1 ||
        y1 > y2 + height2 || y2 > y1 + height1) {
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
        // Добавляем другие направления движения, если нужно
    }
}
int main() {
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT);

    Player player(200, 50, 30); // Создаем игрока в центре экрана над препятствием
    Obstacle obstacle(150, 300, 300, 300); // Создаем препятствие (линию) между (150, 300) и (300, 300)

    while (true) { // Цикл будет выполняться, пока не нажата клавиша
        cleardevice(); // Очищаем экран

        // Рисуем игрока и препятствие
        player.draw();
        obstacle.draw();

        // Проверяем столкновение с землей
        if (!isGrounded) {
            player.fall(obstacle.getTopY());

        }
        // Проверяем столкновение с препятствием
        if (isRectangleIntersecting(player.getX() - player.getSize() / 2, player.getY() + player.getSize() / 2, player.getSize(), 1,
            obstacle.getX1(), obstacle.getTopY(), obstacle.getX2() - obstacle.getX1(), 1))
            player.setGrounded(true);

        // Если игрок на земле, он должен падать
        if (!isGrounded)
            player.fall(obstacle.getTopY());


        // Проверяем нажатие клавиш
        if (kbhit()) {
            char key = getch(); // Получаем код клавиши
            std::cout << "Pressed key: " << static_cast<int>(key) << std::endl; // Вывод нажатой клавиши
            if (key == ' ') {
                player.jump();
            }
            // Выход из цикла, если нажата клавиша выхода (Esc)
            if (key == 27)
                break;

            // Вызываем функцию для перемещения игрока
            move(key, player);
        }

        delay(50); // Задержка для плавного движения

        // Обновляем экран
        swapbuffers();
    }

    closegraph();
    return 0;
}