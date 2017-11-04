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
BST * delete(BST * tree, int data, int height);

//Global variable
int success = 0;

int main(int argc, char* argv[]) {

	char dete;
	int data;

	//Create BST
	BST * tree = malloc( sizeof(BST) );
  	
  	//input file name
	char * file = argv[1];
    FILE *fp = fopen(file, "r");	// open the file to "r" --> read

    int amt;		//checks if line read 2 variables
	while ( !feof(fp) ) {

		amt = fscanf(fp, "%c %d", &dete, &data);

		if (amt == 2) {
			
			if (dete == 'i') {	//insert
				tree = insert(tree, data, 1);
				//printf("new root: %d\n", tree->data);
			}

			else if (dete == 's') {	// search			
				tree = search(tree, data, 0);
			}

			else if (dete == 'd') {
				tree = delete(tree, data, 1);

				if (success) printf("success\n");
				else printf("fail\n");

				//printf("root number: %d\n", tree->data);
			}
		}
	}

	fclose(fp);

	return 0;
}

BST * delete(BST * tree, int data, int height) {

	//Base case if case is not found
	if (tree == NULL) {
		success = 0;
		return tree;
	}
	
	//Traverse through the tree
	else if (data < tree->data)
		delete(tree->left, data, height+1);

	else if (data > tree->data)
		delete(tree->right, data, height+1);

	//found node to delete. There's 3 cases
	else if(data == tree->data) {

		int replaceData;	//number to replace	

		//If we are dealing with the root
		if (height == 1) {

			//if there are no children and just the root
			if (tree->left == NULL && tree->right == NULL) {
				BST * newRoot = malloc( sizeof(BST) );
				newRoot->data = 0;
				//free(tree);
				success = 1;
				return newRoot;
			}

			//if there is a right child
			else if (tree->right != NULL) {
				BST * replace = tree->right;	//new number/node

				while (replace->left != NULL) {
					replace = replace->left;
				}
				replaceData = replace->data;

				//Now take the data and replace it with
				//data in node target for deletion
				tree->data = replaceData;

				//Clear used node
				tree->right = delete(tree->right, replaceData, height+1);

				//free(replace);
				//printf("root success\n");
				success = 1;
				return tree;			
			}

			//if we just have a left child
			else {
				//printf("root success\n");
				success = 1;
				return tree->left;
			}
		}

		//Case 1: there's nodes attached on both sides
		else if (tree->left != NULL && tree->right != NULL) {
			
			/*
			 * Find the smallest number on right subtree
			 * (also known as the replacement number)
			 */	
			BST * replace = tree->right;	//new number/node

			while (replace->left != NULL) {
				replace = replace->left;
			}
			replaceData = replace->data;

			//Now take the data and replace it with
			//data in node target for deletion
			tree->data = replaceData;

			//Clear used node
			tree->right = delete(tree->right, replaceData, height+1);

			//free(replace);
			//printf("c1 success %d\n", tree->data);
			success = 1;
			return tree;
		}

		//Case 2: there's nodes attached to the left
		else if (tree->right == NULL) {
			//printf("c2 success %d\n", tree->data);
			success = 1;
			return tree->left;	//skip over the node
		}

		//Case 3: there's nodes attached to the right
		else if (tree->left == NULL){
			//printf("c3 success %d\n", tree->data);
			success = 1;
			return tree->right;	//skip over the node
		}

	}

	return tree;

}

BST * search(BST * tree, int data, int height) {

	//Base case and if data not found
	//Also covers if tree is etmpty
	if (tree == NULL) {
		printf("absent\n");
		return tree;
	}

	//Base case: data found!
	else if (data == tree->data) {
		if (height == 0) height++;
		printf("present %d\n", height);
		return tree;
	}

	//Traverse through the tree
	else if (data < tree->data){
		//printf("BRANCH LEFT -> %d\n", tree->data);
		//printf("Height: %d", height);
		search(tree->left, data, height+1);
	}

	else if (data > tree->data){
		//printf("BRANCH RIGHT -> %d\n", tree->data);
		//printf("Height: %d", height);		
		search(tree->right, data, height+1);
	}

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

	//If we have a null node midway through deleting everything
	if (tree->data == 0) {
		tree->data = data;
		printf("inserted %d\n", height);
		return tree;
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