#include <iostream>
#include <string>

using namespace std;

struct Node
{
	int key;
	string name;
	Node* next;
};

class LinkedList
{
private:
	Node* head;
	int listLength;
public:
	LinkedList()
	{
		head = NULL;
		listLength = 0;
	};
	Node* previous(Node* node)
	{
		Node* temp = head;
		Node* previous = head;
		if (node == head)
			return NULL;
		while (temp != node)
		{
			previous = temp;
			temp = temp->next;
		}
		return previous;
	}
	Node* getIndex(int n)
	{
		Node* temp = head;
		for (int i = 0; i < n; i++)
		{
			temp = temp->next;
		}
		return temp;
	}
	int size()
	{
		return listLength;
	}
	void push_front(string Name, int Key)
	{
		Node* NewNode = new Node;
		NewNode->key = Key;
		NewNode->name = Name;
		NewNode->next = head;
		head = NewNode;
		listLength++;
	}
	void pop_front()
	{
		if (listLength > 0)
		{
			head = head->next;
			listLength--;
		}
	}
	int top_front()
	{
		return head->key;
	}
	bool find(string value)
	{
		if (listLength > 0)
		{
			Node* temp = head;
			for (int i = 0; i < listLength; i++)
			{
				if (temp->name == value)
				{
					return true;
				}
				temp = temp->next;
			}
		}
		return false;
	}
	bool empty()
	{
		if (listLength == 0)
			return true;
		else
			return false;
	}
	void display()
	{
		Node* current = head;
		while (current != NULL)
		{
			cout << current->name << endl;
			current = current->next;
		}
	}
	void erase(string value)
	{
		Node* temp = head;
		if (temp->name == value)
		{
			pop_front();
		}
		else
		{
			for (int i = 0; i < listLength; i++)
			{
				if (temp->name == value)
				{
					previous(temp)->next = temp->next;
					listLength--;
					break;
				}
				temp = temp->next;
			}
		}
	}
	string name()
	{
		return head->name;
	}
	void set_name(string Name)
	{
		head->name = Name;
	}
};
