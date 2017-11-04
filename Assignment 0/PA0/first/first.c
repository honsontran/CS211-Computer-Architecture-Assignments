#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
 
//Create struct for linked list.
typedef struct _node {
    int data;                   //holds integers
    struct _node * next;        // manages pointers
}node;                          // call this struct, node.
 
//declare methods
void toString(node* list);
int findData(char * line);
node * findIndex(node * list, int targetData, char mode);
node * insertNode(node * list, int data);
node* deleteNode(node * list, int data);
bool isEmpty(char file[]);
int counter(node * currNode);
 
int main(int argc, char* argv[]) {
 
    node * root = malloc( sizeof(node) );   //create the root for beginning of linked list.
    root->next = NULL;

 	//input file name
 	char * file = argv[1];
 	//strcpy(file, argv[1]);
 	
    FILE *fp = fopen(file, "r");    // open the file to "r" --> read
 
    //Special case 1: if file does not exist
    if (fp == 0) {
        printf("error");
        return 0;
    }
 
    //Special case 2: if the file is empty
    if ( isEmpty(file) ) {
        printf("0");
        return 0;
    }
 
    /*
     * Main Algorithm:
     */
 
    char dete = 0;          //determines insert/delete
    int num = 0;            //holds int data
    int amt = 0;            //amt of varibles held from fscanf

    //Start at the very first insert. Skip all the other deletes.
    while ( dete != 'i' && !feof(fp) ) {
 
        amt = fscanf(fp,"%c %d", &dete, &num);
        if (amt == 2) {
            if (dete == 'i') {
                root->data = num;
            }
        }
		
		//checks if the rest of the file is all deletes
	    if (feof(fp)) {
			printf("0\n");
			return 0;
        }
    }
 
    //Go through the txt file and determine whether to insert or delete nodes.
    while( !feof(fp) ) {
         
        //scan each line and save ins/del and the number.
        amt = fscanf(fp,"%c %d", &dete, &num);
         
        //Check if the there are 2 variables
        if(amt == 2) {
  
            //Compare the line and see if we insert or delete.               
                if (dete == 'd') {
                    //printf("Now deleting: %d\n", num);
                    root = deleteNode(root, num);
                    //toString(root);
                    //printf("\n---------------------\n");
                }
                  
                else if (dete == 'i') {
                    //printf("Now inserting: %d\n", num); 
                    root = insertNode(root, num);
                    //printf("Ending iteration: \n");
                    //toString(root);
                    //printf("\n---------------------\n");
                }
        }   
    }
 
    fclose(fp);     //close the reader
	
	//create the counter

    toString(root);         // print the linked list
 
    return 0;
}
 
/*
 * Finds the node to delete and reroutes the linked list.
 */
node* deleteNode(node * list, int data) {
     
    //node * temp = malloc( sizeof(node) );   // temp for swap
 
    //find position
    node * prevIndex = malloc( sizeof(node) );
    prevIndex = findIndex(list, data, 'd');

    //printf("prevIndex: %d | list->data: %d\n", prevIndex->data, list->data);
 
    //reroute the list

    if (data == list->data && list->next == NULL) {
    	//printf("hitting only one node condition");
    	node * root = malloc( sizeof(node) );
    	root->next = NULL;
    	return root;
    }

    //Case 1: If we reach the end and it's null.
    if(prevIndex->next == NULL) {
        prevIndex->next = NULL;
        return list;
    }
 
    //Case 2: If we delete the front node
    if(data == list->data) {
        //printf(GOCKLEreturning: %d\n", list->next->data);
       
        if (counter(list) > 2) {
        	list->next = list->next->next;
        	return list;
        }

        else
        	return list->next;      
    }

    if(prevIndex->data == list->data) {
        //printf("hit new condition\n");
        //printf("returning: %d\n", list->next->data);    	
    }
 
    //Case 3: Average case (skip over)
    prevIndex->next = prevIndex->next->next;
 
    return list;
}
 
/* NOTE: CREATE FIRST NODE OUTSIDE OF METHOD FIRST.
 * Creates the node and calls the find index method to find where
 * to insert the node.
 */
