
/*****************************************************************
 *
 * NAME: Spencer Allen
 *
 * HOMEWORK: Project 2
 *
 * CLASS: ICS 212
 *
 * INSTRUCTOR: Ravi Narayan
 *
 * DATE: Nov 24, 2015
 *
 * FILE: main.c
 *
 * DESCRIPTION: This file contains the user interface and functions for Address Book.
 *
 *****************************************************************/
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "llist.h"
using namespace std;


void getAddress(char *, int);
int getYear();
void getTelNum(char *);
void getName(char *);

int main(int argc, char *argv[]) 
{
    int exitprogram = 0;
    char optionarray[50];
    int inputvaliditycheck = 0;

    char name[25];
    char address[80];
    int yearofbirth = 0;
    char telNumber[15];

    llist *mylist;
    char filename[] = "proj2.txt";
    mylist = new llist(filename);

    cout << "\nWelcome to Address Book! \n";
    while (exitprogram < 1) 
    {
        cout << "\nPlease select an option: \n";
        cout << "    1. Add a new record to the database \n";
        cout << "    2. Modify a record in the database using the name as the key \n";
        cout << "    3. Print information about a record using the name as the key \n";
        cout << "    4. Print all information in the database \n";
        cout << "    5. Delete an existing record from the database using the name as a key \n";
        cout << "    6. Clean up database by deleting all records. \n";
        cout << "    7. Quit the program \n";
        cout << "    8. Reverse the address list \n";


        inputvaliditycheck = 0;

        if (cin >> optionarray) 
        {
            /*Add */
            if (strstr(optionarray, "1") != NULL || strstr(optionarray, "Add") != NULL || strstr(optionarray, "add") != NULL) 
            {
                cout << "Please enter the following information for the person you want to add:";
                getName(name);
                getAddress(address, sizeof (address) + 1);
                yearofbirth = getYear();
                getTelNum(telNumber);
                mylist->addRecord(name, address, yearofbirth, telNumber);
            }/*Modify */
            else if (strstr(optionarray, "2") != NULL || strstr(optionarray, "Modify") != NULL || strstr(optionarray, "modify") != NULL) 
            {
                cout << "Please enter the following information for the person you want to modify:";
                getName(name);
                getAddress(address, sizeof (address) + 1);
                getTelNum(telNumber);
                mylist->modifyRecord(name, address, telNumber);
            }/*Print 1 */
            else if (strstr(optionarray, "3") != NULL || strstr(optionarray, "Print") != NULL || strstr(optionarray, "print") != NULL && strstr(optionarray, "Print All") == NULL && strstr(optionarray, "print all") == NULL) 
            {

                cout << "Please enter the name of the person whose info you want to print: \n";

                getName(name);
                mylist->printRecord(name);
            }/*Print All */
            else if (strstr(optionarray, "4") != NULL || strstr(optionarray, "Print All") != NULL || strstr(optionarray, "Print all") != NULL || strstr(optionarray, "print all") != NULL || strstr(optionarray, "print All") != NULL) 
            {
                cout << mylist;

            }/*Delete */
            else if (strstr(optionarray, "5") != NULL || strstr(optionarray, "Delete") != NULL || strstr(optionarray, "delete") != NULL) 
            {

                cout << "Please enter the name of the person whose info you want to delete: \n";

                getName(name);
                mylist->deleteRecord(name);
            }/*Cleanup*/
            else if (strstr(optionarray, "6") != NULL || strstr(optionarray, "Cleanup") != NULL || strstr(optionarray, "cleanup") != NULL) 
            {

                cout << "Cleaning up records... \n";
                mylist->~llist();
            }/*Quit */
            else if (strstr(optionarray, "7") != NULL || strstr(optionarray, "Quit") != NULL || strstr(optionarray, "quit") != NULL) 
            {
                exitprogram++;
            }/*Reverse*/
            else if (strstr(optionarray, "8") != NULL || strstr(optionarray, "Reverse") != NULL || strstr(optionarray, "reverse") != NULL)
            {
               mylist->reverse();
            }/*Bad input */
            else
            {
                cout << "Invalid selection. Type the number or name of the option you want from the list.\n";
            }
        }
    }
    delete(mylist);
    return (0);
}

