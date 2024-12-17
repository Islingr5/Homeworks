#ifndef ITEM_H
#define ITEM_H

#define MAX_INVENTORY 50
#define MAX_NAME 50
#define MAX_DESCRIPTION 256
#define MAX_ITEMS 92

typedef struct
{
    char name[MAX_NAME];
    char description[MAX_DESCRIPTION];
    int damage;
    int health_regen;
    int quantity;
} Item;

Item *createLightsaber();
Item *createAnduril();

void saveItems(FILE *file);
void loadItems(FILE *file);

#endif // ITEM_H