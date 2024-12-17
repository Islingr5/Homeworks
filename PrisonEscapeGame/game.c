#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"

int playerX = 0; // Start in the cell at the first row
int playerY = 0; // Start at the first column

int main()
{
    srand((unsigned int)time(NULL));
    startGame(); // Start the game with load or new game option

    while (1)
    {
        printPrison();
        printf("\n> ");
        char command[100];
        if (fgets(command, sizeof(command), stdin) != NULL)
        {
            command[strcspn(command, "\n")] = 0; // Remove newline character

            // Check if the command is empty
            if (strlen(command) == 0)
            {
                printf("Please enter a command.\n");
                continue; // Prompt for input again
            }

            parseCommand(command);
        }
        else
        {
            printf("Error reading input.\n");
            break; // Exit the loop on error
        }
    }

    printPrison();
    freeMemory();
    return 0;
}

void initializePrison()
{
    // Initialize rooms with descriptions and enemies
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (i == 1)
            {
                // Corridor
                strcpy(prison[i][j].description, "\nYou are in the corridor.");
                prison[i][j].enemy = NULL;   // No enemy in the corridor
                prison[i][j].item_count = 0; // No items in the corridor
            }
            else
            {
                // Cells
                sprintf(prison[i][j].description, "\nYou are in cell (%d, %d).", i, j);
                prison[i][j].enemy = NULL;   // No enemy initially
                prison[i][j].item_count = 0; // No items initially
            }
        }
    }
    addEnemies();

    // Add random items to rooms
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            addRandomItemToRoom(&prison[i][j]);
        }
    }
}

void printPrison()
{
    printf("\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (i == playerX && j == playerY)
            {
                printf("[P] "); // Player's position
            }
            else
            {
                printf("[ ] "); // Empty space
            }
        }
        printf("\n");
    }
    printf("%s \n", prison[playerX][playerY].description);
    if (prison[playerX][playerY].enemy)
    {
        printf("\nA %s is here!\n", prison[playerX][playerY].enemy->name);
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

void combat(Character *enemy)
{
    Item *droppedItem = NULL; // Pointer to hold the dropped item
    while (player.health > 0 && enemy->health > 0)
    {
        printf("\nYou encounter a %s!\n", enemy->name);
        printf("\nChoose your action:\n");
        printf("1. Attack\n");
        printf("2. Flee\n");
        printf("3. Use Item\n");
        printf("4. Change Equipped Item\n");

        int choice;
        // Use a loop to ensure valid input
        while (1)
        {
            printf("\nEnter your choice: ");
            if (scanf("%d", &choice) == 1) // Check if input is a valid integer
            {
                if (choice >= 1 && choice <= 4) // Check if choice is within valid range
                {
                    clearInputBuffer(); // Clear the input buffer before proceeding
                    break;              // Valid input, exit the loop
                }
                else
                {
                    printf("\nInvalid choice. Please choose again.\n");
                }
            }
            else
            {
                printf("\nInvalid input. Please enter a number between 1 and 4.\n");
                clearInputBuffer(); // Clear the input buffer
            }
        }

        switch (choice)
        {
        case 1: // Attack
            printf("\nYou attack the %s!\n", enemy->name);
            enemy->health -= player.strength;
            printf("You dealt %d damage to the %s.\n", player.strength, enemy->name);
            break;
        case 2: // Flee
            printf("\nYou attempt to flee!\n");
            if (rand() % 2 == 0) // 50% chance to successfully flee
            {
                printf("\nYou successfully fled from the %s!\n", enemy->name);
                return; // Exit combat
            }
            else
            {
                printf("\nYou failed to flee!\n");
            }
            break;
        case 3:          // Use Item
            inventory(); // Show the player's inventory
            printf("\nEnter the name of the item you want to use: ");
            char item_name[MAX_NAME];
            scanf("%s", item_name); // Read the item name from input
            useItem(item_name);     // Call the existing useItem function
            break;
        case 4:          // Change Equipped Item
            inventory(); // Show the player's inventory
            printf("\nEnter the name of the item you want to equip (or type 'unequip' to unequip the current item): ");
            char equip_name[MAX_NAME];
            scanf("%s", equip_name); // Read the item name from input

            if (strcmp(equip_name, "unequip") == 0)
            {
                unequipItem(); // Call the unequip function
                printf("\nYou have unequipped the current item.\n");
            }
            else
            {
                equipItem(equip_name); // Call the equip function
            }
            break;
        }

        // Check if the enemy is still alive before it attacks
        if (enemy->health > 0)
        {
            printf("\nThe %s attacks you!\n", enemy->name);
            player.health -= enemy->strength;
            printf("The %s dealt %d damage to you.\n", enemy->name, enemy->strength);
        }

        // Display health status
        printf("\nYour health: %d, %s health: %d\n", player.health, enemy->name, enemy->health);
    }

    // Check if player is defeated
    if (player.health <= 0)
    {
        printf("\nYou have been defeated! Game Over!\n\n");
        exit(0);
    }
    else
    {
        printf("You defeated the %s!\n\n", enemy->name);
        droppedItem = (Item *)malloc(sizeof(Item)); // Allocate memory for dropped item
        // Randomly assign a dropped item
        if (rand() % 4 == 0)
        {
            sprintf(droppedItem->name, "SnickersBar");
            sprintf(droppedItem->description, "A delicious chocolate bar that restores 25 health.");
            droppedItem->health_regen = 25;
        }
        else
        {
            sprintf(droppedItem->name, "MysteriousKey");
            sprintf(droppedItem->description, "A key that might open something.");
            droppedItem->health_regen = 0;
        }
        dropItem(droppedItem);                 // Handle the dropped item
        free(enemy);                           // Free the enemy memory
        prison[playerX][playerY].enemy = NULL; // Remove enemy from room
    }
}

void saveGame(const char *filepath)
{
    FILE *file = fopen(filepath, "w");
    if (!file)
    {
        printf("\nError saving game.\n\n");
        return;
    }
    fprintf(file, "%s\n%d\n%d\n%d\n%d\n%d\n", player.name, player.health, player.base_strength, player.strength, player.last_x, player.last_y);
    saveEnemies(file); // Save surviving enemies
    saveItems(file);   // Save items in the rooms
    fclose(file);
    printf("\nGame saved to %s.\n\n", filepath);
}

bool loadGame(const char *filepath)
{
    FILE *file = fopen(filepath, "r");
    if (!file)
    {
        return false; // Return false if the file could not be opened
    }
    fscanf(file, "%s\n%d\n%d\n%d\n%d\n%d\n", player.name, &player.health, &player.base_strength, &player.strength, &player.last_x, &player.last_y);

    // Set playerX and playerY based on loaded last position
    playerX = player.last_x;
    playerY = player.last_y;

    loadEnemies(file); // Load surviving enemies
    loadItems(file);   // Load items in the rooms and inventory
    fclose(file);
    printf("Game loaded from %s.\n\n", filepath);
    printf("Welcome back, %s!\n\n", player.name); // Optional: greet the player
    return true;                                  // Return true if loading was successful
}

void freeMemory()
{
    for (int i = 0; i < player.current_inventory_size; i++)
    {
        free(player.inventory[i]);
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (prison[i][j].enemy)
            {
                free(prison[i][j].enemy);
            }
            for (int k = 0; k < prison[i][j].item_count; k++)
            {
                free(prison[i][j].items[k]);
            }
        }
    }
}

