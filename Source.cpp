#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Map.h"
#include "Enemy.h"
#include "FontActions.h"
#include <sstream>

using namespace sf;

int main() {
    RenderWindow window(VideoMode(1150, 900), "Coronatime"); // Создание игрового окна
    Player p(40, 48, 26, 15,
             "sources/images/Final.png"); // Создание игрока
    Map map("sources/images/mapplus.png"); // Создание карты
    Enemy Red(416, 448, 28, 28,
              "sources/images/Red.png", "Red"); // Создание недоврага
    Enemy Purple(416, 448, 28, 28,
                 "sources/images/Purple.png", "Purple"); // Создание недоврага
    Enemy Green(448, 448, 28, 28,
                "sources/images/Green.png", "Green"); // Создание недоврага
    Enemy Orange(448, 448, 28, 28,
                 "sources/images/Orange.png", "Orange"); // Создание недоврага
    Clock clock; // Обьявление таймера
    float timer;
    FontActions font("sources/font.ttf"); // Создание обьекта для отрисоки текста

    Music music;
    if (!music.openFromFile("sources/Virus.ogg"))
        return -1; // error
    music.play();
    music.setLoop(true);
    while (window.isOpen()) { // Основной цикл
        if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
        timer = clock.getElapsedTime().asMicroseconds(); // Запись времени в макросекндах
        timer /= 800;
        clock.restart(); // Перезапуск таймера
        sf::Event event{}; // Обьявление обьекта события
        while (window.pollEvent(event)) { // Проверка всех событий
            if (event.type == sf::Event::Closed) // Если события это событие закртия, то
                window.close(); // Закрыть окно
        }
        p.Control(timer, map); // Функция класса Player для управления игроком
        Red.setPlayer(p, &p.isEaten,
                      &p.chaseMode); // Передача обьекту врага ссылки на обьект игрока для отслеживания текущих координат
        Red.update(timer, map); // Обновление позиции врага

        Purple.setPlayer(p, &p.isEaten,
                         &p.chaseMode); // Передача обьекту врага ссылки на обьект игрока для отслеживания текущих координат
        Purple.update(timer, map); // Обновление позиции врага

        Green.setPlayer(p, &p.isEaten,
                        &p.chaseMode); // Передача обьекту врага ссылки на обьект игрока для отслеживания текущих координат
        Green.update(timer, map); // Обновление позиции врага

        Orange.setPlayer(p, &p.isEaten,
                         &p.chaseMode); // Передача обьекту врага ссылки на обьект игрока для отслеживания текущих координат
        Orange.update(timer, map); // Обновление позиции врага

        window.clear(); // Очищение окна
        if (map.getMaskCounter() != 0 && !p.isEaten) { // Если маски еще есть на карте, то
            map.drawMap(window); // Фунция класса Map для отрисовки карты
            window.draw(p.getHero()); // Функция класса Player для отриовки игрока
            window.draw(Red.heroSprite); // Функция класса Enemy для отрисовки врага
            window.draw(Purple.heroSprite); // Функция класса Enemy для отрисовки врага
            window.draw(Green.heroSprite); // Функция класса Enemy для отрисовки врага
            window.draw(Orange.heroSprite); // Функция класса Enemy для отрисовки врага
            std::ostringstream str; // Создание строкового потока
            str << p.maskCounter; // Запись в поток числа собраных масок
            font.drawText(window, str); // Функция класса FontActions для отрисовки очков
        } else {
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                p.maskCounter = 0; // Обнуление счетчика
                map.RestartMap(); // Перезапуск карты
                p.isEaten = false;
                Red.x = 416, Red.y = 448;
                Red.dir = Enemy::Direction::UP;
                Purple.x = 416, Purple.y = 448;
                Purple.dir = Enemy::Direction::UP;
                Green.x = 448, Green.y = 448;
                Green.dir = Enemy::Direction::UP;
                Orange.x = 448, Orange.y = 448;
                Orange.dir = Enemy::Direction::UP;
                p.x = 40;
                p.y = 48;
                p.heroSprite.setPosition(p.x, p.y);
            } else {
                std::ostringstream str; // Создание строкового потока
                str << p.maskCounter; // Запись в поток числа собраных масок
                if (!p.isEaten) {
                    font.drawWin(window, str); // Фунция класса FontActions для отрисовки конца игры
                } else {
                    font.drawLose(window, str);
                }
            }
        }
        window.display(); // Отображение всех отрисованых деталей
    }
    return 0;
}