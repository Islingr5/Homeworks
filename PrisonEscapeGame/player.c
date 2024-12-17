#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

Player player;

void addItemToInventory(Item *item)
{
    int quantity = isItemInInventory(item->name); // Check if the item is already in the inventory

    if (quantity > 0)
    {
        // If the item exists, increase the quantity
        for (int i = 0; i < player.current_inventory_size; i++)
        {
            if (strcmp(player.inventory[i]->name, item->name) == 0)
            {
                player.inventory[i]->quantity++; // Increase quantity
                printf("\nIncreased %s quantity to %d.\n\n", item->name, player.inventory[i]->quantity);
                free(item); // Free the item since it's already in inventory
                return;
            }
        }
    }
    else
    {
        // If the item is not in the inventory, add it
        if (player.current_inventory_size < player.inventory_capacity)
        {
            item->quantity = 1; // Set initial quantity to 1
            player.inventory[player.current_inventory_size++] = item;
            printf("\nAdded %s to inventory.\n\n", item->name);
        }
        else
        {
            printf("\nInventory is full!\n\n");
            free(item); // Free the item if not added
        }
    }
}

int isItemInInventory(const char *item_name)
{
    for (int i = 0; i < player.current_inventory_size; i++)
    {
        if (strcmp(player.inventory[i]->name, item_name) == 0)
        {
            return player.inventory[i]->quantity; // Return the quantity of the item
        }
    }
    return 0; // Return 0 if the item is not found
}