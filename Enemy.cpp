#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

float Enemy::countDistance() {
    return sqrt(pow(tmpX - x, 2) + pow(tmpY - y, 2));
}

float Enemy::countDistanceForRed(float x, float y) {
    if (chase) {
        return sqrt(pow(player.x - x, 2) + pow(player.y - y, 2)); // Расчет дистанции от врага к игроку
    } else {
        return sqrt(pow(928 - x, 2) + pow(0 - y, 2));
    }
}

float Enemy::countDistanceForGreen(float x, float y, Enemy::Direction dir) {
    if (chase) {
        int multiple = 0;
        if (dir == DOWN) {
            multiple = 6;
        }
        return sqrt(pow((player.x + multiple * 32) - x, 2) +
                    pow((player.y + 6 * 32) - y, 2)); // Расчет дистанции от врага к игроку
    } else {
        return sqrt(pow(928 - x, 2) + pow(960 - y, 2));
    }
}

float Enemy::countDistanceForOrange(float x, float y) {
    if (chase) {
        float dist = sqrt(pow(player.x - x, 2) + pow(player.y - y, 2));
        if (dist <= 256) { // 8 * 32
            return sqrt(pow(0 - x, 2) + pow(960 - y, 2));
        } else {
            return dist;
        }
    } else {
        return sqrt(pow(0 - x, 2) + pow(960 - y, 2));
    }
}

float Enemy::countDistanceForPurple(float x, float y, Direction dir) {
    if (chase) {
        int multiple = 0;
        if (dir == UP) {
            multiple = 4;
        }
        return sqrt(pow((player.x - multiple * 32) - x, 2) +
                    pow((player.y - 4 * 32) - y, 2)); // Расчет дистанции от врага к игроку
    } else {
        return sqrt(pow(0 - x, 2) + pow(0 - y, 2));
    }
}


Enemy::Enemy(float x, float y, int height, int width, String fileName, String Name) { // Создание врага
    name = Name;
    heroImage.loadFromFile(fileName); // Загрузка изображения из файла
    heroImage.createMaskFromColor(Color::White); // Создаем маску для белого цвета
    heroTexture.loadFromImage(heroImage); // Загружаем в текстуру изображение
    heroSprite.setPosition(x, y); // Устанавливаем позицию справйта
    scareImage.loadFromFile("sources/images/virus.png");
    scareImage.createMaskFromColor(Color::White);
    scareTexture.loadFromImage(scareImage);
    this->x = x; // Устанавливаем координату по х и у
    this->y = y;
    this->height = height; // Устанавливаем высоту и ширину
    this->width = width;
    this->fileName = fileName; // Устанавливаем путь к файлу
    isTeleport = false; // Не телепортируемся
    dir = UP; // Первоначальное направление = вверх
    eat = NULL;
    chase = true;
    isScary = false;
    dist = 0;
    isMove = false;
}

void Enemy::update(float time, Map &map) { // Обновление позиции врага
    speed = 0.05; // Устанавливаем скорость
    timerForChasing += time;
    if (*isChase) {
//		std::cout << "Player false";
        chase = false;
        isScary = true;
        timerForChasing = 0;
        if (name == "Orange")
            *isChase = false;
    }
    if (isScary) {
        heroSprite.setTexture(scareTexture);
        heroSprite.setScale((float) 1 / 34.96, (float) 1 / 34.28);
    } else {
        heroSprite.setTexture(heroTexture);
        heroSprite.setScale((float) 1 / 34.96, (float) 1 / 34.28);
    }
    if (chase && timerForChasing >= 40000 || !chase && timerForChasing >= 20000 ||
        isScary && timerForChasing >= 10000) {
        chase = !chase;
        isScary = false;
//		std::cout << (chase == true ? "true" : "false");
        timerForChasing = 0;
    }
    switch (Enemy::dir) // В зависимоти от напрвления двигаемся
    {
        case LEFT:
            x -= speed * time;
            break;
        case RIGHT:
            x += speed * time;
            break;
        case UP:
            y -= speed * time;
            break;
        case DOWN:
            y += speed * time;
            break;
    }
    speed = 0; // Зануляем скорость
    isTeleport = false; // Без телепортов
    InteractWithMap(Enemy::dir, map); // Взаемодействуем с картой
    if (isTeleport) {
        x = Enemy::dir == LEFT ? 840 : 48;
    }
    heroSprite.setPosition(x, y); // Устанавливаем позицию спрайта
}

