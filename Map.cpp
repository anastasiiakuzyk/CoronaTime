#include "Map.h"

using namespace sf;

void Map::RestartMap() { // Перезапуск карты
    for (int i = 0; i < mapheigh; i++) {
        MapTile[i] = mapT[i]; // Присваиваем изменненой карте стартовую карту
    }
    maskCounter = 1;
}

void Map::drawMap(RenderWindow &window) {
    maskCounter = 0; // Обнуление количества масок
    for (int i = 0; i < mapheigh; i++) { // Проход по всей "карте"
        for (int j = 0; j < mapwidth; j++) {
            if (MapTile[i][j] == '0') { // Если натыкаемся на "0", то это стена
                mapSprite.setTextureRect(IntRect(96, 0, 32, 32));
            } else if (MapTile[i][j] == 'f') { // Если натыкаемся на "0", то это стена
                mapSprite.setTextureRect(IntRect(128, 0, 32, 32));
            } else if (MapTile[i][j] == 'd') { // Если натыкаемся на "0", то это стена
                mapSprite.setTextureRect(IntRect(160, 0, 32, 32));
            } else if (MapTile[i][j] == 'g') { // Если натыкаемся на "0", то это стена
                mapSprite.setTextureRect(IntRect(192, 0, 32, 32));
            } else if (MapTile[i][j] == ' ' ||
                       MapTile[i][j] == 't') { // Если натыкаемся на " " или "t", то это дефолтный камушек
                mapSprite.setTextureRect(IntRect(32, 0, 32, 32));
            } else if (MapTile[i][j] == 'm') { // Если натыкаемся на "m", то это маска
                mapSprite.setTextureRect(IntRect(0, 0, 32, 32));
                maskCounter++;
            } else if (MapTile[i][j] == 'a') { // Если натыкаемся на "a", то это антисептик
                mapSprite.setTextureRect(IntRect(64, 0, 32, 32));
                maskCounter++;
            }
            mapSprite.setPosition(j * 32, i * 32); // Ставим каждому тайлу позицию
            window.draw(mapSprite); // И прорисовываем этот тайл
        }
    }
}

Map::Map(String path) { // Констуктор для загрузки текстуры карты
    mapTexture.loadFromFile(path); // Загружаем текстуру с файла за даным путем
    mapSprite.setTexture(mapTexture); // Загрузка текстуры в спрайт
    maskCounter = 1;
    int k = 0;
    for (int i = 0; i < mapheigh; i++) {
        for (int j = 0; j < mapwidth; j++) {
            if (vMap[i][j] == 's') {
                turns[k++] = {(float) j * 32 + 16, (float) i * 32 + 14};
            }
        }
    }
    k = 0;
    for (int i = 0; i < mapheigh; i++) {
        for (int j = 0; j < mapwidth; j++) {
            if (vMap[i][j] == 's') {
                turns1[k++] = {(float) j * 32 + 16, (float) i * 32 + 18};
            }
        }
    }
    k = 0;
    for (int i = 0; i < mapheigh; i++) {
        for (int j = 0; j < mapwidth; j++) {
            if (vMap[i][j] == 's') {
                turns2[k++] = {(float) j * 32 + 14, (float) i * 32 + 16};
            }
        }
    }
    k = 0;
    for (int i = 0; i < mapheigh; i++) {
        for (int j = 0; j < mapwidth; j++) {
            if (vMap[i][j] == 's') {
                turns3[k++] = {(float) j * 32 + 18, (float) i * 32 + 16};
            }
        }
    }
    k = 0;
    for (int i = 0; i < mapheigh; i++) {
        for (int j = 0; j < mapwidth; j++) {
            if (vMap[i][j] == 's') {
                turns4[k++] = {(float) j * 32 + 16, (float) i * 32 + 16};
            }
        }
    }
}
