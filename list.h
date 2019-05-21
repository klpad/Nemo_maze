#ifndef LIST_H
#define LIST_H

#include<iostream>
#include<assert.h>
// Linked List object that maintains both head and tail pointers
// and the size of the list.  Note that you have to keep the head,
// tail and size consistent with the intended state of the List 
// otherwise very bad things happen. 
template<typename Type>
class List {
public:

	List();
	~List();

	void	printItems() const;
	bool	isEmpty() const;

	void	addToFront(Type item);
	void	addToRear(Type item);
	void	addItem(int index, Type item);

	// Note that the user must first ensure the list is not empty
	// Prior to calling these functions.
	Type	getFront() const;
	Type	getRear() const;
	Type	getItem(int index) const;


	int		getSize() const;
	int		findItem(Type item) const;

	bool	deleteFront();
	bool	deleteRear();
	bool	deleteItem(int index);

private:
	// Forward declare the nodes for our List.
	// Will be implemented along with list's
	// member functions
	class Node;

	// We'll have both head and tail points for 
	// Fast insertion/deletion from both ends.
	Node*	head;
	Node*	tail;

	// Keep track of size of list
	int		size;
};


// List Implementation
//
//  Since List is a template class, which is not an actual 
//  class yet, not until we actually instantiate the list, 
//  we need to keep the class implementation together with 
//  the definition.  There are ways to simulate having 
//  separate "implementation/definition" with templates, 
//  but they aren't necessary and can be confusing.
//

// Node definition
//		Already Implemented, nothing to do here but to use it.
template<typename Type>
class List<Type>::Node {
public:
	Node() :next(nullptr) {}
	Node(Type item, Node* next) : item(item), next(next) {}

	Type  item;
	Node* next;
};

// List default constructor
//		Set head and tail pointer to point to nothing, size is zero
template<typename Type>
List<Type>::List() {

	head = nullptr;
	tail = nullptr;
	size = 0;

}

// List destructor
//		Traverses the nodes and deletes them without causing memory leak
template<typename Type>
List<Type>::~List() {

	if (head == nullptr)					//when is empty list
		return;

	Node *p = head;
	while (p != nullptr)     //doing traverse and delete the node until the last node
	{
		Node *temp = p->next;
		delete p;
		p = temp;
	}

}

// List printItems
//		Traverses list and prints items in list to console followed by newline.
//		Assumes << is overloaded for object Type.
//		Indicates the Front and Rear of list, for example:
//
//			Front (3,4) (2,4) (1,1) Rear
//
template<typename Type>
void List<Type>::printItems() const {

	if (isEmpty())
	{
		return;
	}
	else
	{
		std::cout << "Front ";

		Node *p = head;
		while (p != nullptr)									//do traversal and print the item 
		{
			std::cout << p->item;
			std::cout << " ";
			p = p->next;
		}

		std::cout << "Rear";
	}
	std::cout << std::endl;

}

// List isEmpty
//		returns true if there are no items in the list
//		otherwise returns false.
template<typename Type>
bool List<Type>::isEmpty() const {

	if (head == nullptr)
		return true;
	else
		return false;

}


// List addToFront
//		Adds a new item to the front of the list
//		updates head, tail, and size accordingly.
//		
//		Two cases to consider: If the list is empty 
//		and if the list has items already it.
//
template<typename Type>
void List<Type>::addToFront(Type item) {

	if (isEmpty())                              //when is empty list, creating the new node and let head & tail ponit to it
	{
		Node *p;
		p = new Node(item, nullptr);
		head = p;
		tail = p;
		size++;
	}
	else
	{
		Node *p;
		p = new Node(item, head);		//creating a new node and let it's next value point to head;
		head = p;					 //change the head point to the new node, no need to change the tail
		size++;
	}

}

// List addToRear
//		Adds a new item to the rear of the list
//		updates head, tail, and size accordingly.
//
//		Two cases to consider: If the list is empty 
//		and if the list has items already it.
//
template<typename Type>
void List<Type>::addToRear(Type item) {

	if (isEmpty())                              //when is empty list, creating the new node and let head & tail ponit to it
	{
		Node *p;
		p = new Node(item, nullptr);
		head = p;
		tail = p;
		size++;
	}
	else
	{
		Node *p;
		p = new Node(item, nullptr);           //make the last node's next point to new Node & change tail point to new node
		tail->next = p;
		tail = p;
		size++;
	}

}

