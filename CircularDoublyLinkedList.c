// Copyright 2021 Iordache Madalina Gabriela 313CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"

cdll* create_galaxy()
{
    // create and initialize a circular doubly linkedlist
    cdll *galaxy = calloc(1, sizeof(cdll));

    galaxy->head = NULL;
    galaxy->tail = NULL;
    galaxy->size = 0;

    return galaxy;
}

cdll *create_shields(unsigned int nr_shields)
{
    // memory allocation of shield list
    // data in every node is equal to 1
    cdll *shields = calloc(1, sizeof(cdll));
    shields->size = nr_shields;
    int nr = 1;

    for (unsigned int i = 0; i < nr_shields; i++) {
        struct node *temp = calloc(1, sizeof(node));
        temp->data = calloc(1, sizeof(int));
        memcpy(((int *)temp->data), &nr, sizeof(int));

         // insert shield when shield list is empty
        if (shields->head == NULL) {
            shields->head = temp;
            shields->tail = temp;
            temp->prev = shields->tail;
            temp->next = shields->head;

        } else {
            // insert shield at the end of the shield list
            temp->prev = shields->tail;
            shields->tail->next = temp;
            temp->next = shields->head;
            shields->head->prev = temp;
            shields->tail = temp;
        }
    }
    return shields;
}

void add_planet(cdll *galaxy, char *name, unsigned int pos_planet,
                unsigned int nr_shields)
{
    struct node *curr = galaxy->head;

    // error when trying to insert planet on position bigger than galaxy size
    if (pos_planet > galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    }

    // allocate memory for a planet
    // initialize main characteristics of the planet
    struct node *temp = calloc(1, sizeof(node));
    temp->data = calloc(1, sizeof(struct planet));
    strncpy(((struct planet *)(temp->data))->name, name, 25);
    ((struct planet*)temp->data)->kills = 0;
    ((struct planet*)temp->data)->shields = create_shields(nr_shields);

    if (galaxy->head == NULL) {
        // insert planet when galaxy is empty
        galaxy->head = temp;
        galaxy->tail = temp;
        temp->prev = galaxy->tail;
        temp->next = galaxy->head;

        printf("The planet %s has joined the galaxy.\n",
               ((struct planet*)temp->data)->name);
    } else if (pos_planet == galaxy->size) {
        // insert planet at the end of the galaxy
        temp->prev = galaxy->tail;
        galaxy->tail->next = temp;
        temp->next = galaxy->head;
        galaxy->head->prev = temp;
        galaxy->tail = temp;

        printf("The planet %s has joined the galaxy.\n",
               ((struct planet*)temp->data)->name);
    } else if (pos_planet == 0) {
        // insert planet at the beginning of the galaxy
        temp->next = galaxy->head;
        galaxy->head->prev = temp;
        temp->prev = galaxy->tail;
        galaxy->tail->next = temp;
        galaxy->head = temp;

        printf("The planet %s has joined the galaxy.\n",
               ((struct planet*)temp->data)->name);
    } else {
        // insert planet at arbitrary position
        unsigned int i = 0;
        while (i != pos_planet - 1) {
            curr = curr->next;
            i++;
        }
        temp->prev = curr;
        temp->next = curr->next;
        curr->next->prev = temp;
        curr->next = temp;

        printf("The planet %s has joined the galaxy.\n",
               ((struct planet*)temp->data)->name);
    }
    // increase galaxy size after adding a planet
    galaxy->size++;
}

