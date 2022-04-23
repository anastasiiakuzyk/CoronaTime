#include <SFML/Graphics.hpp>
#include "Map.h"

#pragma once

using namespace sf;

class Player {// Класс "Игрок"
    float timer;
public:
    bool isGameOver; // Переменная: закончилась ли игра
    enum Direction {
        UP, RIGHT, DOWN, LEFT
    }; // Перечисление всех возможных направлений
    Direction dir; // Создание экземпляра перечисления
    bool isEaten, chaseMode, isTeleport; // Булевое значение для проверки: телепортируемся или нет;
    float x, y, width, height, currentFrame = 0, speed = 0; // Переменные для текущей позиции по х и у, высота и ширина спрайта, текущий кадр тайлсета и скорость
    String fileName; // Путь к изображению
    Image heroImage; // Изображение персонажа
    Texture heroTexture; // Текстура персонажа
    Sprite heroSprite; // Спрайт персонажа
    int maskCounter; // Количество масок собрано
    Player(float x, float y, float height, float width, String fileName); // Конструктор для создания игрока
    Player() {} // Пустой конструктор
    void update(Direction dir, float time, Map &); // Обновление позиции персонажа
    Sprite getHero() { return heroSprite; } // Геттер для спрайта игрока
    float &getX() { return x; } // Геттер для текущей позиции по х
    float &getY() { return y; } // Геттер для текущей позиции по у
    void Control(float, Map &); // Функция для взаемодействия с персонажем
    void InteractWithMap(Direction &, Map &); // Функция для взаесодействия игрока с картой
    void animate(Direction dir, int ypos); // Функция для анимации персонажа
};