node * insertNode(node * list, int data) {
 
    node * temp = malloc( sizeof(node) );           //temp node for inserting.
    node * prevIndex = malloc( sizeof(node) );      //index for algorithm
 
    //printf("Our insert list from insertNode(): \n");
    //toString(list);
    //printf("\n");
    //printf("prevIndex: %d | list.data: %d | data: %d\n", prevIndex->data, list->data, data);
 
    prevIndex = findIndex(list, data, 'i'); //find index to insert.
 
    if (prevIndex->next != NULL) {
 
        //create the new node and prepare data
        node * newNode = (node *) malloc( sizeof(node) );
        newNode -> data = data;
        newNode->next = NULL;
 
        //swap
        temp = newNode;
        newNode->next = prevIndex->next;
        prevIndex->next = temp;
 
    } // end else for average case
 
    else {  //if pointer is null, insert to front, end, or LL is empty. 
		
        /* 
         * Case 1: If we insert to front, make a new node
         * and modify the list here.
         */
        if(data < list->data) {
            node * newNode = (node *) malloc( sizeof(node) );
            newNode->data = data;
            newNode->next = list;
 
            return newNode;
        }

        /* 
         * Case 2: insert to end, create the node here since
         * we will be returning the pointer to the end of the
         * list.
         */
        else if(data > prevIndex->data) {
 
            node * back = malloc( sizeof(node) );
            back->data = data;
            back->next = NULL;
 
            prevIndex->next = back;
 
            return list;
        }

        //Special Case: if this is the first node
	    else if(list->next == NULL) {	        
	        list->data = data;
	        return list;
	    } 

    } //end else for special cases

    return list;
}
 
/* 
 * returns location before the target of where to
 * insert/delete nodes (returns ideal sorted location).
 */
node * findIndex(node * list, int targetData, char mode) {
 
    //create pointer to go through the list.
    node * targetIndex = malloc( sizeof(node) );
    targetIndex = list;
 
    //create node to keep track of prev
    node * prev = malloc( sizeof(node) );
 
    //create a null node return
    node * nullNode = malloc( sizeof(node) );
    nullNode->next = NULL;
 
    //Mode: Insert. Find if number prev < x < next
    if (mode == 'i') {
 
        //Special Case: if this is the first node.
        if(list -> next == NULL) {
            return targetIndex;
        }
 
        //Special case: if node is inserted in front, create it and return
        else if (targetData < list->data) {
            node * front = malloc( sizeof(node) );
            front->data = targetData;
            front->next = NULL;
            return front;
        }
 
        while (targetIndex->next != NULL) {  //traverse
 
            prev = targetIndex;     //keep track of previous
 
            //Create a node to keep track of next target
            node * nextTarget = malloc( sizeof(node) );
            nextTarget = targetIndex->next;
 
            //Objective: prev < targetData < next
            int prevInt = prev->data;
            //printf("prevPtr: %d | prevInt: %d", prev->data, prevInt);
            int nextInt = nextTarget->data;
 
            //Debug: Check Iterations
            //printf("\nPrev: %d | Curr: %d | Next: %d", prev->data, targetIndex->data, nextInt);
            //printf("\n---------------------------------------------");
 
            if (prevInt < targetData && targetData < nextInt) {               
                return prev;
            }
 
            targetIndex = targetIndex->next;     //next node
 
        }//end traversal
         
        //Special Case: we insert at the end of the list.
        if (targetIndex->next == NULL) {
            return targetIndex;
        }
    } // end mode insert if
 
    //Mode: Delete. Find node to delete and return its address.
    else if (mode == 'd') {
 
        while (targetIndex != NULL) {   //traverse
 
            //Since the list is in order, if the previous node is greater,
            //then we have already passed our target. Not found.
            int currInt = targetIndex->data;
             
            //Debug: Check Iterations
            //printf("\nCurr: %d", currInt);
            //printf("\n---------------------------------------------");    
 
            if (currInt > targetData) {  
                return nullNode;
            }
 
            else if (currInt == targetData) {   //target found
                 
                //If we need to delete front node.
                if (list->data == currInt) {
                    //printf("hitting here\n");
                    return targetIndex;
                }
 
                return prev;
            }
 
            prev = targetIndex;     //keep track of prev
 
            targetIndex = targetIndex -> next;   //next node
        }
 
        //if we still can't find
        return nullNode;    
    } //end else if mode delete

    return nullNode;
}
 
 
/* 
 * looks in the C-string to find the data.
 */
int findData(char * line) {
 
    char dete;
    int num;
 
    //printf("our line is: %s\n", line);
 
    //Extract information
    sscanf(line, "%c %d", &dete, &num);
 
    //printf("Mode: %c | Num: %d", dete, num);
 
    return num;     //only return num
}
 
/* 
 * prints out the linked list with one entry every line
 */
void toString(node * currNode) {

	//find how many objects in the list
	printf("%d\n", counter(currNode));

    while( currNode != NULL ) {

        printf("%d\t", currNode->data);
        currNode = currNode->next;        	

    }
}

/* 
 * returns int for amt of nodes in list
 */
int counter(node * currNode) {
	
	int counter = 0;	

	while ( currNode != NULL) {
		currNode = currNode->next;
		counter++;
	}

	return counter;
}
 
/*
 * Checks if the file is empty.
 */
bool isEmpty(char file[]) {
 
    FILE * fp2 = fopen(file, "r");;     //test pointer to check file
 	char str[20];

    fscanf(fp2,"%s", str);
 
    //if pointer is still at origin, file is empty
    if ( strlen(str) == 0 ) {
        return true;
    }
 
    return false;
}