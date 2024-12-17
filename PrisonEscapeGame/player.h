#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"

#define MAX_INVENTORY 50
#define MAX_NAME 50
#define MAX_DESCRIPTION 256
#define MAX_ENEMIES 32
#define MAX_ITEMS 96

typedef struct
{
    char name[MAX_NAME];
    int health;
    int strength;
    int damage; // Damage value for items
} Character;

typedef struct
{
    char name[MAX_NAME];
    int health;
    int base_strength;
    int strength;
    int inventory_capacity;
    int current_inventory_size;
    Item *inventory[MAX_INVENTORY];
    Item *equipped_item;
    int last_x;
    int last_y;
    int max_health;
} Player;

extern Player player;

void addItemToInventory(Item *item);
int isItemInInventory(const char *item);

#endif // PLAYER_H