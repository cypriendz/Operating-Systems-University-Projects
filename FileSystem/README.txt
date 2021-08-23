YOUTUBE LINK: https://www.youtube.com/watch?v=SkOoJlYwRf0&feature=youtu.be&ab_channel=cypriendzialo

program consists of main.c main.h string.h string.c tree.c tree.h and Makefile. The string files are for
parsing, the tree files are for the BST and Hashmap structures as well as their respective functions, and main
has two functions that and a main function that put the program together. Makefile is exactly a make file. .h
files contain prototypes and .c files fulfil these prototype functions.

In this readme file I will explain how my main.c runs since that is what controls the program. Although my main
is rather short, I will attempt to give a valid explenation of how it controls the program. Before I start I
would like you to know that there is a bug somewhere in my program that's causing a segfault dump that I did not
have time to locate. Although this is the case I can still take inputs in all the possible ways required, but
my program will segfault before any output. This is shown in the youtube video for reference. Before I explain
my main I will explain the BST I have. I created a BST structure in tree.h with a structure called "node".
"node" has variables, "right" which is a node pointer for the right branch of the node, "left" which is a node
pointer for left branch of node, "word" which is a string that is the word within the node, and "times" which is
an int that represents the frequency of the word for a node. All the BST functions such as printing, searching,
etc are within tree.c, and their prototypes within tree.h. Now for the hashtable/ hash function, I created a
struct "map". This struct has 26 BST within it, each representing one letter of the alphabet. For the hash
function I have findBST(...) that is within tree.c and tree.h as a prototype. How this function works exactly is
explained in tree.c, but in short it compares the first letter of a word to a letter in the alphabet, and then
returns the corresponding BST for the letter that matches with the first letter of the word. 

Now for main.c, I will cover the actual main function. So first I create two variables, "int fd*" and "int num".
"int fd*" is an array that will hold all the file descriptors of whatever files or inputs where given to the
program. "int num" is the number of files that was given. "fd" is then assigned a value that come from the
function "allInputs(...). I have explained this function in the comments of main.c, but in short this function
gets all the file descriptors from whatever was inputed into the program, and returns an array of all these file
descritors collected. I then decare and intialize a hash map know as map with the wordParse(...) function. This
function has also been explained in the comments of string.c, but in short this function parses all the words
within a file or file(s), and then inserts all these words into the correct BST that is within a map. This
updated map is then returned. Lastly I use the printWords(...) function to print out the words and frequencies of each of the 26
BSTs that the map has. 