// List addItem
//		Adds a new item at the index indicated
//		updates head, tail, and size accordingly.
//
//		If the index is less than or equal to zero 
//			add to the front.
//		If the index is greater than or equal to
//			the size of the list, add to the rear.
//		All other cases, add the item to the appropriate
//			location
//
template<typename Type>
void List<Type>::addItem(int index, Type item) {

	if (index <= 0)                          //add to front
	{
		addToFront(item);
	}
	else if (index >= size)                  //add to rear
	{
		addToRear(item);
	}
	else
	{
		Node *p = head;
		for (int i = 1; i < index; i++)        //tranverse to the adding location
		{
			p = p->next;
		}
		Node *temp = new Node(item, p->next);   //inserting the item
		p->next = temp;
		size++;
	}

}

// List getFront
//		returns the first item in the list.
//
template<typename Type>
Type List<Type>::getFront() const {
	// Force check that the head is pointing to a Node
	// Typical solution for deployement code is to throw
	// exceptions, but since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(head != nullptr);
	return head->item;

	//Type dumbyVariableSoCodeCompiles_DontActuallyUseThis
		//return dumbyVariableSoCodeCompiles_DontActuallyUseThis;

}

// List getRear
//		returns the last item in the list
//
template<typename Type>
Type List<Type>::getRear() const {

	// Force check that the tail is pointing to a Node
	// Typical solution for deployement code is to throw
	// exceptions, but since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(tail != nullptr);

	return tail->item;

	Type dumbyVariableSoCodeCompiles_DontActuallyUseThis;
	return dumbyVariableSoCodeCompiles_DontActuallyUseThis;
}

// List getItem
//		returns the item at index
//
template<typename Type>
Type List<Type>::getItem(int index) const {

	// Force index to be correct before getting the Item
	// Typical solution for deployement code is to throw
	// exceptions, but since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(index >= 0 && index < size);

	Node *p = head;
	for (int i = 0; i < index; i++)        //tranverse to the index location
	{
		p = p->next;
	}
	return p->item;

	Type dumbyVariableSoCodeCompiles_DontActuallyUseThis;
	return dumbyVariableSoCodeCompiles_DontActuallyUseThis;
}

// List getSize
//		return the size of the list
template<typename Type>
int List<Type>::getSize() const {

	return size;

}

// List findItem
//		Traverses the list to see if the item is in the list
//		if it is return the index of that item, otherwise
//		return -1. Assumes the == operator is overloaded for
//		object Type.
template<typename Type>
int List<Type>::findItem(Type item) const {

	int index = 0;
	Node *p = head;
	while (p != nullptr)
	{
		if (p->item == item)
		{
			return index;
		}
		p = p->next;
		index++;
	}

	return -1;
}

// List deleteFront
//		Removes the first item in the list returns true
//		if the item was deleted, false otherwise. Updates 
//		head, tail, and size accordingly.
//
//		Must consider at least two cases where the list: is empty, 
//		has one or more items.
//		
template<typename Type>
bool List<Type>::deleteFront() {

	if (isEmpty())            //when is empty list, nothing to delete
	{
		return false;
	}
	else if (getSize() == 1)     //when there is only one item
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		size = 0;
		return true;
	}
	else                                  //when more than 1 item in the list
	{
		Node *p = head;
		head = head->next;
		delete p;
		size--;
		return true;
	}

}
// List deleteRear
//		Removes the last item in the list returns true
//		if the item was deleted, false otherwise. Updates 
//		head, tail, and size accordingly.
//
//		Must consider at least three cases where the list: is empty, 
//		has one item, has two or more items.
//	
template<typename Type>
bool List<Type>::deleteRear() {

	if (isEmpty())            //when is empty list, nothing to delete
	{
		return false;
	}
	else if (getSize() == 1)     //when there is only one item
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		size = 0;
		return true;
	}
	else                                  //when more than 1 item in the list
	{
		Node *p = head;
		while (p->next->next != nullptr)        //traversal to the node before the last one
		{
			p = p->next;
		}

		delete tail;                    //delete the last element
		tail = p;
		tail->next = nullptr;
		size--;
		return true;
	}

}

// List deleteItem
//		Removes the item at the index returns true
//		if the item was deleted, false otherwise. Updates 
//		head, tail, and size accordingly. If the index is
//		out of bounds return false.
//
template<typename Type>
bool List<Type>::deleteItem(int index) {

	if (isEmpty())                   //when is empty list, nothing to delete
	{
		return false;
	}
	else if (index >= getSize() || index < 0)
	{
		return false;
	}
	else
	{
		Node *p = head;
		for (int i = 1; i < index; i++)     //do traversal, stop one node above the target
		{
			p = p->next;
		}
		Node *killMe = p->next;
		p->next = p->next->next;
		delete killMe;
		size--;
		return true;
	}
}

#endif//LIST_H