/*****************************************************************
 *
 * Function name: getAddress
 *
 * DESCRIPTION: A function that prompts the user for their address, then gets their input for it.
 *
 * Parameters: address (char[]):  Pointer to address array in program so we can save the user's input.
 * length (int) : The length of the array so we don't overflow from user input.
 *
 * Return values: None.
 *
 *****************************************************************/
void getAddress(char address[], int length)
{
    char stringbuff[20];
#ifdef DEBUGMODE
    cout << "\n***...DEBUG MODE...***\n";
    cout << "~METHOD: getAddress\n";
    cout << "~PARAMS:\n";
    cout << "~ADDRESS: " << address << "\n";
    cout << "~LENGTH: " << length << "\n";
#endif

    cout << "\nEnter address:\n(Press * then enter/newline to stop)\n";

    address[0] = '\0';
    while (strstr(address, "*") == NULL) 
    {
        cin.getline(stringbuff, 20);
        strcat(stringbuff, "\n");
        strcat(address, stringbuff);

    }
    address[strlen(address) - 2] = '\0';
}

/*****************************************************************
 *
 * Function name: getYear
 *
 * DESCRIPTION: A function that prompts the user for their year of birth, then gets their input for it.
 *
 * Parameters: None.
 *
 * Return values: temp (int) : The temp int used to hold user's date of birth.
 *
 *****************************************************************/
int getYear() 
{
    int check = 0;
    int temp;
#ifdef DEBUGMODE
    cout << "\n***...DEBUG MODE...***\n";
    cout << "~METHOD: getYear\n";
    cout << "~PARAMS:\n";
    cout << "~NONE~\n";
#endif


    while (check < 1) 
    {
        cout << "\nEnter year of birth: \n";
        cin>>temp;
        if (!cin.fail()) 
        {
            check++;
        } else 
        {
            cout << "\nInput must be a number.\n";
            cin.clear();
            cin.ignore(999, '\n');
        }
    }


    return (temp);
}

/*****************************************************************
 *
 * Function name: getTelNum
 *
 * DESCRIPTION: A function that prompts the user for their telephone number, then gets their input for it.
 *
 * Parameters: telNumber (char[]):  Pointer to telNumber array in program so we can save the user's input.
 * 
 *
 * Return values: None.
 *
 *****************************************************************/
void getTelNum(char telNumber[]) 
{

#ifdef DEBUGMODE
    cout << "\n***...DEBUG MODE...***\n";
    cout << "~METHOD: getTelNum\n";
    cout << "~PARAMS:\n";
    cout << "~TELNUMBER: %s\n", telNumber;
#endif

    cout << "\nEnter telephone number: \n";
    cin >> telNumber;
    telNumber[strcspn(telNumber, "\r\n")] = '\0';
}

/*****************************************************************
 *
 * Function name: getTelNum
 *
 * DESCRIPTION: A function that prompts the user for their name, then gets their input for it.
 *
 * Parameters: name (char[]):  Pointer to name array in program so we can save the user's input.
 * 
 *
 * Return values: None.
 *
 *****************************************************************/
void getName(char name[]) 
{
    char dummy;
#ifdef DEBUGMODE

    cout << "\n***...DEBUG MODE...***\n";
    cout << "~METHOD: getName\n";
    cout << "~PARAMS:\n";
    cout << "~" << name << ": %s\n";
#endif
    dummy = cin.get();
    std::cout << "\nEnter name: \n";
    cin.getline(name, 25);
    name[strcspn(name, "\r\n")] = '\0';

}












