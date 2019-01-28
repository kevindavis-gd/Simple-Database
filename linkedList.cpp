#pragma once
#include "linkedList.h"
#include <string>
#include "linkedList.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

linkedList::linkedList()
{
	head = NULL;
}

linkedList::~linkedList()
{
	node *p = head;
	while (p != NULL)
	{
		head = p->next;
		delete(p);
		p = head;
	}
}



//****************************INSERT****************************
void linkedList::insert(string ln, string fn, string ID, double g)
{
	
	node *p, *c;
	//creates a pointer that points to a new node
	node *copy = new node(ln, fn, ID, g);

	if (head == NULL || copy->lastName < head->lastName
		|| copy->lastName == head->lastName &&
		   copy->firstName < head->firstName)
	{
		copy->next = head;
		head = copy;
	}

	else
	{
		p = head;
		c = head;
		
		while (c !=NULL && copy->lastName > c->lastName
			  || c != NULL && copy->lastName == c->lastName 
			  && copy->firstName > c->firstName)
		{
			p = c;
			c = c->next;
		}

		p->next = copy;
		p = copy;
		copy->next = c;
	}

}


//****************************PRINT****************************
void linkedList::print()
{
	node *p;
	// Set the pointer to the beginning of the list
	p = head;
	// if the list is empty 
	if (p == NULL)
		cout << setw(43) << "THIS LIST IS EMPTY \n";
	// do this until the p points to null
	while (p != NULL)
	{
		cout << endl << left
			 << setw(12) << p->lastName << "  "
			 << setw(12) << p->firstName << "  "
			 << setw(10) << p->IDnumber << "  "
			 << setw(4) << fixed << setprecision(2) << p->gpa << "  "
			 << endl << right;

		p = p->next;
	}
	cout << "\n";
}


//****************************DELETE****************************
bool linkedList::del(string ID)
{
	node *p = head, *c = head;
	while (c != NULL && c->IDnumber != ID)
	{
		p = c;
		c = c->next;
	}
	if (c == NULL)
	return 0;
	else		
	{							
		if (c == head)	
		{							
			head = c->next; 
			delete(c);			
			p = c = NULL;
		}
		else
		{						
			p->next = c->next;
			delete(c);
			c = NULL;
		}
		return 1;
	}

}


//****************************SEARCH****************************
void linkedList::search(string ID)
{
	node *p = head, *c = head;
	while (c != NULL && c->IDnumber != ID)
	{
		p = c;
		c = c->next;
	}
	// if th eitem not in list print not found
	if (c == NULL)
		cout << endl << setw(42) << " Record Not Found !\n";
	// if item fount, print out the contents
	else
	{
		cout << endl << left
			<< setw(12) << p->lastName << "  "
			<< setw(12) << p->firstName << "  "
			<< setw(10) << p->IDnumber << "  "
			<< setw(4) << fixed << setprecision(2) << p->gpa << "  "
			<< endl;
	}
}


//****************************OUTPUT****************************
void linkedList::outfile(string filename, int amount)
{
	ofstream output;
	output.open(filename);

		// Creates a pointer to a node
		node *p;
		// Set the pointer to the beginning of the list
		p = head;
		output << amount << endl;
		while (p != NULL)
		{
			output  << endl << left
					<< setw(12) << p->lastName << "  "
					<< setw(12) << p->firstName << "  "
					<< setw(10) << p->IDnumber << "  "
					<< setw(4) << fixed << setprecision(2) << p->gpa << "  "
					<< endl;;
			p = p->next;
		}
		output << "\n";
		output.close();
	}
