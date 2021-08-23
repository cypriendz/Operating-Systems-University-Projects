#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "items.h"
#include "room.h"
#include "characters.h"
#include <string.h> 
//this is the structure for the Answer. An Answer has an item, a room, and a character	
struct Answer{	
	struct Item *item;
	struct Room *room;
	struct Character* character;
};
	
int isAnswer = 1;		//variable for checking if answer is correct, 1 for no, 0 for yes				
struct Answer *answer(struct Item *item, struct Room *room, struct Character* character); //all are protypes for functions that will be explained later
struct Room* answer_room(struct Answer *answer);
struct Item* answer_item(struct Answer *answer);
struct Character* answer_character(struct Answer *answer);
void shuffle_board(struct Room *board[3][3]);
void print_board(struct Room *board[3][3]);
void connect_map(struct Room *b[3][3]);
void characterToRoom(struct Room *b[3][3], struct Character* cArr[5]);
void itemToRoom(struct Room *b[3][3], struct Item *itArr[6]); 
void shuffle_characters(struct Character* cArr[5]);
void shuffle_items(struct Item *itArr[6]);
void theAnswer(struct Room *rArr[9], struct Answer *ans, struct Item *it[6], struct Character *ch[5]);
void help();
void list(struct Room *rArr[9],struct Character *cArr[5],struct Item *itArr[6]);
void look(struct Room* board[3][3]);
void inventory(struct Avatar* player);
void place_player(struct Room* board[3][3],struct Avatar * player);
void go_north(struct Room *board[3][3], struct Avatar *player);
void go_south(struct Room *board[3][3], struct Avatar *player);
void go_east(struct Room *board[3][3],struct Avatar *player );
void go_west(struct Room *board[3][3], struct Avatar *player);
void drop_item(struct Room *board[3][3],struct Avatar *player, char *item);
void take_revolver(struct  Room *board[3][3],struct Avatar *player, char *name);
void take_dagger(struct  Room *board[3][3],struct Avatar *player, char *name);
void take_rope(struct  Room *board[3][3],struct Avatar *player, char *name);
void take_candlestick(struct  Room *board[3][3],struct Avatar *player, char *name);
void take_wrench(struct  Room *board[3][3],struct Avatar *player, char *name);
void take_pillow(struct  Room *board[3][3],struct Avatar *player, char *name);
void clue_plum(int isAnswer,struct Room *board[3][3],struct Avatar *player, struct Answer *ans, struct Character *character2);
void clue_scarlett(int isAnswer ,struct Room *board[3][3],struct Avatar *player, struct Answer *ans,struct Character *character1);
void clue_peacock(int isAnswer ,struct Room *board[3][3],struct Avatar *player, struct Answer *ans,struct Character *character3);
void clue_green(int isAnswer ,struct Room *board[3][3],struct Avatar *player, struct Answer *ans,struct Character *character4);
void clue_mustard(int isAnswer ,struct Room *board[3][3],struct Avatar *player, struct Answer *ans,struct Character *character5);
void drop_revolver(struct Room *board[3][3],struct Avatar *player, char *name);			
void drop_rope(struct Room *board[3][3],struct Avatar *player, char *name);
void drop_candlestick(struct Room *board[3][3],struct Avatar *player, char *name);											
void drop_pillow(struct Room *board[3][3],struct Avatar *player, char *name);											
void drop_dagger(struct Room *board[3][3],struct Avatar *player, char *name);
void drop_wrench(struct Room *board[3][3],struct Avatar *player, char *name);																		
int main(int argc, char *argv[]) { //look at README.txt for explaination of main
	struct Item *items1 = item("dagger", NULL);
	struct Item *items2 = item("rope", NULL);
	struct Item *items3 = item("candlestick", NULL);
	struct Item *items4 = item("wrench", NULL);
	struct Item *items5 = item("revolver", NULL);
	struct Item *items6 = item("pillow", NULL);
	
	struct Character *character1 = character("Scarlett",NULL);
	struct Character *character2 = character("Plum",NULL);
	struct Character *character3 = character("Peacock",NULL);
	struct Character *character4 = character("Green",NULL);
	struct Character *character5 = character("Mustard",NULL);
																								
	struct Room *room1 = room("kitchen",NULL," a large pink painted kitchen" , NULL, NULL, NULL, NULL, NULL,NULL,NULL);
	struct Room *room2 = room("hallway", NULL,"a long hall way with weird pictures on the walls" , NULL, NULL, NULL, NULL, NULL,NULL,NULL); 
	struct Room *room3 = room("ballroom",NULL, "a ballroom with shoe marks on the ground" , NULL, NULL, NULL, NULL, NULL,NULL,NULL); 
	struct Room *room4 = room("theater",NULL, "a movie theater but no movie playing" , NULL, NULL, NULL, NULL, NULL,NULL,NULL); 
	struct Room *room5 = room("dining room",NULL, "a dining room with some nice chairs" , NULL, NULL, NULL, NULL, NULL,NULL,NULL); 
	struct Room *room6 = room("library",NULL, "a library with lots of picture books" , NULL, NULL, NULL, NULL, NULL,NULL,NULL); 
	struct Room *room7 = room("office",NULL, "an office with some cold tea on the desk" , NULL, NULL, NULL, NULL, NULL,NULL,NULL); 
	struct Room *room8 = room("bathroom",NULL, "a bathroom that smells real bad" , NULL, NULL, NULL, NULL, NULL,NULL,NULL); 
	struct Room *room9 = room("bedroom",NULL, "a bedroom with a cradle but no bed" , NULL, NULL, NULL, NULL, NULL,NULL,NULL); 
	
	struct Room *rArr[9] = {room1,room2,room3,room4,room5,room6,room7,room8,room9};
	struct Room *board[3][3] = {{room1,room2,room3},{room4,room5,room6},{room7,room8,room9}};
	struct Character* cArr[5] = {character1,character2,character3,character4,character5};
	struct Item* itArr[6] = {items1,items2,items3,items4,items5,items6};
							
	struct Answer *ans = answer(NULL,NULL,NULL);
	struct Avatar *player = avatar(NULL, "cyp");
		
	shuffle_board(board);
	shuffle_characters(cArr);
	shuffle_items(itArr);
	itemToRoom(board,itArr);
	characterToRoom(board,cArr);
	connect_map(board);
	theAnswer(rArr, ans, itArr, cArr);
	place_player(board, player);	
	int numGuesses = 0;
	
	while (isAnswer != 0){
		printf("\n");
		printf("what would you like to do, type help for options\n");

		char *buffer;
     		size_t bufsize = 32;
    		size_t characters;	
		buffer = (char *)malloc(bufsize * sizeof(char));
		characters = getline(&buffer,&bufsize,stdin);  		
			if( buffer == NULL){
        		perror("Unable to allocate buffer");
        		exit(1);
			}		
		
		printf("You typed: %s\n",buffer);
		
		int result = strncmp(buffer, "help",strlen("help"));
			if(result == 0){
				help();
			}
						
		int result1 = strncmp(buffer, "list",strlen("list"));
                        if(result1 == 0){
                		list(rArr,cArr,itArr);
		        }
		int result3 = strncmp(buffer, "look",strlen("look"));
                        if(result3 == 0){
                        	look(board);
                        }
		int result4 = strncmp(buffer, "go NORTH",strlen("go NORTH"));
                        if(result4 == 0){
                                go_north(board,player);
                        }
		int result5 = strncmp(buffer, "go SOUTH",strlen("go SOUTH"));
                        if(result5 == 0){
                                go_south(board, player);
                        }
		int result6 = strncmp(buffer, "go EAST",strlen("go EAST"));
                        if(result6 == 0){
                                go_east(board, player);
                        }
		int result7 = strncmp(buffer, "go WEST",strlen("go WEST"));
                        if(result7 == 0){
                                go_west(board, player);
                        }
		int result8 = strncmp(buffer, "drop ITEM",strlen("drop ITEM"));
                        if(result8 == 0){
                                
                        }
		int result9 = strncmp(buffer, "inventory",strlen("inventory"));
                        if(result9 == 0){
                        	inventory(player);
			}
		int result11 = strncmp(buffer, "take revolver",strlen("take revolver"));
			if(result11 == 0){
				take_revolver(board,player,"revolver");
                        }
		int result12 = strncmp(buffer, "take dagger",strlen("take dagger"));
                        if(result12 == 0){
                                take_dagger(board,player,"dagger");
                        }			
		int result13 = strncmp(buffer, "take pillow",strlen("take pillow"));
                        if(result13 == 0){
                                take_pillow(board,player,"pillow");
                        }
		int result14 = strncmp(buffer, "take rope",strlen("take rope"));
                        if(result14 == 0){
                                take_rope(board,player,"rope");
                        }
		int result15 = strncmp(buffer, "take candlestick",strlen("take candlestick"));
                        if(result15 == 0){
                                take_candlestick(board,player,"candlestick");
                        }
		int result16 = strncmp(buffer, "take wrench",strlen("take wrench"));
                        if(result16 == 0){
                                take_wrench(board,player,"wrench");
                        }
		int result17 = strncmp(buffer, "clue PLUM",strlen("clue PLUM"));
                        if(result17 == 0){
				clue_plum(isAnswer,board,player,ans,character2);
                       		numGuesses++;
			}
		int result18 = strncmp(buffer, "clue GREEN",strlen("clue GREEN"));
                        if(result18 == 0){
                        	clue_green(isAnswer ,board,player,ans,character4);
				numGuesses++;
			}
		int result19 = strncmp(buffer, "clue MUSTARD",strlen("clue MUSTARD"));
                        if(result19 == 0){
                        	clue_mustard(isAnswer ,board,player,ans,character5);
				numGuesses++;
			}
		int result20 = strncmp(buffer, "clue SCARLETT",strlen("clue SCARLETT"));
                        if(result20 == 0){
				clue_scarlett(isAnswer ,board,player,ans,character1);
				numGuesses++;
                        }
		int result21 = strncmp(buffer, "clue PEACOCK",strlen("clue PEACOCK"));
                        if(result21 == 0){
                        	clue_peacock(isAnswer ,board,player,ans,character3);
				numGuesses++;
			}
		int result22 = strncmp(buffer,"drop revolver",strlen("drop revolver"));
			if(result22 == 0){
				drop_revolver(board,player,"revolver");
			}	
		int result23 = strncmp(buffer,"drop wrench",strlen("drop wrench"));
                        if(result23 == 0){
                                drop_wrench(board,player,"wrench");
                        }		
		int result24 = strncmp(buffer,"drop dagger",strlen("drop dagger"));
                        if(result24 == 0){
                                drop_dagger(board,player,"dagger");
                        }
		int result25 = strncmp(buffer,"drop candlestick",strlen("drop candlestick"));
                        if(result25 == 0){
                                drop_candlestick(board,player,"candlestick");
                        }
		int result26 = strncmp(buffer,"drop pillow",strlen("drop pillow"));
                        if(result26 == 0){
                                drop_pillow(board,player,"pillow");
                        }
		int result27 = strncmp(buffer,"drop rope",strlen("drop rope"));
                        if(result27 == 0){
                                drop_wrench(board,player,"rope");
                        }

		printf("num Guesses: %d\n", numGuesses); 
		if(numGuesses >= 10 && isAnswer != 0){
			free(items1);
			free(items2);
			free(items3);
			free(items4);
			free(items5);
			free(items6);
			free(character1);
			free(character2);
			free(character3);
			free(character4);
			free(character5);
			free(room1);
			free(room2);
			free(room3);
			free(room4);
			free(room5);
			free(room6);
			free(room7);
			free(room8);
			free(room9);
			free(ans);
			free(player);
			free(board);
			free(itArr);
			free(cArr);
			free(rArr); 
			printf("you've lost after 10 clues \n");
			exit(0);
		}
		
		


	}
	printf("you won! \n");
	 free(items1);
                        free(items2);
                        free(items3);
                        free(items4);
                        free(items5);
                        free(items6);
                        free(character1);
                        free(character2);
                        free(character3);
                        free(character4);
                        free(character5);
                        free(room1);
                        free(room2);
                        free(room3);
                        free(room4);
                        free(room5);
                        free(room6);
                        free(room7);
                        free(room8);
                        free(room9);
                        free(ans);
                        free(player);
                        free(board);
                        free(itArr);
                        free(cArr);
                        free(rArr); 
	

}
//this function takes each index of a 2-d array that holds rooms and gives each room a North, South, East, and West room. 
void connect_map(struct Room *b[3][3]){
        b[0][0]->north = b[2][0];
        b[0][0]->south = b[1][0];
        b[0][0]->east = b[0][1];
        b[0][0]->west = b[0][2];

	b[1][0]->north = b[0][0];
        b[1][0]->south = b[2][0];
        b[1][0]->east = b[1][1];
        b[1][0]->west = b[2][1];

	b[2][0]->north = b[1][0];
        b[2][0]->south = b[0][0];
        b[2][0]->east = b[2][1];
        b[2][0]->west = b[2][2];

	b[0][1]->north = b[2][1];
        b[0][1]->south = b[1][1];
        b[0][1]->east = b[0][2];
        b[0][1]->west = b[0][0];

        b[1][1]->north = b[0][1];
        b[1][1]->south = b[2][1];
        b[1][1]->east = b[1][2];
        b[1][1]->west = b[1][0];

        b[2][1]->north = b[1][1];
        b[2][1]->south = b[0][1];
        b[2][1]->east = b[2][2];
        b[2][1]->west = b[2][0];

	b[0][2]->north = b[2][2];
        b[0][2]->south = b[2][1];
        b[0][2]->east = b[0][0];
        b[0][2]->west = b[0][1];

        b[2][1]->north = b[0][2];
        b[2][1]->south = b[2][2];
        b[2][1]->east = b[1][0];
        b[2][1]->west = b[1][1];

        b[2][2]->north = b[1][2];
        b[2][2]->south = b[0][2];
        b[2][2]->east = b[2][0];
        b[2][2]->west = b[2][1];
}

