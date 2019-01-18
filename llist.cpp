#include <cstddef>
#include <iostream>
#include <fstream>
#include "llist.h"
#include <string.h>
#include <string>
#include <sstream>

/*
 *     Function name: llist
 *
 *     
 *     Description: Constructor that takes no parameters for the llist class
 *
 *
 *     Return values: None
 */

llist :: llist()
{
    this->start = NULL;  
    readfile();   
}

/*
 *    Function name: llist
 *
 *
 *    Description: Constructor for the llist class that takes a char array as a parameter
 *
 *
 *    Parameters: file : filename to be used
 *
 *
 *    Return values: None
 */

llist :: llist(char file[])
{
    this->start = NULL;
    strcpy(this->filename, file);
    readfile();

}

/*
 *     Function name: llist
 *
 *
 *     Description: Copy constructor for the llist class
 *
 *
 *     Parameters: copylist : the list object to pass through the copy constructor
 *
 *
 *     Return values: None
 */

llist :: llist(const llist &copy)
{
    start = copy.start;

}

/*
 *    Function name: ~llist
 *
 *
 *    Description: Desctructor for the llist class that writes the data to a file and frees the memory in the linked list
 *
 *
 *    Return values: none
 */

llist :: ~llist()
{ 
    writefile();
    cleanup();

}

/*
 *    Function Name: addRecord
 *      
 *           
 *    Description: Adds a record to the bank database
 *            
 *                 
 *    Parameters: int : the account number | char name [] : name of the person | char address[] : address of the person
 *                  
 *                       
 *    Return values: 0 : Success | -1 : Did not add record to the list
 *                        
 */

using namespace std;

int llist :: addRecord(int accountno, char name[], char address[])
{
    int retval;
    int check;
    struct record *newNode = new record();
    struct record *temp;    
    struct record *previous;

    check = 0;
    temp = start;
    previous = start;

    newNode->accountno = accountno;
    strcpy(newNode->address, address);
    strcpy(newNode->name, name); 
    newNode->next = NULL;

    if (start == NULL)
    {        
       start = newNode;
       retval = 0;
       
    } else if (newNode->accountno < temp->accountno || newNode->accountno == temp->accountno) {
         
        newNode->next = temp;
        start = newNode;
        retval = 0;
                   
    } else {
       
        while (temp != NULL && check == 0)
        {
            if (newNode->accountno == previous->accountno || newNode->accountno < temp->accountno )
            { 
                previous->next = newNode;
                newNode->next = temp; 
                retval = 0; 
                check = 1;   
            
            } else if ((temp->next == NULL)) {
     
                temp->next = newNode;
                newNode->next = NULL;
                previous = temp;
                retval = 0;
                check = 1;

            } else {
               
               previous = temp;
               temp = temp->next;
               retval = 1;
            
            }

         }

     }

#ifdef debug

    cout << "**DEBUG addRecord**" << endl << "accountno: " << accountno << endl  << "name:" << name << endl << "address: " << address << endl;
    
#endif

return retval;

}


/*
 *    Function Name: printRecord
 *      
 *           
 *    Descrption: Prints the record of a person
 *            
 *              
 *    Parameters: struct record * : Where the record of the person is in memory | int : account number
 *                  
 *                  
 *    Return Values: 0 : success | -1 : Failure 
 *                       
 */

using namespace std;

int llist :: printRecord(int accountno)
{
    int retval;
    struct record *temp;

    temp = start;

    if (start == NULL)
    {
        retval = -1;

    } else if (start != NULL) {

        while (temp != NULL)
        {
            if (temp->accountno == accountno)
            {
                cout << "Account Number: " << temp->accountno << endl << "Name: " << temp->name << endl << "Address: " << temp->address << endl;
                retval = 0;

            } else {
 
                retval = -1;

            }

            temp = temp->next;
        
        }

    }

#ifdef debug
   
    cout << "**DEBUG printRecord**" << endl << "accountno: " << accountno << endl;

#endif

return retval;

}

/*
 *    Function Name: deleteRecord
 *      
 *            
 *    Description: Deletes a record within the database
 *            
 *                 
 *    Parameters: struct record **: location of addresses to delete | int : account number to delete
 *                  
 *               
 *    Return Values: 0 : Success | -1 Record was not deleted/does not exist
 *                     
 */

