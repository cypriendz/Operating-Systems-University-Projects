#include "tree.h"
#include "string.h"
//this fuction parses each word of a file and then adds the word to output.txt using the insert function that is
//located within tree.c. The file being read is held within the argument fd* and int files argument is the
//number of files to be read 
struct map* wordParse(int files, int *fd){
	char buf[17000] = "\0"; //buffer that holds the btyes for reading
	struct map * map = newMap(); //map used for insertation 
	char word [50] = ""; //a buffer that holds a parsed word of a file with a max size of 50 bytes
	int reads = 0; //number of bytes being placed into buf[]
	int tot = 0; //total number of btyes read from a file
	int numBuffs = 0; //the number of bufs[] that have been used 
	int last = 0; //is the last btye in a file

	for(int i = 0; i < files; numBuffs++){ //loops through each of the files given by fd and int files
		reads = read(fd[i],buf,17000); //reads the file that is held in fd[i]
		if(reads == -1){ //error checking
			char *error = strerror(errno);
                        write(2,error,strlen(error));	
		}
		if(reads < 17000){ //if program reads less btyes than max bytes of 17k, then we are done with
//this read and we closed the file 
			int fdout = close(fd[i]);
			
			if(fdout == -1){ //error checking
				char *error = strerror(errno);
				write(2,error,strlen(error));
			}
			i++; //increment i so that next file in fd can be read 
		}

		int charWord = 0; //the current character of a word
		for(int j = 0; j < reads; j++){ //time to loop through each character that was read above and
//check if its a letter and not some other character
			if(isalpha(buf[j])){ //checks if character is a letter
			word[charWord + 1] = tolower(buf[j]); //the letter is made lower case 
			}
			else if(buf[j] == '-' || buf[j] == ' ' || buf[j] == '\r' || buf[j]
== '\f' || buf[j] == '\v' || buf[j] == '\t' || buf[j] == '\n'){  //if not a letter is it one of these characters
				if(strcmp(word, "") != 0){  //if the no letter character also is not a space 
					word[charWord] = '\0'; // we create a new word by making making non
//letter character the end of the string/word

					charWord = 0; //we are now on a new word so the character that we are at of
//the new word is index 0/ first letter
				
					insert(&map,word);	//we insert the old word into a BST using insert
					word[0] = '\0'; //word is over and we are now going to a new word/string 
				}
			}

		}
		if(last < i){ //if we are at the end of our file (0 < some file that was read) 
			word[charWord] = '\0'; //were onto a new word/string
			insert(&map,word); //we insert the last word
		}
	}
	free(fd); // at the end we free array that was holding all the file directories 
	return map; //return the newly edited hashmap
}
