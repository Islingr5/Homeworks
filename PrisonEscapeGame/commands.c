#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "player.h"
#include "room.h"
#include "game.h"
#include "item.h"
#include "enemy.h"

void parseCommand(char *command)
{
    char *token = strtok(command, " ");
    if (strcmp(token, "GeneralKenobi") == 0)
    {
        printf("Hello There!\n");
        Item *lightsaber = createLightsaber();
        addItemToInventory(lightsaber); // Add the Lightsaber to the inventory
        return;
    }
    else if (strcmp(token, "MyPrecious") == 0)
    {
        printf("You Have My Sword.\n");
        Item *anduril = createAnduril();
        addItemToInventory(anduril); // Add Anduril to the inventory
        return;
    }
    if (strcmp(token, "move") == 0)
    {
        token = strtok(NULL, " ");
        if (token)
        {
            move(token);
        }
        else
        {
            printf("\nMove where?\n\n");
        }
    }
    else if (strcmp(token, "look") == 0)
    {
        look();
    }
    else if (strcmp(token, "inventory") == 0)
    {
        inventory();
    }
    else if (strcmp(token, "status") == 0)
    { // New command to check status
        showStatus();
    }
    else if (strcmp(token, "pickup") == 0)
    {
        token = strtok(NULL, " ");
        if (token)
        {
            pickup(token);
        }
        else
        {
            printf("\nPickup what?\n\n");
        }
    }
    else if (strcmp(token, "discard") == 0)
    { // New command to discard an item
        token = strtok(NULL, " ");
        if (token)
        {
            discardItem(token);
        }
        else
        {
            printf("\nDiscard what?\n\n");
        }
    }
    else if (strcmp(token, "use") == 0)
    {
        token = strtok(NULL, " ");
        if (token)
        {
            useItem(token);
        }
        else
        {
            printf("\nUse what?\n\n");
        }
    }
    else if (strcmp(token, "equip") == 0)
    {
        token = strtok(NULL, " ");
        if (token)
        {
            equipItem(token);
        }
        else
        {
            printf("\nEquip what?\n\n");
        }
    }
    else if (strcmp(token, "unequip") == 0)
    {
        unequipItem();
    }
    else if (strcmp(token, "attack") == 0)
    {
        attack();
    }
    else if (strcmp(token, "save") == 0)
    {
        token = strtok(NULL, " ");
        if (token)
        {
            saveGame(token);
        }
        else
        {
            printf("\nSave to what file? (e.g., Save1.txt)\n\n");
        }
    }
    else if (strcmp(token, "load") == 0)
    {
        token = strtok(NULL, " ");
        if (token)
        {
            loadGame(token);
        }
        else
        {
            printf("\nLoad from what file? (e.g., Save1.txt)\n\n");
        }
    }
    else if (strcmp(token, "exit") == 0)
    {
        freeMemory();
        exit(0);
    }
    else
    {
        printf("\nInvalid command.\n\n");
    }
}

void move(char *direction)
{
    if (strcmp(direction, "up") == 0 && playerX > 0)
    {
        playerX--;
    }
    else if (strcmp(direction, "down") == 0 && playerX < 2)
    {
        playerX++;
    }
    else if (strcmp(direction, "left") == 0 && playerY > 0)
    {
        playerY--;
    }
    else if (strcmp(direction, "right") == 0 && playerY < 14)
    {
        playerY++;
    }
    else
    {
        printf("\nYou can't go that way.\n\n");
        return;
    }
    player.last_x = playerX; // Update last position
    player.last_y = playerY; // Update last position
    randomEncounter();       // Check for random encounters after moving
}

void look()
{
    printf("%s\n\n", prison[playerX][playerY].description);

    if (prison[playerX][playerY].enemy)
    {
        // Display enemy's name and stats
        printf("A %s is here!\n", prison[playerX][playerY].enemy->name);
        printf("\nHealth: %d\n", prison[playerX][playerY].enemy->health);
        printf("\nStrength: %d\n", prison[playerX][playerY].enemy->strength);
    }

    if (prison[playerX][playerY].item_count > 0)
    {
        printf("\nYou see items here:\n\n");
        for (int i = 0; i < prison[playerX][playerY].item_count; i++)
        {
            printf("-> %s: %s\n", prison[playerX][playerY].items[i]->name, prison[playerX][playerY].items[i]->description);
        }
    }
}

