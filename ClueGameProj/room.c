#include <stdlib.h>
#include <stdio.h>
#include "room.h"
#include "characters.h"
#include "items.h"

																														
struct Room *room(char *name,struct Character *character,char *description, struct Item* items, struct Room *north, struct Room
*south, struct Room *east, struct Room *west,struct Avatar *avatar, struct Room *next){

	struct Room *ruum = (struct Room *) malloc(sizeof(struct Room));
	ruum->name = name;
	ruum->character = character;  
	ruum->description = description;
  	ruum->items = items;
  	ruum->north = north;
  	ruum->south = south;
  	ruum->east = east;
  	ruum->west = west;
	ruum->avatar = avatar;
  	ruum->next = next;
	return ruum;
}



struct Room* room_north(struct Room* room){
        if (room == NULL){
                return NULL;
        }
        else{
                return room->north;
        }

}

struct Room *room_south(struct Room* room){
        if (room == NULL){
                return NULL;
        }
        else{
                return room->south;
        }

}

struct Room* room_east(struct Room* room){
        if (room == NULL){
                return NULL;
        }
        else{
                return room->east;
        }

}

struct Room* room_west(struct Room* room){
        if (room == NULL){
                return NULL;
        }
        else{
                return room->west;
        }

}

char* room_description(struct Room* room){
	if (room == NULL){ 
        	return NULL;
        }
        else{
                return room->description;
        }
}

char* room_name(struct Room* room){
        if (room == NULL){
                return NULL;
        }
        else{
                return room->name;
        }
}


struct Character* character_in_room(struct Room* room){
	if(room == NULL){
        	return NULL;
        }
        else{
                return room->character;
        }
}

struct Item* item_in_room(struct Room* room){
        if (room == NULL){
                return NULL;
        }
        else{
                return room->items;
        }

}
struct Avatar* avatar_in_room(struct Room* room){
	if (room == NULL){
                return NULL;
        }
        else{
                return room->avatar;
        }
}



struct Room* next_room(struct Room* room){
	if(room == NULL){
		return NULL;
	}
	else{
		return room->next;
	}
} 
