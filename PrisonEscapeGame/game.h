#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "player.h"
#include "room.h"
#include "item.h"
#include "enemy.h"
#include "commands.h"

#define MAX_INVENTORY 50
#define MAX_NAME 50
#define MAX_DESCRIPTION 256
#define MAX_ENEMIES 32
#define MAX_ITEMS 96

extern int playerX, playerY;

void initializePrison();
void printPrison();
void combat(Character *enemy);
void saveGame(const char *filepath);
bool loadGame(const char *filepath);
void freeMemory();
void handleRandomEvent();
void startGame();
void selectCharacterClass();
void showStatus();
void dropItem(Item *item);
void clearInputBuffer();
void showIntro();
void finalizeGame();

#endif // GAME_H