node *remove_planet(cdll *galaxy, unsigned int pos_planet, int type)
{
    struct node *temp = galaxy->head;
    if (temp == NULL) {
        printf("Planet out of bounds!\n");
        return NULL;
    }

    if (pos_planet >= galaxy->size && type == 1) {
        printf("Planet out of bounds!\n");
        return NULL;
    } else if (pos_planet == 0) {
        // remove planet from the beginning of the galaxy
        struct node *copy = galaxy->head;

        galaxy->head = galaxy->head->next;
        galaxy->head->prev = galaxy->tail;
        galaxy->tail->next = galaxy->head;

        if (type == 1) {
            printf("The planet %s has been eaten by the vortex.\n",
               ((struct planet*)copy->data)->name);
        } else {
            printf("The planet %s has imploded.\n",
            ((struct planet*)copy->data)->name);
        }
        galaxy->size--;
         if ((int)galaxy->size == 0) {
            galaxy->head = NULL;
            galaxy->tail = NULL;
        }
        return copy;
    } else if (pos_planet == (galaxy->size - 1)) {
        // remove planet from the end of the galaxy
        struct node *aux = galaxy->tail;

        galaxy->tail = galaxy->tail->prev;
        galaxy->tail->next = galaxy->head;
        galaxy->head->prev = galaxy->tail;

        if (type == 1) {
            printf("The planet %s has been eaten by the vortex.\n",
               ((struct planet*)aux->data)->name);
        } else {
            printf("The planet %s has imploded.\n",
            ((struct planet*)aux->data)->name);
        }
        galaxy->size--;
        if ((int)galaxy->size == 0) {
            galaxy->head = NULL;
            galaxy->tail = NULL;
        }
        return aux;
    } else {
        // remove planet at an arbitrary position
        unsigned int i = 0;

        while (i < pos_planet) {
            temp = temp->next;
            i++;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        if (type == 1) {
        printf("The planet %s has been eaten by the vortex.\n",
            ((struct planet*)temp->data)->name);
        } else {
        printf("The planet %s has imploded.\n",
        ((struct planet*)temp->data)->name);
        }
        // decrease galaxy size after planet deletion
        // return deleted planet
        galaxy->size--;
        return temp;
    }
}

void shield_upgrade(cdll *galaxy, unsigned int pos_planet,
                    unsigned int pos_shield, unsigned int val_upgrade)
{
    struct node *temp = galaxy->head;
    unsigned int i = 0, k = 0;
    // find the planet whose defense grid will be modified
    while (i != pos_planet) {
        i++;
        temp = temp->next;
    }
    if (pos_planet >= galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    } else if (pos_shield >= ((struct planet*)temp->data)->shields->size) {
        printf("Shield out of bounds!\n");
        return;
    } else {
        struct node *temp2 = ((struct planet*)(temp->data))->shields->head;

        // find the shield which will be upgraded
        while (k != pos_shield) {
            k++;
            temp2 = temp2->next;
        }
        // upgrade the shield with given upgrade value
        *(int *)temp2->data += val_upgrade;
    }
}

void add_shield(cdll *galaxy, unsigned int pos_planet,
                unsigned int shield_val)
{
    struct node *temp = galaxy->head;
    unsigned int  i = 0;

    // find the searched planet
    while (i != pos_planet) {
        i++;
        temp = temp->next;
    }

    if (pos_planet >= galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    } else {
        // allocate memory for every added shield
        struct node *aux = malloc(sizeof(node));
        aux->data = malloc(sizeof(int));
        memcpy(((int *)aux->data), &shield_val, sizeof(int));

        // insert shield at the ending of shield list

        node *tail = (((struct planet*)(temp->data))->shields)->tail;
        node *head = (((struct planet*)(temp->data))->shields)->head;
        tail->next = aux;
        head->prev = aux;
        aux->next = head;
        aux->prev = tail;
        (((struct planet*)(temp->data))->shields)->tail = aux;

        // increase size of shield list after adding a shield
        ((struct planet*)temp->data)->shields->size++;
    }
}

node *remove_shield(cdll *galaxy, unsigned int pos_planet,
                    unsigned int pos_shield)
{
    struct node *temp = galaxy->head;
    unsigned int  i = 0;

    // find the searched planet
    while (i != pos_planet) {
        i++;
        temp = temp->next;
    }

    if (pos_planet >= galaxy->size) {
        printf("Planet out of bounds!\n");
    } else if (pos_shield >= ((struct planet*)temp->data)->shields->size) {
        printf("Shield out of bounds!\n");
    } else if (((struct planet*)temp->data)->shields->size == 4) {
        printf("A planet cannot have less than 4 shields!\n");
    } else {
        struct node *temp2 = ((struct planet*)(temp->data))->shields->head;

        if (pos_shield == 0) {
        // remove shield from the beginning of the shields list
        struct node *copy = ((struct planet*)(temp->data))->shields->head;

        (((struct planet*)(temp->data))->shields)->head =
            (((struct planet*)(temp->data))->shields)->head->next;

        (((struct planet*)(temp->data))->shields)->head->prev =
            (((struct planet*)(temp->data))->shields)->tail;

        (((struct planet*)(temp->data))->shields)->tail->next =
            (((struct planet*)(temp->data))->shields)->head;

        (((struct planet*)(temp->data))->shields)->size--;
        free(copy->data);
        free(copy);
        copy = NULL;
        return copy;
        } else if (pos_shield ==
                   ((((struct planet*)(temp->data))->shields)->size - 1)) {
            // remove shield from the ending of the shields list
            struct node *aux = (((struct planet*)(temp->data))->shields)->tail;

            (((struct planet*)(temp->data))->shields)->tail =
                (((struct planet*)(temp->data))->shields)->tail->prev;

            (((struct planet*)(temp->data))->shields)->tail->next =
                (((struct planet*)(temp->data))->shields)->head;

            (((struct planet*)(temp->data))->shields)->head->prev =
                (((struct planet*)(temp->data))->shields)->tail;

            // decrease size of shield list after shield deletion
            (((struct planet*)(temp->data))->shields)->size--;
            // free memory and return deleted shield
            free(aux->data);
            free(aux);
            aux = NULL;
            return aux;
        } else {
            // remove shield at an arbitrary position in the shields list
            unsigned int i = 0;
            while (i != pos_shield) {
                temp2 = temp2->next;
                i++;
            }
            struct node* prev = temp2->prev;
            struct node* next = temp2->next;
            prev->next = next;
            next->prev = prev;

            (((struct planet*)(temp->data))->shields)->size--;
            free(temp2->data);
            free(temp2);
            temp2 = NULL;
            return temp2;
        }
    }
    return NULL;
}

void rotate_planet(cdll *galaxy, unsigned int pos_planet,
                   char direction, unsigned int units)
{
    struct node *temp = galaxy->head;
    unsigned int  i = 0, k = 0;

    // find the searched planet whose shield list will be rotated
    while (i != pos_planet) {
        i++;
        temp = temp->next;
    }

    if (pos_planet >= galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    }
    // do nothing if requested to rotate list
    // with a number of units equal to size
    if (units % ((struct planet *)(temp->data))->shields->size == 0) {
        return;
    }

    if (direction == 'c') {
        // clockwise rotation

        struct node *temp2 = ((struct planet *)(temp->data))->shields->head;

        // find given node position where rotation begins
        while (k != (units % ((struct planet *)(temp->data))->shields->size)) {
            k++;
            temp2 = temp2->prev;
        }

        // change list head and tail to rotate list
        ((struct planet *)(temp->data))->shields->head = temp2;
        ((struct planet *)(temp->data))->shields->tail = temp2->prev;
    } else if (direction == 't') {
        // counterclockwise rotation

        struct node *temp2 = ((struct planet *)(temp->data))->shields->head;

        // find given node position where rotation begins
        while (k != (units % ((struct planet *)(temp->data))->shields->size)) {
            k++;
            temp2 = temp2->next;
        }

        ((struct planet *)(temp->data))->shields->head = temp2;
        ((struct planet *)(temp->data))->shields->tail = temp2->prev;
    } else {
        printf("Not a valid direction!\n");
    }
}

void galactic_warfare(cdll *galaxy, unsigned int pos_planet1,
                      unsigned int pos_planet2)
{
    unsigned int  i = 0;
    int k = 0, n = 0;

    if (pos_planet1 >= galaxy->size || pos_planet2 >= galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    } else {
        // find the searched planet1
        struct node *temp = galaxy->head;
        while (i != pos_planet1) {
            i++;
            temp = temp->next;
        }

        // find the second planet which is right after the first one
        struct node *aux = temp->next;

        // choose position of shields involved in collision
        int pos_shield1 = ((struct planet *)(temp->data))->shields->size/4;
        int pos_shield2 = (((struct planet *)(aux->data))->shields->size/4)*3;

        // find given shields and decrease their values
        struct node *temp2 = ((struct planet *)(temp->data))->shields->head;
        while (k != pos_shield1) {
            k++;
            temp2 = temp2->next;
        }
        *(int*)temp2->data -= 1;

        struct node *aux2 = ((struct planet *)(temp->next->data))->
                            shields->head;
        while (n != pos_shield2) {
            n++;
            aux2 = aux2->next;
        }
        *(int*)aux2->data -= 1;

        // if a planet with a null shield is involved in a collision
        // it is removed from the galaxy
        if (*(int*)temp2->data == -1 && *(int*)aux2->data >= 0) {
            ((struct planet*)aux->data)->kills += 1;

            struct node *temp = remove_planet(galaxy, pos_planet1, 0);
            free_deletedPlanet(&temp);
        } else if (*(int*)aux2->data == -1 && *(int*)temp2->data >= 0) {
            ((struct planet*)temp->data)->kills += 1;

            struct node *temp = remove_planet(galaxy, pos_planet2, 0);
            free_deletedPlanet(&temp);
        } else if (*(int*)temp2->data == -1 && *(int*)aux2->data == -1) {
            struct node *temp1 = remove_planet(galaxy, pos_planet1, 0);
            free_deletedPlanet(&temp1);

            struct node *temp2 = remove_planet(galaxy, pos_planet2 - 1, 0);
            free_deletedPlanet(&temp2);
        }
    }
}

void print_planet(cdll *galaxy, unsigned int pos_planet)
{
    struct node *temp = galaxy->head;
    unsigned int  i = 0;

    while (i != pos_planet) {
        i++;
        temp = temp->next;
    }

    printf("NAME: %s\n", ((struct planet*)temp->data)->name);
    printf("CLOSEST: %s and %s", ((struct planet*)temp->prev->data)->name,
           ((struct planet*)temp->next->data)->name);
    printf("\n");

    struct node *temp2 = ((struct planet *)temp->data)->shields->head;
    printf("SHIELDS: ");
    while (temp2 != ((struct planet *)temp->data)->shields->tail) {
        int nr = *(int*)temp2->data;
        printf("%d ", nr);
        temp2 = temp2->next;
    }
    int nr = *(int*)temp2->data;
    printf("%d ", nr);
    printf("\n");
    printf("KILLED: %d\n", ((struct planet*)temp->data)->kills);
}

void print_edge_cases(int type, cdll *galaxy)
{
    struct node *temp = galaxy->head;

    if (type == 0) {
        // galaxy has only 2 planets and I want to show details of first planet
        printf("NAME: %s\n", ((struct planet*)temp->data)->name);
        printf("CLOSEST: %s", ((struct planet*)temp->next->data)->name);
        printf("\n");

        struct node *temp2 = ((struct planet *)temp->data)->shields->head;
        printf("SHIELDS: ");
        while (temp2 != ((struct planet *)temp->data)->shields->tail) {
            int nr = *(int*)temp2->data;
            printf("%d ", nr);
            temp2 = temp2->next;
        }
        int nr = *(int*)temp2->data;
        printf("%d ", nr);
        printf("\n");
        printf("KILLED: %d\n", ((struct planet*)temp->data)->kills);
    } else if (type == 1) {
        // galaxy has only 2 planets and I want to show details of 2nd planet
        temp = temp->next;
        printf("NAME: %s\n", ((struct planet*)temp->data)->name);
        printf("CLOSEST: %s", ((struct planet*)temp->prev->data)->name);
        printf("\n");

        struct node *temp2 = ((struct planet *)temp->data)->shields->head;
        printf("SHIELDS: ");
        while (temp2 != ((struct planet *)temp->data)->shields->tail) {
            int nr = *(int*)temp2->data;
            printf("%d ", nr);
            temp2 = temp2->next;
        }
        int nr = *(int*)temp2->data;
        printf("%d ", nr);
        printf("\n");
        printf("KILLED: %d\n", ((struct planet*)temp->data)->kills);
    } else {
        // galaxy has only 1 planet
        printf("NAME: %s\n", ((struct planet*)temp->data)->name);
        printf("CLOSEST: none");
        printf("\n");

        struct node *temp2 = ((struct planet *)temp->data)->shields->head;
        printf("SHIELDS: ");
        while (temp2 != ((struct planet *)temp->data)->shields->tail) {
            int nr = *(int*)temp2->data;
            printf("%d ", nr);
            temp2 = temp2->next;
        }
        int nr = *(int*)temp2->data;
        printf("%d ", nr);
        printf("\n");
        printf("KILLED: %d\n", ((struct planet*)temp->data)->kills);
    }
}

void planet_facts(cdll *galaxy, unsigned int pos_planet)
{
    // show characteristics for given planet
    if (pos_planet >= galaxy->size) {
        printf("Planet out of bounds!\n");
        return;
    } else  if (galaxy->size == 2) {
        if (pos_planet == 0) {
            print_edge_cases(0, galaxy);
        } else if (pos_planet == 1) {
            print_edge_cases(1, galaxy);
        }
    } else if (galaxy->size == 1) {
        print_edge_cases(2, galaxy);
    } else {
        print_planet(galaxy, pos_planet);
    }
}

void free_galaxy(struct cdll **galaxy)
{
    // deallocation of memory
    struct node *aux = (*galaxy)->head;
    if (*galaxy == NULL) {
        return;
    }

    do {
        aux = (*galaxy)->head;
        (*galaxy)->head = (*galaxy)->head->next;

        struct node *temp = ((struct planet *)aux->data)->shields->head;
        while (temp != ((struct planet *)aux->data)->shields->tail) {
            ((struct planet *)aux->data)->shields->head =
                ((struct planet *)aux->data)->shields->head->next;
            free(temp->data);
            free(temp);
            temp = ((struct planet *)aux->data)->shields->head;
        }
        free(temp->data);
        free(temp);
        free(((struct planet *)aux->data)->shields);

        free(aux->data);
        free(aux);
        aux = (*galaxy)->head;
        (*galaxy)->size--;
    } while ((*galaxy)->size != 0);
    free((*galaxy));
}

void free_deletedPlanet(struct node **aux)
{
    // deallocate memory for every deleted planet
    if (*aux == NULL) {
        return;
    }
    struct node *temp = ((struct planet *)(*aux)->data)->shields->head;
    while (temp != ((struct planet *)(*aux)->data)->shields->tail) {
        ((struct planet *)(*aux)->data)->shields->head =
            ((struct planet *)(*aux)->data)->shields->head->next;
        free(temp->data);
        free(temp);
        temp = ((struct planet *)(*aux)->data)->shields->head;
    }
    free(temp->data);
    free(temp);
    free(((struct planet *)(*aux)->data)->shields);

    free((*aux)->data);
    free(*aux);
}

void free_deletedShield(struct node **aux)
{
    // deallocate memory for every deleted shield
    if (*aux == NULL) {
        return;
    }
    free((*aux)->data);
    free(*aux);
}