int llist :: deleteRecord(int accountno)
{
    int retval;
    struct record *temp;
    struct record *previous;

    temp = start;
    previous = NULL;

    if (start == NULL)
    {
        retval = -1;

    } else if (start != NULL) {
 
        while (temp != NULL)
        {
             if (previous == NULL && temp->accountno == accountno)
            {
                start = temp->next;
                delete(temp);
                temp = start;
                retval = 0;

            } else if (temp->accountno == accountno) {

                previous->next = temp->next;
                delete(temp);
                temp = temp->next;
                retval = 0;

            } else if (temp->accountno != accountno) {

                previous = temp;
                temp = temp->next;
                retval = 0;

            }

        }

    }

#ifdef debug

    std :: cout << "**DEBUG deleteRecord**" << endl << "accountno: " << accountno << endl;

#endif

return retval;

}
/*
 *     Function name: reverse
 *
 *
 *     Description: Helper function to call the reverse function to reverse the database.
 *
 *
 *     Parameters: None
 *
 *     
 *     Return Values: None
 */

void llist :: reverse()
{
    start = reverse(start);

}

/*
 *     Function name: cleanup
 *
 *
 *     Description: Deletes the linked list to prevent a memory leak after writing the list to a file
 *
 *
 *     Parameters: None
 *
 *
 *     Return values: None
 */

void llist :: cleanup()
{
    struct record *temp;
    struct record *next;

    temp = start;

    while (temp != NULL)
    {
        next = temp->next;
        delete(temp);
        temp = next;

    }

}

/*
 *    Function Name: readfile
 *      
 *        
 *    Description: reads the contents of a file to a linked list
 *            
 *              
 *    Parameters: None                 
 *                     
 *    
 *    Return Values: records : the amount of records read into the list 
 *                       
 */

int llist :: readfile()
{    
    string saccountno;
    string sname;
    string saddress;
    string trash;
    stringstream convert;

    int accountno;
    int records;
    char name[25];
    char address[80];
    ifstream inf;

    records = 0;

    inf.open("database.txt");
 
    if (inf)
    { 
        while (getline(inf, saccountno))  
        {
            getline(inf, sname);
            getline(inf, saddress, '/');
            getline(inf, trash);
            
            convert << saccountno;
            convert >> accountno; 
    
            convert.clear(); 
            convert.str(string());    

            strcpy(name, sname.c_str());
            strcpy(address, saddress.c_str());
                        
            addRecord(accountno, name, address);
            
            records++;
        }

    inf.close();
    
    }

return records;

}

/*
 *    Function Name: writefile
 *      
 *        
 *    Description: Writes the contents of an linked list to a file
 *            
 *             
 *    Parameters: none                  
 *                      
 *    
 *    Return Values: none                    
 */

void llist :: writefile()
{   
    struct record *temp;
  
    temp = start;
    ofstream outf;
    outf.open("database.txt");
    
    if (start != NULL)
    {       
        if (outf != NULL)
        {
            while (temp != NULL)
            {
                outf << temp->accountno << endl << temp->name << endl << temp->address << "/" << endl;
                temp = temp->next;
        
            }

        } else {

            outf.close();
        }
    }

    outf.close();
}

/*
 *    Function name: reverse
 *
 *    
 *    Description: A recursive function to reverse the linked list
 *
 *
 *    Parameters: temp : the pointer to the list to pass in to reverse
 *
 *
 *    Return values: record * : the new start of the list
 *
 */

record * llist :: reverse(record* temp)
{
    struct record *newStart;

    if (temp->next == NULL)
    {
        newStart = temp;

    } else {
   
        newStart = reverse(temp->next);
        temp->next->next = temp;
        temp->next = NULL;
           
    }      

return newStart;

}

/*
 *    Function name: operator <<
 *
 *
 *    Description: Overload of the << operator to print all the records in the list
 *
 *
 *    Parameters: out : the operator<< to modify | list : the object to overload with
 *
 *
 *    Return values: ostream : the newly overloaded operator<<
 */

ostream & operator<<(ostream & out, const llist & list)
{
    llist list1;
    record *temp;

    temp = list.start;
    
    while (temp != NULL)
    {
        out << "Account Number: " << temp->accountno << endl << "Name: " << temp->name << endl << "Address: " << temp->address << endl;
        temp = temp->next;
       
    }
    
    if (list.start == NULL)
    {
        cout << "There are no records in the database\n";
    
    } else {
        
        cout << "You have printed all the records within the Bank Database\n";
   
    }

return out;

}
