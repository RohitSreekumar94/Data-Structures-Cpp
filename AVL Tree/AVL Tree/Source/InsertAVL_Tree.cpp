/**********************************************************************************
* File Name	: InsertAVL_Tree.h
* Contents	:
*
* Rev  Name			        Date				        Description
* =================================================================================
* 1.0  Rohit				10/08/2017 					Created
***********************************************************************************/
#include "InsertAVL_Tree.h"


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

/**************************************************************************
* Function Name : Max
* Description   : Function to get maximum of two integers
***************************************************************************/
int Max(int num1, int num2)
{
	if (num1 > num2)
	{
		return num1;
	}
	else
	{
		return num2;
	}
}

/**************************************************************************
* Function Name : GetNodeHeight
* Description   : Function to get height of a node in a binary search tree
***************************************************************************/
int GetNodeHeight(TREE *node)
{
	if (NULL == node)
	{
		return 0;
	}

	if (NULL == node->L_Child && NULL == node->R_Child)
	{
		return 0;
	}
	else
	{
		return 1 + Max(GetNodeHeight(node->L_Child), GetNodeHeight(node->R_Child));
	}
}

/***********************************************************************************************
* Function Name : UpdateParent
* Description   : Function to update the parent of each node in the tree - traversing pre order
************************************************************************************************/
void UpdateParent(TREE **node)
{
	if (NULL == (*node))
	{
		return;
	}

	if ((*node)->L_Child != NULL)
	{
		(*node)->L_Child->Parent = (*node);
	}

	if ((*node)->R_Child != NULL)
	{
		(*node)->R_Child->Parent = (*node);
	}

	UpdateParent(&(*node)->L_Child);
	UpdateParent(&(*node)->R_Child);

}
/***********************************************************************************
* Function Name : UpdateHeight
* Description   : Function to update the height of each node in the tree
************************************************************************************/
void UpdateHeight(TREE **node)
{
	if (NULL == *node)
	{
		return;
	}
	
	else
	{
		(*node)->height = GetNodeHeight(*node);
	}

	if (NULL != (*node)->L_Child)
	{
		UpdateHeight(&(*node)->L_Child);
	}

	if (NULL != (*node)->R_Child)
	{
		UpdateHeight(&(*node)->R_Child);
	}

	return;
}

/*****************************************************************************************
* Function Name : GetRootNode
* Description   : Function to get the root of a TREE
******************************************************************************************/
TREE *GetRootNode(TREE *node)
{
	if (NULL == node)
	{
		return NULL;
	}

	if (NULL == node->Parent)
	{
		return node;
	}
	else
	{
		return GetRootNode(node->Parent);
	}
}

/*****************************************************************************************
* Function Name : CopySubTree
* Description   : Function to create a copy of the given tree
******************************************************************************************/
void CopySubTree(TREE **node, TREE **copy)
{
	if (NULL == *node)
	{
		return;
	}
	//Allocating memory for copy
	if (NULL == *copy)
	{
		*copy = (TREE*)calloc(1, sizeof(TREE));
	}

	memcpy(*copy, (*node), sizeof((*node)));

	CopySubTree(&(*node)->L_Child, &(*copy)->L_Child);
	CopySubTree(&(*node)->R_Child, &(*copy)->R_Child);
	
}

/*****************************************************************************************
* Function Name : FreeSubTree
* Description   : Function to free memory of the given tree via postorder traversal
******************************************************************************************/
void FreeSubTree(TREE **node)
{
	if (NULL == (*node))
	{
		return;
	}

	FreeSubTree(&(*node)->L_Child);
	FreeSubTree(&(*node)->R_Child);

	//Free memory
	free((*node));
}


