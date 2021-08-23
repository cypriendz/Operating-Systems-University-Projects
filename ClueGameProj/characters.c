#include <stdio.h>
#include <stdlib.h>
#include "characters.h"

struct Character* character(char *name,struct Character *next){
	struct Character *newCharacter = (struct Character*) malloc(sizeof(struct Character));
	newCharacter-> name = name;
	newCharacter-> next = next;
	return newCharacter;
}

char* character_name(struct Character* character){
	if(character == NULL){
		return NULL;
}
	else{
		return character->name;
	}
}

struct Character* next_character(struct Character* character){
	if(character == NULL){
                return NULL;
}
        else{
                return character->next;
        }

}

struct Avatar *avatar(struct Item *item, char *name){
	struct Avatar *newAvatar = (struct Avatar*) malloc(sizeof(struct Avatar));
        newAvatar-> item = item;
	newAvatar->name = name;
	return newAvatar;
	
}

struct Item*  avatar_item(struct Avatar *avatar){
	if(avatar == NULL){
		return NULL;
	}
	else{
		return avatar->item;
	}
}

char* avatar_name(struct Avatar *avatar){
	if(avatar == NULL){
                return NULL;
        }
        else{
                return avatar->name;
        }
}

