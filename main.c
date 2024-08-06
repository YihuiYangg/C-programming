/**
 * @file main.c
 * @author Yihui Yang
 *
 */

// You may include more built-in C libraries if needed
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// This is the header for this file - it contains the struct and function definitions.
#include "main.h"

// FUNCTIONS - you can use these as-is, totally remove them and write your own,
// or change them to suit your own development preference if you wish.

// Validates the map to ensure it follows the rules
int validate_map(Map *island)
{
    int startCount = 0;
    int treasureCount = 0;

    for (int i = 0; i < island->size; i++)
    {
        for (int j = 0; j < island->size; j++)
        {
            char c = island->map[i][j];

            // Check for valid characters
            if (c != 'w' && c != 'T' && c != ' ' && c != 'H' && c != 'S')
            {
                return 0;
            }

            // Ensure borders are 'w'
            if (i == 0 || i == island->size - 1 || j == 0 || j == island->size - 1)
            {
                if (c != 'w')
                {
                    return 0;
                }
            }

            // Count start point and treasures
            if (c == 'S')
            {
                island->startPoint.x = j;
                island->startPoint.y = i;
                startCount++;
            }
            else if (c == 'H')
            {
                treasureCount++;
            }
        }
    }

    // Ensure exactly one start point and three treasures
    if (startCount != 1 || treasureCount != 3)
    {
        return 0;
    }

    return 1;
}

/**
 * Reads in the data from the map file and stores it into the Map struct passed from main.
 * Should ensure you validate the Map is valid.
 * return should indicate whether this was successful or not.
 */
int read_file(Map *island, FILE *file)
{
    // Read the map file
    int i;
    char line[100]; 
    int rowIndex = -1;
   
    while (fgets(line, sizeof(line), file) != NULL)
    {
        int len = strlen(line);
        if (len - 1 != island->size)
        { 
            return 0;
        }
        rowIndex++;
        for (i = 0; i < island->size; i++)
        {
            island->map[rowIndex][i] = line[i];
        }
    }
    // Validate the map structure and contents
    if (!validate_map(island))
    {
        return 0;
    }

    return 1;
}

/**
 * This is a utility function which will strip the newline off the end of a string.
 * You may find this useful when reading in the file or getting user inputs.
 */
void strip_newline(char *str)
{
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}

/**
 * Prints the map in the expected format - if you want to re-write this please
 * ensure you follow this exact format as it will be used in testing.
 */
void print_map(Map *island, Player *player)
{
    for (int i = 0; i < island->size; i++)
    {
        for (int j = 0; j < island->size; j++)
        {
            // player printed as 'X'
            if (player->currentPosition.x == j && player->currentPosition.y == i)
            {
                printf("X");
            }
            // treasure and start point are shown as ' 's
            else if (island->map[i][j] == 'H' || island->map[i][j] == 'S')
            {
                printf(" ");
            }
            // trees or water shown as 'T'/'w' as appropriate.
            else
            {
                printf("%c", island->map[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * check that the player's intended move is legal and then moves
 * their position if necessary.
 */
int move(char direction, Player *player, Map *island)
{
    Coord newPos = player->currentPosition;

    switch (direction)
    {
    case 'w':
    case 'W':
        newPos.y--;
        break;
    case 'a':
    case 'A':
        newPos.x--;
        break;
    case 's':
    case 'S':
        newPos.y++;
        break;
    case 'd':
    case 'D':
        newPos.x++;
        break;
    // Invalid move
    default:
        return 0;
    }

    if (newPos.x < 0 || newPos.x >= island->size || newPos.y < 0 || newPos.y >= island->size)
    {
        printf("invalid move!\n");
        return 0;
    }

    char terrian = island->map[newPos.y][newPos.x];
    if (terrian == 'T' || terrian == 'w')
    {
        printf("invalid move!\n");
        return 0;
    }

    player->currentPosition = newPos;
    if (terrian == 'H')
    {
        player->foundTreasure++;
        island->map[newPos.y][newPos.x] = ' ';
        printf("You have found %d out of 3 hidden treasures\n", player->foundTreasure);
    }
    return 1;
}

/**
 * check if the player has won - useful for loop control.
 */
int has_won(Player *player)
{
    if (player->foundTreasure == 3)
    {
        printf("You win the game!!\n");
        return 1;
    }
    return 0;
}

/**
 * dynamically allocate the array for island->map so you can use the array
 */
int allocate_map(Map *island)
{
    // Allocate memory for the array of row pointers
    island->map = (char **)malloc(island->size * sizeof(char *));
    if (island->map == NULL)
    {
        return 0;
    }

    // Allocate memory for each row
    for (int i = 0; i < island->size; i++)
    {
        island->map[i] = (char *)malloc(island->size * sizeof(char));
       
    }
    return 1;
}

/**
 * free all the dynamically allocated memory for the array - use before exits.
 */
void free_map(Map *island)
{
    if (island->map != NULL)
    {
        for (int i = 0; i < island->size; i++)
        {
            if (island->map[i] != NULL)
            {
                free(island->map[i]);
                island->map[i] = NULL;
            }
        }
        free(island->map);
        island->map = NULL;
    }
}

int main(int argc, char *argv[])
{
    // arg checks
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <mapfilepath> <dimension>\n", argv[0]);
        return EXIT_BAD_ARGS;
    }
    //
    int size = atoi(argv[2]);
    if (size < 5 || size > 100)
    {
        fprintf(stderr, "Invalid dimension");
        return EXIT_BAD_ARGS;
    }
    // Creating pointers to a Map and a Player which can be passed by reference to other functions.
    Map *island = malloc(sizeof(Map));
    if (island == NULL)
    {
        fprintf(stderr, "Memory allocation for map failed.\n");
        return EXIT_BAD_FILE;
    }
    island->size = size;
    Player *player = malloc(sizeof(Player));
    if (player == NULL)
    {
        fprintf(stderr, "Memory allocation for player failed.\n");
        return EXIT_BAD_FILE;
    }
    // allocate memory for the array
    if (!allocate_map(island))
    {
        fprintf(stderr, "Memory allocation for the array failed.\n");
        return EXIT_BAD_FILE;
    }
    // open file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening map file.\n");
        return EXIT_BAD_FILE;
    }
    // read file
    if (!read_file(island, file))
    {
        fprintf(stderr, "Error reading map file or invalid map.\n");
        return EXIT_BAD_DATA;
    }
    // close file
    fclose(file);
    // Initialize player starting position
    player->currentPosition = island->startPoint;
    player->foundTreasure = 0;
    // play the game
    char input;
    print_map(island, player);
    while (!has_won(player))
    {   

        printf("Enter move (WSAD):");
        input = getchar();
        // getchar();
        strip_newline(&input);
        move(input, player, island);
        print_map(island, player);
       
    }
    // exit
    free_map(island);
    return EXIT_SUCCESS;
}