void Enemy::InteractWithMap(Direction &dir, Map &map) {
    Direction currDirection = dir; // Текущее направление для того чтоб дух не ходил назад
    Vector2f heroCoord = {x + width / 2, y + height / 2};
    for (int i = x / 32; i < (x + width) / 32; i++) { // Проверяем соприкасается ли спрайт с картой
        for (int j = y / 32; j < (y + height) / 32; j++) {
            if (map.vMap[j][i] == '0') { // Соприкоснавение с стенкой
                if (dir == LEFT) {
                    x = (i * 32) + 32;
                }
                if (dir == RIGHT) {
                    x = i * 32 - width;
                }
                if (dir == UP) {
                    y = j * 32 + 32;
                }
                if (dir == DOWN) {
                    y = j * 32 - height;
                }
                changeDirection(map, currDirection, dir);
            }
            if (map.vMap[j][i] == 't') { // Телепортируемся
                isTeleport = !((x >= 830 && x <= 840) || (x >= 48 && x <= 50));
                break;
            }
            if (!isScary) {
                if ((int) (heroCoord.x / 32) == (int) (player.x / 32) &&
                    (int) (heroCoord.y / 32) == ((int) player.y + 10) / 32) {
                    *eat = true;
                    break;
                }
            }

        }
    }
    float dist = countDistance();
    if (dist >= 32) {
        isMove = false;
    }
    if (!isMove) {
        if (dir == UP || dir == DOWN) {
            for (int i = 0; i < 41; i++) {
                if (((int) heroCoord.x == map.turns2[i].x && (int) heroCoord.y == map.turns2[i].y) ||
                    ((int) heroCoord.x == map.turns3[i].x && (int) heroCoord.y == map.turns3[i].y) ||
                    ((int) heroCoord.x == map.turns4[i].x && (int) heroCoord.y == map.turns4[i].y)) {

                    isMove = true;
                    tmpX = x;
                    tmpY = y;
                    changeDirection(map, currDirection, dir);
                    break;
                }
            }
        } else {
            for (int i = 0; i < 41; i++) {
                if (((int) heroCoord.x == map.turns[i].x && (int) heroCoord.y == map.turns[i].y) ||
                    ((int) heroCoord.x == map.turns1[i].x && (int) heroCoord.y == map.turns1[i].y) ||
                    ((int) heroCoord.x == map.turns4[i].x && (int) heroCoord.y == map.turns4[i].y)) {

                    isMove = true;
                    tmpX = x;
                    tmpY = y;
                    changeDirection(map, currDirection, dir);
                    break;
                }
            }
        }
    }
}


void Enemy::changeDirection(Map &map, Direction &currDir, Direction &dir) {
    Direction opositeDirection, tmp = UP;
    switch (currDir) {
        case LEFT:
            opositeDirection = RIGHT;
            break;
        case RIGHT:
            opositeDirection = LEFT;
            break;
        case UP:
            opositeDirection = DOWN;
            break;
        case DOWN:
            opositeDirection = UP;
            break;
    }
    int Xindex = x / 32, Yindex = y / 32, currX, currY;
    float currDist, minDist = 99999999;
    for (int i = 0; i < 4; i++) {
        currX = i == 0 || i == 2 ? x + width / 2 : (i == 1 ? x + width : x);
        currY = i == 1 || i == 3 ? y + height / 2 : (i == 0 ? y : y + height);
        if ((Direction) i == opositeDirection) {
            continue;
        }
        if ((Direction) i == LEFT) {
            if (map.vMap[Yindex][Xindex - 1] == '0') {
                continue;
            }
        }
        if ((Direction) i == RIGHT) {
            if (map.vMap[Yindex][Xindex + 1] == '0') {
                continue;
            }
        }
        if ((Direction) i == UP) {
            if (map.vMap[Yindex - 1][Xindex] == '0') {
                continue;
            }
        }
        if ((Direction) i == DOWN) {
            if (map.vMap[Yindex + 1][Xindex] == '0') {
                continue;
            }
        }
        if (name == "Red") {
            currDist = countDistanceForRed(currX, currY);
        } else if (name == "Purple") {
            currDist = countDistanceForPurple(currX, currY, currDir);
        } else if (name == "Green") {
            currDist = countDistanceForGreen(currX, currY, currDir);
        } else if (name == "Orange") {
            currDist = countDistanceForOrange(currX, currY);
        }
        if (currDist < minDist) {
            minDist = currDist;
            switch (i) {
                case 0:
                    tmp = UP;
                    break;
                case 1:
                    tmp = RIGHT;
                    break;
                case 2:
                    tmp = DOWN;
                    break;
                case 3:
                    tmp = LEFT;
                    break;
            }
        }
    }
    dir = tmp;
}