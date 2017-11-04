#ifndef three_H
#define	three_H
typedef struct _node {
    int data;                  	//holds integers
    struct _node * next;  		// manages pointers
}node;                        	// call this struct, node.

typedef struct _hashTable {
	node * tableList[10000]; //elements of table
} hashTable;

#endif