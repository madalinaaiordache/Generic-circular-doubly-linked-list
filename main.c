// Copyright 2021 Iordache Madalina Gabriela 313CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CircularDoublyLinkedList.c"

int main()
{
    cdll *galaxy;
    char command[16];
    char direction;
    char data[25];
    unsigned int M, pos_planet, pos_shield, pos_planet1, pos_planet2,
                 nr_shields, shield_val, val_upgrade, units;

    scanf("%u", &M);
    galaxy = create_galaxy(1024);
    for (unsigned int i = 0; i < M; i++) {
        scanf("%s", command);
        if (strncmp(command, "ADD", 3) == 0) {
            scanf("%s", data);
            scanf("%u", &pos_planet);
            scanf("%u", &nr_shields);
            add_planet(galaxy, data, pos_planet, nr_shields);
        }
        if (strncmp(command, "BLH", 3) == 0) {
            scanf("%u", &pos_planet);
            struct node *temp = remove_planet(galaxy, pos_planet, 1);
            free_deletedPlanet(&temp);
        }
        if (strncmp(command, "UPG", 3) == 0) {
            scanf("%u", &pos_planet);
            scanf("%u", &pos_shield);
            scanf("%u", &val_upgrade);
            shield_upgrade(galaxy, pos_planet, pos_shield, val_upgrade);
        }
        if (strncmp(command, "EXP", 3) == 0) {
            scanf("%u", &pos_planet);
            scanf("%u", &shield_val);
            add_shield(galaxy, pos_planet, shield_val);
        }
        if (strncmp(command, "RMV", 3) == 0) {
            scanf("%u", &pos_planet);
            scanf("%u", &pos_shield);
            struct node *temp = remove_shield(galaxy, pos_planet, pos_shield);
            if (temp != NULL) {
                free(temp->data);
                free(temp);
            }
        }
        if (strncmp(command, "COL", 3) == 0) {
            scanf("%u %u", &pos_planet1, &pos_planet2);
            galactic_warfare(galaxy, pos_planet1, pos_planet2);
        }
        if (strncmp(command, "ROT", 3) == 0) {
            scanf("%u", &pos_planet);
            scanf(" %c", &direction);
            scanf("%u", &units);
            rotate_planet(galaxy, pos_planet, direction, units);
        }
        if (strncmp(command, "SHW", 3) == 0) {
            scanf("%u", &pos_planet);
            planet_facts(galaxy, pos_planet);
        }
    }
    free_galaxy(&galaxy);
    return 0;
}
