#include <iostream>
#include <string>
#include<vector>
#include<fstream>
#include <sstream>
using namespace std;

//allow the user to :

//Enter a description, amount, and date

//Store it in a struct like :


struct Expense
{
	string description;
	double amount;
	string date;
};




void saveExpensesToFile(const vector<Expense>& expenses)
{
	ofstream outFile("expenses.txt");

	for (const Expense& e : expenses)
	{
		outFile << e.description << "," << e.amount << "," << e.date << "\n";
	}

	outFile.close();
}


void loadExpensesFromFile(vector<Expense>& expenses)
{
	ifstream inFile("expenses.txt");
	string line;

	while (getline(inFile, line))
	{
		stringstream ss(line);
		string desc, amtStr, date;

		getline(ss, desc, ',');
		getline(ss, amtStr, ',');
		getline(ss, date);


		double amount = stod(amtStr);
		expenses.push_back(Expense{ desc,amount,date });

	}
	inFile.close();
}




double getValidAmount() {
	double amount;

	while (true) {
		cout << "Please enter the Amount: ";
		if (cin >> amount) {
			// Success: we got a valid number
			break;
		}
		else {
			// Fail: clear and ignore bad input
			cout << "Invalid input. Please enter a valid number.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

	// Clear any remaining input (just in case)
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return amount;
}

//1. Add Expense
//2. View Expenses
//3. Exit


int main()
{
	vector<Expense> ExpenseList;

	loadExpensesFromFile(ExpenseList);
	bool running = true;
	int option;
	cout << "Welcome to the Expense Channel, please choose from the following options..." << endl;
	while (running)
	{
		cout << "1. Add Expense" << endl;
		cout << "2. View Expenses" << endl;
		cout << "3. Total Expenses" << endl;
		cout << "4.Exit" << endl;
		
		cin >> option;

		if (option == 1)
		{

			


			string new_description;
			double new_amount;
			string new_date;
			

			cout << "Please enter the Description: " << endl;
			cin.ignore(); // Clear the leftover newline
			getline(cin, new_description);
			
			/*cout << "Please enter the Amount: " << endl;*/ 
			new_amount = getValidAmount();

			cout << "Please enter the Date: " << endl;
			cin.ignore();
			getline(cin, new_date);
			
			Expense new_exspense = { new_description, new_amount, new_date };
			ExpenseList.push_back(new_exspense);
		}

		else if (option == 2)
		{
			if (ExpenseList.empty())
			{
				cout << "Sorry There is no data. please enter some to use this function. " << endl;

			}

			else {
				for (const auto& expense : ExpenseList) {
					cout << "Description: " << expense.description << endl;
					cout << "Amount: " << expense.amount << endl;
					cout << "Date: " << expense.date << endl;
					cout << "-------------------------" << endl;
				}
			}
		}


		else if (option == 3)
		{
			double total = 0;
			for (const auto& e : ExpenseList)
			{
				
				total += e.amount;

				
			}
			cout << "The Toal Expense to pay is: " << total << endl;
		}

		else if(option == 4)
		{
			cout << "Thanks for using this service, GoodBye!" << endl;
			saveExpensesToFile(ExpenseList);
			running = false;
		}



	}

	

}