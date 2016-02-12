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
 * FILE: llist.cpp
 *
 * DESCRIPTION: This file contains the user database functions.
 *
 *****************************************************************/

#include <iomanip>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "record.h"

#ifndef LLIST_H
#define LLIST_H


class llist {
#include <fstream>
#include <iostream>
private:
    record * start;
    char filename[16];
    int readfile();
    int writefile();
    record * reverse(record *);
    void cleanup();

public:
    llist();
    llist(char[]);
    ~llist();
    int addRecord(char[], char[], int, char[]);
    int printRecord(char[]);
    int modifyRecord(char[], char[], char[]);
    void printAll();
    int deleteRecord(char[]);
    void reverse();
    friend std::ostream& operator<<(std::ostream&, llist*);
};
#endif

using namespace std;

/*****************************************************************
 *
 * Function name: llist
 *
 * DESCRIPTION: Constructs the llist with a default filename
 *
 * Parameters: N/A
 * 
 * Return values: N/A
 *
 *****************************************************************/
llist::llist() 
{
#ifdef DEBUGMODE
    cout << "\n***...DEBUG MODE...***\n";
    cout << "~METHOD: llist\n";
    cout << "~PARAMS:\n";
#endif
    this->start = NULL;
    strcpy(this->filename, "proj2.txt");
    readfile();
}

/*****************************************************************
 *
 * Function name: llist
 *
 * DESCRIPTION: Constructs the llist with a given filename
 *
 * Parameters: N/A
 * 
 * Return values: N/A
 *
 *****************************************************************/
llist::llist(char fn[]) 
{
#ifdef DEBUGMODE
    cout << "\n***...DEBUG MODE...***\n";
    cout << "~METHOD: llist\n";
    cout << "~PARAMS:\n";
    cout << "~FILENAME*: " << fn << "\n";
#endif
    this->start = NULL;
    strcpy(this->filename, fn);
    readfile();
}

/*****************************************************************
 *
 * Function name: ~llist
 *
 * DESCRIPTION: Destructs the llist
 *
 * Parameters: N/A
 * 
 * Return values: N/A
 *
 *****************************************************************/
llist::~llist() 
{
#ifdef DEBUGMODE
    cout << "\n***...DEBUG MODE...***\n";
    cout << "~METHOD: ~llist\n";
    cout << "~PARAMS:\n";
#endif
    writefile();
    this->cleanup();
}

/*****************************************************************
 *
 * Function name: reverse
 *
 * DESCRIPTION: Rcursively reverses the linked list
 *
 * Parameters: start (record *) : the start of the list to reverse
 * 
 * Return values: start : the address of the record being passed
 *
 *****************************************************************/
record * llist::reverse(record * start) 
{
#ifdef DEBUGMODE
    cout << "\n***...DEBUG MODE...***\n";
    cout << "~METHOD: reverse\n";
    cout << "~PARAMS:\n";
    cout << "~RECORD*: start\n";
#endif
    if(start != NULL)
    {
        if (start->next == NULL) 
        {
        this->start = start;
        return start;
        } 
        else 
        {
        (reverse(start->next))->next = start;
        start->next = NULL;
        }
    }
    return start;
}

/*****************************************************************
 *
 * Function name: reverse
 *
 * DESCRIPTION: Calls the private reverse method
 *
 * Parameters: N/A
 * 
 * Return values: 
 *
 *****************************************************************/
void llist::reverse() 
{
#ifdef DEBUGMODE
    cout << "\n***...DEBUG MODE...***\n";
    cout << "~METHOD: reverse\n";
    cout << "~PARAMS:\n";
#endif
    this->reverse(this->start);
}

/*****************************************************************
 *
 * Function name: cout <<
 *
 * DESCRIPTION: Prints llist
 *
 * Parameters: out (ostream&) : Where to print out to
 * mylist (llist *) : the llist to print the information from
 * 
 * Return values: N/A
 *
 *****************************************************************/
ostream& operator<<(ostream& out, llist * mylist) 
{

#ifdef DEBUGMODE
    cout << "\n***...DEBUG MODE...***\n";
    cout << "~METHOD: cout<<\n";
    cout << "~PARAMS:\n";
    cout << "~OSTREAM&&: out\n";
    cout << "~LLIST: mylist\n";
#endif
    struct record *temp;
    temp = mylist->start;
    if ((mylist->start) != NULL) 
    {
        do {
            std::cout << "\nName: " << temp->name << "\nAddress: " << temp->address << "\nBirth Year: " << temp->yearofbirth << "\nPhone #: " << temp->telno << "\n\n";

            if (temp->next == NULL) 
            {
                break;
            }
            temp = temp->next;
        } while (temp != NULL);
    }
}

/*****************************************************************
 *
 * Function name: addRecord
 *
 * DESCRIPTION: Adds a record to the end of the database. Allows duplicates.
 *
 * Parameters: name (char *) : Name of person to be added.
 * address (char *) : Address of person to be added.
 * yearofbirth (int) : Year of birth of person to be added.
 * telno (char *) : Telephone number of person to be added.
 * 
 * Return values: 1: success
 *
 *****************************************************************/
