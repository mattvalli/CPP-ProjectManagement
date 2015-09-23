#include<iostream>
#include<fstream>
#include<string>
#include "Event.h"
#include "Activity.h"

using namespace std;

void promptForEvent();
void promptForActivity();



int main()
{
	
	


	//Inputting events
    promptForEvent();
	
	//Inputting activities
	

	system("pause");
	return 0;
}



void promptForEvent() {
    // Local Variables
    char response;
    string path, eName;
    int id = 0;
    

		while (true)
		{
			cout << "\nPlease enter the following information:" << endl;
			cout << "Event name: ";
			cin >> eName;
			
			//Store information into class here
            Event *currentEvent = new Event(id, eName);
            
            
			char add;
			cout << "\nWould you like to add another event? (y/n)" << endl;
			cin >> add;
			if (add == 'n')
				break;
		}

}
void promptForActivity() {
    // Local Vars
    char response;
    string path, eName;
    int eTime, eStart, eEnd, id = 0;
    cout << "\nDo you have an XML file for activities? (y/n)" << endl;
	cin >> response;
	if (response == 'y')
	{
		ifstream activityFile;
		cout << "\nPlease enter the address of your XML file:" << endl;
        cin.ignore();
		getline(cin, path);
		activityFile.open(path);
	}
	else
	{
		while (true)
		{
			cout << "\nPlease enter the following information:" << endl;
			cout << "Event name: ";
			cin >> eName;
			cout << "Duration/units: ";
			cin >> eTime;
			cout << "Start Vertex: ";
			cin >> eStart;
			cout << "Duration/units: ";
			cin >> eEnd;
			
            
			//Store information into class here
            
            
			char add;
			cout << "\nWould you like to add another event? (y/n)" << endl;
			cin >> add;
			if (add == 'n')
				break;
		}
	}
}