/*****************************************************************************************
* Function Name : PerformSingleRotation
* Description   : Function to perform single rotation.
******************************************************************************************/
TREE* PerformSingleRotation(TREE *node,char string[])
{
	TREE *temp_1 = NULL;
	TREE *temp_2 = NULL;

	if (!strcmp(string, "LEFT_STRAIGHT_LINE"))
	{
		if (node->Parent != NULL)
		{
			if (node == node->Parent->L_Child)
			{
				//Relink parent's left node with node's left node
				node->Parent->L_Child = node->L_Child;
			}
			else
			{
				//Relink parent's right node with node's left node
				node->Parent->R_Child = node->L_Child;
			}
		}

		temp_1 = node->L_Child;

		if (NULL != temp_1)
		{
			temp_2 = temp_1->R_Child;
			temp_1->R_Child = node; 
			temp_1->Parent = node->Parent;
		}

		node->L_Child = temp_2;
		if (temp_2 != NULL)
		{
			node->L_Child->Parent = temp_2->Parent;
		}
		
		
	}

	else if (!strcmp(string, "RIGHT_STRAIGHT_LINE"))
	{
		if (node->Parent != NULL)
		{
			if (node == node->Parent->L_Child)
			{
				//Relink parent's left node with node's right node
				node->Parent->L_Child = node->R_Child;
			}
			else
			{
				//Relink parent's right node with node's right node
				node->Parent->R_Child = node->R_Child;
			}
		}	

		temp_1 = node->R_Child;

		if (NULL != temp_1)
		{
			temp_2 = temp_1->L_Child;
			temp_1->L_Child = node;
			temp_1->Parent = node->Parent;
		}

		node->R_Child = temp_2;

		if (temp_2 != NULL)
		{
			node->R_Child->Parent = temp_2->Parent;
		}
	}

	//UpdateParent(&temp_1);
	UpdateHeight(&temp_1);

	return temp_1;
}

/*****************************************************************************************
* Function Name : PerformDoubleRotation
* Description   : Function to perform double rotation.
******************************************************************************************/
TREE* PerformDoubleRotation(TREE *node, char string[])
{
	if (!strcmp(string, "LEFT_ZIG_ZAG_LINE"))
	{
		node->L_Child = PerformSingleRotation(node->L_Child, "RIGHT_STRAIGHT_LINE");
		return PerformSingleRotation(node, "LEFT_STRAIGHT_LINE");
	}

	else if (!strcmp(string, "RIGHT_ZIG_ZAG_LINE"))
	{
		node->R_Child = PerformSingleRotation(node->R_Child, "LEFT_STRAIGHT_LINE");
		return PerformSingleRotation(node, "RIGHT_STRAIGHT_LINE");
	}
	else
	{
		return NULL;
	}
}

/*****************************************************************************************
* Function Name : ChooseRotation
* Description   : Function to choose what rotation to employ.
******************************************************************************************/
void ChooseRotation(TREE **node,char string[])
{
	if (!strcmp(string, "LEFT_STRAIGHT_LINE"))
	{
		(*node) = PerformSingleRotation(*node,string);
	}

	else if (!strcmp(string, "LEFT_ZIG_ZAG_LINE"))
	{
		(*node) = PerformDoubleRotation(*node, string);
	}

	else if (!strcmp(string, "RIGHT_STRAIGHT_LINE"))
	{
		(*node) = PerformSingleRotation(*node,string);
	}

	else if (!strcmp(string, "RIGHT_ZIG_ZAG_LINE"))
	{
		(*node) = PerformDoubleRotation(*node,string);
	}
}

/*****************************************************************************************
* Function Name : CheckImbalance
* Description   : Function to check imbalance in the tree
******************************************************************************************/
TREE* CheckImbalance(TREE *node)
{
	TREE* temp = NULL;

	if (NULL == node)
	{
		return NULL;
	}
	else
	{
		if (NULL != (node)->L_Child && NULL != (node)->R_Child)
		{
			if (abs((node)->L_Child->height - (node)->R_Child->height) > 1)
			{
				return node;
			}
		}

		else if (NULL != (node)->L_Child && NULL == (node)->R_Child)
		{
			if ((node)->height > 1)
			{
				//Imbalance found in left subtree
				return node;
			}
		}

		else if (NULL != (node)->R_Child && NULL == (node)->L_Child)
		{
			if ((node)->height > 1)
			{
				//Imbalance found in right subtree
				return node;
			}
		}

		else
		{
			//No imbalance
			return NULL;
		}
	}

	return temp;
}