void attack()
{
    if (prison[playerX][playerY].enemy)
    {
        combat(prison[playerX][playerY].enemy);
    }
    else
    {
        printf("\nThere is no enemy to attack.\n");
    }
}

void inventory()
{
    if (player.current_inventory_size == 0)
    {
        printf("\nYour inventory is empty.\n\n");
    }
    else
    {
        printf("\nYou have:\n\n");
        for (int i = 0; i < player.current_inventory_size; i++)
        {
            printf("%s x%d\n\n", player.inventory[i]->name, player.inventory[i]->quantity);
        }
        if (player.equipped_item)
        {
            printf("Currently equipped: %s\n", player.equipped_item->name);
        }
        else
        {
            printf("No item currently equipped.\n");
        }
    }
}

void pickup(char *item_name)
{
    for (int i = 0; i < prison[playerX][playerY].item_count; i++)
    {
        if (strcmp(prison[playerX][playerY].items[i]->name, item_name) == 0)
        {
            addItemToInventory(prison[playerX][playerY].items[i]);
            // Remove item from room
            for (int j = i; j < prison[playerX][playerY].item_count - 1; j++)
            {
                prison[playerX][playerY].items[j] = prison[playerX][playerY].items[j + 1];
            }
            prison[playerX][playerY].item_count--;
            printf("You picked up %s.\n", item_name);
            return;
        }
    }
    printf("\nItem '%s' not found in the room.\n", item_name);
}

void discardItem(char *item_name)
{
    for (int i = 0; i < player.current_inventory_size; i++)
    {
        if (strcmp(player.inventory[i]->name, item_name) == 0)
        {
            free(player.inventory[i]); // Free the memory of the item
            printf("You discarded %s.\n\n", item_name);
            // Shift items in inventory
            for (int j = i; j < player.current_inventory_size - 1; j++)
            {
                player.inventory[j] = player.inventory[j + 1];
            }
            player.current_inventory_size--;
            player.inventory[player.current_inventory_size] = NULL; // Nullify the last item
            return;
        }
    }
    printf("\nItem not found in inventory.\n");
}

void equipItem(char *item_name)
{
    // Check if the item is already equipped
    if (player.equipped_item != NULL && strcmp(player.equipped_item->name, item_name) == 0)
    {
        // The item is already equipped
        printf("\nYou are already equipped with %s. Your strength remains %d.\n", item_name, player.strength);
        return;
    }

    // If there is an equipped item, unequip it
    if (player.equipped_item != NULL)
    {
        player.strength -= player.equipped_item->damage; // Decrease strength by the damage of the equipped item
        printf("\nYou unequipped %s. Your strength is now %d.\n", player.equipped_item->name, player.strength);
    }

    // Now equip the new item
    for (int i = 0; i < player.current_inventory_size; i++)
    {
        if (strcmp(player.inventory[i]->name, item_name) == 0)
        {
            player.equipped_item = player.inventory[i];
            player.strength += player.equipped_item->damage; // Increase player's strength
            printf("\nYou equipped %s. Your strength is now %d.\n", item_name, player.strength);
            return;
        }
    }

    // If the item was not found in the inventory
    printf("\nItem not found in inventory.\n");
}

void unequipItem()
{
    if (player.equipped_item)
    {
        player.strength -= player.equipped_item->damage; // Decrease player's strength
        printf("\nYou unequipped %s. Your strength is now %d.\n", player.equipped_item->name, player.strength);
        player.equipped_item = NULL; // Remove equipped item
    }
    else
    {
        printf("\nNo item is currently equipped.\n");
    }
}

void useItem(char *item_name)
{
    for (int i = 0; i < player.current_inventory_size; i++)
    {
        if (strcmp(player.inventory[i]->name, item_name) == 0)
        {
            if (player.inventory[i]->health_regen > 0)
            {
                // Check if player's health is already at maximum
                if (player.health >= player.max_health)
                {
                    printf("\nYou can't use %s because your health is already at maximum.\n\n", item_name);
                }
                else
                {
                    // Restore health
                    player.health += player.inventory[i]->health_regen;

                    // Ensure health does not exceed max_health
                    if (player.health > player.max_health)
                    {
                        player.health = player.max_health;
                    }

                    printf("\nYou used %s and restored %d health.\n\n", item_name, player.inventory[i]->health_regen);
                    discardItem(item_name); // Remove the item after use
                }
            }
            else
            {
                printf("\nYou can't use %s.\n\n", item_name);
            }
            return;
        }
    }
    printf("Item not found in inventory.\n\n");
}