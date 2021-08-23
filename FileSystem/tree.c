#include "tree.h"
//this function is used to create a new map.
struct map *newMap(){
	struct map *map = malloc (sizeof (struct map)); //allocates space from a map struct
	if(map == NULL){ //error checking
		char *error = strerror(errno);
                write(2,error,strlen(error));
                exit(1);
        }
		map->a = NULL; //sets the root nodes to NULL for each BST
		map->b = NULL;
		map->c = NULL;
		map->d = NULL;
		map->e = NULL;
		map->f = NULL;
		map->g = NULL;
		map->h = NULL;
		map->i = NULL;
		map->j = NULL;
		map->k = NULL;
		map->l = NULL;
		map->m = NULL;
		map->n = NULL;
		map->o = NULL;
		map->p = NULL;
		map->q = NULL;
		map->r = NULL;
		map->s = NULL;
		map->t = NULL;
		map->u = NULL;
		map->v = NULL;
		map->w = NULL;
		map->x = NULL;
		map->y = NULL;
		map->z = NULL;
		return map; // returns the newly created map
}

void printNode(struct node* node){ //this function prints a node of a BST
	char word[50]; //char for string holding a max size of 50 bytes
	sprintf(word,"%18s:%6i\n",node->word,node->times); // uses sprintf to hold the word of a node and its freq/times in the word array
	char *outputtxt = "output.txt"; //creates output.txt for open
	int fdw = open(outputtxt,O_RDWR| O_CREAT|O_TRUNC,0664); //opens output.txt 
        if(fdw == -1) { //error checking
                char *error = strerror(errno); 
                write(2,error,strlen(error));
        }
	else{ 
		int theWrite = write(fdw,word,strlen(word)); //writes word of node into the output.txt
		if(theWrite == -1){ //error checking
			 char *error = strerror(errno);
  		         write(2,error,strlen(error));
		}
	}
}
//recursively prints contents of a BST using the printNode for the printing of the individual node
void printTree(struct node* tree){
	if(tree != NULL){	
		printTree(tree->left);
		printNode(tree);	
		printTree(tree->right);
	}		
	
}
//recursively frees the word within the node as well as the the node
void freeWord(struct node **node){
	if(node != NULL){
		freeWord(&(*node)->right);
		free((*node)->word); //freeing of word
		freeWord(&(*node)->left);
		free(*node); //freeing of node
		*node = NULL;
	}
}
//frees the BSTs for each letter of the alphabet using the freeWord function and frees the map itself at the end
void freeMap(struct map **map){ 
	freeWord(&((*map)->a)); //freeing of BSTs
	freeWord(&((*map)->b));
	freeWord(&((*map)->c));
	freeWord(&((*map)->d));
	freeWord(&((*map)->e));
	freeWord(&((*map)->f));
	freeWord(&((*map)->g));
	freeWord(&((*map)->h));
	freeWord(&((*map)->i));
	freeWord(&((*map)->j));
	freeWord(&((*map)->k));
	freeWord(&((*map)->l));
	freeWord(&((*map)->m));
	freeWord(&((*map)->n));
	freeWord(&((*map)->o));
	freeWord(&((*map)->p));
	freeWord(&((*map)->q));
	freeWord(&((*map)->r));
	freeWord(&((*map)->s));
	freeWord(&((*map)->t));
	freeWord(&((*map)->u));
	freeWord(&((*map)->v));
	freeWord(&((*map)->w));
	freeWord(&((*map)->x));
	freeWord(&((*map)->y));
	freeWord(&((*map)->z));
	free(*map); //freeing of map
	*map = NULL;
	
}

		
//my hash function that compares the first letter of a word to all the possible letters in the alphabet, if first letter matches one of the letters, it returns that BST for the corresponding letter
struct node* findBST(char* word, struct map * map){
	if(word[0] == 'a'){
		return map->a;	
	}	 
	else if(word[0] == 'b'){
                return map->b;
        }
	else if(word[0] == 'c'){
                return map->c;
        }
	else if(word[0] == 'd'){
                return map->d;
        }
 	else if(word[0] == 'e'){
                return map->e;
        }
 	else if(word[0] == 'f'){
                return map->f;
        }
 	else if(word[0] == 'g'){
                return map->g;
        }
 	else if(word[0] == 'h'){
                return map->h;
        }
 	else if(word[0] == 'i'){
                return map->i;
        }
 	else if(word[0] == 'j'){
                return map->j;
        }
 	else if(word[0] == 'k'){
                return map->k;
        }
 	else if(word[0] == 'l'){
                return map->l;
        }
 	else if(word[0] == 'm'){
                return map->m;
        }
 	else if(word[0] == 'n'){
                return map->n;
        }
 	else if(word[0] == 'o'){
                return map->o;
        }
 	else if(word[0] == 'p'){
                return map->p;
        }
 	else if(word[0] == 'q'){
                return map->q;
        }
 	else if(word[0] == 'r'){
                return map->r;
        }
 	else if(word[0] == 's'){
                return map->s;
        }
 	else if(word[0] == 't'){
                return map->t;
        }
 	else if(word[0] == 'u'){
                return map->u;
        }
 	else if(word[0] == 'v'){
                return map->v;
        }
 	else if(word[0] == 'w'){
                return map->w;
        }
 	else if(word[0] == 'x'){
                return map->x;
        }
 	else if(word[0] == 'y'){
                return map->y;
        }
 	else if(word[0] == 'z'){
                return map->z;
        }
		
}
//this function places a node into a BST using recursion
struct node* placeWord(struct node * node, char *word){
	struct node** holder = &node; //a holder the current node
	if(node == NULL){ //case if there is no root node
		struct node *new = (struct node*) malloc(sizeof(struct node)); //allocates memory for new node
		new -> word = word; //assigns word 
		new -> left = NULL; 
		new -> right = NULL;
		new -> times = 1; 
		return new; //returns the new node
	}
	if(strcmp(((*holder)->word),word) == 0){ //if the word in the argument is found within the given BST
		(*holder)-> times++; //increments the freq/times 
		return node;  //returns the node found that has the word given in argument
	}	
	else if(strcmp(((*holder)->word),word) < 0){ //if word in argument is larger than current node word, go
//to the right branch of the current node
		(*holder)->right = placeWord((*holder)->right,word);
		return node;
	}
	else{
		(*holder)->left = placeWord((*holder)->left,word); //else go to left node of current node
		return node;
	}  
}	
//creates a node that will be placed into one of the BSTs found by findBST
struct node* insert(struct map **map, char* word){
	struct node *tree = (struct node*) malloc(sizeof(struct node));  //the node created
		tree = findBST(word,*map); //finds which BST to use with thisi hash function
		placeWord(tree,word); //the node into the BST found
}






