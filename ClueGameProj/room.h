#ifndef room_H
#define room_H
#include <stdlib.h>
#include <stdio.h>
#include "items.h"
#include "characters.h"
struct Room{
	char *name; 	 
	struct Character *character;
	char *description;
  	struct Item *items;
  	struct Room *north;
	struct Room *south;
  	struct Room *east;
	struct Room *west; 
	struct Avatar *avatar;
	struct Room *next;
};

																																
struct Room *room(char *name,struct Character *character,char *description, struct Item* items, struct Room *north, struct Room
*south, struct Room *east,struct Room *west,struct Avatar *avatar, struct Room *next);

struct Room* room_north(struct Room* room);

struct Room* room_south(struct Room* room);

struct Room* room_east(struct Room* room);

struct Room* room_west(struct Room* room);

char* room_description(struct Room* room);

struct Character* character_in_room(struct Room* room);

struct Item* item_in_room(struct Room* room);

struct Avatar* avatar_in_room(struct Room* room);

struct Room* next_room(struct Room* room);

char* room_name(struct Room* room);

#endif
