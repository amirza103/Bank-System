/*
Author: Ali Mirza

Date: April 20, 2020

Function: Bank accounts and Bank management system

*/
/* Header File*/

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

/*Class used in project*/

class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();
	void show_account() const;
	void modify();
	void dep(int);
	void draw(int);
	void report() const;
	int retacno() const;
	int retdeposit() const;
	char rettype() const;

};

void account::create_account()
{
	cout << "\nEnter The account No. :";
	cin >> acno;
	cout << "\n\nEnter The Name of the account Holder : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nEnter Type of The account (C/S) : ";
	cin >> type;
	type = toupper(type);
	cout << "\nEnter the Initial amount( >=250 for saving and >=1000 for current ) : ";
	cin >> deposit;
	cout << "\n\n\nAccount Created...";
	
}

void account::show_account() const
{
	cout << "\nAccount No. :" << acno;
	cout << "\nAccount Holder NAme : ";
	cout << name;
	cout << "\nType of Account : " << type;
	cout << "\nBalance Amount : " << deposit;
}

void account::modify()
{
	cout << "\nAccount No. : " << acno;
	cout << "\nModify The Account Holders Name : ";
	cin.ignore();
	cin.getline(name, 50); \
	cout << "\nModify The Type of Account (C/S) : ";
	cin >> type;
	type = toupper(type);
	cout << "\nModify The Accounts Balance Amount : ";
	cin >> deposit;
}

void account::dep(int x)
{
	deposit += x;
}

void account::draw(int x)
{
	deposit -= x;
}

void account::report() const
{
	cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}

/* declaration of the fucntion*/

void write_account(); // writes record into binary file
void display_sp(int); //displays the account info given by user
void modify_account(int); //modifies the acount on file
void delete_account(int); //deletes the account on file
void display_all(); //displays all the account details
void deposit_withdraw(int, int); //withdraw and deposit function for the account chosen
void intro(); // intro screen 

// main function of the program//

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout << "\n\n\n\tMAIN MENU";
		cout << "\n\n\t01. NEW ACCOUNT";
		cout << "\n\n\t02. DEPOSIT AMOUNT";
		cout << "\n\n\t03. WITHDRAW AMOUNT";
		cout << "\n\n\t04. BALANCE ENQUIRY";
		cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout << "\n\n\t06. CLOSE AN ACCOUNT";
		cout << "\n\n\t07. MODIFY AN ACCOUNT";
		cout << "\n\n\t08. EXIT";
		cout << "\n\n\tSelect Your Option (1-8) ";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout << "\n\n\tEnter The Account No. : "; cin >> num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout << "\n\n\tEnter The Account No. : "; cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout << "\n\n\tEnter The Account No. : "; cin >> num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout << "\n\n\tEnter The Account No. : "; cin >> num;
			delete_account(num);
			break;
		case '7':
			cout << "\n\n\tEnter The Account No . : "; cin >> num;
			modify_account(num);
			break;
		case '8':
			cout << "\n\n\tThanks for using bank managment system";
			break;
		default:cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != '8');
	return 0;
}

/*Function to write in the file*/

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
	outFile.close();

}

/*Function that reads the specific record from file*/

void display_sp(int n)
{
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be opened! Press any Key...";
		return;
	}
	cout << "\nBALANCE DETAILS\n";

	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.retacno() == n)
		{
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n\nAccount number does not exist";
}

/*Modifies the record on file*/

void modify_account(int n)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be opened! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			cout << "\n\nEnter The Details of Account" << endl;
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}

/* Deleting records on file */

void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be opened! Press any Key...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.retacno() != n)
		{
			outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << "\n\n\tRecord Deleted...";
}

/*Displays all accounts on deposit list*/

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be opened! Press any Key...";
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << "=======================================\n";
	cout << "A/c no.   NAME			Type  Balance\n";
	cout << "=======================================\n";
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

/*Deposit and withdraw amount function */

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be opened! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retacno() == n)
		{
			ac.show_account();
			if (option == 1)
			{
				cout << "\n\n\tTO DEPOSIT AMOUNT ";
				cout << "\n\nEnter The amount being deposited";
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tTO WITHDRAW AMOUNT";
				cout << "\n\nEnter the amount being withdrawn";
				cin >> amt;
				int bal = ac.retdeposit() - amt;
				if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
					cout << "Insufficient Balance";
				else
					ac.draw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}

/* Introduction */

void intro()
{
	cout << "\n\n\n\t BANK";
	cout << "\n\n\tMANAGEMENT";
	cout << "\n\n\tSYSTEM";
	cout << "\n\n\n\nMADE BY : ALI MIRZA";
	cout << "\n\nSCHOOL : SCHOOLCRAFT COLLEGE";
	cin.get();
}

/*End of the project*/
