/**********************************************************************************
* File Name	: BinaryTreeBasicOp.c
* Contents	:
*
* Rev  Name			        Date				        Description
* =================================================================================
* 1.0 			Rohit		9/27/2017    					Created
***********************************************************************************/
#include "BinaryTreeBasicOp.h"
#include "Prims_Algo.h"

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


/************************************************************************
* Function Name : InsertBinarySearchTreeElement
* Description   : Function to insert an element to a binary search tree
************************************************************************/
void InsertBinarySearchTreeElement(TREE **rootNode, TREE **searchNode, int elementToBeInserted,SIDE side)
{


	if (NULL == (*rootNode) && side == INVALID)
	{
		//Allocating memory for root Node
		*rootNode = (TREE*)calloc(1, sizeof(TREE));

		(*rootNode)->value = elementToBeInserted;
		return;
	}

	if(NULL == *searchNode)
	{
		return;
	}

	if (side == LEFT)
	{

		if (NULL == (*searchNode)->L_Child)
		{
			//Allocating memory for left child Node
			(*searchNode)->L_Child = (TREE*)calloc(1, sizeof(TREE));
			(*searchNode)->L_Child->value = elementToBeInserted;
			return;
		}
		else
		{
			InsertBinarySearchTreeElement(&(*searchNode)->L_Child,&(*searchNode)->L_Child,elementToBeInserted,side);
		}
	}
	else if(side == RIGHT)
	{
		if (NULL == (*searchNode)->R_Child)
		{
			//Allocating memory for left child Node
			(*searchNode)->R_Child = (TREE*)calloc(1, sizeof(TREE));
			(*searchNode)->R_Child->value = elementToBeInserted;
			return;
		}
		else
		{
			InsertBinarySearchTreeElement(&(*searchNode)->R_Child, &(*searchNode)->R_Child, elementToBeInserted,side);
		}
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
		cout << toAlpha_R(node->value) << " ";
		InOrderDisplayTree(node->R_Child);
	}
}

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

