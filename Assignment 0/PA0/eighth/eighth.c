#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct _bst {
	int data;
	struct _bst* left;
	struct _bst* right;
}BST;

//declare functions
BST * search(BST * tree, int data, int height);
BST * insert(BST * tree, int data, int height);

int main(int argc, char* argv[]) {

	char dete;
	int data;

	//Create BST
	BST * tree = NULL;

  	//input file name
	char * file = argv[1];
    FILE *fp = fopen(file, "r");	// open the file to "r" --> read

    int amt;		//checks if line read 2 variables

	while ( !feof(fp) ) {

		amt = fscanf(fp, "%c %d", &dete, &data);

		if (amt == 2) {
			
			if (dete == 'i') {	//insert
				tree = insert(tree, data, 1);
			}

			else if (dete == 's') {	// search			
				tree = search(tree, data, 1);
			}
		}
	}

	fclose(fp);

	return 0;
}

BST * search(BST * tree, int data, int height) {

	//Base case and if data not found
	//Also covers if tree is etmpty
	if (tree == NULL) {
		printf("absent\n");
	}

	//Base case: data found!
	else if (data == tree->data) {
		printf("present %d\n", height);
		return tree;
	}

	//Traverse through the tree
	else if (data < tree->data)
		search(tree->left, data, height+1);

	else if (data > tree->data)
		search(tree->right, data, height+1);

	//if all else fails

	return tree;

}

BST * insert(BST * tree, int data, int height) {

	//If the tree is empty.
	if (tree == NULL) {
		//printf("\nenters tree==null\n");
		//Create the node.
		BST * node = (BST*) malloc( sizeof(BST) );
		node->data = data;
		node->left = node->right = NULL;

		printf("inserted %d\n", height);
		return node;	//inserted = true;
	}

	//If data is smaller
	if (data < tree->data)
		tree->left = insert(tree->left, data, height+1);

	//If data is bigger
	else if (data > tree->data)
		tree->right = insert(tree->right, data, height+1);

	//duplicate found
	else if (data == tree->data) {
		printf("duplicate\n");
		return tree;
	}

	return tree;	// if all else fails
}