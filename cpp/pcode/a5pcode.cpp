// Pseudo-code for assignment 5
// need to have a few set function types
// void addRecord(fstream &);
// void veiwRecord(fstream &);
// void changeRecord(fstream &);
// needs to be able to read from and modify a file

#include <iostream>
#include <string>
#include <fstream>

using namespace std;


// Declare function prototypes
void addRecord(fstream &);
void viewRecord(fstream &);
void changeRecord(fstream &);

int main()
{
    int selection;
    do{
        cout<<"Select a function[1-3]:\n[0 to exit] "<<endl;
        cin >> selection; 
        
        switch (selection)
        {
            case 1 : addRecord(fstream &);
                break;
            case 2 : viewRecord(fstream &);
                break;
            case 3 : changeRecord(fstream &);
                break;
        }

      }while(selection != 0)
    return 0;
}
