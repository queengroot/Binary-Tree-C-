//Kate Blunt
//COP2535.001
//Project 7
//Binary Tree Project

//To Do 
//Make EmplyeeInfo class/set up tree
//read from file
//populate the tree
//option to enter id number
//if the number is in the tree, display the name
//if not, let the user know
//loop so user can search again

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include<vector>

using std::vector;
using std::stringstream;
using std::ifstream;
using std::string;




//binary tree itself

class EmployeeInfo
{
private:

	int value;
	string firstName;
	string lastName;

	EmployeeInfo* left;
	EmployeeInfo* right;


	friend class BST;


public:

	//constructor
	EmployeeInfo(int val, string fn, string ln, EmployeeInfo* leftp = NULL, EmployeeInfo* rightp = NULL)
	{

		//incoming item from the file
		value = val;
		firstName = fn;
		lastName = ln;

		left = leftp;
		right = rightp;

	}

};

class BST
{

private:

	//void inorder(vector<T>&, EmployeeInfo<T>*);
	EmployeeInfo* tree;
	void insert(int, string, string);

	//input file
	ifstream inEmployee;

	//variable 
	int oneTwo = 0;

	//methods

	void display();
	void openFile();
	void testFile();
	void populate();
	void userEntry();
	void validateUser(int&);
	void validateNum(int&);
	void searchTree(int);
	void closeFile();
	void selectAgain();

public:

	BST();
	void driver();


};

/******************************Main***************************/

int main()
{

	//instantiate instant of the class
	BST treeObj;

	treeObj.driver();

	system("pause");

	return 0;
	

}


/**************************BST Methods**********************/

//constructor for BST
BST::BST()
{
	tree = NULL;
}

//display the title
void BST::display()
{

	using std::cout;
	using std::endl;

	cout << endl << " ***************Employee Search Program***************" << endl << endl;

}


//BST::open file
//open the input file

void BST::openFile()
{

	inEmployee.open("employee.txt");

	testFile();

}

//BST:: testFile

//test if random.txt opened properly

void BST::testFile()
{
	if (!inEmployee)
	{
		using std::cerr;
		using std::endl;

		std::cerr << "employee.txt did not open properly." << endl;
		system("pause");
		exit(777);

	}

}


//BST::CloseFile
//close the input file

void BST::closeFile()
{
	inEmployee.close();
}

//BST::populate
//read the values in and store in binary tree

void BST::populate()
{

	string content;

	while(getline(inEmployee, content))
	
	{
		//local variable 
		
		string fn;
		string ln;
		string line;

		stringstream iss(content);

		while (iss >> line >> fn >> ln)
		{
			int val;

			//cout << line << fn << ln;
			
			for (int i = 0; i < line.length(); i++)
			{
				//if there is a digit, convert to an int
				if (line[i] >= '0' && line[i] <= '9' || line[i] < '0')
				{

					 val = std::stoi(line);
				}
				
			}

			//insert the employee, first name, and last name into the tree
			insert(val, fn, ln);
			

		}
		

	}

}

//BST::Insert
//insert a leaf into the tree

void BST::insert(int v, string f, string l)
{
	//testing to see if data got here
	//cout << v << " " << f << " " << l << endl;

	//check to see if tree is empty:

	if (tree == NULL)
	{

		tree = new EmployeeInfo(v, f, l);

		//test to see the first node was added correctly
		//cout << " First node was added. " << endl << endl;


		return;

		
		
	}

	//if not the first node
	//use a p to search for the right place to insert
	//p will point to the node that will be the parent
	//of the node being added

	//Always leave tree alone

	EmployeeInfo* p = tree;

	while (p != NULL)
	{
		if (v <= p->value)
		{
			//v goes to the left of p 
			if (p->left == NULL)
			{
				p->left = new EmployeeInfo(v, f, l);

				//cout << "New node added" << endl;

				return;

			}
			else
				p = p->left;

		}

		else
		{

			if (p->right == NULL)
			{

				p->right = new EmployeeInfo(v, f, l);

				//cout << "New node added" << endl;

				return;
			}
			else
				p = p->right;
		}
		


	}

	

}


//BST::userInput
//ask the user to search the tree
void BST::userEntry()
{
	
		int num;
		using std::cin;
		using std::cout;
		using std::endl;

		//ask the user for an employee ID number

		cout << endl << " Please enter an Employee ID number: " << endl << endl;
		fseek(stdin, 0, SEEK_END);
		cout << " ";
		cin >> num;
		validateUser(num);
		searchTree(num);
		selectAgain();


}

//BST::validateUser
//validate the user has entered an integer and not a charcer
void BST::validateUser(int& n)
{
	using std::cin;
	while (!cin)
	{
		using std::cout;
		using std::endl;

		//validate the user entered an integer and not a character
		cout << " Please enter an integer: " << endl << endl;
		fseek(stdin, 0, SEEK_END);
		cin.clear();
		cout << " ";
		cin >> n;
		cout << endl << endl;
	}


}

//BST::searchTree
//search through the tree for the user's entry
void BST::searchTree(const int n)
{
	using std::cout;
	using std::endl;

	//set p to the tree in order to traverse the list
	EmployeeInfo* p = tree;


	//nothing in the tree
	if (p == NULL)
	{
		cout << " There are no nodes in the tree." << endl << endl;
		exit(777);
	}

	//the number searched is the root
	if (p->value == n)
	{
		//p->value because each node had three values, an int, first and last name
		cout << " The employee's name is: " << p->firstName << " " << p->lastName << endl << endl;
		return;

	}

	//search the tree
	while (p->value != n)
	{
		//if the value in the tree is greater than the number entered, go left
		if (p->value > n)
		{
			p = p->left;
		}

		//if not go right
		else
		{
			p = p->right;
		}

		if (p == NULL)
		{
			cout << " " << n << " is not a valid Employee ID." << endl << endl;
			return;
		}
		
	}

	cout  << " The employee's name is: " << p->firstName << " " << p->lastName << endl << endl;
	
	
}
//BST:: select Again
//ask if the user wants to find another employee
void BST::selectAgain()
{
	using std::cin;
	using std::cout;
	using std::endl;

	cout << endl << " Enter 1 to search for another employee. Enter 2 to exit: " << endl << endl;
	cout << " ";
	fseek(stdin, 0, SEEK_END);
	cin >> oneTwo;
	validateNum(oneTwo);

	if (oneTwo == 1)
		userEntry();
	else
		cout << endl << endl << " Thank you for using this program!" << endl;
		exit(777);


}

//BST:validate Char
//make sure the user entered y or n
void BST::validateNum(int& n)
{
	using std::cin;
	while (n != 1 && n != 2)
	{
		using std::cout; 
		using std::endl;

		//user can only enter 1 or 2
		cout << endl << " Please enter 1 or 2: " << endl << endl;
		cout << " ";
		fseek(stdin, 0, SEEK_END);
		cin.clear();
		cin >> n;
	}



}




//Bst:: driver
//order of operations

void BST::driver()
{

	//display the title
	display();


	//open the file
	openFile();

	//populate the file
	populate();

	//user 
	userEntry();


	//close the file
	closeFile();

}






















