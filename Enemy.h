#pragma once

#include "Player.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy { // Наследуемся от абстрактного класса "Субьект"
    float dist, tmpX, tmpY;
    bool isMove;
public:
    enum Direction {
        UP, RIGHT, DOWN, LEFT
    }; // Перечисление всех возможных направлений
    Texture scareTexture;
    Image scareImage;
    String name;
    Player empty;
    Player &player = empty; // Для получения координат игрока в текущий момент времени
    float countDistanceForRed(float x, float y); // Вычисление дистанции от игрока к духу
    float countDistanceForPurple(float x, float y, Direction); // Вычисление дистанции от игрока к духу
    float countDistanceForGreen(float x, float y, Direction); // Вычисление дистанции от игрока к духу
    float countDistanceForOrange(float x, float y); // Вычисление дистанции от игрока к духу
    float countDistance();

    float timerForChasing;

    void changeDirection(Map &, Direction &, Direction &);

    bool *eat, chase, *isChase, isScary;
    Direction dir; // Создание экземпляра перечисления
    float x, y, width, height, currentFrame = 0, speed = 0; // Переменные для текущей позиции по х и у, высота и ширина спрайта, текущий кадр тайлсета и скорость
    String fileName; // Путь к изображению
    Image heroImage; // Изображение персонажа
    Texture heroTexture; // Текстура персонажа
    Sprite heroSprite; // Спрайт персонажа
    bool isTeleport; // Булевое значение для проверки: телепортируемся или нет
    Enemy(float x, float y, int height, int width, String fileName, String Name); // Конструктор для создания духа
    void InteractWithMap(Direction &,
                         Map &); // Взаемодействие с картой (Проверка на столкновения со стенами и проход в телепорт)
    void update(float time, Map &); // Передвижение духа
    void setPlayer(Player &p, bool *isEaten, bool *isChase) {
        player = p;
        eat = isEaten;
        this->isChase = isChase;
    } // Сеттер для ссылки на игрока
};