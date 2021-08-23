#include <stdio.h>
#include <stdlib.h>
#include "items.h"

struct Item *item(char* name, struct Item* next){
	struct Item* newItem = (struct Item*) malloc(sizeof(struct Item));
         newItem->name = name;
         newItem-> next = next;
         return newItem;
}

char* item_name(struct Item* item){
	if (item == NULL){
		return NULL;
	}
	else{
		return item->name;
	}

}


struct Item* item_next(struct Item* item){
	if (item == NULL){
               return NULL;
        }
	else{
               return item->next;
        }
	
}

struct Item* item_take(char* name, struct Item** first){
	struct Item *current = *first;
	struct Item *previous = NULL;
	int strcmp();
		
		if(current == NULL){
			return NULL;
		}
	
		struct Item* nextItem = item_next(current);
		
			while(current != NULL) {
				if(strcmp(name, item_name(current)) == 0) {
					if(nextItem == NULL){
						if(previous == NULL){
							first = NULL;
							return current;
						}
					previous->next = NULL;
					return current;
					}
				else if(previous != NULL){
					previous->next = nextItem;
					current->next = NULL;
					return current;
				}
				
				else{
					*first = nextItem;
					return current;
				}
			}
			previous = current;
			current = item_next(current);
			nextItem = item_next(current);
		}
		return NULL;
}

struct Item* item_drop(char* name, struct Item** first){

}

