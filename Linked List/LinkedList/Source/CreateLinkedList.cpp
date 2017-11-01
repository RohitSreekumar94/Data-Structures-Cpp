/****************************************************************
* File Name	: CreateLinkedList.c
* Contents	:
*
* Rev  Name			        Date				        Description
* ==============================================================
* 1.00 			Rohit		8/31/2017    					Created
****************************************************************/

#include "CreateLinkedList.h"

/*****************************************************************
* Global Variables
******************************************************************/
short nodeCount = 1;


/***************************************************************************
* Function Name : R_Sleep
* Description   : Function to pause execution for specified amount of time
****************************************************************************/
void R_Sleep(unsigned long seconds)
{
#ifdef WIN32
	Sleep(seconds * 1000);
#else
	sleep(seconds);
#endif

}

/***************************************************************************
* Function Name : CreateLinkedList
* Description   : Function to create a linked list by taking input from user
****************************************************************************/
void CreateLinkedList(NODE **node,int numNodes)
{
	if (0 == numNodes)
	{
		return;
	}
	else
	{
		*node = new NODE;
		cout << "\nEnter value for Node "<< nodeCount++ << ": ";
		cin >> (*node)->value;
		(*node)->next = NULL;
		CreateLinkedList(&((*node)->next), --numNodes);
	}
}

/*************************************************************************
* Function Name : Display
* Description   : Function to display the node values in the linked list
**************************************************************************/
void Display(NODE *node)
{
	if (NULL == node)
	{
		return;
	}
	else
	{
		cout << " " << node->value;
		Display(node->next);
	}
}

/*************************************************************************
* Function Name : DeleteLinkedList
* Description   : Function to delete node from the Linked list
**************************************************************************/
void DeleteLinkedList(NODE *node, NODE *nodeToBeDeleted)
{
	NODE *tmp = NULL;
	if (NULL == node || NULL == nodeToBeDeleted)
	{
		cout << "\nNo node to be deleted\n";
		return;
	}

	if (node->next == nodeToBeDeleted)
	{
		tmp = node->next->next;
		delete node->next; //Will delete the first node encountered in the linked list
		node->next = tmp;
		return;
	}

	DeleteLinkedList(node->next, nodeToBeDeleted);
}

/*************************************************************************
* Function Name : SearchNode
* Description   : Funciton to search for node in the linked list
**************************************************************************/
NODE *SearchNode(NODE *head,int valueToBeDeleted)
{
	if (NULL == head)
	{
		return NULL;
	}

	else if (head->value == valueToBeDeleted)
	{
		return head;
	}
	else
	{
		return SearchNode(head->next, valueToBeDeleted);
	}
}

/*************************************************************************
* Function Name : AddNode
* Description   : Function to add node to the end of the linked list
**************************************************************************/
int AddNode(NODE *head, int valueToBeAdded)
{
	if (NULL == head)
	{
		//If the head pointer is NULL then a new linked list will be created with head containing the valueToBeAdded
		head = new NODE;
		head->value = valueToBeAdded;
		head->next = NULL;
		return TRUE;
	}
	else if (NULL == head->next)
	{
		head->next = new NODE;
		head->next->value = valueToBeAdded;
		head->next->next = NULL;
		return TRUE;
	}
	else
	{
		return AddNode(head->next, valueToBeAdded);
	}
}

/****************************************************************************
* Function Name : LinkedListBasicOp
* Description   : Function to provide user menu to provide for various linked
				  list basic operations.
*****************************************************************************/
void LinkedListBasicOp(NODE **head)
{
	unsigned int	numNodes		 = 0;
	int				valueToBeDeleted = 0;
	NODE			*foundNode		 = NULL;
	unsigned short  option			 = 0;
	char			userContinue	 = 0;
	int				valueToBeAdded   = 0;

	do
	{
		cout << "\n************* Basic Operations Menu ********************\n\n";
		cout << "1. Create Linked list\n";
		cout << "2. Add Node to Linked List\n";
		cout << "3. Delete Node \n";
		cout << "4. View Linked List\n";
		/*cout << "5. Quit program\n";*/
		cout << "Enter your option(1 - 4) : ";
		cin >> option;

		switch (option)
		{
		case 1:
			cout << "\nEnter number of nodes :";
			cin >> numNodes;

			nodeCount = 1;
			//Function to create the linked lists based on the number of nodes given by the user.
			CreateLinkedList(head, numNodes);
			break;

		case 2:

			//User input to give the value to be deleted
			cout << "\nEnter value to be added: ";
			cin >> valueToBeAdded;

			//Function to add node.
			if (0 == AddNode(*head, valueToBeAdded))
			{
				cout << "\nError. Could not add node";
			}
			else
			{
				cout << "\nNode Succesfully added";
			}
			break;

		case 3:
			//User input to give the value to be deleted
			cout << "\n Enter value to be deleted: ";
			cin >> valueToBeDeleted;

			//Function to find the node to be deleted.
			foundNode = SearchNode(*head, valueToBeDeleted);
			if (NULL == foundNode)
			{
				cout << "\nError.Given value does not exist.Please Enter valid value";
			}
			else
			{
				//Function to delete the node.
				DeleteLinkedList(*head, foundNode);
				cout << "\nNode with value : " << valueToBeDeleted << " deleted";
			}

			break;

		case 4:
			//Displaying the linked list
			cout << "\nThe linked list : ";
			Display(*head);
			cout << "\n";
			break;

		default:
			cout << "Invalid option.Please provide a value in the range (1-4)";
		}

		cout << "\nDo you want to quit the basic operations menu? (Y/n) : ";
		cin >> userContinue;
	} while (userContinue != 'Y');
}
