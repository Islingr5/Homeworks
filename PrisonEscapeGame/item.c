#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "room.h"

Item *createLightsaber()
{
    Item *lightsaber = (Item *)malloc(sizeof(Item));
    strcpy(lightsaber->name, "Lightsaber");
    strcpy(lightsaber->description, "A glowing sword that hums with power.");
    lightsaber->damage = 30;
    lightsaber->health_regen = 0;
    lightsaber->quantity = 1;
    return lightsaber;
}

Item *createAnduril()
{
    Item *anduril = (Item *)malloc(sizeof(Item));
    strcpy(anduril->name, "Anduril");
    strcpy(anduril->description, "The Flame of the West, a sword of great power.");
    anduril->damage = 25;
    anduril->health_regen = 0;
    anduril->quantity = 1;
    return anduril;
}

void saveItems(FILE *file)
{
    // Save the equipped item if it exists
    if (player.equipped_item)
    {
        fprintf(file, "EQUIPPED %s %s %d\n",
                player.equipped_item->name,
                player.equipped_item->description,
                player.equipped_item->damage);
    }

    // Save items in the rooms
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            Room *room = &prison[i][j];
            for (int k = 0; k < room->item_count; k++)
            {
                Item *item = room->items[k];
                if (item->health_regen > 0)
                {
                    fprintf(file, "HEALTH_ITEM %s %s %d %d %d\n",
                            item->name, item->description,
                            item->health_regen, i, j);
                }
                else
                {
                    fprintf(file, "WEAPON %s %s %d %d %d\n",
                            item->name, item->description,
                            item->damage, i, j);
                }
            }
        }
    }
    fprintf(file, "ITEM END\n");

    // Save the player's inventory
    for (int i = 0; i < player.current_inventory_size; i++)
    {
        Item *item = player.inventory[i];
        if (item->health_regen > 0)
        {
            fprintf(file, "HEALTH_ITEM %s %s %d\n",
                    item->name, item->description,
                    item->health_regen);
        }
        else
        {
            fprintf(file, "WEAPON %s %s %d\n",
                    item->name, item->description,
                    item->damage);
        }
    }
    fprintf(file, "INVENTORY END\n");
}

void loadItems(FILE *file)
{
    char item_name[MAX_NAME];
    char item_description[MAX_DESCRIPTION];
    int value, x, y;

    // Clear previous inventory and room items
    player.current_inventory_size = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            Room *room = &prison[i][j];
            for (int k = 0; k < room->item_count; k++)
            {
                free(room->items[k]); // Free old items
            }
            room->item_count = 0;
        }
    }

    player.equipped_item = NULL; // Clear equipped item

    // Start loading from file
    while (fscanf(file, "%s", item_name) != EOF)
    {
        if (strcmp(item_name, "EQUIPPED") == 0)
        {
            fscanf(file, "%s %s %d", item_name, item_description, &value);
            player.equipped_item = (Item *)malloc(sizeof(Item));
            strcpy(player.equipped_item->name, item_name);
            strcpy(player.equipped_item->description, item_description);
            player.equipped_item->damage = value;
        }
        else if (strcmp(item_name, "HEALTH_ITEM") == 0 || strcmp(item_name, "WEAPON") == 0)
        {
            int is_health_item = strcmp(item_name, "HEALTH_ITEM") == 0;
            fscanf(file, "%s %s %d %d %d", item_name, item_description, &value, &x, &y);

            Item *newItem = (Item *)malloc(sizeof(Item));
            strcpy(newItem->name, item_name);
            strcpy(newItem->description, item_description);
            if (is_health_item)
            {
                newItem->health_regen = value;
                newItem->damage = 0;
            }
            else
            {
                newItem->damage = value;
                newItem->health_regen = 0;
            }

            prison[x][y].items[prison[x][y].item_count++] = newItem;
        }
        else if (strcmp(item_name, "INVENTORY") == 0)
        {
            while (fscanf(file, "%s", item_name) != EOF)
            {
                if (strcmp(item_name, "INVENTORY END") == 0)
                    break;

                Item *newItem = (Item *)malloc(sizeof(Item));
                fscanf(file, "%s %s %d", item_description, &value);
                strcpy(newItem->name, item_name);
                strcpy(newItem->description, item_description);

                if (strcmp(item_name, "HEALTH_ITEM") == 0)
                {
                    newItem->health_regen = value;
                    newItem->damage = 0;
                }
                else
                {
                    newItem->damage = value;
                    newItem->health_regen = 0;
                }

                player.inventory[player.current_inventory_size++] = newItem;
            }
        }
        else if (strcmp(item_name, "ITEM END") == 0)
        {
            break;
        }
    }
}