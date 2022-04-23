#include "Player.h"
#include "Map.h"

Player::Player(float x, float y, float height, float width, String fileName) { // Конструктор для создания игрока
    heroImage.loadFromFile(fileName); // Загрузка изображения из файла по заданому пути
    heroImage.createMaskFromColor(Color::White); // Создание маски для белого цвета (белый цвет не будет отображатся)
    heroTexture.loadFromImage(heroImage); // Загружаем текстуру из изображения
    heroSprite.setTexture(heroTexture); // Загрузка спрайта из текстуры
    heroSprite.setTextureRect(IntRect(1, 0, 15, 26)); // Отображаем только заданый прямоугольник
    heroSprite.setPosition(x, y); // Ставим спрайт у заданую позицию
    dir = LEFT; // Инициализируем направление
    this->x = x; // Инициализция текущих координат персонажа
    this->y = y;
    this->height = height; // Инициализация высоты и ширины спрайта
    this->width = width;
    this->fileName = fileName; // Инициализация пути к картинке
    isTeleport = false; // Телепортироватся мы не будем)
    maskCounter = 0; // Масок собрано 0
    isGameOver = false; // Игра не окончена
    isEaten = false;
    chaseMode = false;
}


void Player::InteractWithMap(Direction &dir, Map &map) { // Функция для взаемодействия с картой
    width = dir == LEFT || dir == RIGHT ? 15 : 14; // В зависимости от направления движения изменяется ширина спрайта
    for (int i = x / 32; i < (x + width) / 32; i++) { // Проход по спрайту по х
        for (int j = (y + 10) / 32; j < (y + height) / 32; j++) { // Проход по у
            if (map.MapTile[j][i] == '0') { // Если спрайт столкнулся со стенкой('0'), то
                if (dir == LEFT) { // В зависимости от напрвления движения меняем х или у
                    x = (i * 32) + 32;
                } else if (dir == RIGHT) {
                    x = (i * 32) - width;
                } else if (dir == DOWN) {
                    y = (j * 32) - height;
                } else if (dir == UP) {
                    y = (j * 32) + 22;
                }
            }
            if (map.MapTile[j][i] == 'm') { // Если находим на маску ('m'), то счетчик увеличивается
                map.MapTile[j][i] = ' '; // и маска меняется на пустой камушек
                maskCounter++;
            }
            if (map.MapTile[j][i] == 'a') { // Если встечаем антисептик ('a'), то счетчик так же уеличивается
                map.MapTile[j][i] = ' '; // и маска меняется на пустой камушек
                chaseMode = true;
                maskCounter += 10;
            }
            if (map.MapTile[j][i] == 't') { // Если находим на телепорт ('t'),то
                isTeleport = true; // Булевая переменная принимает значения true
                break;
            }
        }
    }
}

// ypos - позиция по игреку на картинке.
void Player::animate(Direction dir, int ypos) { // Анимация персонажа
    if (dir == LEFT || dir == RIGHT) { // Если двигаемся влево или вправо
        int multiple1 = dir == LEFT ? 1 : -1; // Если движемся влево, то множитель 1, вправо -- -1
        int multiple2 = dir == LEFT ? 0 : 1; // Если движемся влево,то множитель 0, вправо - 1

        /* При отображении персонажа с картинки мы передаем начальную позицию и ширину с высотой тайла

        Символ "*" - начальная позиция, "/" - конечная точка, "-" - движение по картинке

        Для отображения движения вправо мы програмно переворачиваем тайлсет.

        Нормальное отображение спрайта             Програмно переворачиваем
        *-----										-----*
             -										-
             -										-
             /										/

        Так же ось игреков немного отличается от прывычной нам, игреки снизу позитивные и увеличиваются, а сверху негативные.

        */
        // 16 это ширина нашего тайла, при движении вправо нам нужно добавить ширину поскольку у нас начальная позиция будет смещена вправо
        heroSprite.setTextureRect(IntRect(16 * multiple2 + 16 * (int) currentFrame, ypos, 15 * multiple1, 26));
    } else { // Координат по игреку мы передаем в качестве аргумента функции, а координата по х будет зависить от текущего кадра
        heroSprite.setTextureRect(IntRect(16 * (int) currentFrame, ypos, 14, 26));
    }
}

void Player::update(Direction dir, float time, Map &map) { // Функция для обновления позиции игрока
    currentFrame += 0.005 * time; // Изменяем переменную, которая отвечает за текущий кадр
    if (currentFrame >= 4) { // У нас 4 кадра, мы откатуемся к первому кадру, если мы дошли к 4 кадру
        currentFrame -= 4;
    }
    speed = 0.1; // Устанавливаем скорость
    switch (dir) { // В зависимости от направления изменяем соответсвующую координату и вызываем функцию для анимации персонажа
        case LEFT:
            x -= speed * time;
            animate(dir, 1);
            break;
        case RIGHT:
            x += speed * time;
            animate(dir, 1);
            break;
        case UP:
            y -= speed * time;
            animate(dir, 59);
            break;
        case DOWN:
            y += speed * time;
            animate(dir, 29);
            break;
    }
    speed = 0; // Зануляем скорость
    isTeleport = false; // Телепортироватся мы не будем
    InteractWithMap(dir, map); // Взаемодействие с картой
    if (isTeleport) { // Телепортация на соответвующею точку в зависимости от направления движения
        x = dir == LEFT ? 840 : 32;
    }
    heroSprite.setPosition(x, y); // Устанавливаем спрайт на заданую позицию
}

void Player::Control(float time, Map &map) { //Функция для управления персонажем
    isGameOver = isEaten || map.getMaskCounter() == 0; // Если масок нет, то игра окончена
    if (!isGameOver) { // Если игра не окончена, то мы можем управлять персонажем
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            update(LEFT, time, map);
        } else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            update(RIGHT, time, map);
        } else if (Keyboard::isKeyPressed(Keyboard::Up)) {
            update(UP, time, map);
        } else if (Keyboard::isKeyPressed(Keyboard::Down)) {
            update(DOWN, time, map);
        }
    } else { // Если же игра окнчена, то при нажатии на "Пробел" игра перезапустится
        //x = 40; y = 48;
        //update(LEFT, time, map);
    }
}
