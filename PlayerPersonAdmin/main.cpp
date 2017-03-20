#include <iostream>
#include <windows.h>
#include <fstream>
#include <ctime>
#include "Person.h"
#include "Person.h"
#include "Admin.h"
#include "Login.h"
using namespace std;

void myfunction ()
{
    char filename[100];
    ifstream thando;
    cout << "Enter the name of your file : ";
    cin.getline(filename,100);
    thando.open(filename);

    if(!thando.is_open())
        {
        cout <<"\n\nThe file you entered does not exist! "<< endl;
        exit(EXIT_FAILURE);
     }
    char word[100];
    thando >> word;

    string myarray[5];
    int i = 0;
    while(thando.good()){
        myarray[i] = word;
        thando >> word;
        i++;
    }
   // delete thando; // deleting the object i created
//*****************************************************

    srand(time(NULL));
    int usedRandomNumber[5];
    cout << "\n";
    for(int i = 0; i < 5 ; i++)
        {
        bool check;
        int randomNum;
        do
        {
            randomNum = rand()%5;
            check = true;
            for(int j = 0; j < i ; j++)
            {
                if(randomNum == usedRandomNumber[j])
                {
                    check = false;
                    break;
                }
            }
        } while(!check);
        usedRandomNumber[i] = randomNum;
        string selectedWord = myarray[randomNum];
        string filenameAndPath = "./images/"+selectedWord+".jpg";
        cout << selectedWord << " - "<< filenameAndPath << endl;
    }
}
int main()
{
    myfunction();
    return 0;
}
