// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//Support Library
#include "UNIXBOARD.h"


// User libraries
#include "Game.h"

// **** Set any macros or preprocessor directives here ****
#define NORTH 'n'
#define EAST 'e'
#define SOUTH 's'
#define WEST 'w'
#define QUIT 'q'
// **** Declare any data types here ****
char title[GAME_MAX_ROOM_TITLE_LENGTH];
char desc[GAME_MAX_ROOM_DESC_LENGTH];
uint8_t exits;
// **** Define any global or external variables here ****

// **** Declare any function prototypes here ****
void DisplayRoom(void);

int main()
{
    /**************************************************************************************************/
    //Initialize Game Directions
    GameInit();
    uint8_t dir = 0;
    uint8_t roomExits = 0;
    if (GameInit() == STANDARD_ERROR) {
        printf("Failed to Load Starting Room");
        FATAL_ERROR();
    }
    
    DisplayRoom();

    while (TRUE) {
        printf("Enter Direction to Travel(n, e, s, w) or q to quit followed by enter: ");
        dir = getchar();
        roomExits = GameGetCurrentRoomExits();
        
        switch (dir) {
            case NORTH:
                if (roomExits & GAME_ROOM_EXIT_NORTH_EXISTS) {
                    int check = GameGoNorth();
                    if (check == STANDARD_ERROR) {
                        FATAL_ERROR();
                    } else {
                        DisplayRoom();
                    }
                } break;
            case EAST:
                if (roomExits & GAME_ROOM_EXIT_EAST_EXISTS) {
                    int check = GameGoEast();
                    if (check == STANDARD_ERROR) {
                        FATAL_ERROR();
                    } else {
                        DisplayRoom();
                    }
                } break;
            case SOUTH:
                if (roomExits & GAME_ROOM_EXIT_SOUTH_EXISTS) {
                    int check = GameGoSouth();
                    if (check == STANDARD_ERROR) {
                        FATAL_ERROR();
                    } else {
                        DisplayRoom();
                    }
                } break;
            case WEST:
                if (roomExits & GAME_ROOM_EXIT_WEST_EXISTS) {
                    int check = GameGoWest();
                    if (check == STANDARD_ERROR) {
                        FATAL_ERROR();
                    } else {
                        DisplayRoom();
                    }
                } break;
            case QUIT:
                printf("Thank you for Playing!\n\n");
                exit(0);
                break;
            default:
                DisplayRoom();
        } 
        while(getchar() != '\n');       
    }

    /**************************************************************************************************/
}

void DisplayRoom(void) {
        GameGetCurrentRoomTitle(title);
        GameGetCurrentRoomDescription(desc);
        exits = GameGetCurrentRoomExits();

        printf("\n<======%s======>\n", title);
        printf("%s\n", desc);
        printf("\n\nDirections Available:\n");
        if (exits & GAME_ROOM_EXIT_NORTH_EXISTS) {
            printf("\033[0;32m");
            printf("North\n");
            printf("\033[0;0m");
        } else {
            printf("\033[0;31m");
            printf("North\n");
            printf("\033[0;0m");
        }
        if (exits & GAME_ROOM_EXIT_EAST_EXISTS) {
            printf("\033[0;32m");
            printf("East\n");
            printf("\033[0;0m");
        } else {
            printf("\033[0;31m");
            printf("East\n");
            printf("\033[0;0m");
        }
        if (exits & GAME_ROOM_EXIT_SOUTH_EXISTS) {
            printf("\033[0;32m");
            printf("South\n");
            printf("\033[0;0m");
        } else {
            printf("\033[0;31m");
            printf("South\n");
            printf("\033[0;0m");
        }
        if (exits & GAME_ROOM_EXIT_WEST_EXISTS) {
            printf("\033[0;32m");
            printf("West\n");
            printf("\033[0;0m");
        } else {
            printf("\033[0;31m");
            printf("West\n");
            printf("\033[0;0m");
        }
    }
