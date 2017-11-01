/**********************************************************************************
* File Name	: TreeUtilities.h
* Contents	:
*
* Rev  Name			        Date				        Description
* =================================================================================
* 1.0 			Rohit		9/27/2017    					Created
***********************************************************************************/
#ifndef TREE_UTILITIES
#define TREE_UTILITIES

#include "BinaryTreeBasicOp.h"


/*****************************************************************
* Function Declaration
******************************************************************/

/**************************************************************************
* Function Name : GetNodeHeight
***************************************************************************/
int GetNodeHeight(TREE *node);

/************************************************************
* Function Name : DisplayTree
*************************************************************/
void InOrderDisplayTree(TREE *node);

/**************************************************************************
* Function Name : GetNodeDepth
***************************************************************************/
int GetNodeDepth(TREE *node);

/************************************************************************************
* Function Name : SwapUntilLeafNode
************************************************************************************/
TREE *SwapUntilLeafNode(TREE *node);

/**************************************************************************
* Function Name : Max
***************************************************************************/
int Max(int num1, int num2);

#endif