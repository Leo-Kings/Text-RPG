/*
 * 
 * TextBased-RPG
 * Leo King 
 * May 26, 2021 
 * 
 */
//Personal Library
#include "UNIXBOARD.h"
#include "Game.h"
#include "Player.h"

//Standard Library
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


//Variable Definitions
static struct {
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    uint8_t north;
    uint8_t east;
    uint8_t south;
    uint8_t west;
} currentRoom = {};

//Helper Function Prototype
int LoadRoom(uint16_t roomNumber);

//Direction Control
int GameGoNorth(void) {
    if (currentRoom.north != 0) {
        return LoadRoom(currentRoom.north);
    }
    return STANDARD_ERROR;
}

int GameGoEast(void) {
    if (currentRoom.east!= 0) {
        return LoadRoom(currentRoom.east);
    }
    return STANDARD_ERROR;
}

int GameGoSouth(void) {
    if (currentRoom.south != 0) {
        return LoadRoom(currentRoom.south);
    }
    return STANDARD_ERROR;
}

int GameGoWest(void) {
    if (currentRoom.west != 0) {
        return LoadRoom(currentRoom.west);
    }
    return STANDARD_ERROR;
}

//Initializes at the Starting Room
int GameInit(void) {
    return LoadRoom(STARTING_ROOM);
}

//Stores the title as a string in our structure
int GameGetCurrentRoomTitle(char *title) {
    strncpy(title, currentRoom.title, GAME_MAX_ROOM_TITLE_LENGTH + 1);
    return strlen(title);
}

//Stores the description as a string in our structure
int GameGetCurrentRoomDescription(char *desc) {
    strncpy(desc, currentRoom.description, GAME_MAX_ROOM_DESC_LENGTH + 1);
    return strlen(desc);
}

//Checks for all the Available Exits
uint8_t GameGetCurrentRoomExits(void) {
    uint8_t RoomExits = 0;
    if (currentRoom.north != 0) {
        RoomExits += GAME_ROOM_EXIT_NORTH_EXISTS;
    }
    if (currentRoom.east != 0) {
        RoomExits += GAME_ROOM_EXIT_EAST_EXISTS;
    }
    if (currentRoom.south != 0) {
        RoomExits += GAME_ROOM_EXIT_SOUTH_EXISTS;
    }
    if (currentRoom.west != 0) {
        RoomExits += GAME_ROOM_EXIT_WEST_EXISTS;
    }
    return RoomExits;
}

//Helper Function Code
int LoadRoom(uint16_t roomNumber) {
    FILE *room;

    char roomFileName[50];
    int index;
    int x = TRUE;
    //int counter = 0;
    sprintf(roomFileName, "RoomFiles/room%d.txt", roomNumber);
    room = fopen(roomFileName, "rb");
    if (room == NULL) {
        fclose(room);
        return STANDARD_ERROR;
    }
    
    //Skips through first 3 letters
    fgetc(room);
    fgetc(room);
    fgetc(room);
    //Title
    int titlelength = fgetc(room); //Files are formulated to have the 4th value as the title length
    if (titlelength == EOF || fgets(currentRoom.title, titlelength + 1, room) == NULL) {
        fclose(room);
        return STANDARD_ERROR;
    }
    currentRoom.title[titlelength] = '\0';

    while (x) {
        int itemlength = fgetc(room);
        if (itemlength == EOF) {
            return STANDARD_ERROR;
        }
        int missingItem = FALSE;
        for (index = 0; index < itemlength; index++) {
            int ret = FindInInventory(fgetc(room));
            if (ret == STANDARD_ERROR) {
                missingItem = TRUE;
            }
        }
        
        if (missingItem) {
            int desclength = fgetc(room);
            fseek(room, desclength, SEEK_CUR);
            int itemcontainedlength = fgetc(room);
            fseek(room, itemcontainedlength, SEEK_CUR);
            fgetc(room);
            fgetc(room);
            fgetc(room);
            fgetc(room);
            
        } else {
            int desclength = fgetc(room);
            fgets(currentRoom.description, desclength + 1, room);
            int itemcontainedlength = fgetc(room);
            for (index = 0; index < itemcontainedlength; index++) {
                int ret = AddToInventory(fgetc(room));
                if (ret == STANDARD_ERROR) {
                    return STANDARD_ERROR;
                }
            } 
            currentRoom.north = fgetc(room);
            currentRoom.east = fgetc(room);
            currentRoom.south = fgetc(room);
            currentRoom.west = fgetc(room);
            break;
            }
        }
    fclose(room);
    return SUCCESS;
}