//this function is used to create an answer pointer. It takes an all the requiured variable info from the parameter and assigns it to the respective variables that make
//up an Answer struct
struct Answer *answer(struct Item *item, struct Room *room, struct Character* character){
	struct Answer* newAnswer = (struct Answer*) malloc(sizeof(struct Answer));
	newAnswer-> item = item;
	newAnswer-> room = room;
	newAnswer-> character = character;
	return newAnswer;
}
//this function takes an answer and returns its room if the answer is not NULL
struct Room* answer_room(struct Answer *answer){
	if(answer == NULL){
		return NULL;
	}
	else{
		return answer->room;
	}
}
//this function takes an answer and returns its item if the answer is not NULL								
struct Item* answer_item(struct Answer *answer){
	if(answer == NULL){
                return NULL;
        }
        else{
                return answer->item;
        }
}

//this function takes an answer and returns its character if the answer is not NULL
struct Character* answer_character(struct Answer *answer){
	if(answer == NULL){
                return NULL;
        }
        else{
                return answer->character;
        }
}

//this function generates a random number b/w 0 and i, then shuffles the array using this random number and a temporary room to assign each index of the 2d array to a
//random location
void shuffle_board(struct Room *board[3][3]){
 	srand(time(NULL));
        for (int i=0; i < 3; i++){
                int r = rand() % (i+1);

                for (int j = 0; j < 3; j++){
                        struct Room *temp =  board[i][j];
                        board[i][j] =  board[r][j];
                        board[r][j] = temp;
                }
        }

}

//this function places each of the randomized characters in the character array given to a location on the 2d array. Each room is randomly placed each game so characters
//end up in different rooms each game.
void characterToRoom(struct Room *b[3][3], struct Character* cArr[5]){
	b[0][0]->character = cArr[0];
        b[1][0]->character = cArr[1];
        b[2][1]->character = cArr[2];
        b[0][2]->character = cArr[3];
        b[1][2]->character = cArr[4];

}																			
//this function places each of the randomized item in the item array given to a location on the 2d array. Each room is randomly placed each game so item
//end up in different rooms each game.
void itemToRoom(struct Room *b[3][3], struct Item *itArr[6]){
	b[0][0]->items = itArr[0];
	b[1][1]->items = itArr[1];
	b[2][2]->items = itArr[2];
	b[2][0]->items = itArr[3];
	b[0][2]->items = itArr[4];
	b[2][1]->items = itArr[5]; 
}

//this function takes a character array and shuffles the characters within it by using a randomy generated number and a temp character to place each character in a random
//index w/o losing any of the characters
void shuffle_characters(struct Character* cArr[5]){
	
	srand(time(NULL));	
	for (int i= 0; i < 5; i++){
                int r = rand() % (i+1);
		struct Character *temp = cArr[r];
                 cArr[r] = cArr[i];
                 cArr[i] = temp;
	}	
}
//this function takes n item array and shuffles the items within it by using a randomy generated number and a temp item to place each item in a random
//index w/o losing any of the characters
void shuffle_items(struct Item *itArr[6]){
	srand(time(NULL));
        for (int i= 0; i < 6; i++){
                int r = rand() % (i+1);
                struct Item *temp = itArr[r];
                 itArr[r] = itArr[i];
                 itArr[i] = temp;
        }

}
//This generates two random numbers and places the player on the 2d board given with the indexs supplied by the random number
void place_player(struct Room* board[3][3],struct Avatar * player){
	srand(time(NULL));
	int r = rand() % 3;
	int r1 = rand() % 3;
	board[r][r1] -> avatar = player;
}
//generates a random number within the bounds of each array size. Then places the variables of the randomly indexed arrays to the respective Answer variables
void theAnswer(struct Room* rArr[9], struct Answer *ans, struct Item *it[6], struct Character *ch[5]){
	srand(time(NULL));
	ans->item =  it[0 + rand() % 6];
	ans->room = rArr[0 + rand() % 9];
	ans->character = ch[0 + rand() % 5];
}
//prints out all the possible commands
void help(){
	printf("list: shows you all the rooms, items, and characters in game \n");
	printf("look: tells you the room your in, the rooms in each direction, the ITEM  in the room, and the character in the room \n");
	printf("north: places you in the room north of current room \n");
	printf("south: places you in the room south of current room \n");
	printf("east: places you in the room east of current room \n");	
	printf("west: places you in the room west of current room \n");		
	printf("take ITEM: places ITEM  in room into your inventory \n");
	printf("drop ITEM: removes ITEM in your inventory and places it in current room \n");
	printf("inventory: shows all items in your inventory \n");
	printf("clue Character: allows you to make a guess for the answer \n");
}
//lists all the items, characters, and rooms of the game by traversing each of the given arrays and printing at each index the contents inside of them until last index of
//is printed
void list(struct Room *rArr[9],struct Character *cArr[5],struct Item *itArr[6]){
	printf("The rooms are: \n");
	printf("%s\n",room_description(rArr[0]));
	for( int i = 1; i <= 8; i++){
		printf("%s\n",room_description(rArr[i]));
	}
	printf("\n");	
	printf("The ITEMS are: \n");
        printf("%s\n",item_name(itArr[0]));
        for( int i = 1; i <= 5; i++){
                printf("%s\n",item_name(itArr[i]));
        }

	printf("\n");
        printf("The characters are: \n");
        printf("%s\n",character_name(cArr[0]));
	for( int i = 1; i <=  4; i++){
                printf("%s\n",character_name(cArr[i]));
	}

}
															
