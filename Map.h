#pragma once

#include "SFML/Graphics.hpp"

using namespace sf;

class Map {
    Texture mapTexture; // Текстура карты
    Sprite mapSprite; // Спрайт карты
    const int mapheigh = 28; // Высота карты
    const int mapwidth = 28; // Ширина карты
    int maskCounter; // Счетчик масок на карте
public:
    Vector2f turns[39];
    Vector2f turns1[39];
    Vector2f turns2[39];
    Vector2f turns3[39];
    Vector2f turns4[39];

    int getMaskCounter() { return maskCounter; } // Геттер для получения числа масок на карте
    void drawMap(RenderWindow &window); // Функция для отрисовки карты
    Map(String path); // Контсруктор для загрузки текстуры карты
    void RestartMap(); // Функция для перезапуска карты
    String MapTile[28] = {    // Карта для грока
            "0000000000000000000000000000",
            "0mmmmmmmmmmmm00mmmmmmmmmmmm0",
            "0m0000m00000m00m00000m0000m0",
            "0a00f0m00f00m00m00f00m0f00a0",
            "0m0000m00000m00m00000m0000m0",
            "0mmmmmmmmmmmmmmmmmmmmmmmmmm0",
            "0m0000m00m00000000m00m0000m0",
            "0m0000m00m00000000m00m0000m0",
            "0mmmmmm00mmmm00mmmm00mmmmmm0",
            "000000m00000 00 00000m000000",
            "000f00m00000 00 00000m00f000",
            "0000d0m00          00m0d0000",
            "000000m00 000  000 00m000000",
            "t     m   0      0   m     t",
            "t     m   0      0   m     t",
            "000000m00 0      0 00m000000",
            "000g00m00 00000000 00m00g000",
            "00f000m00          00m000f00",
            "000000m00 00000000 00m000000",
            "0mmmmmmmmmmmm00mmmmmmmmmmmm0",
            "0m0000m00000m00m00000m0000m0",
            "0m0000m00000m00m00000m0000m0",
            "0mmm00mmmmmmmmmmmmmmmm00mmm0",
            "000m00m00m00000000m00m00m000",
            "0mmmmmm00mmmm00mmmm00mmmmmm0",
            "0a0000000000m00m0000000000a0",
            "0mmmmmmmmmmmmmmmmmmmmmmmmmm0",
            "0000000000000000000000000000"
    };
    String vMap[28] = {     // Карта для врагов
            "0000000000000000000000000000",
            "0     s      00      s     0",
            "0 0000 00000 00 00000 0000 0",
            "0 0000 00000 00 00000 0000 0",
            "0 0000 00000 00 00000 0000 0",
            "0s    s  s  s  s  s  s    s0",
            "0 0000 00 00000000 00 0000 0",
            "0 0000 00 00000000 00 0000 0",
            "0     s00    00    00s     0",
            "000000 00000 00 00000 000000",
            "000000 00000 00 00000 000000",
            "000000 00   s  s   00 000000",
            "000000 00 000  000 00 000000",
            "t     s  s0      0s  s     t",
            "t     s  s0      0s  s     t",
            "000000 00 0      0 00 000000",
            "000000 00 00000000 00 000000",
            "000000 00s        s00 000000",
            "000000 00 00000000 00 000000",
            "0     s  s   00   s  s     0",
            "0 0000 00000 00 00000 0000 0",
            "0 0000 00000 00 00000 0000 0",
            "0   00s  s  s  s  s  s00   0",
            "000 00 00 00000000 00 00 000",
            "0  s  s00    00    00   s  0",
            "0 0000000000 00 0000000000 0",
            "0           s  s           0",
            "0000000000000000000000000000"
    };
};

// Карта для перезагрузки
const String mapT[28] = {
        "0000000000000000000000000000",
        "0mmmmmmmmmmmm00mmmmmmmmmmmm0",
        "0m0000m00000m00m00000m0000m0",
        "0a00f0m00f00m00m00f00m0f00a0",
        "0m0000m00000m00m00000m0000m0",
        "0mmmmmmmmmmmmmmmmmmmmmmmmmm0",
        "0m0000m00m00000000m00m0000m0",
        "0m0000m00m00000000m00m0000m0",
        "0mmmmmm00mmmm00mmmm00mmmmmm0",
        "000000m00000 00 00000m000000",
        "000f00m00000 00 00000m00f000",
        "0000d0m00          00m0d0000",
        "000000m00 000  000 00m000000",
        "t     m   0      0   m     t",
        "t     m   0      0   m     t",
        "000000m00 0      0 00m000000",
        "000g00m00 00000000 00m00g000",
        "00f000m00          00m000f00",
        "000000m00 00000000 00m000000",
        "0mmmmmmmmmmmm00mmmmmmmmmmmm0",
        "0m0000m00000m00m00000m0000m0",
        "0m0000m00000m00m00000m0000m0",
        "0mmm00mmmmmmmmmmmmmmmm00mmm0",
        "000m00m00m00000000m00m00m000",
        "0mmmmmm00mmmm00mmmm00mmmmmm0",
        "0a0000000000m00m0000000000a0",
        "0mmmmmmmmmmmmmmmmmmmmmmmmmm0",
        "0000000000000000000000000000"
};