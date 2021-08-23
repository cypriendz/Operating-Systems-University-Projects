#ifndef items_H
#define items_H
#include <stdio.h>
#include <stdlib.h>


struct Item{
char *name;
struct Item* next;
};

struct Item *item(char* name, struct Item* next);

char* item_name(struct Item* item);

struct Item* item_next(struct Item* item);

struct Item* item_take(char* name, struct Item** first);

struct Item* item_drop(char* name, struct Item** first);

#endif
