#include "FontActions.h"
#include <sstream>

using namespace std;
using namespace sf;

FontActions::FontActions(String path) {
    font.loadFromFile(path); // Загрузка шрифта
    text.setFont(font); // Установка шрифта тексту
    text.setString("Score: "); // Задаем строку тексту
    text.setCharacterSize(50); // Установка размера текста
}

void FontActions::drawText(RenderWindow &window, ostringstream &str) { // Отрисовка "очков" игрока
    text.setString("Score: " + str.str()); // задаем строку с очками игрока
    text.setPosition(900, 100); // устанавливаем позицию для текста
    window.draw(text); // отрисовка текста
}

void FontActions::drawWin(RenderWindow &window, ostringstream &str) { // Отрисовка сообщения о конце игры
    text.setString(
            "You Win!\nYour score: " + str.str() + "\nTo restart press space.\nTo exit press Esc."); // Задаем строку
    text.setCharacterSize(100); // Задаем размер текста
    text.setPosition(100, 200); // Устанавливаем позицию текста
    window.draw(text); // Отрисовываем текст
    text.setCharacterSize(50); // Устанавливаем нормальный размер текста
}

void FontActions::drawLose(RenderWindow &window, ostringstream &str) { // Отрисовка сообщения о конце игры
    text.setString("You are infected!\nYour score: " + str.str() +
                   "\nTo restart press space.\nTo exit press Esc."); // Задаем строку
    text.setCharacterSize(100); // Задаем размер текста
    text.setPosition(100, 200); // Устанавливаем позицию текста
    window.draw(text); // Отрисовываем текст
    text.setCharacterSize(50); // Устанавливаем нормальный размер текста
}
