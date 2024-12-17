#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enemy.h"

void saveEnemies(FILE *file)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (prison[i][j].enemy)
            { // Check if enemy exists
                fprintf(file, "%s %d %d %d %d\n",
                        prison[i][j].enemy->name,
                        prison[i][j].enemy->health,
                        prison[i][j].enemy->strength,
                        i, j);
            }
        }
    }
    fprintf(file, "END\n\n"); // Mark the end of enemy data
}

void loadEnemies(FILE *file)
{
    char enemy_name[MAX_NAME];
    int health, strength, x, y;
    while (fscanf(file, "%s", enemy_name) != EOF)
    {
        if (strcmp(enemy_name, "END") == 0)
            break; // Stop loading if we reach the end marker
        fscanf(file, "%d %d %d %d", &health, &strength, &x, &y);

        // Ensure the room index is valid before adding the enemy
        if (x >= 0 && x < 3 && y >= 0 && y < 15)
        {
            prison[x][y].enemy = (Character *)malloc(sizeof(Character)); // Allocate memory for enemy
            if (prison[x][y].enemy == NULL)
            {
                printf("Memory allocation failed for enemy %s.\n", enemy_name);
                return; // Exit if memory allocation fails
            }
            strcpy(prison[x][y].enemy->name, enemy_name);
            prison[x][y].enemy->health = health;
            prison[x][y].enemy->strength = strength;
            printf("Loaded enemy: %s in room (%d, %d)\n", enemy_name, x, y);
        }
        else
        {
            printf("Invalid room coordinates (%d, %d) for enemy %s.\n", x, y, enemy_name);
        }
    }
}

void addEnemies()
{
    // Define the enemy types and their stats
    Character enemyTypes[] = {
        {"PrisonerTypeA", 66, 5},
        {"PrisonerTypeB", 72, 7},
        {"PrisonerTypeC", 78, 10},
        {"PrisonerTypeD", 82, 12},
        {"PoliceGroup", 130, 20},
        {"MuscularCriminal", 84, 14},
        {"BrassKnucklesUser", 88, 16},
        {"KnifeWieldingCriminal", 93, 17},
        {"Thug", 50, 6},
        {"GangLeader", 90, 12},
        {"RogueGuard", 80, 10},
        {"Psychopath", 70, 8},
        {"EscapeArtist", 60, 7},
        {"BrutalEnforcer", 100, 15},
        {"Drug Dealer", 55, 5},
        {"MysteriousStranger", 75, 9}};

    // Define spawn rates for each enemy type (in percentage)
    int spawnRates[] = {15, 10, 10, 10, 10, 10, 10, 10, 5, 5, 5, 5, 5, 5, 5, 5}; // Adjust these values as needed
    int enemyCount = sizeof(enemyTypes) / sizeof(enemyTypes[0]);

    // Randomly place enemies in the prison
    for (int i = 0; i < 3; i++) // Iterate through rows
    {
        for (int j = 0; j < 15; j++) // Iterate through columns
        {
            // Check if there is already an enemy in this room
            if (prison[i][j].enemy == NULL)
            {
                // Randomly determine if an enemy should spawn in this room
                int randomValue = rand() % 100; // Generate a random number between 0 and 99
                int cumulativeChance = 0;

                for (int k = 0; k < enemyCount; k++)
                {
                    cumulativeChance += spawnRates[k];
                    if (randomValue < cumulativeChance)
                    {
                        // Allocate memory for the new enemy
                        prison[i][j].enemy = (Character *)malloc(sizeof(Character));
                        strcpy(prison[i][j].enemy->name, enemyTypes[k].name);
                        prison[i][j].enemy->health = enemyTypes[k].health;
                        prison[i][j].enemy->strength = enemyTypes[k].strength;
                        break; // Exit the loop after placing the enemy
                    }
                }
            }
        }
    }
}