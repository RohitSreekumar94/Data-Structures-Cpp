#include "CreateLinkedList.h"

int LargestNumInSingleLinkedList(NODE *node)
{
	int temp = 0;
	if (NULL == node->next)
	{
		return node->value;
	}
	else
	{
		temp = LargestNumInSingleLinkedList(node->next);
		if (temp > node->value)
		{
			return temp;
		}
		else
		{
			return node->value;
		}
	}
}

int main()
{
	NODE			*head = NULL;
	unsigned short  option = 0;
	char			userContinue = 0;
	int				largestNum = 0;

	do
	{
		cout << "\n\n***************************************";
		cout << "\n************* Menu ********************\n";
		cout << "***************************************\n\n";
		cout << "1. Generate Linked list\n";
		cout << "2. Get Largest Number in Linked List\n";
		cout << "3. Exit\n";

		cout << "Enter your option(1 - 2) : ";
		cin >> option;

		switch (option)
		{
		case 1:
			//Creating the linked list
			LinkedListBasicOp(&head);
			break;

		case 2:
			largestNum = LargestNumInSingleLinkedList(head);
			cout << "The Largest Number in the linked list : " << largestNum;
			break;

		case 3:
			cout << "\nAre you sure you want to quit (Y/n) : ";
			cin >> userContinue;

			if (userContinue == 'Y')
			{
				cout << "Exiting Program . Goodbye :-)";
				R_Sleep(2);
				exit(0);
			}
			break;

		default:
			cout << "Invalid option.Please provide a value in the range (1-5)";
		}
	} while (TRUE);
}

