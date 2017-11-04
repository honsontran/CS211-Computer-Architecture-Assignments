#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "third.h"

//declare methods
hashTable * createTable();
int hash(hashTable * table, int key, int size);
void insert(hashTable * table, int key, int size);
int search(hashTable * table, int key, int size);

int main(int argc, char* argv[]) {

	char dete;			//insert or search
	int data;			//what to search or insert

	//create table
	hashTable * table = createTable();
  	
  	//input file name
	char * file = argv[1];
    FILE *fp = fopen(file, "r");	// open the file to "r" --> read
	
	int amt;
	while ( !feof(fp) ) {
		amt = fscanf(fp, "%c %d", &dete, &data);

		if (amt == 2) {
			//printf("\n%c %d\n", dete, data);
			if (dete == 'i') {	//insert
				insert(table, data, 10000);
			}

			else if (dete == 's') {	// search
				int found = search(table, data, 10000);

				if(found) printf("present\n");

				else printf("absent\n");
			}
		}
	}
	fclose(fp);
	return 0;
}

/*
 * Our hash function (key % elements)
 * This creates the key, node, and inserts.
 */
int hash(hashTable * table, int key, int size) {
	
	//Find where our hash index is
	int hashIndex = key % size;
	return hashIndex;
}

/*
 * Goes to the index, and inserts if none is present.
 */
void insert(hashTable * table, int key, int size) {

	//Find index
	int hashIndex = hash(table, key, size);

	//Keep track of current and future list.
	node * currList;
	node * newNode = malloc( sizeof(node) );

	//Check and see if the object is already present
	int searchResult = search(table, key, size);

	if ( searchResult == 0 ) { //if absent
		
		if (table->tableList[hashIndex] == NULL) {

			//place int into node
			newNode->data = key;
			newNode->next = NULL;

			//put node into hashtable
			table->tableList[hashIndex] = newNode;

			printf("inserted\n");
		}

		else {	//if there is already a list there
			
			//add to front
			currList = table->tableList[hashIndex];
			newNode->data = key;
			newNode->next = currList;
			table->tableList[hashIndex] = newNode;

		}
	}

	else {	//if present
		printf("duplicate\n");
	}
}

/*
 * Search returns 1 if present, 0 if absent.
 */
int search(hashTable * table, int key, int size) {

	//Find hashIndex
	int hashIndex = hash(table, key, size);

	node * list = table->tableList[hashIndex];

	//traverse and search through the linked list
	for (; list != NULL; list = list->next) {

		if (list->data == key) {
			return 1;
		}
	}

	return 0;
}

/* 
 * Creates the hash table 
 */
hashTable * createTable() {
	
	hashTable * table = malloc( sizeof(hashTable) );

	//Initialize all elements in hash table
	int i = 0;
	for(; i < 10000; i++) {
		table->tableList[i] = NULL;
	}

	return table;
}