/*****************************************************************************************
* Function Name : CorrectImbalance
* Description   : Function to correct imbalance in the tree
******************************************************************************************/
void CorrectImbalance(TREE **node)
{
	char string[100] = { 0 };

	if (NULL == *node)
	{
		return;
	}
	
	else
	{
		if (NULL != (*node)->L_Child && NULL != (*node)->R_Child)
		{
			if (abs((*node)->L_Child->height - (*node)->R_Child->height) > 1)
			{
				if ((*node)->L_Child->height > (*node)->R_Child->height)
				{
					//Imbalance found in left subtree
					if ((*node)->L_Child != NULL)
					{
						if ((*node)->L_Child->L_Child != NULL && (*node)->L_Child->R_Child != NULL)
						{ 
							if ((*node)->L_Child->L_Child->height > (*node)->L_Child->R_Child->height)
							{
								strcpy(string, "LEFT_STRAIGHT_LINE");
							}
							else
							{
								strcpy(string, "LEFT_ZIG_ZAG_LINE");
							}
						}
						else if ((*node)->L_Child->L_Child != NULL)
						{
							strcpy(string, "LEFT_STRAIGHT_LINE");
						}
						else if ((*node)->L_Child->R_Child != NULL)
						{
							strcpy(string, "LEFT_ZIG_ZAG_LINE");
						}
					}

					//Perform rotations
					ChooseRotation(node, string);
				}
				else
				{
					//Imbalance found in right subtree
					if ((*node)->R_Child != NULL)
					{
						if ((*node)->R_Child->R_Child != NULL && (*node)->R_Child->L_Child != NULL)
						{
							if ((*node)->R_Child->R_Child->height > (*node)->R_Child->L_Child->height)
							{
								strcpy(string, "RIGHT_STRAIGHT_LINE");
							}
							else
							{
								strcpy(string, "RIGHT_ZIG_ZAG_LINE");
							}
						}
						else if ((*node)->R_Child->R_Child != NULL)
						{
							strcpy(string, "RIGHT_STRAIGHT_LINE");
						}
						else if ((*node)->R_Child->L_Child != NULL)
						{
							strcpy(string, "RIGHT_ZIG_ZAG_LINE");
						}
					}
					//Perform rotations
					ChooseRotation(node, string);
				}
			}
		}
		else if (NULL != (*node)->L_Child && NULL == (*node)->R_Child)
		{
			if ((*node)->height > 1)
			{
				//Imbalance found in left subtree
				if ((*node)->L_Child->L_Child != NULL && (*node)->L_Child->R_Child != NULL)
				{
					if ((*node)->L_Child->L_Child->height > (*node)->L_Child->R_Child->height)
					{
						strcpy(string, "LEFT_STRAIGHT_LINE");
					}
					else
					{
						strcpy(string, "LEFT_ZIG_ZAG_LINE");
					}
				}
				else if ((*node)->L_Child->L_Child != NULL)
				{
					strcpy(string, "LEFT_STRAIGHT_LINE");
				}
				else if ((*node)->L_Child->R_Child != NULL)
				{
					strcpy(string, "LEFT_ZIG_ZAG_LINE");
				}
			
				//Perform rotations
				ChooseRotation(node, string);
			}
		}
		else if (NULL != (*node)->R_Child && NULL == (*node)->L_Child)
		{
			if ((*node)->height > 1)
			{
				//Imbalance found in right subtree
				if ((*node)->R_Child->R_Child != NULL && (*node)->R_Child->L_Child != NULL)
				{
					if ((*node)->R_Child->R_Child->height > (*node)->R_Child->L_Child->height)
					{
						strcpy(string, "RIGHT_STRAIGHT_LINE");
					}
					else
					{
						strcpy(string, "RIGHT_ZIG_ZAG_LINE");
					}
				}
				else if ((*node)->R_Child->R_Child != NULL)
				{
					strcpy(string, "RIGHT_STRAIGHT_LINE");
				}
				else if ((*node)->R_Child->L_Child != NULL)
				{
					strcpy(string, "RIGHT_ZIG_ZAG_LINE");
				}
				
				//Perform rotations
				ChooseRotation(node, string);
			}
		}
		else
		{
			//No imbalance 
		}
	}

	return;
}

