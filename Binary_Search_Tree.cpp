// Binary_Search_Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
	Node* left;
	Node* right;
	Node* parent;
	int data;
};


struct Print
{
	Print* prev;
	string str;

	Print(Print* prev, string str)
	{
		this->prev = prev;
		this->str = str;
	}
};


bool isEmpty(Node *root)
{
	if (root == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}

}

Node* find(Node* p, int k)
{
	while (p && p->data != k)
	{
		p = (k < p->data) ? p->left : p->right;
	}

	return p;
}

void insert(Node*& root, int values)
{
	Node* w, * p;

	w = new Node;

	w->left = w->right = nullptr;
	w->data = values;

	p = root;

	if (!p)
	{
		root = w;
	}
	else
	{
		while (1)
			if (values < p->data)
			{
				if (!p->left)
				{
					p->left = w;
					break;
				}
				else p = p->left;
			}
			else
			{
				if (!p->right)
				{
					p->right = w;
					break;
				}
				else p = p->right;
			}
	}

	w->parent = p;
}


Node* leftMost(Node* root)
{
	if (!root)
	{
		return nullptr;
	}
	while (root->left)
	{
		root = root->left;
	}

	return root;
}


Node* deleteNode(Node* root)
{
	if (!root->left)
	{
		Node* child = root->right;
		root = nullptr;
		return child;
	}
	else if (!root->right)
	{
		Node* child = root->left;
		root = nullptr;
		return child;
	}

	Node* next = leftMost(root->right);

	root->data = next->data;

	root->right = deleteNode(root->right);

	return root;
}



Node* removeRange(Node* node, int low, int high)
{
	if (!node)
	{
		return nullptr;
	}

	node->left = removeRange(node->left, low, high);

	node->right = removeRange(node->right, low, high);

	if (node->data >= low && node->data <= high)
	{
		return deleteNode(node);
	}

	return node;
}



void helpshow(Print* p)
{
	if (p == nullptr)
	{
		return;
	}

	helpshow(p->prev);

	cout << p->str;
}



void showtree(Node* root, Print* prev, bool isLeft)      // INORDER
{
	if (root == nullptr)
	{
		return;
	}

	string prev_str = "    ";
	Print* trunk = new Print(prev, prev_str);

	showtree(root->right, trunk, true); 

	if (!prev)
	{
		trunk->str = "---";
	}
	else if (isLeft)
	{
		trunk->str = ".---";
		prev_str = "   |";
	}
	else
	{
		trunk->str = "`---";
		prev->str = prev_str;
	}

	helpshow(trunk);
	cout << root->data << endl;

	if (prev)
	{
		prev->str = prev_str;
	}
	trunk->str = "   |";

	showtree(root->left, trunk, false); 
	
	
}




int main()
{
	int option = 0;
	int low = 0;
	int high = 0;
	ifstream file("test.txt");
	int input;
	vector<int> data;
	if (file.good() == 0)
	{
		cerr << "Brak pliku tekstowego w katalogu\n";
	}
	else
	{
		while (file >> input)
		{
			data.push_back(input);
		}
	}

	Node* root = nullptr;

	do
	{
		cout << " -------------------------------\n";
		cout << "|             MENU              |\n";
		cout << "|            GLOWNE             |\n";
		cout << " -------------------------------\n";
		cout << "|        1. Insert Node         |\n";
		cout << "|        2. Show BST values     |\n";
		cout << "|        3. Delete Node         |\n";
		cout << "|        4. Clear               |\n";
		cout << "|        0. Exit program        |\n";
		cout << "|_______________________________|\n";
		cout << "\n";
		cout << "Wprowadz numer opcji: ";
		cin >> option;
		switch (option)
		{
		case 0:
		{
			cout << "Wyjscie z programu\n";
			break;
		}
		case 1:
		{
			for (int i = 0; i <data.size(); ++i)
			{
				insert(root, data[i]);
			}

			break;
		}
		case 2:
		{
			if (!(isEmpty(root)))
			{
				showtree(root, nullptr, false);
				break;
			}
			else
			{
				cout << "Brak drzewa \n";
				break;
			}
		}
		case 3:
		{
			if (!(isEmpty(root)))
			{
				cout << "Wprowadz przedzial do usuniecia:";
				cin >> low >> high;
				cout << "Twoj przedzial to [ " << low << ", " << high << " ]\n";
				root = removeRange(root, low, high);
				break;
			}
			else
			{
				cout << "Drzewo jest puste brak elementow do usuniecia\n";
				break;
			}
		}
		case 4:
		{
			system("cls");
			break;
		}
		default:
		{
			cout << "Wprowadziles numer " << option << ". Sprobuj ponownie\n";
			break;
		}
		}



	} while (option != 0);


	return 0;
}

