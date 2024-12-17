#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "room.h"

Room prison[3][15];

void addRandomItemToRoom(Room *room)
{
    if (rand() % 3 == 0)
    { // 33% chance to add an item
        Item *newItem = (Item *)malloc(sizeof(Item));
        sprintf(newItem->name, "TaperedNail");
        sprintf(newItem->description, "A sharp makeshift weapon.");
        newItem->damage = 2; // Damage value for TaperedNail
        room->items[room->item_count++] = newItem;
    }
    if (rand() % 4 == 0)
    { // Another 25% chance to add a different item
        Item *newItem = (Item *)malloc(sizeof(Item));
        sprintf(newItem->name, "Pipe");
        sprintf(newItem->description, "An old pipe for self-defense.");
        newItem->damage = 3; // Damage value for Pipe
        room->items[room->item_count++] = newItem;
    }
    if (rand() % 6 == 0)
    { // Another 16.6% chance to add a different item
        Item *newItem = (Item *)malloc(sizeof(Item));
        sprintf(newItem->name, "BoxCutter");
        sprintf(newItem->description, "A sharp and dangerous weapon.");
        newItem->damage = 5; // Damage value for BoxCutter
        room->items[room->item_count++] = newItem;
    }
    if (rand() % 20 == 0)
    { // Another 5% chance to add a different item
        Item *newItem = (Item *)malloc(sizeof(Item));
        sprintf(newItem->name, "RustyKnife");
        sprintf(newItem->description, "A melee serious combat weapon. Looks like a little rusty.");
        newItem->damage = 7; // Damage value for RustyKnife
        room->items[room->item_count++] = newItem;
    }
    if (rand() % 5 == 0)
    { // 20% chance to add a StaleBread
        Item *newItem = (Item *)malloc(sizeof(Item));
        sprintf(newItem->name, "Pistol");
        sprintf(newItem->description, "A police pistol. How did it get here?");
        newItem->damage = 15; // Damage value for Pistol
        room->items[room->item_count++] = newItem;
    }
    if (rand() % 4 == 0)
    { // 25% chance to add a StaleBread
        Item *newItem = (Item *)malloc(sizeof(Item));
        sprintf(newItem->name, "StaleBread");
        sprintf(newItem->description, "A stale bread, probably not very edible.");
        newItem->health_regen = 12; // Health regeneration value for StaleBread
        room->items[room->item_count++] = newItem;
    }
}

void randomEncounter()
{
    if (rand() % 2 == 0)
    { // 50% chance of a random encounter
        handleRandomEvent();
    }
}