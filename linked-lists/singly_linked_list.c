/*

Single Linked list implementation in C

I haven't completed everything related to simple linked list.
As of 8/15/2017 (DD/MM/YYYY), there's:
- Insertion of node from beginning.
- Insertion of node from end.
- Searching of node.
- Deletion of node from beginning.
- Deletion of node from end.
- Displaying all nodes.

I haven't added any explanation due to lack of time. I'll add them ASAP.

*/
#include <stdio.h>
#include <malloc.h>
#include <conio.h> //Comment this if you're using Linux.
#include <stdlib.h>

typedef struct Node Node; //So that I don't have to use 'struct Node' everywhere for defining a node. 'Node' would be enough.

struct Node {

	int nValue;
	Node *nextNode = NULL;
};


Node
	*headNode = NULL, 	//Starting node.
	*rearNode = NULL	//Ending node.
;

//Let's first create a function to create a node or to allocate memory for a node.
Node* createNode(int value);
Node* createNode(int value) {

	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->nValue = value;
	newNode->nextNode = NULL;

	return newNode;
}


void insertNode_First(Node *node);
void insertNode_First(Node *node) {

	if(headNode == NULL)
		headNode = rearNode = node;
	else {

		node->nextNode = headNode;
		headNode = node;
	}
}

void insertNode_Last(Node *node);
void insertNode_Last(Node *node) {

	if(headNode == NULL)
		headNode = rearNode = node;
	else {

		Node *tempNode = rearNode;
		tempNode->nextNode = node;
		rearNode = node;
	}
}

int removeNode_First();
int removeNode_First() {

	if(headNode == NULL)
		return 0;
	else {

		Node *tempNode = headNode;
		headNode = headNode->nextNode;
		free(tempNode); //To avoid memory leaks.
	}
	return 1;
}

int removeNode_Last();
int removeNode_Last() {

	if(headNode == NULL)
		return 0;
	else {
		Node *tempNode = headNode;
		while(tempNode->nextNode != rearNode)
			tempNode = tempNode->nextNode;

		tempNode->nextNode = NULL;
		free(rearNode);
		rearNode = tempNode;
	}
	return 1;
}

void displayNodes();
void displayNodes() {

	if(headNode == NULL)
		printf("Linked list is empty!\n");
	else {
		Node *tempNode = headNode;
		do {
			printf("[%d]->", tempNode->nValue);
			tempNode = tempNode->nextNode;
		} while(tempNode != NULL);
		printf("NULL\n");
	}
}

Node* searchNode(int value);
Node* searchNode(int value) {

	if(headNode == NULL)
		return NULL;
	else {
		Node *tempNode = headNode;
		while(tempNode->nextNode != NULL) {

			if(tempNode->nValue == value)
				return tempNode;
			tempNode = tempNode->nextNode;
		}
	}
}


//Main program can be according to your layout. I'm creating main with an aim to call all of the above linked-list functions.

int main() {

	char cProgramState = 'Y';
	int 
		iValue,
		iOption
	;

	printf(
		"-------------------------------------\n"\
		"	Simple/Single Linked List\n"\
		"-------------------------------------"
		);

	while(cProgramState == 'Y' || cProgramState == 'y') {

		printf("\n\n"\
			"1. Insert new node from beginning.\n"\
			"2. Insert new node from ending.\n"\
			"3. Search if a node exists.\n"\
			"4. Display all nodes.\n"\
			"5. Delete first node.\n"\
			"6. Delete last node.\n"\
			"7. Exit.\n"\
			"Choose an operation : "
			);

		scanf("%d", &iOption);

		switch(iOption) {

			case 1 : case 2: {

				printf("Enter a value for the new node : ");
				scanf("%d", &iValue);

				Node *newNode = createNode(iValue);
				if(newNode == NULL)
					printf("ERROR : Failed allocating memory for new node! Make sure if there's enough heap space available.\n");
				else {

					if(iOption == 1)
						insertNode_First(newNode);
					else
						insertNode_Last(newNode);

					printf("Node successfully inserted at the %s.\n", (iOption == 1) ? ("beginning") : ("ending"));
				}
				break;
			}
			case 3: {

				printf("Enter a node's value to check if it exists : ");
				scanf("%d", &iValue);

				Node *fetchedNode = searchNode(iValue);
				if(fetchedNode == NULL)
					printf("The searched node does not exist!\n");
				else
					printf("The searched node exists!\n");

				break;
			}
			case 4: {

				displayNodes();
				break;
			}
			case 5: {

				if(!removeNode_First())
					printf("ERROR : There are no nodes to be removed!\n");
				else
					printf("The first node has been removed successfully. Choose display nodes to list the current list.\n");

				break;
			}
			case 6: {

				if(!removeNode_Last())
					printf("ERROR : There are no nodes to be removed!\n");
				else
					printf("The last node has been removed successfully. Choose display nodes to list the current list.\n");

				break;
			}
			case 7: {

				exit(0);
				break;
			}
			default: 
				printf("ERROR : Invalid operation chosen!");

		}
		cProgramState = 'a';
		while(cProgramState != 'Y' && cProgramState != 'y' && cProgramState != 'N' && cProgramState != 'n') {

			printf("Do you want to continue with linked-list program? (Y to continue / N to exit) : ");
			scanf(" %c", &cProgramState);
		}
	}
	printf("Press any key to close the program...");
	getch();
	return 0;
}