void handleRandomEvent()
{
    int eventChance = rand() % 13; // Generate a random number between 0 and 12

    switch (eventChance)
    {
    case 0:
        printf("\nYou encountered a harmless rat! It scurries away.\n");
        break;
    case 1:
        printf("\nSuddenly you heard a sizzling sound and the light bulb right above you broke.\n");
        break;
    case 2:
        printf("\nWhile walking, you suddenly heard a painful scream coming from a distant place.\n");
        break;
    case 3:
        printf("\nYou heard a gunshot coming from a very far place.\n");
        break;
    case 4:
        printf("\nYou heard the noises of a crowded group of prisoners.\n");
        break;
    case 5:
        printf("\nA gentle breeze flows through the corridor, carrying the faint scent of something sweet.\n");
        break;
    case 6:
        printf("\nYou notice a small crack in the wall, and a tiny flower is growing out of it, defying the odds.\n");
        break;
    case 7:
        printf("\nThe distant sound of dripping water echoes through the hall, creating a rhythmic pattern.\n");
        break;
    case 8:
        printf("\nYou hear the faint sound of a radio playing somewhere in the distance, playing an old tune.\n");
        break;
    case 9:
        printf("\nA flickering light casts strange shadows on the walls, making the place feel alive.\n");
        break;
    case 10:
        printf("\nYou feel the air getting colder around you.\n");
        break;
    case 11:
        printf("\nWails echo through the dilapidated prison halls.\n");
        break;
    case 12:
        printf("\nLong-suffered prisoners seek their zealous revenge.\n");
        break;
    default:
        // This case should never be reached due to the range of eventChance
        break;
    }
}

