/**********************************************************************************
* File Name	: BinaryTreeBasicOp.c
* Contents	:
*
* Rev  Name			        Date				        Description
* =================================================================================
* 1.0 			Rohit		9/27/2017    					Created
***********************************************************************************/
#include "BinaryTreeBasicOp.h"
#include "TreeUtilities.h"

/*****************************************************************
* Global Variables
******************************************************************/
short g_elementNum = 2;

/***************************************************************************
* Function Name : Swap
* Description   : Function to swap two nodes
****************************************************************************/
void Swap(TREE *node1, TREE *node2)
{
	int temp = 0;

	temp = node1->value;
	node1->value = node2->value;
	node2->value = temp;
}

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

/************************************************************************
* Function Name : InsertBinarySearchTreeElement
* Description   : Function to insert an element to a binary search tree
************************************************************************/
void InsertBinarySearchTreeElement(TREE **rootNode,int elementToBeInserted)
{
	if (NULL == (*rootNode))
	{
		(*rootNode)->value = elementToBeInserted;
		return;
	}

	if ((*rootNode)->value > elementToBeInserted)
	{
		if (NULL == (*rootNode)->L_Child)
		{
			//Allocating memory for left child Node
			(*rootNode)->L_Child = (TREE*)calloc(1, sizeof(TREE));
			(*rootNode)->L_Child->value = elementToBeInserted;

			//Setting up parent Node
			(*rootNode)->L_Child->Parent = *rootNode;


			return;
		}
		else
		{
			InsertBinarySearchTreeElement(&(*rootNode)->L_Child, elementToBeInserted);
		}
	}
	else
	{
		if (NULL == (*rootNode)->R_Child)
		{
			//Allocating memory for left child Node
			(*rootNode)->R_Child = (TREE*)calloc(1, sizeof(TREE));
			(*rootNode)->R_Child->value = elementToBeInserted;

			//Setting up parent Node
			(*rootNode)->R_Child->Parent = *rootNode;

			return;
		}
		else
		{
			InsertBinarySearchTreeElement(&(*rootNode)->R_Child, elementToBeInserted);
		}
	}
}

/***********************************************************************************
* Function Name : CreateBinarySearchTree
* Description   : Function to create a binary search tree by taking input from user
************************************************************************************/
void CreateBinarySearchTree(TREE **rootNode,int numElements)
{
	int newElementVal = 0;

	//Allocating memory for root Node
	*rootNode = (TREE*)calloc(1,sizeof(TREE));
	
	cout << "Enter root value (Element 1): ";
	cin >> (*rootNode)->value;

	for (int i = 1; i < numElements; i++, g_elementNum++)
	{
		cout << "Enter element " << g_elementNum << ": ";
		cin >> newElementVal;
		InsertBinarySearchTreeElement(rootNode, newElementVal);
	}
}

/***********************************************************************************
* Function Name : InitializeNodeDepth
* Description   : Function to update the depth of each node in the tree
************************************************************************************/
//void InitializeNodeDepth(TREE **node)
//{
//	if (NULL == *node)
//	{
//		return;
//	}
//	
//	else
//	{
//		(*node)->depth = GetNodeDepth(*node);
//	}
//
//	if (NULL != (*node)->L_Child)
//	{
//		InitializeNodeDepth(&(*node)->L_Child);
//	}
//
//	if (NULL != (*node)->R_Child)
//	{
//		InitializeNodeDepth(&(*node)->R_Child);
//	}
//
//	return;
//}

/********************************************************************************************
* Function Name : SearchTree
* Description   : Function to search the tree through inorder traversing for the given value
*********************************************************************************************/
TREE *SearchTree(TREE *node, int searchVal)
{
	TREE *temp = NULL;
	if (NULL == node)
	{
		return NULL;
	}
	
	//Searching the left node
	temp = SearchTree(node->L_Child, searchVal);
	if (NULL == temp)
	{
		if (searchVal == node->value)
		{
			cout << "\nValue Found";
			return node;
		}

#ifdef DS_DEBUG
		cout << "\nNode Checked: " << node->value;
#endif
		//Searching the right node
		temp = SearchTree(node->R_Child, searchVal);
	}

	return temp;
}

/***********************************************************************************
* Function Name : LocatePredecessor
* Description   : Function to find the Predecessor of a given node from the tree
************************************************************************************/
TREE *LocatePredecessor(TREE *node)
{
	TREE *temp = node;
	static int flag = 0;

	if (NULL == node)
	{
		return NULL;
	}
	else
	{
		if (0 == flag)
		{
			if (node->L_Child != NULL)
			{
				temp = node->L_Child;
				flag = 1;
			}
		}
		if (NULL != temp->R_Child)
		{
			temp = LocatePredecessor(temp->R_Child);
		}
	}

	return temp;
}

/***********************************************************************************
* Function Name : LocateSuccessor
* Description   : Function to find the Successor of a given node from the tree
************************************************************************************/
TREE *LocateSuccessor(TREE *node)
{
	TREE *temp = node;
	static int flag = 0;

	if (NULL == node)
	{
		return NULL;
	}
	else
	{
		if (0 == flag)
		{
			if (node->R_Child != NULL)
			{
				temp = node->R_Child;
				flag = 1;
			}
		}
		if (NULL != temp->L_Child)
		{
			temp = LocatePredecessor(temp->L_Child);
		}
	}

	return temp;
}

