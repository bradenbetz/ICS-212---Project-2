/*
 *    Name: Braden Betz
 *   
 *    Homework: Project 2
 *     
 *    Class: ICS 212
 *       
 *    Instructor: Ravi Narayan
 *         
 *    Date: November 13, 2018
 *           
 *    File: UI.cpp
 *             
 *    Description:  This file contiains the user interface to implement a Bank Database Application.               
 */

#include <iostream>
#include <istream>
#include "llist.h" 

/*
 *    Function Name: main
 *   
 *   
 *    Description:  This main holds the User Interface to implement a Bank Database Application
 *      
 *       
 *    Parameters: int argc : Holds number of command line arguements |  char argv [] holds the command line arguement that was typed
 *         
 *          
 *    Return Values: 0 : Success
 *            
 */

using namespace std;

int main(int argc, char ** argv)
{
    #ifdef debug
        cout << "You are now in DEBUG mode\n";
    #endif
 
    int check;
   
    llist list1;
    llist copy(list1);
      
    check = 1;
      
    cout << "Welcome to the Bank Database, please use numbers 1 through 5 to select an option from the Database\n";
     
    while (check == 1)
    {
        int choice;
        choice = -1;

        cout << " [1] Add a record \n [2] Print a record \n [3] Print all available records \n [4] Delete a Record \n [5] Reverse the database \n [6] Quit\n" << "Enter your option here\n";
        
        cin >> choice;
        
        while (!cin.good())
        {
            cout << "Invalid choice, please try again\n";

            cin.clear();
            cin.ignore(256, '\n');

            cin >> choice;

        }

        if (choice == 1)
        {
            int accountno;
            char name[25];
            char address[80];
   
            cin.clear();
            cin.ignore(256, '\n');
 
            cout << "Please enter your address below, press the '/' key to finish!\n";
            cin.getline(address, 80, '/');

            cin.clear();
            cin.ignore(256, '\n'); 
 
            cout << "Please enter your Account Number here: \n";
            cin >> accountno;
            
            while (!cin.good())
            {
                cout << "Invalid Account Number, please try again\n";

                cin.clear();
                cin.ignore(256, '\n');

                cin >> accountno;

            }

            cin.clear();
            cin.ignore(256, '\n');
 
            cout << "Please enter your name here:\n"; 
            cin.get(name, 25);

            cin.clear();
            cin.ignore(256, '\n');

            list1.addRecord(accountno, name, address);

        } else if (choice == 2) {

            int accountno;
            int check;
     
            cout << "Enter a account number to print: \n";
            cin >> accountno;
            
            while (!cin.good())
            {
                cout << "Invalid Account Number, please try again\n";

                cin.clear();
                cin.ignore(256, '\n');

                cin >> accountno;

            }

            cin.clear();
            cin.ignore(256, '\n');

            check = list1.printRecord(accountno);
 
            if (check == 0)
            {
                cout << "Here is your record\n";

            } else {
 
                cout << "The record with accountno " << accountno <<  " does not exist in the database\n";
 
            }
     
        } else if (choice == 3) {
       
            cout << list1;
            
        } else if (choice == 4) {
  
            int accountno;
            int check;

            cout << "Enter an account number to delete from the database\n";
            cin >> accountno;
            
            while (!cin.good())
            {
                cout << "Invalid Account Number, please try again\n";
                
                cin.clear();
                cin.ignore(256, '\n');
                
                cin >> accountno; 
                 
            }
           
            cin.clear();
            cin.ignore(256, '\n');
            
            check = list1.deleteRecord(accountno);
           
            if (check == 0)
            {
                cout << "The record with account number " << accountno << " has been deleted\n";
       
            } else {

                cout << "The database is empty, or the record with account number " << accountno << " does not exist\n";  

            }
 
        } else if (choice == 5) {

            list1.reverse();
        
        } else if (choice == 6) {
         
           cout << "Thank you for using the Bank Database, you have exited the program!\n"; 
           check = 0;
        
        } else {

            cout << "Invalid choice, please try again\n";
    
        }

    }
    
return 0;

}

