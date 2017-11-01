/**********************************************************************************
* File Name	: TreeUtilities.c
* Contents	:
*
* Rev  Name			        Date				        Description
* =================================================================================
* 1.0 			Rohit		9/27/2017    					Created
***********************************************************************************/
#include "TreeUtilities.h"

/*****************************************************************
* Global Variables
******************************************************************/

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

/**************************************************************************
* Function Name : GetNodeDepth
* Description   : Function to get dpeth of a node in a binary search tree
***************************************************************************/
int GetNodeDepth(TREE *node)
{
	if (NULL == node)
	{
		return 0;
	}

	if (NULL == node->Parent)
	{
		return 0;
	}
	else
	{
		return 1 + GetNodeDepth(node->Parent);
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
		cout << node->value<< " ";
		InOrderDisplayTree(node->R_Child);
	}
}

/************************************************************************************
* Function Name : SwapUntilLeafNode
* Description   : 
************************************************************************************/
TREE *SwapUntilLeafNode(TREE *node)
{
	TREE *temp = NULL;

	//Check wheather the predecessor is a leaf node or not
	if (node->L_Child == NULL && node->R_Child == NULL)
	{
		return node;
	}

	if (node->L_Child != NULL)
	{
		Swap(node, node->L_Child);
		temp = SwapUntilLeafNode(node->L_Child);
	}
	else if (node->R_Child != NULL)
	{
		Swap(node, node->R_Child);
		temp = SwapUntilLeafNode(node->R_Child);
	}

	return temp;
}
