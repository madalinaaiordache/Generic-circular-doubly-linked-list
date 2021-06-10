// Copyright 2021 Iordache Madalina Gabriela 313CA
#ifndef CIRCULARDOUBLYLINKEDLIST_H_
#define CIRCULARDOUBLYLINKEDLIST_H_

// every node is a planet
typedef struct node node;
struct node
{
    void *data;
    node *prev, *next;
};

// the circular doubly linkedlist is our galaxy
typedef struct cdll cdll;
struct cdll
{
    node *head;
    node *tail;
    void *data_size;
    unsigned int size;
};

struct planet
{
    // the circular doubly linkedlist is our planetary defense grid
    // every node is a shield
    cdll *shields;
    char name[25];
    int kills;
};


// functions which must be implemented

cdll *create_galaxy();

cdll *create_shields(unsigned int nr_shields);

void add_planet(cdll *galaxy, char *name, unsigned int pos_planet,
               unsigned int nr_shields);

node *remove_planet(cdll *galaxy, unsigned int pos_planet, int type);

void planet_facts(cdll *galaxy, unsigned int pos_planet);

void shield_upgrade(cdll *galaxy, unsigned int pos_planet,
                    unsigned int pos_shield, unsigned int val_upgrade);

void add_shield(cdll *galaxy, unsigned int pos_planet,
                unsigned int shield_val);

node *remove_shield(cdll *galaxy, unsigned int pos_planet,
                    unsigned int pos_shield);

void galactic_warfare(cdll *galaxy, unsigned int pos_planet1,
                      unsigned int pos_planet2);

void rotate_planet(cdll *galaxy, unsigned int pos_planet,
                   char direction, unsigned int units);

void free_galaxy(struct cdll **galaxy);

void free_deletedPlanet(struct node **aux);

void free_deletedShield(struct node **aux);

#endif  // CIRCULARDOUBLYLINKEDLIST_H_