// traverse board given to find which room character is in. Then prints the given variables of the Room struct. Items and Characters of room are printed until the
// final node of their lists is NULL 
void look(struct Room* board[3][3]){
	for (int i = 0; i < 3; i++){
		for(int j= 0; j < 3; j++){
			if(avatar_in_room(board[i][j]) != NULL){
				printf("the room you're in is ");
				printf("%s \n", room_description(board[i][j]));
				
				if(character_in_room(board[i][j]) != NULL){
					struct Character* temp = character_in_room(board[i][j]);
                                        struct Character* next = next_character(character_in_room(board[i][j]));
					
					while(temp != NULL){
						printf("the characters in the room are: ");
						printf("%s \n" ,character_name(temp));
						temp = next;
						next = next_character(next);
					}	
				}

				if(item_in_room(board[i][j]) != NULL){
					struct Item* temp = item_in_room(board[i][j]);
					struct Item* next = item_next(item_in_room(board[i][j]));
					
					while(temp != NULL){
						printf("the items in the room are: ");
						printf("%s \n" ,item_name(temp));
						temp = next;
						next = item_next(next);
					}
				}
			
				printf("The room to the north is:");
				printf("%s \n", room_description(room_north(board[i][j])));
				printf("The room to the south is:");
 				printf("%s \n", room_description(room_south(board[i][j])));			
				printf("The room to the east is:");
                                printf("%s \n", room_description(room_east(board[i][j])));
				printf("The room to the west is:");
                                printf("%s \n", room_description(room_west(board[i][j])));


			}	
		} 
	}
}
//goes through the linked list of items of the player Avatar Struct and prints each of the items until there are no left					
void inventory(struct Avatar *player){
	struct Item *temp;
	
	if(avatar_item(player) == NULL){
		printf("no items in inventory\n");
		return;
	}
	temp = player->item;
	while(temp != NULL){
		printf("%s \n",item_name(temp));
		temp = temp->next;  
	}
	
}
//places the avatar in the room that is north of its current location/postition on the board. done by traversing the 2d room board until player is found, then assigning the
//player to the avatar struct variable of the room to the north of the current room that was found
void go_north(struct Room *board[3][3], struct Avatar *player){
	for (int i = 0; i < 3; i++){
                for(int j= 0; j < 3; j++){
                        if(avatar_in_room(board[i][j]) != NULL){
				board[i][j]->north->avatar = player;
				board[i][j]-> avatar = NULL;
				return;
			}
		}
	}
}
//places the avatar in the room that is south of its current location/postition on the board. done by traversing the 2d room board until player is found, then assigning the
//player to the avatar struct variable of the room to the south of the current room that was found
void go_south(struct Room *board[3][3], struct Avatar *player){
	for (int i = 0; i < 3; i++){
                for(int j= 0; j < 3; j++){
                        if(avatar_in_room(board[i][j]) != NULL){
                                board[i][j]->south->avatar = player;
                                board[i][j]-> avatar = NULL;
                                return;
                        }
                }
        }
}
//places the avatar in the room that is east of its current location/postition on the board. done by traversing the 2d room board until player is found, then assigning the
//player to the avatar struct variable of the room to the east of the current room that was found
void go_east(struct Room *board[3][3], struct Avatar *player ){
	for (int i = 0; i < 3; i++){
                for(int j= 0; j < 3; j++){
                        if(avatar_in_room(board[i][j]) != NULL){
                                board[i][j]->east->avatar = player;
                                board[i][j]-> avatar = NULL;
                                return;
                        }
                }
        }
}

//places the avatar in the room that is west of its current location/postition on the board. done by traversing the 2d room board until player is found, then assigning the
//player to the avatar struct variable of the room to the west of the current room that was found	
void go_west(struct Room *board[3][3], struct Avatar *player){
	for (int i = 0; i < 3; i++){
                for(int j= 0; j < 3; j++){
                        if(avatar_in_room(board[i][j]) != NULL){
                                board[i][j]->west->avatar = player;
                                board[i][j]-> avatar = NULL;
                                return;
                        }
                }
        }
}

//finds player on the board by traversing the 2d room array until index with player is located. checks if the room contains the item that was typed in for name(revolver) in
//parameter. If the item isn't in the room, terminate. If the item is in the room, We take that item and place it into our characters inventory. Before that though we
//check if the inventory has any items. If it does we find the next open spot on the linked list and place the item there. We then go about removing the item from the
//loaction on the board/ room that was located.
void take_revolver(struct Room *board[3][3],struct Avatar *player, char *name){
int c = 0;
        int d = 0;
                for (int i = 0; i < 3; i++){
                        for(int j= 0; j < 3; j++){
                                if(avatar_in_room(board[i][j]) != NULL){
                                        c = i;
                                        d = j;
                                }
                        }
                }

                struct Item *current = item_in_room(board[c][d]);
                struct Item *previous = NULL;
                int strcmp();

                if(current == NULL){
                        return;
                }
                struct Item* nextItem = item_next(current);

                        while(current != NULL) {
                                if(strcmp(name, item_name(current)) == 0) {
                                        if(nextItem == NULL){
                                                if(previous == NULL){



                                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){

                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(avatar_item(player) == NULL){
                                                                	board[c][d]-> items = NULL;
                                                                	player->item = current;
                                                                	return;
                                                                }

                                                                else if(numNext == 0){
                                                                	board[c][d]-> items = NULL;
                                                                	player->item->next = current;
                                                                	return;
								 }

                                                                else if(numNext == 0){
                                                                	board[c][d]-> items = NULL;
                                                                	player->item->next = current;
                                                                	return;
                                                                }

                                                                else if(numNext == 1){
                                                                	board[c][d]-> items = NULL;
                                                                	player->item->next->next = current;
                                                                	return;
                                                                }

                                                                else if(numNext == 2){
                                                                	board[c][d]-> items = NULL;
                                                                	player-> item -> next -> next -> next = current;
                                                                	return;
                                                                }
//
                                                                else if(numNext == 3){
                                                                	board[c][d]-> items = NULL;
                                                                	player-> item -> next -> next -> next -> next = current;
                                                                	return;
                                                                }

                                                                else if(numNext == 4){
                                                                	board[c][d]-> items = NULL;
                                                                	player-> item -> next -> next -> next -> next -> next = current;
                                                                	return;
                                                                }

                                                }
                                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                        }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(avatar_item(player) == NULL){
                                                                	previous -> next = NULL;
                                                                	player->item = current;
									return;
                                                                }

                                                                else if(numNext == 0){
                                                                	previous -> next = NULL;
                                                                	player->item->next = current;
                                                                	return;
                                                                }

                                                                else if(numNext == 1){
                                                                	previous -> next = NULL;
                                                                	player->item->next->next = current;
                                                                	return;
                                                                }

                                                                else if(numNext == 2){
                                                                	previous -> next = NULL;
                                                                	player-> item -> next -> next -> next = current;
                                                                	return;
                                                                }

                                                                else if(numNext == 3){
                                                                	previous -> next = NULL;
                                                                	player-> item -> next -> next -> next -> next = current;
                                                                	return;
                                                                }

                                                                else if(numNext == 4){
                                                                	previous -> next = NULL;
                                                                	player-> item -> next -> next -> next -> next -> next = current;
                                                                	return;
                                                                }


                                                }


                                else if(previous != NULL){
                                        previous->next = nextItem;
                                        current->next = NULL;

                                        if(avatar_item(player) == NULL){
                                        	board[c][d]-> items = NULL;
                                                player->item = current;
                                                return;
                                        }

                                        struct Item* temp = avatar_item(player);
                                        struct Item* next = item_next(avatar_item(player));
                                        int numNext = 0;


                                        while(next != NULL){
                                                temp = next;;
                                                next = item_next(next);
						numNext++;
                                        }
                                                if(avatar_item(player) == NULL){
                                                        player->item = current;
                                                        return;
                                                }

                                                else if(numNext == 0){
                                                	player->item->next = current;
                                                	return;
                                                }

                                                else if(numNext == 1){
                                                	player->item->next->next = current;
                                                	return;
                                                }

                                                else if(numNext == 2){
                                                	player-> item -> next -> next -> next = current;
                                                	return;
                                                }

                                                else if(numNext == 3){
                                                	player-> item -> next -> next -> next -> next = current;
                                                	return;
                                                }

                                                else if(numNext == 4){
                                                	player-> item -> next -> next -> next -> next -> next = current;
                                                	return;
                                                }

                                }

                                else{
                                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(avatar_item(player) == NULL){
                                                                	board[c][d]-> items = NULL;
                                                                	player->item = current;
                                                                	return;
                                                                }
								else if(numNext == 0){
                                                                	board[c][d]-> items = NULL;
                                                                	player->item->next = current;
                                                                	return;
                                                                }

                                                                else if(numNext == 1){
                                                                	board[c][d]-> items = NULL;
                                                                	player->item->next->next = current;
                                                                	return;
                                                                }

                                                                else if(numNext == 2){
                                                                	board[c][d]-> items = NULL;
                                                                	player-> item -> next -> next -> next = current;
                                                                	return;
                                                                }

                                                                else if(numNext == 3){
                                                                	board[c][d]-> items = NULL;
                                                                	player-> item -> next -> next -> next -> next = current;
                                                                	return;
                                                                }

                                                                else if(numNext == 4){
                                                                	board[c][d]-> items = NULL;
                                                                	player-> item -> next -> next -> next -> next -> next = current;
                                                                	return;
                                                                }

                                }
                        }
                        previous = current;
                        current = item_next(current);
                        nextItem = item_next(current);
                }
                return;
}

	//same code as take_revolver but for wrench
