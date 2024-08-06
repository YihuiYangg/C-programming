#ifndef MAIN_FUNCTIONS
#define MAIN_FUNCTIONS
// the above is an 'include guard' - this prevents circular includes


// The standard exit codes to be used.
#define EXIT_SUCCESS 0
#define EXIT_BAD_ARGS 1
#define EXIT_BAD_FILE 2
#define EXIT_BAD_DATA 3

// STRUCTS - you may edit/remove these as you wish.

/**
 * @brief Struct 'Coord' which holds an x,y coordinate pair - useful for a number
 * of applications throughout this game.
 * 
 */
typedef struct _Coord
{
    int x;
    int y;
} Coord;

/**
 * @brief This struct 'Map' holds all the data needed to hold the map file;
 * the array for the map, the size of the map, and the start point.
 *
 */
typedef struct _Map
{
    char **map;
    // if you do not know how to work with dynamic memory
    // then comment out 'char** map;' above and uncomment the next line:
    // char map[100][100];
    int size;
    Coord startPoint;
} Map;

/**
 * @brief Struct 'Player' which holds all the infomation for the player - their
 * current position, and how many treasures they have found.
 * 
 */
typedef struct _Player
{
    Coord currentPosition;
    int foundTreasure;
} Player;

// function declarations - allows you to use these functions elsewhere

int read_file(Map *island, FILE *file);
void strip_newline(char *str);
void print_map(Map *island, Player *player);
int move(char direction, Player *player, Map *island);
int has_won(Player *player);
int allocate_map(Map *island);
void free_map(Map *island);

// this ends the include guard.
#endif