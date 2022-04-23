#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;
using namespace std;

class FontActions { // Класс работы с текстом
    Font font; // шрифт
    Text text; // текст
public:
    FontActions(String); // Конструктор для загрузки шрифта и инициализации обьекта класса text
    void drawText(RenderWindow &, ostringstream &); // Отрисовка "очков" игрока
    void drawLose(RenderWindow &, ostringstream &); // Вывод на экран сообщения о победе
    void drawWin(RenderWindow &, ostringstream &); // Вывод на экран сообщения о победе
};