int llist::addRecord(char name[], char address[], int yearofbirth, char telno[])
{

    struct record *data;
    struct record *temp;
    data = new record;

#ifdef DEBUGMODE
    cout << "\n***...DEBUG MODE...***\n";
    cout << "~METHOD: addRecord\n";
    cout << "~PARAMS:\n";
    cout << "~NAME: " << name << "\n";
    cout << "~ADDRESS: " << address << "\n";
    cout << "~YEAROFBIRTH: " << yearofbirth << "\n";
    cout << "~TELNO: " << telno << "\n";
#endif

    if (start->name != NULL) 
    {
        temp = start;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = data;

    } 
    else
    {
        start = data;
    }

    strcpy(data->name, name);
    strcpy(data->address, address);
    data->yearofbirth = yearofbirth;
    strcpy(data->telno, telno);
    data->next = NULL;

    return 1;
}

/*****************************************************************
 *
 * Function name: printRecord
 *
 * DESCRIPTION: Prints all records that correspond to the given name.
 * 
 * Parameters: name (char *) : Name of person to be printed.
 *
 * Return values: 1 : success
 *  0 : failure
 *
 *****************************************************************/
int llist::printRecord(char name[]) 
{

    struct record *temp = start;

#ifdef DEBUGMODE

    cout << "\n***...DEBUG MODE...***\n";
    cout << "~METHOD: printRecord\n";
    cout << "~PARAMS:\n\n";
    cout << "~NAME: " << name << "\n";
#endif

    if (start != NULL)
    {

        while (temp != NULL) 
        {
            if (strcmp(temp->name, name) == 0)
            {
                cout << "Name: " << temp->name << "\nAddress: " << temp->address << "\nBirth Year: " << temp->yearofbirth << "\nPhone #: " << temp->telno << "\n\n";

            }
            if (temp->next != NULL) 
            {
                temp = temp->next;
            } else if (temp->next == NULL) 
            {
                break;
            }
        }
        return 1;
    } 
    else 
    {
        return 0;
    }
}

/*****************************************************************
 *
 * Function name: modifyRecord
 *
 * DESCRIPTION: Modifies all records that match the given name.
 *
 * Parameters: name (char *) : Name of persons to be modified.
 * address (char *) : Address to modify to.
 * telno (char *) : Telephone number to modify to.
 * 
 * Return values: 1 : success
 *  0 : failure
 *
 *****************************************************************/
int llist::modifyRecord(char name[], char address[], char telno[]) 
{
    struct record *temp;
    if (this != NULL) 
    {
        temp = this->start;
    }
    else 
    {
        return 0;
    }

#ifdef DEBUGMODE

    cout << "\n***...DEBUG MODE...***\n";
    cout << "~METHOD: modifyRecord\n";
    cout << "~PARAMS:\n\n";
    cout << "~NAME: " << name << "\n";
    cout << "~ADDRESS: " << address << "\n";
    cout << "~TELNO: " << telno << "\n";
#endif

    while (temp != NULL) 
    {
        if (strcmp(temp->name, name) == 0)
        {

            strcpy(temp->address, address);
            strcpy(temp->telno, telno);
        }
        if (temp->next != NULL)
        {
            temp = temp->next;
        } else if (temp->next == NULL)
        {
            break;
        }
    }
    return 1;

}

/*****************************************************************
 *
 * Function name: printAllRecords
 *
 * DESCRIPTION: Prints all records.
 *
 * Parameters: 
 * 
 * Return values: None.
 *
 *****************************************************************/
void llist::printAll() 
{
    struct record *temp;
    temp = start;

#ifdef DEBUGMODE

    cout << "\n***...DEBUG MODE...***\n";
    cout << "~METHOD: printAllRecords\n";
    cout << "~PARAMS:\n";
#endif

    if ((start) != NULL) 
    {
        do 
        {
            std::cout << "Name: " << temp->name << "\nAddress: " << temp->address << "\nBirth Year: " << temp->yearofbirth << "\nPhone #: " << temp->telno << "\n\n";

            if (temp->next == NULL) 
            {
                break;
            }
            temp = temp->next;
        } while (temp != NULL);
    }
}

/*****************************************************************
 *
 * Function name: deleteRecord
 *
 * DESCRIPTION: Deletes all records that match the given name.
 *
 *  * Parameters: 
 * 
 * Return values: 1 : success
 *  0 : failure
 *
 *****************************************************************/
int llist::deleteRecord(char name[]) 
{


    struct record *temp = this->start;
    struct record *temp2;

#ifdef DEBUGMODE

    cout << "\n***...DEBUG MODE...***\n";
    cout << "~METHOD: deleteRecord\n";
    cout << "~PARAMS:\n";
    cout << "~NAME: " << name << "\n";

#endif

    if ((this->start) != NULL)
    {
        while (strcmp(this->start->name, name) == 0) 
        {
            this->start = this->start->next;
            delete(temp);
            temp = this->start;

            if (temp == NULL)
            {
                break;
            }
        }

        temp2 = temp;

        while (temp != NULL) 
        {
            if (strcmp(temp->name, name) == 0) 
            {
                if (temp->next == NULL) 
                {
                    temp2->next = NULL;
                    delete(temp);
                    break;
                } else 
                {
                    temp2->next = temp->next;
                    delete(temp);
                    temp = temp2;
                }
            } 
            else 
            {
                temp2 = temp;
            }

            temp = temp->next;
        }
        return 1;
    } 
    else 
    {
        return 0;
    }
}

