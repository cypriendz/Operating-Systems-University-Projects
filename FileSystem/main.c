#include "main.h"
#include "tree.h"
#include "string.h"

//prints the words of each BST for letters a-z using the printTree function for each BST of the map 
void printWords(struct map **map){
	printTree((*map)->a);
	printTree((*map)->b);
	printTree((*map)->c);
	printTree((*map)->d);
	printTree((*map)->e);
	printTree((*map)->f);
	printTree((*map)->g);
	printTree((*map)->h);
	printTree((*map)->i);
	printTree((*map)->j);
	printTree((*map)->k);
	printTree((*map)->l);
	printTree((*map)->m);
	printTree((*map)->n);
	printTree((*map)->o);
	printTree((*map)->p);
	printTree((*map)->q);
	printTree((*map)->r);
	printTree((*map)->s);
	printTree((*map)->t);
	printTree((*map)->u);
	printTree((*map)->v);
	printTree((*map)->w);
	printTree((*map)->x);
	printTree((*map)->y);
	printTree((*map)->z);
	
	freeMap(map); //frees the map at the end
}
//creates an array of files descriptors to be used later for other functions such as parseWord()
int* allFiles(char **names, int num){ //names is the for names of files and num is number of those files
        int* myFiles = calloc(num,sizeof(int)); //creates memory for the array of files descrptors
        if(myFiles == NULL){ //error checking 
                char *error = strerror(errno);
                write(2,error,strlen(error));
        }
	int i = 0;
        while(i < num){  //loops through each file 
                char path[256] = "./reads/"; // a buffer that will hold each .txt file held in the directory
// "reads" that is within  my proj3 directory. 
                strcat(path,names[i]); // adds the .txt name to the buffer path for reading

                myFiles[i] = open(path,O_RDONLY); //adds the file descriptor of a given opened file to the array
// of file descriptors that will end up being returned
                if(myFiles[i] == -1){ //error checking for open
                        char *error = strerror(errno);
                        write(2,error,strlen(error));

                }
		i++; //increments i so that we read the next file 
        }
        return myFiles; //once all files are read, we have an array of all the file descriptors. This array to
//returned for later use
}
//converts all other inputs(envir,command arguments, piping) into file descriptors that will be held in an
//array that we will return and use later. 
int* allInputs(int argc, char* argv[], int* num){

	int* files; //the array that will hold our file descriptors 
	char *wf = getenv("WORD_FREAK"); //sets ups our WORD_FREAK envir variable
	if(wf != NULL){ //error checking
		files = allFiles(&wf,(*num = 1)); //uses allFiles() function to convert envir variable to a file descriptor 
		if(files == NULL){ //error checking
		 	char *error = strerror(errno);
                        write(2,error,strlen(error));
		}
	}
	//if we have a piped input then argc will == 1
	else if (argc == 1){ 
		files = malloc(sizeof(int)); //creates memmory for our file array
		if(files == NULL){ //error checking
			char *error = strerror(errno);
               		write(2,error,strlen(error));
		}
		files[0] = STDIN_FILENO; //assigns first index of our array of file descriptors to what was
//piped in/ standard input 
		*num = 1; //the number of files we have is now one
	}
	
	else if (argc > 1) { //if input is arguments coming from command prompt
		files = allFiles(argv + 1, argc -1); //uses the allFiles() function to get the file descriptors
//that come from the files that are inputed such as ... .txt
		if(files == NULL){//error checking
			char *error = strerror(errno);
                	write(2,error,strlen(error));
		}
		*num = argc-1; //number of files we have, we dont include program so -1
	}
	return files; //finally return the array of file descriptors mentioned above
}
//main function for running the program
int main(int argc, char *argv[]){
	int *fd; //the array of file descriptors
	int num; //num of files to read
	
	fd = allInputs(argc,argv, &num); //get all the file descriptors from whatever was inputed using the
//allInputs function, assigns array of these file descriptors to the fd array
	struct map *map = wordParse(num, fd);
	printWords(&map); //prints all the words of each BST and the frequencies
	
	return 0; //success
}
 
