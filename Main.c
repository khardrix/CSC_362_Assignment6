#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 8


/* ----------------------------------------------- FUNCTION PROTOTYPES ---------------------------------------------- */
struct node* orderedInsert(struct node*, double, char*);     // insert receives front pointer and new datum to insert in proper location
void printBin(int, double, struct node*);
void traverse(struct bin[]);
void destroy(struct node*);
/* ------------------------------------------- END OF FUNCTION PROTOTYPES ------------------------------------------- */


struct bin {
	double capacity;
	struct node* list; // struct node* front;
};

struct node {
	char item[40];
	double weight;
	struct node* next;
};

void main() {

	/* ------------------------------------------ VARIABLE DECLARATIONS ------------------------------------------- */
	// an array of bin structs
	struct bin bins[20];

	char* names[SIZE] = { "Vase","Bowling_ball","Book","Umbrella", "Gold_medal", "Speaker_1", "Walkman", "Speaker_2" };
	double weights[] = { .5, .9, .3, .4, .7, .4, .2, .4 };

	/*
	char* names[SIZE] = { "Small_dog", "Moose_skull", "Squirrel", "Mouse", "Goldfish", "Snake", "Human_finger", "Pig_head",
		"Eagle_feather", "Shark_tooth", "Camel_hump", "Crocodile", "Elephant_tusk", "Cat", "Horse_manure", "Monkey_hand",
		"Octopus_eye", "Sheep_coat", "Bat", "Chicken_wing" };
	double weights[] = { .63, .25, .41, .15, .06, .52, .09, .39, .02, .11, .24, .94, .63, .28, .04, .21, .05, .33, .42, .12 };

	char* names[SIZE] = { "Computer Organization", "Internet_Infrastructure", "The_History_Of_The_Universe", 				"Linux_with_Operating_Systems_Concepts", "C_Programming", "Statistics", "English_For_Dummies", "American_History_2000-",
		"Computer_Architecture", "Hitchhiker's_Guide", "English-Minbari_Dictionary", "Zen_and_the_Art_of_Programming",
		"The_Joy_of_Cooking", "Heart_of_Darkness", "Cincinnati_Yellow_Pages", "Artificial_Intelligence",
		"Business_Programming:__Why?", "The_History_of_Ohio_State_Buckeyes" };
	double weights[] = { .75, .62, .27, .78, .21, .41, .55, .20, .90, .23, .42, .33, .56, .18, .98, .32, .12, .82 };
	*/


	int i = 0, j = 0;

	int isPlaced = 0;
	/* -------------------------------------- END OF VARIABLE DECLARATIONS ---------------------------------------- */


	for (i = 0; i < 20; i++) {
		bins[i].capacity = 1.0;
		bins[i].list = NULL;
	}

	traverse(bins);

	// j++;

	for (i = 0; i < SIZE; i++) {
		isPlaced = 0;
		j = 0;

		while (isPlaced == 0) {
			if (weights[i] < bins[j].capacity + .001) {
				bins[j].capacity -= weights[i];
				bins[i].list = orderedInsert(bins[j].list, weights[i], names[i]);
				isPlaced = 1;
			}
			else {
				j++;
			}
		}
	}
}


// insert new value x into a node at the end of the list, this is far less efficient than the previous
// unordered list where we inserted at the beginning
struct node* orderedInsert(struct node* f, double itemWeight, char *itemName){
	
	struct node* temp, * current, * previous;  // temp will point to new node, current and previous used to traverse list
	temp = (struct node*)malloc(sizeof(struct node));      // allocate a node from heap
	temp->weight = itemWeight;                 // assign the new node its value
	temp->item = itemName;
	temp->next = NULL;              // and it will be the current last node, so make next NULL
	if (f == NULL) return temp;     // special case of empty list, no list to traverse
	else if (strcmp(f->item, itemName) > 0)           // special case 2:  if new node should be inserted at front
	{
		temp->next = f;           // let new node point at rest of list
		return temp;            // and return new node's pointer as new front of the list
	}
	else                         // have to traverse list until we have a pointer at the last node
	{
		current = f;              // initialize our two pointers to work down the list, current always
		previous = NULL;          // pointing at current node while previous points at its predecessor
		while (current != NULL && strcmp(f->item, itemName) < 0){  // traverse list until we either reach the end of find the right location
			previous = current;            // previous always points at prior node
			current = current->next;       // current points at node we are inspecting
		}
		previous->next = temp;      // attach new node to list by having previous point at it
		temp->next = current;       // and reattach rest of list to temp's next field
		return f;               // return the front pointer so that we can reattach list in main
	}
}


void traverse(struct bin printBins[]) {
	int i = 0;
	// int binArrayLength = sizeof(*printBins) / sizeof(struct bin);
	int j = 0;

	for (; i < 20; i++) {
		if (printBins[i].capacity < 1.0) {
			j++;
		}
	}

	for (i = 0; i < j; i++) {
		printBin(i, printBins[i].capacity, printBins[i].list);
		printf("\n");
	}
}


void printBin(int binNumber, double remainingCapacity, struct node* f) {
	printf("Bin %d (%.2f remaining): ", binNumber, remainingCapacity);

	if (f != NULL) {
		struct node* current = f;
		struct node* previous = NULL;
		previous->next = current;
		
		while (previous->next != NULL) {
			printf("%s (%.2f), ", current->item, current->weight);
			previous = current;
			current = current->next;
		}
	}
}

void destroy(struct node* f)                // deallocate all heap memory
{
	struct node* temp = f;                   // need a temp pointer as one pointer will point to next
	while (f != NULL)                         // while we still have list nodes to deallocate
	{
		f = f->next;                        // f now points to the next node in the list
		free(temp);                       // so we can deallocate the current node
		temp = f;
	}
}