/***********************************************************************************
* Function Name : DeleteNodeFromTree
* Description   : Function to delete the given node from the tree
************************************************************************************/
void DeleteNodeFromTree(TREE *node, TREE *foundNode)
{
	TREE *predecessor = NULL;
	TREE *successor = NULL;
	TREE *nodeTobeDeleted = NULL;
	
	if (NULL == foundNode)
	{
		cout << "\nInvalid node. Node does not exist.";
		return;
	}

	if (NULL == foundNode->L_Child && NULL == foundNode->R_Child)
	{
		//It is a leaf node
		if (foundNode == foundNode->Parent->L_Child)
		{
			foundNode->Parent->L_Child = NULL;
		}
		else if (foundNode == foundNode->Parent->R_Child)
		{
			foundNode->Parent->R_Child = NULL;
		}

		free(foundNode);
		foundNode = NULL;
	}
	else if (NULL != foundNode->L_Child && NULL == foundNode->R_Child)
	{
		//Intermediate node
		predecessor = LocatePredecessor(foundNode);

		//Swapping the predecessor and node to be deleted
		Swap(foundNode, predecessor);
		
		//Determine if the node to be deleted is a leaf node or not. If yes bubble the node to be deleted to the leaf.
		nodeTobeDeleted = SwapUntilLeafNode(predecessor);
				
		if (nodeTobeDeleted == nodeTobeDeleted->Parent->L_Child)
		{
			nodeTobeDeleted->Parent->L_Child = NULL;
		}
		else if (nodeTobeDeleted == nodeTobeDeleted->Parent->R_Child)
		{
			nodeTobeDeleted->Parent->R_Child = NULL;
		}

		free(nodeTobeDeleted);
		nodeTobeDeleted = NULL;
	}
	else if (NULL == foundNode->L_Child && NULL != foundNode->R_Child)
	{
		//Intermediate node
		successor = LocateSuccessor(foundNode);

		//Swapping the successor and node to be deleted
		Swap(foundNode, successor);

		//Determine if the node to be deleted is a leaf node or not. If yes bubble the node to be deleted to the leaf.
		nodeTobeDeleted = SwapUntilLeafNode(predecessor);
			
		if (nodeTobeDeleted == nodeTobeDeleted->Parent->L_Child)
		{
			nodeTobeDeleted->Parent->L_Child = NULL;
		}
		else if (nodeTobeDeleted == nodeTobeDeleted->Parent->R_Child)
		{
			nodeTobeDeleted->Parent->R_Child = NULL;
		}

		free(nodeTobeDeleted);
		nodeTobeDeleted = NULL;
	}
	else
	{
		//Intermediate node
		//By default predecessor is taken
		predecessor = LocatePredecessor(foundNode);

		Swap(foundNode, predecessor);

		//Determine if the node to be deleted is a leaf node or not. If yes bubble the node to be deleted to the leaf.
		nodeTobeDeleted = SwapUntilLeafNode(predecessor);
		if (nodeTobeDeleted == nodeTobeDeleted->Parent->L_Child)
		{
			nodeTobeDeleted->Parent->L_Child = NULL;
		}
		else if (nodeTobeDeleted == nodeTobeDeleted->Parent->R_Child)
		{
			nodeTobeDeleted->Parent->R_Child = NULL;
		}

		free(nodeTobeDeleted);
		nodeTobeDeleted = NULL;
		
	}
}

/***********************************************************************************
* Function Name : main
* Description   : 
************************************************************************************/
void main()
{
	TREE			*root				= NULL;
	TREE			*foundNode			= NULL;
	unsigned int	numElements			= 0;
	int				valueToBeDeleted	= 0;
	unsigned short  option				= 0;
	int				valueToBeAdded		= 0;

	do
	{
		cout << "\n************* BST Basic Operations Menu ********************\n\n";
		cout << "1. Create Binary Search Tree\n";
		cout << "2. Add Node to BST\n";
		cout << "3. Delete Node from BST \n";
		cout << "4. View Tree\n";
		cout << "5. Quit program\n";
		cout << "Enter your option(1 - 5) : ";
		cin >> option;

		switch (option)
		{
		case 1:
			cout << "\nEnter number of nodes :";
			cin >> numElements;

			//Function to create the BST based on the number of nodes given by the user.
			CreateBinarySearchTree(&root,numElements);

			//Initializing values for depth
			//InitializeNodeDepth(&root);
			break;

		case 2:

			//User input to give the value to be added
			cout << "\nEnter value to be added: ";
			cin >> valueToBeAdded;

			//Function to add node.
			InsertBinarySearchTreeElement(&root, valueToBeAdded);

			//Initializing values for depth
			//InitializeNodeDepth(&root);
			break;

		case 3:
			//User input to give the value to be deleted
			cout << "\n Enter value to be deleted: ";
			cin >> valueToBeDeleted;

			//Function to find the node to be deleted.
			foundNode = SearchTree(root, valueToBeDeleted);
			if (NULL == foundNode)
			{
				cout << "\nError.Given value does not exist.Please Enter valid value";
			}
			else
			{
				//Function to delete the node.
				DeleteNodeFromTree(root, foundNode);
				cout << "\nNode with value : " << valueToBeDeleted << " deleted";
			}

			break;

		case 4:
			//Displaying the linked list
			cout << "\nThe Binary Search Tree : ";
			InOrderDisplayTree(root);
			cout << "\n";
			break;

		case 5:
			//Exit the program
			cout << "Exiting program. Goodbye :-)";
			R_Sleep(2);
			exit(0);
			break;

		default:
			cout << "Invalid option.Please provide a value in the range (1-5)";
		}
	} while (TRUE);
}