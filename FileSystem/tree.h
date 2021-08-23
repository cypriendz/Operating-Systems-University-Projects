#ifndef tree_H
#define tree_H
//all the includes
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//structure created for a node of a BST/ a structure for the root of a tree
struct node{
	struct node *left;
	struct node *right;
	char* word;
	int times;
};
//structure for a hash map that contains a BST for each letter of the alphabet
struct map{
	struct node *a;
	struct node *b;
	struct node *c;
	struct node *d;
	struct node *e;
	struct node *f;
	struct node *g;
	struct node *h;
	struct node *i;
	struct node *j;
	struct node *k;
	struct node *l;
	struct node *m;
	struct node *n;
	struct node *o;
	struct node *p;
	struct node *q;
	struct node *r;
	struct node *s;
	struct node *t;
	struct node *u;
	struct node *v;
	struct node *w;
	struct node *x;
	struct node *y;
	struct node *z;
}
;
//prototypes which will be explained in source file
void printNode(struct node* node);

void printTree(struct node *tree);

struct node* placeWord(struct node *node, char *word);
					
void freeMap(struct map **map);

void freeWord(struct node **node);

struct map *newMap();

struct node *findBST(char *word, struct map *map);

struct node* insert(struct map **map, char* word);
#endif
