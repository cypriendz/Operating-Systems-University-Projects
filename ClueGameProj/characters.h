#ifndef characters_H
#define characters_H
#include <stdio.h>
#include <stdlib.h>

struct Character{
char *name;
struct Character *next;
};

struct Avatar{
struct Item *item;  
char *name;
};

struct Avatar *avatar(struct Item *item, char* name);

struct Character* character(char *name, struct Character* next);

char* character_name(struct Character* character);

struct Character* next_character(struct Character* character);

struct Item* avatar_item(struct Avatar *avatar);

char* avatar_name(struct Avatar *avatar);
#endif
