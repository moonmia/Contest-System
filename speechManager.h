#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "speaker.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <string>
#include <fstream>


using namespace std;

class SpeechManager
{
public:
	//Constructor
	SpeechManager();

	//Show Meun
	void show_Menu();

	//Exit System
	void exitSystem();

	//Destructor
	~SpeechManager();

	//Initial the vector
	void initSpeech();

	//Create the 12 players
	void createSpeaker();

	//Contest begin, Create the contest control flow
	void startSpeech();

	//Draw slot
	void speechDraw();

	//Contest
	void speechContest();

	//Show score
	void showScore();

	//Save Record
	void saveRecord();


	//vector to store the first time contest scores
	vector<int>v1;

	//vector to store the first time contest winners
	vector<int>v2;

	//vector to store the first three players
	vector<int>vVictory;

	//vector to store the players number and name
	map<int, Speaker>m_Speaker;

	//int to store the times of contest 
	int m_Index;
};