void take_wrench(struct  Room *board[3][3],struct Avatar *player, char *name){
	int c = 0;
        int d = 0;
                for (int i = 0; i < 3; i++){
                        for(int j= 0; j < 3; j++){
                                if(avatar_in_room(board[i][j]) != NULL){
                                        c = i;
                                        d = j;
                                }
                        }
                }

                struct Item *current = item_in_room(board[c][d]);
                struct Item *previous = NULL;
                int strcmp();

                if(current == NULL){
                        return;
                }
                struct Item* nextItem = item_next(current);

                        while(current != NULL) {
                                if(strcmp(name, item_name(current)) == 0) {
                                        if(nextItem == NULL){
                                                if(previous == NULL){



                                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){

                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next = current;
                                                                return;
 								}

                                                                else if(numNext == 0){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next = current;
                                                                return;
                                                                }
//
                                                                else if(numNext == 3){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                }
                                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(avatar_item(player) == NULL){
                                                                previous -> next = NULL;
                                                                player->item = current;
								return;
                                                                }

                                                                else if(numNext == 0){
                                                                previous -> next = NULL;
                                                                player->item->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                previous -> next = NULL;
                                                                player->item->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                previous -> next = NULL;
                                                                player-> item -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                previous -> next = NULL;
                                                                player-> item -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                previous -> next = NULL;
                                                                player-> item -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }


                                                }


                                else if(previous != NULL){
                                        previous->next = nextItem;
                                        current->next = NULL;

                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                        struct Item* temp = avatar_item(player);
                                        struct Item* next = item_next(avatar_item(player));
                                        int numNext = 0;


                                        while(next != NULL){
                                                temp = next;;
                                                next = item_next(next);
						numNext++;
                                        }
                                                if(avatar_item(player) == NULL){
                                                        player->item = current;
                                                        return;
                                                }

                                                else if(numNext == 0){
                                                player->item->next = current;
                                                return;
                                                }

                                                else if(numNext == 1){
                                                player->item->next->next = current;
                                                return;
                                                }

                                                else if(numNext == 2){
                                                player-> item -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 3){
                                                player-> item -> next -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 4){
                                                player-> item -> next -> next -> next -> next -> next = current;
                                                return;
                                                }

                                }

                                else{
                                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }
								else if(numNext == 0){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                }
                        }
                        previous = current;
                        current = item_next(current);
                        nextItem = item_next(current);
                }
                return;
}

		//same code as take_revolver but for dagger
void take_dagger(struct  Room *board[3][3],struct Avatar *player, char *name){
	int c = 0;
        int d = 0;
                for (int i = 0; i < 3; i++){
                        for(int j= 0; j < 3; j++){
                                if(avatar_in_room(board[i][j]) != NULL){
                                        c = i;
                                        d = j;
                                }
                        }
                }

                struct Item *current = item_in_room(board[c][d]);
                struct Item *previous = NULL;
                int strcmp();

                if(current == NULL){
                        return;
                }
                struct Item* nextItem = item_next(current);

                        while(current != NULL) {
                                if(strcmp(name, item_name(current)) == 0) {
                                        if(nextItem == NULL){
                                                if(previous == NULL){



                                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){

                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next = current;
                                                                return;
 								}

                                                                else if(numNext == 0){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next = current;
                                                                return;
                                                                }
//
                                                                else if(numNext == 3){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                }
                                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(avatar_item(player) == NULL){
                                                                previous -> next = NULL;
                                                                player->item = current;
								return;
                                                                }

                                                                else if(numNext == 0){
                                                                previous -> next = NULL;
                                                                player->item->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                previous -> next = NULL;
                                                                player->item->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                previous -> next = NULL;
                                                                player-> item -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                previous -> next = NULL;
                                                                player-> item -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                previous -> next = NULL;
                                                                player-> item -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }


                                                }


                                else if(previous != NULL){
                                        previous->next = nextItem;
                                        current->next = NULL;

                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                        struct Item* temp = avatar_item(player);
                                        struct Item* next = item_next(avatar_item(player));
                                        int numNext = 0;


                                        while(next != NULL){
                                                temp = next;;
                                                next = item_next(next);
						numNext++;
                                        }
                                                if(avatar_item(player) == NULL){
                                                        player->item = current;
                                                        return;
                                                }

                                                else if(numNext == 0){
                                                player->item->next = current;
                                                return;
                                                }

                                                else if(numNext == 1){
                                                player->item->next->next = current;
                                                return;
                                                }

                                                else if(numNext == 2){
                                                player-> item -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 3){
                                                player-> item -> next -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 4){
                                                player-> item -> next -> next -> next -> next -> next = current;
                                                return;
                                                }

                                }

                                else{
                                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }
								else if(numNext == 0){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                }
                        }
                        previous = current;
                        current = item_next(current);
                        nextItem = item_next(current);
                }
                return;
}

															
//same code as take_revolver but for rope
void take_rope(struct  Room *board[3][3],struct Avatar *player, char *name){
	int c = 0;
        int d = 0;
                for (int i = 0; i < 3; i++){
                        for(int j= 0; j < 3; j++){
                                if(avatar_in_room(board[i][j]) != NULL){
                                        c = i;
                                        d = j;
                                }
                        }
                }

                struct Item *current = item_in_room(board[c][d]);
                struct Item *previous = NULL;
                int strcmp();

                if(current == NULL){
                        return;
                }
                struct Item* nextItem = item_next(current);

                        while(current != NULL) {
                                if(strcmp(name, item_name(current)) == 0) {
                                        if(nextItem == NULL){
                                                if(previous == NULL){



                                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){

                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next = current;
                                                                return;
	 							}	

                                                                else if(numNext == 0){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next = current;
                                                                return;
                                                                }
//
                                                                else if(numNext == 3){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                }
                                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(avatar_item(player) == NULL){
                                                                previous -> next = NULL;
                                                                player->item = current;
								return;
                                                                }

                                                                else if(numNext == 0){
                                                                previous -> next = NULL;
                                                                player->item->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                previous -> next = NULL;
                                                                player->item->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                previous -> next = NULL;
                                                                player-> item -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                previous -> next = NULL;
                                                                player-> item -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                previous -> next = NULL;
                                                                player-> item -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }


                                                }


                                else if(previous != NULL){
                                        previous->next = nextItem;
                                        current->next = NULL;

                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                        struct Item* temp = avatar_item(player);
                                        struct Item* next = item_next(avatar_item(player));
                                        int numNext = 0;


                                        while(next != NULL){
                                                temp = next;;
                                                next = item_next(next);
						numNext++;
                                        }
                                                if(avatar_item(player) == NULL){
                                                        player->item = current;
                                                        return;
                                                }

                                                else if(numNext == 0){
                                                player->item->next = current;
                                                return;
                                                }

                                                else if(numNext == 1){
                                                player->item->next->next = current;
                                                return;
                                                }

                                                else if(numNext == 2){
                                                player-> item -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 3){
                                                player-> item -> next -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 4){
                                                player-> item -> next -> next -> next -> next -> next = current;
                                                return;
                                                }

                                }

                                else{
                                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }
								else if(numNext == 0){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                }
                        }
                        previous = current;
                        current = item_next(current);
                        nextItem = item_next(current);
                }
                return;
}


