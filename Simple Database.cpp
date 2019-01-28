#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>
#include "linkedList.h"
#include <stdio.h>

using namespace std;

// ******************Function Prototypes**************************
void openFile(ifstream &input, ofstream &output, string &filename);
void GetData(ifstream &input, linkedList &list, int &amount);
void AddRecord(ifstream &input, linkedList &list, int &amount);
void DeleteRecord(ifstream &input, linkedList &list, int &amount);
void Search(ifstream &input, linkedList &list);
void Selection(ifstream &input, ofstream &output, linkedList &list,
   	 int &amount, string filename, bool &quit);
void Save(ifstream &input, ofstream &output, linkedList &list,
	 int &amount, string filename);
void HeadingScreen();
void HeadingOutput(ofstream &output);

//****************************MAIN***************************
int main()
{
	string filename;
	ifstream input;
	ofstream output;
	linkedList list;
	bool quit = 0;
	int amount = 0;
	
	HeadingScreen();
	openFile(input, output, filename);
	GetData(input, list, amount);
	//loop to keep menu appearing 
	while (quit == 0)
	{
		//clear screen from previous data to avoid clutter
		system("cls");
		//run heading again because it was cleared
		HeadingScreen();
		Selection(input, output, list, amount, filename, quit);
		system("pause");
	} 
	// if the program is stopped without saving then close the file
	if (input.is_open())
		input.close();

	//inform the user that the program has been closed 
	//either from the above code or from within a function
	cout << setw(45) << "PROGRAM CLOSED ! \n\n";
	system("pause");
	return 0;
}


//******************************OPEN FILE********************************
void openFile(ifstream &input, ofstream &output, string &filename)
{
	// create input file
	cout << setw(50) << "Please Enter Name of Input File \n";
	cout << setw(35) << " Enter Here: ";
	cin >> filename;
	input.open(filename);
	// if its incorrect file name send error message
	if (input.fail())
	{
		cerr << "File not found....Program will now close. \n";
		system("pause");
		exit(1);
	}
}


//******************************GET DATA*******************************
void GetData(ifstream &input, linkedList &list, int &amount)
{
	// input first number into amount
	input >> amount;

	//loop through each item and place it into the list
	for (int x = 0; x < amount; x++)
	{
		string fn, ln, ID;
		double gpa;
		input >> ln >> fn >> ID >> gpa;
		list.insert(ln, fn, ID, gpa);
	}
}


//******************************ADD RECORD*****************************
void AddRecord(ifstream &input, linkedList &list, int &amount)
{
	string ln, fn, ID;
	double gpa;

	cout << "First Name: "; 
	cin >> fn;
	cout << endl;

	cout << "Last Name: ";
	cin >> ln;
	cout << endl;

	cout << "ID Number: ";
	cin >> ID;
	cout << endl;

	cout << "GPA: ";
	cin >> gpa;
	cout << endl;

	list.insert(ln, fn, ID, gpa);
// increase the amount of items in the list
	amount++;

	cout << setw(43) << " Item Added sucessfully \n";

}


//*****************************DELETE RECORD**************************
void DeleteRecord(ifstream &input, linkedList &list, int &amount)
{
	string ID;
	bool del;

	cout << setw(50) << " Enter ID of Record to be deleted \n";
	cout << setw(35) << " ID: ";
	cin >> ID;

	//returns a bool to del
	del = list.del(ID);

	if (del == 1)
	{
		cout << setw(23) << " ID: " << ID << " has been deleted \n";
		amount--;
	}
	
	else
		cout << setw(30) << "" << " ID: " << ID <<" Not Found \n";
}


//******************************SEARCH********************************
void Search(ifstream &input, linkedList &list)
{
	string ID;

	cout << setw(48) << " Enter ID of Data to Be Found \n";
	cout << setw(35) << "ID: ";
	cin >> ID;

	list.search(ID);
}


//*****************************SELECTION******************************
void Selection(ifstream &input, ofstream &output, linkedList &list,
	int &amount, string filename, bool &quit)
{
	// used string to capture all errors, including char inputs
	string choice;
	// user will input their menu options
	cout <<"\n-------------------------------------------------------------"
		 <<"---------------\n"
		 << setw(47) << " SELECT A NUMBER BELOW: \n" << left <<"  "
		 << setw(23) << " Add Record:[1] "
		 << setw(23) << " Delete Record:[2] "
		 << setw(23) << " Search Records:[3] \n"
		 << setw(23) << " Display records:[4] "
		 << setw(23) << " Save Changes:[5] "
		 << setw(23) << " QUIT:[6] ";

	cout << "\n\n" << right << setw(38) << "Selection: ";
	cin >> choice;
	cout << setw(35) << " * \n";
	cout << setw(35) << " * \n";
	cout << setw(35) << " * \n";

	//actions based on menu choices
	if (choice == "1")
		AddRecord(input, list, amount);
	else if (choice == "2")
		DeleteRecord(input, list, amount);
	else if (choice == "3")
		Search(input, list);
	else if (choice == "4")
	{
		cout << "Number of Records in List: " << amount << endl;
		list.print();
	}
	else if (choice == "5")
		Save(input, output, list, amount, filename);
	else if (choice == "6")
	{
		quit = 1;
		cout << setw(52) << " You are about to quit....Good Bye \n\n";
	}

	// if user selects number out of range
	else
	{
		cerr << setw(60) << "You Did Not Select an Appropriate Number!\n";
	}
		
}


//*****************************SAVE CHANGES***************************
void Save(ifstream &input, ofstream &output, linkedList &list,
	int &amount, string filename)
{
	//close input file before deleting
	input.close();
	//delete input file
	remove(filename.c_str());
	//print heading to the output file
	//HeadingOutput(output);
		/*Heading is commented out because if it was left in, the 
		progrom would not beable to run the file a second time 
		because the first number would no longer be the 
		amount of records*/

	//create new file with same name and write contents to it
	list.outfile(filename, amount);
	cout << setw(40) << " FILE SAVED !\n";
}


//*****************************COUT HEADING***************************
void HeadingScreen()
{
	cout  << "This program allows a user to edit a file with records. \n"
		 << "it uses linked list to store the files and the user can view, \n"
		 << "delete or add data to the list, which can then be stored at \n"
		 << "the users discression back to the original file.\n"
		 << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n";
}


//***************************OUTPUT HEADING************************
void HeadingOutput(ofstream &output)
{
	output  << "This program allows a user to edit a file with records. \n"
	   	<< "it uses linked list to store the files and the user can view, \n"
		<< "delete or add data to the list, which can then be stored at \n"
	 	<< "the users discression back to the original file.\n"
		<< "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n";
}