/*****************************************************
* Function Name : CheckNodeImbalance
* Description   : Function to check node imbalance 
******************************************************/
TREE* CheckNodeImbalance(TREE *node)
{
	TREE *temp = NULL;

	if (NULL == node)
	{
		return NULL;
	}

	temp = CheckImbalance(node);
	if (NULL != temp)
	{
		CorrectImbalance(&temp);
	}

	return temp;
}

/*****************************************************************************************
* Function Name : InsertElements_AVL_TREE
* Description   : Function to insert an element to an AVL tree and balance it immediately
******************************************************************************************/
TREE* InsertElements_AVL_TREE(TREE **node, int elementToBeInserted)
{
	TREE *root = NULL;
	TREE *tempNode = NULL;

	if (NULL == (*node))
	{
		(*node)= (TREE*)calloc(1, sizeof(TREE));
		(*node)->value = elementToBeInserted;
		return (*node);
	}

	if ((*node)->value > elementToBeInserted)
	{
		(*node)->L_Child = InsertElements_AVL_TREE(&(*node)->L_Child, elementToBeInserted);
		UpdateParent(node);
	}
	else
	{		
		(*node)->R_Child = InsertElements_AVL_TREE(&(*node)->R_Child, elementToBeInserted);
		UpdateParent(node);
	}

	//Function to get root
	root = GetRootNode(*node);
	if (NULL != root)
	{
		//Update the height of nodes
		UpdateHeight(&root);
	}

	//Check for imbalance created by the addition of this new node
	tempNode = CheckNodeImbalance(*node);
	if (NULL != tempNode)
	{
		UpdateParent(&tempNode);
		return tempNode;
	}

	return (*node);

}


/***********************************************************************************
* Function Name : CreateBinarySearchTree
* Description   : Function to create a AVL tree by taking input from user
************************************************************************************/
void CreateAVLTree(TREE **rootNode, int numElements)
{
	int newElementVal = 0;

	//Allocating memory for root Node
	*rootNode = (TREE*)calloc(1, sizeof(TREE));

	cout << "Enter root value (Element 1): ";
	cin >> (*rootNode)->value;
	(*rootNode)->height = 0;

	for (int i = 1; i < numElements; i++, g_elementNum++)
	{
		cout << "Enter element " << g_elementNum << ": ";
		cin >> newElementVal;
		*rootNode = InsertElements_AVL_TREE(rootNode, newElementVal);
	}
}

/************************************************************************************
* Function Name : InOrderDisplayTree
* Description   : Function to display the binary search tree by in order traversing
************************************************************************************/
void InOrderDisplayTree(TREE *node)
{
	if (NULL == node)
	{
		return;
	}
	else
	{
		InOrderDisplayTree(node->L_Child);
		cout << node->value << " ";
		InOrderDisplayTree(node->R_Child);
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
		cout << "\n************* AVL Tree Operations Menu ********************\n\n";
		cout << "1. Insert Elements into TREE\n";
		cout << "2. View Balanced AVL Tree (Inorder traversal)\n";
		cout << "3. Quit program\n";
		cout << "Enter your option(1 - 3) : ";
		cin >> option;

		switch (option)
		{
		case 1:
			cout << "\nEnter number of nodes :";
			cin >> numElements;

			//Function to add elements into the TREE and balance them immediately. 
			CreateAVLTree(&root, numElements);
			break;

		case 2:
			//Displaying the linked list
			cout << "\nThe Binary Search Tree : ";
			InOrderDisplayTree(root);
			cout << "\n";
			break;

		case 3:
			//Exit the program
			cout << "Exiting program. Goodbye :-)";
			R_Sleep(2);
			exit(0);
			break;

		default:
			cout << "\nInvalid option.Please provide a value in the range (1-3)";
		}
	} while (TRUE);
}