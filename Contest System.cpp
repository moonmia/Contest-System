#include <iostream>
using namespace std;
#include "speechManager.h"
#include <string>

int main()
{
	//Create class objects

	SpeechManager sm;

	int choice = 0; // Used to store user's input.

	//You can test the 12 players are created sucessfully first.
	/*
	for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	{
		cout << "Player's number: " << it->first << " Name: " << it->second.m_Name << " Score: " << it->second.m_Name[0] << endl;

	}
	*/




	while (true)
	{
		sm.show_Menu();
		cout << "Please enter your choice: " << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: //Begin Contest
			sm.startSpeech();
			break;
		case 2: //History Lookup
			break;
		case 3: //History Cleanup
			break;
		case 0: //Exit The Contest 
			sm.exitSystem();
			break;
		default: //Clear
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}