void startGame()
{
    char choice[10];
    bool gameLoaded = false; // Flag to check if the game was loaded successfully

    while (!gameLoaded) // Continue until a game is loaded or a new game is started
    {
        printf("\n");
        printf("Do you want to load a saved game or start a new game? (load/new): ");
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n\n")] = 0; // Remove newline character

        if (strcmp(choice, "load") == 0)
        {
            char filepath[MAX_NAME];
            printf("\nEnter the filename to load (e.g., Save1.txt): ");
            fgets(filepath, sizeof(filepath), stdin);
            filepath[strcspn(filepath, "\n\n")] = 0; // Remove newline character

            // Attempt to load the game
            if (loadGame(filepath))
            {
                gameLoaded = true; // Set flag to true if loading was successful
            }
            else
            {
                printf("\nError loading game. Please try again.\n");
                // The loop will continue, prompting the user again
            }
        }
        else if (strcmp(choice, "new") == 0)
        {
            selectCharacterClass(); // Select character class for a new game
            initializePrison();     // Initialize the game state for a new game
            gameLoaded = true;      // Set flag to true since a new game is started
        }
        else
        {
            printf("\nInvalid choice. Please enter 'load' or 'new'.\n");
            // The loop will continue, prompting the user again
        }
    }
}

void selectCharacterClass()
{
    printf("\nEnter your character name: ");
    fgets(player.name, sizeof(player.name), stdin);
    player.name[strcspn(player.name, "\n\n")] = 0; // Remove newline character

    int choice;
    printf("\nSelect your character class:\n\n");
    printf("1. Fighter (Hard)\n\n");
    printf("2. Fork User (Easy)\n\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);
    getchar(); // Consume newline character

    player.health = 100;
    player.base_strength = (choice == 1) ? 10 : 12; // Fighter has 10, Fork User has 12
    player.strength = player.base_strength;
    player.inventory_capacity = MAX_INVENTORY;
    player.current_inventory_size = 0;
    player.equipped_item = NULL; // No item equipped at start
    player.last_x = playerX;     // Initialize last position
    player.last_y = playerY;     // Initialize last position

    for (int i = 0; i < MAX_INVENTORY; i++)
        player.inventory[i] = NULL;

    printf("\nWelcome, %s! You are now a %s.\n\n", player.name, (choice == 1) ? "Fighter" : "Fork User");

    showIntro(); // Show the game introduction
}

void showStatus()
{
    printf("\nPlayer Status:\n\n");
    printf("Name: %s\n\n", player.name);
    printf("Health: %d\n\n", player.health);
    printf("Strength: %d\n\n", player.strength);
    if (player.equipped_item)
    {
        printf("Equipped Item: %s\n\n", player.equipped_item->name);
    }
    else
    {
        printf("No item currently equipped.\n\n");
    }
}

void dropItem(Item *item)
{
    printf("You defeated the enemy! It dropped a %s.\n\n", item->name);
    printf("Do you want to pick it up or discard it? (pick/discard): \n");
    char choice[10];
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n\n")] = 0; // Remove newline character

    if (strcmp(choice, "pick") == 0)
    {
        addItemToInventory(item);
        printf("You picked up the %s.\n\n", item->name);
    }
    else
    {
        printf("You discarded the %s.\n\n", item->name);
        free(item); // Free the item if discarded
    }
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ; // Discard characters until newline or EOF
}

void showIntro()
{
    printf("###########################################\n");
    printf("#######   ########################   #######\n");
    printf("######      THE ESCAPE AWAKENS      #######\n");
    printf("#######   ########################   #######\n");
    printf("###########################################\n");

    printf("\nYou wake up in a dark, damp cell. You have no memory of how you got here.\n");
    printf("You must find a way to escape this prison and uncover the truth.\n");
    printf("Are you going to be a good boy and sit in your cell, or are you going to chase your destiny?\n");
    printf("Explore the prison, fight enemies, and collect items to aid you in your escape.\n");
}

void finalizeGame()
{
    bool enemiesLeft = false;

    // Check each room in the prison for enemies
    for (int i = 0; i < 3; i++) // Assuming 3 rows
    {
        for (int j = 0; j < 15; j++) // Assuming 15 columns
        {
            if (prison[i][j].enemy != NULL) // Check if there is an enemy in the room
            {
                enemiesLeft = true; // Set flag if any enemy is found
                break;              // No need to check further if we found an enemy
            }
        }
        if (enemiesLeft)
            break; // Break outer loop if an enemy is found
    }

    // Provide feedback based on whether enemies are left
    if (!enemiesLeft)
    {
        printf("It's over, player. You have the high ground.\n");
        exit(0); // Exit the game
    }
    else
    {
        printf("There are still enemies left in the area. Keep fighting!\n");
    }
}
