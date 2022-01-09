#ifndef PLAYER_H
#define PLAYER_H



#include "UNIXBOARD.h"
#include "Player.h"
#include <stdint.h>
#define INVENTORY_SIZE 4

static uint8_t inventory_size = 0;
static uint8_t inventory[INVENTORY_SIZE] = {0};
int i;

int AddToInventory(uint8_t item) {
    if (inventory_size == INVENTORY_SIZE) {
        return STANDARD_ERROR;
    }
    inventory[inventory_size] = item;
    inventory_size++;
    return SUCCESS;
}

int FindInInventory(uint8_t item) {
    for (i = 0; i < INVENTORY_SIZE; i++) {
        if (item == inventory[i]) {
            return SUCCESS;
        }
    }
    return STANDARD_ERROR;
}

#endif // PLAYER_H