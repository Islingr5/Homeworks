#ifndef COMMANDS_H
#define COMMANDS_H

#include "game.h"
#include "player.h"

void parseCommand(char *command);
void move(char *direction);
void look();
void attack();
void inventory();
void pickup(char *item_name);
void discardItem(char *item_name);
void equipItem(char *item_name);
void unequipItem();
void useItem(char *item_name);

#endif // COMMANDS_H