/*****************************************************************
 *
 * Function name: readfile
 *
 * DESCRIPTION: Opens a file from given filename. 
 * Copies the information in file into the records in memory.
 * 
 * Parameters: 
 *
 * Return values: -1 : the file could not be found
 * 1 : success
 *
 *****************************************************************/
int llist::readfile() 
{
    char tempstring[100];
    char tempstring2[200];
    int templength = 0;

    struct record *data;
    struct record *temp;
    struct record *temp2;
    char name[25];
    char address[80];
    int yearofbirth;
    char telno[15];
    int check = 0;

    ifstream myfile(this->filename);

#ifdef DEBUGMODE

    cout << "\n***...DEBUG MODE...***\n";
    cout << "~METHOD: readfile\n";
    cout << "~PARAMS:\n";
#endif
    if (!myfile.is_open())
    {
        return 0;
    }
    myfile.peek();
    if (myfile.eof())
    {
        return 1;
    }
    data = new record();
    this->start = data;
    temp = (start);
    tempstring2[0] = '\0';


    while (!myfile.eof()) 
    {
        while (myfile.getline(tempstring, 40)) 
        {

            strcat(tempstring2, tempstring);
            strcat(tempstring2, "\n");
            templength = strlen(tempstring2);

            if (tempstring2[templength - 1] == '*') 
            {
                templength++;
            }
            if (templength > 0 && tempstring2[templength - 2] == '*') 
            {
                if (check == 0) 
                {
                    tempstring2[templength - 2] = '\0';
                    strcpy(name, tempstring2);
                    strcpy(data->name, name);
                    tempstring2[0] = '\0';

                    check++;
                } else if (check == 1) 
                {
                    tempstring2[templength - 2] = '\0';
                    strcpy(address, tempstring2);
                    strcpy(data->address, address);
                    tempstring2[0] = '\0';

                    check++;
                } else if (check == 2)
                {
                    yearofbirth = atoi(tempstring2);
                    data->yearofbirth = yearofbirth;
                    tempstring2[0] = '\0';

                    check++;
                } else if (check == 3)
                {
                    tempstring2[templength - 2] = '\0';
                    strcpy(telno, tempstring2);
                    strcpy(data->telno, telno);
                    tempstring2[0] = '\0';

                    check++;
                }
                if (check == 4)
                {
                    check = 0;
                    if (myfile.eof()) 
                    {
                        return 1;
                    }
                    temp->next = new record();
                    temp2 = temp;
                    data = temp->next;
                    temp = temp->next;
                }
            }
        }
    }
    delete(temp);
    myfile.close();
    return 1;
}

/*****************************************************************
 *
 * Function name: writefile
 *
 * DESCRIPTION: Writes a file to given filename. 
 * Copies the information in records in memory into the file.
 * 
 * Parameters:
 *
 * Return values: 0 : no records found
 * 1 : success
 *
 *****************************************************************/
int llist::writefile()
{

    struct record *temp;
    ofstream myfile;
    myfile.open(this->filename);
    temp = this->start;

#ifdef DEBUGMODE

    cout << "\n***...DEBUG MODE...***\n";
    cout << "~METHOD: writefile\n";
    cout << "~PARAMS:\n";

#endif

    if (this->start != NULL)
    {
        do {
            if (temp->next == NULL) 
            {
                myfile << temp->name << "*\n" << temp->address << "*\n" << temp->yearofbirth << "*\n" << temp->telno << "*";
                break;
            }
            myfile << temp->name << "*\n" << temp->address << "*\n" << temp->yearofbirth << "*\n" << temp->telno << "*\n";

            temp = temp->next;
        }
        while (temp != NULL);
    } 
    else 
    {
        return 0;
    }
    myfile.close();
    return 1;
}

/*****************************************************************
 *
 * Function name: cleanup
 *
 * DESCRIPTION: Deletes all records, sets start to NULL.
 * 
 * Parameters: 
 *
 * Return values: none
 *
 *****************************************************************/
void llist::cleanup() 
{

    struct record *temp = start;
    struct record *temp2;

#ifdef DEBUGMODE

    cout << "\n***...DEBUG MODE...***\n";
    cout << "~METHOD: cleanup\n";
    cout << "~PARAMS:\n";

#endif

    if ((start) != NULL) 
    {

        temp2 = temp;

        while (temp != NULL) 
        {

            if (temp->next == NULL)
            {
                delete(temp);
                temp = NULL;
                temp2 = NULL;
                start = NULL;
                break;
            } 
            else 
            {
                temp2 = temp->next;
                delete(temp);
                temp = temp2;
            }
        }
    }
}