//same code as take_revolver but for candlestick
void take_candlestick(struct  Room *board[3][3],struct Avatar *player, char *name){
	int c = 0;
        int d = 0;
                for (int i = 0; i < 3; i++){
                        for(int j= 0; j < 3; j++){
                                if(avatar_in_room(board[i][j]) != NULL){
                                        c = i;
                                        d = j;
                                }
                        }
                }

                struct Item *current = item_in_room(board[c][d]);
                struct Item *previous = NULL;
                int strcmp();

                if(current == NULL){
                        return;
                }
                struct Item* nextItem = item_next(current);

                        while(current != NULL) {
                                if(strcmp(name, item_name(current)) == 0) {
                                        if(nextItem == NULL){
                                                if(previous == NULL){



                                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){

                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next = current;
                                                                return;
 								}

                                                                else if(numNext == 0){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next = current;
                                                                return;
                                                                }
//
                                                                else if(numNext == 3){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                }
                                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(avatar_item(player) == NULL){
                                                                previous -> next = NULL;
                                                                player->item = current;
								return;
                                                                }

                                                                else if(numNext == 0){
                                                                previous -> next = NULL;
                                                                player->item->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                previous -> next = NULL;
                                                                player->item->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                previous -> next = NULL;
                                                                player-> item -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                previous -> next = NULL;
                                                                player-> item -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                previous -> next = NULL;
                                                                player-> item -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }


                                                }


                                else if(previous != NULL){
                                        previous->next = nextItem;
                                        current->next = NULL;

                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                        struct Item* temp = avatar_item(player);
                                        struct Item* next = item_next(avatar_item(player));
                                        int numNext = 0;


                                        while(next != NULL){
                                                temp = next;;
                                                next = item_next(next);
						numNext++;
                                        }
                                                if(avatar_item(player) == NULL){
                                                        player->item = current;
                                                        return;
                                                }

                                                else if(numNext == 0){
                                                player->item->next = current;
                                                return;
                                                }

                                                else if(numNext == 1){
                                                player->item->next->next = current;
                                                return;
                                                }

                                                else if(numNext == 2){
                                                player-> item -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 3){
                                                player-> item -> next -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 4){
                                                player-> item -> next -> next -> next -> next -> next = current;
                                                return;
                                                }

                                }

                                else{
                                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }
								else if(numNext == 0){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                }
                        }
                        previous = current;
                        current = item_next(current);
                        nextItem = item_next(current);
                }
                return;
}

