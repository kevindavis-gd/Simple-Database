#pragma once
#include <string>
#include <fstream>

using namespace std;

//****************************NODE STRUCT**************************************
struct node
{
	double gpa;
	string lastName, firstName, IDnumber;
	// pointer to point to next node
	node *next;

	node()
	{
		next = NULL;
	}

	node(string LName, string fName, string ID, double grade, node *nxt = NULL)
	{
		lastName = LName;
		firstName = fName;
		IDnumber = ID;
		gpa = grade;
		next = nxt;
	}
};

//**************************Class*******************************
class linkedList
{
public:
	linkedList();
	~linkedList();
private:
	node *head;
public:
	void insert(string ln, string fn, string ID, double g);
	void print();
	bool del(string ID);
	void search(string ID);
	void outfile(string filename, int amount);
};

