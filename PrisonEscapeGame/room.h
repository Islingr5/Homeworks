#ifndef ROOM_H
#define ROOM_H

#include "item.h"
#include "game.h"
#include "player.h"

typedef struct
{
    char description[MAX_DESCRIPTION];
    Character *enemy;
    Item *items[MAX_ITEMS];
    int item_count;
} Room;

extern Room prison[3][15];

void addRandomItemToRoom(Room *room);
void randomEncounter();

#endif // ROOM_H