//same code as take_revolver but for pillow
void take_pillow(struct  Room *board[3][3],struct Avatar *player, char *name){
	int c = 0;
        int d = 0;
                for (int i = 0; i < 3; i++){
                        for(int j= 0; j < 3; j++){
                                if(avatar_in_room(board[i][j]) != NULL){
                                        c = i;
                                        d = j;
                                }
                        }
                }

                struct Item *current = item_in_room(board[c][d]);
                struct Item *previous = NULL;
                int strcmp();

                if(current == NULL){
                        return;
                }
                struct Item* nextItem = item_next(current);

                        while(current != NULL) {
                                if(strcmp(name, item_name(current)) == 0) {
                                        if(nextItem == NULL){
                                                if(previous == NULL){



                                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){

                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next = current;
                                                                return;
								 }

                                                                else if(numNext == 0){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next = current;
                                                                return;
                                                                }
//
                                                                else if(numNext == 3){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                }
                                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(avatar_item(player) == NULL){
                                                                previous -> next = NULL;
                                                                player->item = current;
								return;
                                                                }

                                                                else if(numNext == 0){
                                                                previous -> next = NULL;
                                                                player->item->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                previous -> next = NULL;
                                                                player->item->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                previous -> next = NULL;
                                                                player-> item -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                previous -> next = NULL;
                                                                player-> item -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                previous -> next = NULL;
                                                                player-> item -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }


                                                }


                                else if(previous != NULL){
                                        previous->next = nextItem;
                                        current->next = NULL;

                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                        struct Item* temp = avatar_item(player);
                                        struct Item* next = item_next(avatar_item(player));
                                        int numNext = 0;


                                        while(next != NULL){
                                                temp = next;;
                                                next = item_next(next);
						numNext++;
                                        }
                                                if(avatar_item(player) == NULL){
                                                        player->item = current;
                                                        return;
                                                }

                                                else if(numNext == 0){
                                                player->item->next = current;
                                                return;
                                                }

                                                else if(numNext == 1){
                                                player->item->next->next = current;
                                                return;
                                                }

                                                else if(numNext == 2){
                                                player-> item -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 3){
                                                player-> item -> next -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 4){
                                                player-> item -> next -> next -> next -> next -> next = current;
                                                return;
                                                }

                                }

                               		 else{
                                                        if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(avatar_item(player) == NULL){
                                                                board[c][d]-> items = NULL;
                                                                player->item = current;
                                                                return;
                                                                }
								else if(numNext == 0){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                board[c][d]-> items = NULL;
                                                                player->item->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                board[c][d]-> items = NULL;
                                                                player-> item -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                }
                        }
                        previous = current;
                        current = item_next(current);
                        nextItem = item_next(current);
                }
                return;
}

																							//finds
																						
//finds where the clued character is by traversing the 2d array until found. Saves that location indexs within in c and d. Then finds players location by traversing the
//2d array until found. brings the character clued "plum" to the room where the avatar is. Before this it the list of characters in the room with the avatar is checked.
//The next one spot on the list of items in this room is then given to the clued character. the avatars inventory, room location, and characters surrounding in the room
//are checked against the answer for each of these. If a match comes up for one of them then it is printed with Match...	
void clue_plum(int isAnswer ,struct Room *board[3][3],struct Avatar *player, struct Answer *ans,struct Character *character2){
	int c = 0;
        int d = 0;
        int e = 0;
        int f = 0;
        int cMatch = 1;
        int rMatch = 1;
        int itMatch = 1;
        struct Character *characters[5] = {NULL,NULL,NULL,NULL,NULL};

        for(int i = 0; i < 3; i++){
                for(int j= 0; j < 3; j++){
                        struct Character* temp = character_in_room(board[i][j]);
                        struct Character* next = next_character(character_in_room(board[i][j]));
											
                        while(temp != NULL){
                                int result1 = strncmp(character_name(temp), "Plum",strlen("Plum"));
                                if(result1 == 0){
                                        e = i;
                                        f = j;
                                }
                                temp = next;
                                next = next_character(next);
                        }
                }
        }


        for(int i = 0; i < 3; i++){
                for(int j= 0; j < 3; j++){
                        if(avatar_in_room(board[i][j]) != NULL){
                                c = i;
                                d = j;
                        }
                }
        }


        struct Character* temp1 = character_in_room(board[c][d]);
        struct Character* next1 = next_character(character_in_room(board[c][d]));
        int numNext = 0;


         while(next1 != NULL){
                temp1 = next1;
                next1 = next_character(next1);
                numNext++;
        }
                printf("numnext: %d\n",numNext);
                if(character_in_room(board[c][d]) == NULL){
                                board[c][d]->character = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                 }

                else if(numNext ==0){
                                board[c][d]->character->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                }
                else if(numNext == 1){
                                board[c][d]->character->next->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                }
                else if(numNext == 2){
                                board[c][d]->character->next->next->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                        }

                else if(numNext == 3){
                                board[c][d]->character->next->next->next->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                }
                struct Character *temp3 = character_in_room(board[c][d]);
                struct Character *next3 = next_character(character_in_room(board[c][d]));
                while(temp3 != NULL){
                        if(strcmp(character_name(temp3),character_name(answer_character(ans))) == 0){
                                cMatch = 0;
                        }
                        temp3 = next3;
                        next3 = next_character(next3);
                }


                if(strcmp(room_name(board[c][d]),room_name(answer_room(ans))) == 0){
                        rMatch = 0;
                }
		struct Item *temp2 = avatar_item(player);
                struct Item *next2 = item_next(avatar_item(player));
                while(temp2 != NULL){
                        if(strcmp(item_name(temp2),item_name(answer_item(ans))) == 0){
                                itMatch = 0;
			}			
                        temp2 = next2;
                        next2 = item_next(next2);
                }

                if(rMatch == 0){
                        printf("Room Match\n");
                }

                if(cMatch == 0){
                        printf("Character Match\n");
                }

                if(itMatch == 0){
                        printf("Item Match\n");
                }

                if(rMatch == 0 && cMatch == 0 && itMatch == 0){
                        isAnswer = 0;
                }

}
			

	
	//same as clue plum
void clue_scarlett(int isAnswer ,struct Room *board[3][3],struct Avatar *player, struct Answer *ans,struct Character *character1){
	int c = 0;
        int d = 0;
        int e = 0;
        int f = 0;
        int cMatch = 1;
        int rMatch = 1;
        int itMatch = 1;
        struct Character *characters[5] = {NULL,NULL,NULL,NULL,NULL};

        for(int i = 0; i < 3; i++){
                for(int j= 0; j < 3; j++){
                        struct Character* temp = character_in_room(board[i][j]);
                        struct Character* next = next_character(character_in_room(board[i][j]));
										
                        while(temp != NULL){
                                int result1 = strncmp(character_name(temp), "Scarlett",strlen("Scarlett"));
                                if(result1 == 0){
                                        e = i;
                                        f = j;
                                }
                                temp = next;
                                next = next_character(next);
                        }
                }
        }


        for(int i = 0; i < 3; i++){
                for(int j= 0; j < 3; j++){
                        if(avatar_in_room(board[i][j]) != NULL){
                                c = i;
                                d = j;
                        }
                }
        }


        struct Character* temp1 = character_in_room(board[c][d]);
        struct Character* next1 = next_character(character_in_room(board[c][d]));
        int numNext = 0;


         while(next1 != NULL){
                temp1 = next1;
                next1 = next_character(next1);
                numNext++;
        }
                printf("numnext: %d\n",numNext);
                if(character_in_room(board[c][d]) == NULL){
                                board[c][d]->character = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                 }

                else if(numNext ==0){
                                board[c][d]->character->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                        }
                else if(numNext == 1){
                                board[c][d]->character->next->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                        }
                else if(numNext == 2){
                                board[c][d]->character->next->next->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                }

                else if(numNext == 3){
                                board[c][d]->character->next->next->next->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                }
                struct Character *temp3 = character_in_room(board[c][d]);
                struct Character *next3 = next_character(character_in_room(board[c][d]));
                while(temp3 != NULL){
                        if(strcmp(character_name(temp3),character_name(answer_character(ans))) == 0){
                                cMatch = 0;
                        }
                        temp3 = next3;
                        next3 = next_character(next3);
                }


                if(strcmp(room_name(board[c][d]),room_name(answer_room(ans))) == 0){
                        rMatch = 0;
                }
		struct Item *temp2 = avatar_item(player);
                struct Item *next2 = item_next(avatar_item(player));
                while(temp2 != NULL){
                        if(strcmp(item_name(temp2),item_name(answer_item(ans))) == 0){
                                itMatch = 0;
			}
                        temp2 = next2;
                        next2 = item_next(next2);
                }

                if(rMatch == 0){
                        printf("Room Match\n");
                }

                if(cMatch == 0){
                        printf("Character Match\n");
                }

                if(itMatch == 0){
                        printf("Item Match\n");
                }

                if(rMatch == 0 && cMatch == 0 && itMatch == 0){
                        isAnswer = 0;
                }

}
//same code as clue plum
void clue_peacock(int isAnswer ,struct Room *board[3][3],struct Avatar *player, struct Answer *ans,struct Character *character3){
	int c = 0;
        int d = 0;
        int e = 0;
        int f = 0;
        int cMatch = 1;
        int rMatch = 1;
        int itMatch = 1;
        struct Character *characters[5] = {NULL,NULL,NULL,NULL,NULL};

        for(int i = 0; i < 3; i++){
                for(int j= 0; j < 3; j++){
                        struct Character* temp = character_in_room(board[i][j]);
                        struct Character* next = next_character(character_in_room(board[i][j]));
											
                        while(temp != NULL){
                                int result1 = strncmp(character_name(temp), "Peacock",strlen("Peacock"));
                                if(result1 == 0){
                                        e = i;
                                        f = j;
                                }
                                temp = next;
                                next = next_character(next);
                        }
                }
        }


        for(int i = 0; i < 3; i++){
                for(int j= 0; j < 3; j++){
                        if(avatar_in_room(board[i][j]) != NULL){
                                c = i;
                                d = j;
                        }
                }
        }


        struct Character* temp1 = character_in_room(board[c][d]);
        struct Character* next1 = next_character(character_in_room(board[c][d]));
        int numNext = 0;


         while(next1 != NULL){
                temp1 = next1;
                next1 = next_character(next1);
                numNext++;
        }
                printf("numnext: %d\n",numNext);
                if(character_in_room(board[c][d]) == NULL){
                                board[c][d]->character = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                 }

                else if(numNext ==0){
                                board[c][d]->character->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                }
                else if(numNext == 1){
                                board[c][d]->character->next->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                }
                else if(numNext == 2){
                                board[c][d]->character->next->next->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                }

                else if(numNext == 3){
                                board[c][d]->character->next->next->next->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                }
                struct Character *temp3 = character_in_room(board[c][d]);
                struct Character *next3 = next_character(character_in_room(board[c][d]));
                while(temp3 != NULL){
                        if(strcmp(character_name(temp3),character_name(answer_character(ans))) == 0){
                                cMatch = 0;
                        }
                        temp3 = next3;
                        next3 = next_character(next3);
                }


                if(strcmp(room_name(board[c][d]),room_name(answer_room(ans))) == 0){
                        rMatch = 0;
                }
		struct Item *temp2 = avatar_item(player);
                struct Item *next2 = item_next(avatar_item(player));
                while(temp2 != NULL){
                        if(strcmp(item_name(temp2),item_name(answer_item(ans))) == 0){
                                itMatch = 0;
			}
                        temp2 = next2;
                        next2 = item_next(next2);
                }

                if(rMatch == 0){
                        printf("Room Match\n");
                }

                if(cMatch == 0){
                        printf("Character Match\n");
                }

                if(itMatch == 0){
                        printf("Item Match\n");
                }

                if(rMatch == 0 && cMatch == 0 && itMatch == 0){
                        isAnswer = 0;
                }

}
			//same code as clue plum										
void clue_green(int isAnswer ,struct Room *board[3][3],struct Avatar *player, struct Answer *ans,struct Character *character4){
	int c = 0;
        int d = 0;
        int e = 0;
        int f = 0;
        int cMatch = 1;
        int rMatch = 1;
        int itMatch = 1;
        struct Character *characters[5] = {NULL,NULL,NULL,NULL,NULL};

        for(int i = 0; i < 3; i++){
                for(int j= 0; j < 3; j++){
                        struct Character* temp = character_in_room(board[i][j]);
                        struct Character* next = next_character(character_in_room(board[i][j]));
												
                        while(temp != NULL){
                                int result1 = strncmp(character_name(temp), "Green",strlen("Green"));
                                if(result1 == 0){
                                        e = i;
                                        f = j;
                                }
                                temp = next;
                                next = next_character(next);
                        }
                }
        }


        for(int i = 0; i < 3; i++){
                for(int j= 0; j < 3; j++){
                        if(avatar_in_room(board[i][j]) != NULL){
                                c = i;
                                d = j;
                        }
                }
        }


        struct Character* temp1 = character_in_room(board[c][d]);
        struct Character* next1 = next_character(character_in_room(board[c][d]));
        int numNext = 0;


         while(next1 != NULL){
                temp1 = next1;
                next1 = next_character(next1);
                numNext++;
        }
                printf("numnext: %d\n",numNext);
                if(character_in_room(board[c][d]) == NULL){
                                board[c][d]->character = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                 }

                else if(numNext ==0){
                                board[c][d]->character->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                }
                else if(numNext == 1){
                                board[c][d]->character->next->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                }
                else if(numNext == 2){
                                board[c][d]->character->next->next->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                }

                else if(numNext == 3){
                                board[c][d]->character->next->next->next->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                }
                struct Character *temp3 = character_in_room(board[c][d]);
                struct Character *next3 = next_character(character_in_room(board[c][d]));
                while(temp3 != NULL){
                        if(strcmp(character_name(temp3),character_name(answer_character(ans))) == 0){
                                cMatch = 0;
                        }
                        temp3 = next3;
                        next3 = next_character(next3);
                }


                if(strcmp(room_name(board[c][d]),room_name(answer_room(ans))) == 0){
                        rMatch = 0;
                }
		struct Item *temp2 = avatar_item(player);
                struct Item *next2 = item_next(avatar_item(player));
                while(temp2 != NULL){
                        if(strcmp(item_name(temp2),item_name(answer_item(ans))) == 0){
                                itMatch = 0;
			}	
                        temp2 = next2;
                        next2 = item_next(next2);
                }

                if(rMatch == 0){
                        printf("Room Match\n");
                }

                if(cMatch == 0){
                        printf("Character Match\n");
                }

                if(itMatch == 0){
                        printf("Item Match\n");
                }

                if(rMatch == 0 && cMatch == 0 && itMatch == 0){
                        isAnswer = 0;
                }

}

//same code as clue plum
void clue_mustard(int isAnswer ,struct Room *board[3][3],struct Avatar *player, struct Answer *ans,struct Character *character5){
	int c = 0;
        int d = 0;
        int e = 0;
        int f = 0;
        int cMatch = 1;
        int rMatch = 1;
        int itMatch = 1;
        struct Character *characters[5] = {NULL,NULL,NULL,NULL,NULL};

        for(int i = 0; i < 3; i++){
                for(int j= 0; j < 3; j++){
                        struct Character* temp = character_in_room(board[i][j]);
                        struct Character* next = next_character(character_in_room(board[i][j]));
										
                        while(temp != NULL){						
                                int result1 = strncmp(character_name(temp), "Mustard",strlen("Mustard"));
                                if(result1 == 0){
                                        e = i;
                                        f = j;
                                }
                                temp = next;
                                next = next_character(next);
                        }
                }
        }


        for(int i = 0; i < 3; i++){
                for(int j= 0; j < 3; j++){
                        if(avatar_in_room(board[i][j]) != NULL){
                                c = i;
                                d = j;
                        }
                }
        }


        struct Character* temp1 = character_in_room(board[c][d]);
        struct Character* next1 = next_character(character_in_room(board[c][d]));
        int numNext = 0;


         while(next1 != NULL){
                temp1 = next1;
                next1 = next_character(next1);
                numNext++;
        }
                printf("numnext: %d\n",numNext);
                if(character_in_room(board[c][d]) == NULL){
                                board[c][d]->character = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                 }

                else if(numNext ==0){
                                board[c][d]->character->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                        }
                else if(numNext == 1){
                                board[c][d]->character->next->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                        }
                else if(numNext == 2){
                                board[c][d]->character->next->next->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                }

                else if(numNext == 3){
                                board[c][d]->character->next->next->next->next = character_in_room(board[e][f]);
                                board[e][f]->character = NULL;
                }
                struct Character *temp3 = character_in_room(board[c][d]);
                struct Character *next3 = next_character(character_in_room(board[c][d]));
                while(temp3 != NULL){
                        if(strcmp(character_name(temp3),character_name(answer_character(ans))) == 0){
                                cMatch = 0;
                        }
                        temp3 = next3;
                        next3 = next_character(next3);
                }


                if(strcmp(room_name(board[c][d]),room_name(answer_room(ans))) == 0){
                        rMatch = 0;
                }
		struct Item *temp2 = avatar_item(player);
                struct Item *next2 = item_next(avatar_item(player));
                while(temp2 != NULL){
                        if(strcmp(item_name(temp2),item_name(answer_item(ans))) == 0){
                                itMatch = 0;
                        }
                        temp2 = next2;
                        next2 = item_next(next2);
                }

                if(rMatch == 0){
                        printf("Room Match\n");
                }

                if(cMatch == 0){
                        printf("Character Match\n");
                }

                if(itMatch == 0){
                        printf("Item Match\n");
                }

                if(rMatch == 0 && cMatch == 0 && itMatch == 0){
                        isAnswer = 0;
                }

}


																	



//finds player on the board by traversing the 2d room array until index with player is located. checks if the inventory of player/avatar  contains the item that was typed in for name(revolver) in
//parameter. If the item isn't in the inventory, terminate. If the item is in the inventory, We take that item and place it into our room where the player/ avatar stands. Before that though we
//check if the room has any items. If it does we find the next open spot on the linked list and place the item there. We then go about removing the item from the
//inventory.
void drop_revolver(struct Room *board[3][3],struct Avatar *player, char *name){
	int c = 0;
        int d = 0;
                for (int i = 0; i < 3; i++){
                        for(int j= 0; j < 3; j++){
                                if(avatar_in_room(board[i][j]) != NULL){
                                        c = i;
                                        d = j;
                                }
                        }
                }
		 printf("%s \n", item_name(avatar_item(player)));
                struct Item *current = avatar_item(player);
                struct Item *previous = NULL;
                int strcmp();
                 printf("%s \n",item_name(current));
		if(current == NULL){
                        return;
                }
                struct Item* nextItem = item_next(avatar_item(player));

                        while(current != NULL) {
                                if(strcmp(name, item_name(current)) == 0) {
                                        if(nextItem == NULL){
                                                if(previous == NULL){



                                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                        struct Item* temp = item_in_room(board[c][d]);
                                                        struct Item* next = item_next(item_in_room(board[c][d]));
                                                        int numNext = 0;


                                                        while(next != NULL){

                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;

								 }		

                                                                else if(numNext == 0){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next = current;
                                                                return;
                                                                }
//
                                                                else if(numNext == 3){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                }
                                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(item_in_room(board[c][d]) == NULL){
                                                                previous -> next = NULL;
                                                                board[c][d]->items = current;
								return;
                                                                }

                                                                else if(numNext == 0){
                                                                previous -> next = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                previous -> next = NULL;
                                                                board[c][d]->items->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                previous -> next = NULL;
                                                                board[c][d]-> items -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                previous -> next = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                previous -> next = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }


                                                }


                                else if(previous != NULL){
                                        previous->next = nextItem;
                                        current->next = NULL;

                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                        struct Item* temp = item_in_room(board[c][d]);
                                        struct Item* next = item_next(item_in_room(board[c][d]));
                                        int numNext = 0;


                                        while(next != NULL){
                                                temp = next;;
                                                next = item_next(next);
						numNext++;
                                        }
                                                if(item_in_room(board[c][d]) == NULL){//
                                                        player->item = current;
                                                        return;
                                                }

                                                else if(numNext == 0){
                                                board[c][d]->items->next = current;
                                                return;
                                                }

                                                else if(numNext == 1){
                                                board[c][d]->items->next->next = current;
                                                return;
                                                }

                                                else if(numNext == 2){
                                                board[c][d]-> items -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 3){
                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 4){
                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                return;
                                                }

                                }

                                else{
                                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                        struct Item* temp = item_in_room(board[c][d]);
                                                        struct Item* next = item_next(item_in_room(board[c][d]));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }
								
								else if(numNext == 0){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                }
                        }
                        previous = current;
                        current = item_next(current);
                        nextItem = item_next(current);
                }
                return;
}


//same as drop_revolver but for rope
void drop_rope(struct Room *board[3][3],struct Avatar *player, char *name){
	int c = 0;
        int d = 0;
                for (int i = 0; i < 3; i++){
                        for(int j= 0; j < 3; j++){
                                if(avatar_in_room(board[i][j]) != NULL){
                                        c = i;
                                        d = j;
                                }
                        }
                }
                 printf("%s \n", item_name(avatar_item(player)));
                struct Item *current = avatar_item(player);
                struct Item *previous = NULL;
                int strcmp();
                 printf("%s \n",item_name(current));
                if(current == NULL){
                        return;
                }
                struct Item* nextItem = item_next(avatar_item(player));

                        while(current != NULL) {
                                if(strcmp(name, item_name(current)) == 0) {
                                        if(nextItem == NULL){
                                                if(previous == NULL){



                                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                        struct Item* temp = item_in_room(board[c][d]);
                                                        struct Item* next = item_next(item_in_room(board[c][d]));
                                                        int numNext = 0;


                                                        while(next != NULL){

                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
 								}	

                                                                else if(numNext == 0){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next = current;
                                                                return;
                                                                }
//
                                                                else if(numNext == 3){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                }
                                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;;
                                                                next = item_next(next);
                                                                numNext++;
							}	
                                                                if(item_in_room(board[c][d]) == NULL){
                                                                previous -> next = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                previous -> next = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                previous -> next = NULL;
                                                                board[c][d]->items->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                previous -> next = NULL;
                                                                board[c][d]-> items -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                previous -> next = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                previous -> next = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }


                                                }


                                else if(previous != NULL){
                                        previous->next = nextItem;
                                        current->next = NULL;

                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                        struct Item* temp = item_in_room(board[c][d]);
                                        struct Item* next = item_next(item_in_room(board[c][d]));
                                        int numNext = 0;
 					while(next != NULL){
                                                temp = next;;
                                                next = item_next(next);
                                                numNext++;
                                        }
                                                if(item_in_room(board[c][d]) == NULL){//
                                                        player->item = current;
                                                        return;
                                                }

                                                else if(numNext == 0){
                                                board[c][d]->items->next = current;
                                                return;
                                                }

                                                else if(numNext == 1){
                                                board[c][d]->items->next->next = current;
                                                return;
                                                }

                                                else if(numNext == 2){
                                                board[c][d]-> items -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 3){
                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 4){
                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                return;
                                                }

                                }

                                else{
                                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                        struct Item* temp = item_in_room(board[c][d]);
                                                        struct Item* next = item_next(item_in_room(board[c][d]));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                               
						 		if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                }
                        }
                        previous = current;
                        current = item_next(current);
                        nextItem = item_next(current);
                }
                return;
}

								//same as drop_revolver				
void drop_candlestick(struct Room *board[3][3],struct Avatar *player, char *name){
	int c = 0;
        int d = 0;
                for (int i = 0; i < 3; i++){
                        for(int j= 0; j < 3; j++){
                                if(avatar_in_room(board[i][j]) != NULL){
                                        c = i;
                                        d = j;
                                }
                        }
                }
                 printf("%s \n", item_name(avatar_item(player)));
                struct Item *current = avatar_item(player);
                struct Item *previous = NULL;
                int strcmp();
                 printf("%s \n",item_name(current));
                if(current == NULL){
                        return;
                }
                struct Item* nextItem = item_next(avatar_item(player));

                        while(current != NULL) {
                                if(strcmp(name, item_name(current)) == 0) {
                                        if(nextItem == NULL){
                                                if(previous == NULL){



                                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                        struct Item* temp = item_in_room(board[c][d]);
                                                        struct Item* next = item_next(item_in_room(board[c][d]));
                                                        int numNext = 0;


                                                        while(next != NULL){

                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
								 }	

                                                                else if(numNext == 0){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next = current;
                                                                return;
                                                                }
//
                                                                else if(numNext == 3){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                }
                                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;;
                                                                next = item_next(next);
                                                                numNext++;
								}
                                                                if(item_in_room(board[c][d]) == NULL){
                                                                previous -> next = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                previous -> next = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                previous -> next = NULL;
                                                                board[c][d]->items->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                previous -> next = NULL;
                                                                board[c][d]-> items -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                previous -> next = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                previous -> next = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }


                                                }


                                else if(previous != NULL){
                                        previous->next = nextItem;
                                        current->next = NULL;

                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                        struct Item* temp = item_in_room(board[c][d]);
                                        struct Item* next = item_next(item_in_room(board[c][d]));
                                        int numNext = 0;
 					while(next != NULL){
                                                temp = next;;
                                                next = item_next(next);
                                                numNext++;
                                        }
                                                if(item_in_room(board[c][d]) == NULL){//
                                                        player->item = current;
                                                        return;
                                                }

                                                else if(numNext == 0){
                                                board[c][d]->items->next = current;
                                                return;
                                                }

                                                else if(numNext == 1){
                                                board[c][d]->items->next->next = current;
                                                return;
                                                }

                                                else if(numNext == 2){
                                                board[c][d]-> items -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 3){
                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 4){
                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                return;
                                                }

                                }

                                else{
                                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                        struct Item* temp = item_in_room(board[c][d]);
                                                        struct Item* next = item_next(item_in_room(board[c][d]));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                               
 								if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                }
                        }
                        previous = current;
                        current = item_next(current);
                        nextItem = item_next(current);
                }
                return;
}
//same as drop revolver but for pillow

void drop_pillow(struct Room *board[3][3],struct Avatar *player, char *name){
int c = 0;
        int d = 0;
                for (int i = 0; i < 3; i++){
                        for(int j= 0; j < 3; j++){
                                if(avatar_in_room(board[i][j]) != NULL){
                                        c = i;
                                        d = j;
                                }
                        }
                }
                 printf("%s \n", item_name(avatar_item(player)));
                struct Item *current = avatar_item(player);
                struct Item *previous = NULL;
                int strcmp();
                 printf("%s \n",item_name(current));
                if(current == NULL){
                        return;
                }
                struct Item* nextItem = item_next(avatar_item(player));

                        while(current != NULL) {
                                if(strcmp(name, item_name(current)) == 0) {
                                        if(nextItem == NULL){
                                                if(previous == NULL){



                                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                        struct Item* temp = item_in_room(board[c][d]);
                                                        struct Item* next = item_next(item_in_room(board[c][d]));
                                                        int numNext = 0;


                                                        while(next != NULL){

                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
								 }

                                                                else if(numNext == 0){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next = current;
                                                                return;
                                                                }
//
                                                                else if(numNext == 3){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                }
                                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;;
                                                                next = item_next(next);
                                                                numNext++;
								}
                                                                if(item_in_room(board[c][d]) == NULL){
                                                                previous -> next = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                previous -> next = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                previous -> next = NULL;
                                                                board[c][d]->items->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                previous -> next = NULL;
                                                                board[c][d]-> items -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                previous -> next = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                previous -> next = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }


                                                }


                                else if(previous != NULL){
                                        previous->next = nextItem;
                                        current->next = NULL;

                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                        struct Item* temp = item_in_room(board[c][d]);
                                        struct Item* next = item_next(item_in_room(board[c][d]));
                                        int numNext = 0;
 					while(next != NULL){
                                                temp = next;;
                                                next = item_next(next);
                                                numNext++;
                                        }
                                                if(item_in_room(board[c][d]) == NULL){//
                                                        player->item = current;
                                                        return;
                                                }

                                                else if(numNext == 0){
                                                board[c][d]->items->next = current;
                                                return;
                                                }

                                                else if(numNext == 1){
                                                board[c][d]->items->next->next = current;
                                                return;
                                                }

                                                else if(numNext == 2){
                                                board[c][d]-> items -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 3){
                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 4){
                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                return;
                                                }

                                }

                                else{
                                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                        struct Item* temp = item_in_room(board[c][d]);
                                                        struct Item* next = item_next(item_in_room(board[c][d]));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                               
 								if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                }
                        }
                        previous = current;
                        current = item_next(current);
                        nextItem = item_next(current);
                }
                return;
}
//same as drop_revolver

void drop_dagger(struct Room *board[3][3],struct Avatar *player, char *name){
int c = 0;
        int d = 0;
                for (int i = 0; i < 3; i++){
                        for(int j= 0; j < 3; j++){
                                if(avatar_in_room(board[i][j]) != NULL){
                                        c = i;
                                        d = j;
                                }
                        }
                }
                 printf("%s \n", item_name(avatar_item(player)));
                struct Item *current = avatar_item(player);
                struct Item *previous = NULL;
                int strcmp();
                 printf("%s \n",item_name(current));
                if(current == NULL){
                        return;
                }
                struct Item* nextItem = item_next(avatar_item(player));

                        while(current != NULL) {
                                if(strcmp(name, item_name(current)) == 0) {
                                        if(nextItem == NULL){
                                                if(previous == NULL){



                                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                        struct Item* temp = item_in_room(board[c][d]);
                                                        struct Item* next = item_next(item_in_room(board[c][d]));
                                                        int numNext = 0;


                                                        while(next != NULL){

                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
 								}

                                                                else if(numNext == 0){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next = current;
                                                                return;
                                                                }
//
                                                                else if(numNext == 3){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                }
                                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;;
                                                                next = item_next(next);
                                                                numNext++;
							}
                                                                if(item_in_room(board[c][d]) == NULL){
                                                                previous -> next = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                previous -> next = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                previous -> next = NULL;
                                                                board[c][d]->items->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                previous -> next = NULL;
                                                                board[c][d]-> items -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                previous -> next = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                previous -> next = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }


                                                }


                                else if(previous != NULL){
                                        previous->next = nextItem;
                                        current->next = NULL;

                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                        struct Item* temp = item_in_room(board[c][d]);
                                        struct Item* next = item_next(item_in_room(board[c][d]));
                                        int numNext = 0;
 					while(next != NULL){
                                                temp = next;;
                                                next = item_next(next);
                                                numNext++;
                                        }
                                                if(item_in_room(board[c][d]) == NULL){//
                                                        player->item = current;
                                                        return;
                                                }

                                                else if(numNext == 0){
                                                board[c][d]->items->next = current;
                                                return;
                                                }

                                                else if(numNext == 1){
                                                board[c][d]->items->next->next = current;
                                                return;
                                                }

                                                else if(numNext == 2){
                                                board[c][d]-> items -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 3){
                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 4){
                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                return;
                                                }

                                }

                                else{
                                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                        struct Item* temp = item_in_room(board[c][d]);
                                                        struct Item* next = item_next(item_in_room(board[c][d]));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                               
 								if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                }
                        }
                        previous = current;
                        current = item_next(current);
                        nextItem = item_next(current);
                }
                return;
}
//same as drop_revolver but for wrench
void drop_wrench(struct Room *board[3][3],struct Avatar *player, char *name){
int c = 0;
        int d = 0;
                for (int i = 0; i < 3; i++){
                        for(int j= 0; j < 3; j++){
                                if(avatar_in_room(board[i][j]) != NULL){
                                        c = i;
                                        d = j;
                                }
                        }
                }
                 printf("%s \n", item_name(avatar_item(player)));
                struct Item *current = avatar_item(player);
                struct Item *previous = NULL;
                int strcmp();
                 printf("%s \n",item_name(current));
                if(current == NULL){
                        return;
                }
                struct Item* nextItem = item_next(avatar_item(player));

                        while(current != NULL) {
                                if(strcmp(name, item_name(current)) == 0) {
                                        if(nextItem == NULL){
                                                if(previous == NULL){



                                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                        struct Item* temp = item_in_room(board[c][d]);
                                                        struct Item* next = item_next(item_in_room(board[c][d]));
                                                        int numNext = 0;


                                                        while(next != NULL){

                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                                                if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
 								}

                                                                else if(numNext == 0){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next = current;
                                                                return;
                                                                }
//
                                                                else if(numNext == 3){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                }
                                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                        struct Item* temp = avatar_item(player);
                                                        struct Item* next = item_next(avatar_item(player));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;;
                                                                next = item_next(next);
                                                                numNext++;
							}		
                                                                if(item_in_room(board[c][d]) == NULL){
                                                                previous -> next = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                previous -> next = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                previous -> next = NULL;
                                                                board[c][d]->items->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                previous -> next = NULL;
                                                                board[c][d]-> items -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                previous -> next = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                previous -> next = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }


                                                }


                                else if(previous != NULL){
                                        previous->next = nextItem;
                                        current->next = NULL;

                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                        struct Item* temp = item_in_room(board[c][d]);
                                        struct Item* next = item_next(item_in_room(board[c][d]));
                                        int numNext = 0;
 					while(next != NULL){
                                                temp = next;;
                                                next = item_next(next);
                                                numNext++;
                                        }
                                                if(item_in_room(board[c][d]) == NULL){//
                                                        player->item = current;
                                                        return;
                                                }

                                                else if(numNext == 0){
                                                board[c][d]->items->next = current;
                                                return;
                                                }

                                                else if(numNext == 1){
                                                board[c][d]->items->next->next = current;
                                                return;
                                                }

                                                else if(numNext == 2){
                                                board[c][d]-> items -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 3){
                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                return;
                                                }

                                                 else if(numNext == 4){
                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                return;
                                                }

                                }

                                else{
                                                        if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                        struct Item* temp = item_in_room(board[c][d]);
                                                        struct Item* next = item_next(item_in_room(board[c][d]));
                                                        int numNext = 0;


                                                        while(next != NULL){
                                                                temp = next;
                                                                next = item_next(next);
                                                                numNext++;
                                                        }
                                               
								 if(item_in_room(board[c][d]) == NULL){
                                                                player-> item = NULL;
                                                                board[c][d]->items = current;
                                                                return;
                                                                }

                                                                else if(numNext == 0){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 1){
                                                                player-> item = NULL;
                                                                board[c][d]->items->next->next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 2){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 3){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                                                else if(numNext == 4){
                                                                player-> item = NULL;
                                                                board[c][d]-> items -> next -> next -> next -> next -> next = current;
                                                                return;
                                                                }

                                }
                        }
                        previous = current;
                        current = item_next(current);
                        nextItem = item_next(current);
                }
                return;
}
       
