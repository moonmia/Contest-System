#include "SpeechManager.h"


//Constructor
SpeechManager::SpeechManager()
{
	//initial the vector
	this->initSpeech();

	//Create the 12 players
	this->createSpeaker();

}


//Show Meun
void SpeechManager::show_Menu()
{
	cout << "*************************************" << endl;
	cout << "*** Welcome To The Contest Speech ***" << endl;
	cout << "***        1. Speech Start        ***" << endl;
	cout << "***        2. History Lookup      ***" << endl;
	cout << "***        3. History Cleanup     ***" << endl;
	cout << "***        0. Exit The Contest    ***" << endl;
	cout << "*************************************" << endl;
	cout << endl;
}

//Exit System
void SpeechManager::exitSystem()
{
	cout << "Thanks for using" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech()
{
	//initial all the vector to be empty
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//initial the times of contest
	this->m_Index = 1;
}

//Create the 12 players
void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "Player";
		name += nameSeed[i];
		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;
		}

		//Create player's number and put them to vector1
		this->v1.push_back(i + 10001);

		//put Players' number and players to map
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//Contest begin, Create the contest control flow
void SpeechManager::startSpeech()
{
	//The first contest begin

	//1. Draw lots
	this->speechDraw();
	//2. Contest start
	this->speechContest();
	//3. Show scores
	this->showScore();


	//The second contest begin
	this->m_Index++;

	//1. Draw lots
	this->speechDraw();
	//2. Contest start
	this->speechContest();
	//3. Show final score
	this->showScore();
	//4. store score to file
	this->saveRecord();

	cout << "The contest is completed!" << endl;
	system("pause");
	system("cls");
}


void SpeechManager::speechDraw()
{
	cout << "The " << this->m_Index << "times of players are drawing lots" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "After lot drawing, the order of contest speech are showing below: " << endl;

	if (this->m_Index == 1)
	{
		//First time
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//Final round
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}

	cout << "-------------------------------------------------" << endl;
	system("pause");
	cout << endl;
}

//Contest
void SpeechManager::speechContest()
{
	
	cout << "The " << this->m_Index << "times of contest are begin" << endl;

	//Prepare a temp map to score the team's score
	multimap<double, int, greater<double>> groupScore;

	int num = 0; //Record the players number, 6 players are a team.

	
	vector<int>v_Src; //Players vector
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//Look up all the players to start the contest
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//Giving score
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f; //600-1000
			// cout << score << " ";
			d.push_back(score);
		}
		// cout << endl;
		sort(d.begin(), d.end(), greater<double>()); //descending sort
		d.pop_front(); //Get rid of the highest score;
		d.pop_back(); //Get rid of the lowest score;

		double sum = accumulate(d.begin(), d.end(), 0.0f); //the total of score.
		double avg = sum / (double)d.size(); //Average score

		//print out the avg
		cout << "the player: " << *it << " name: " << this-> m_Speaker[*it].m_Name << " average score is: " << avg << endl;

		//Put the average score to map
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//put the average to temp map
		groupScore.insert(make_pair(avg, *it)); //key is the average, value is the specific players's number
		//Get the first three from every 6 players 
		if (num % 6 == 0)
		{
			cout << "The " << num / 6 << " team's rank is: " << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "The " << it->second << " Name: " << this->m_Speaker[it->second].m_Name << " Score: "
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			//Get the first three players to the next map
			int count = 0;
			for (multimap<double, int, greater<double>> ::iterator it = groupScore.begin(); it != groupScore.end() && count <3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}

			}

			groupScore.clear(); //clear the group score every time
			cout << endl;
		}

	}
	cout << "The " << this->m_Index << "contest is ended" << endl;
	system("pause");
}

//Show score
void SpeechManager::showScore()
{
	cout << "The " << this->m_Index << "times of contest winner players are here: " << endl;
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "Player: " << *it << " Name: " << this->m_Speaker[*it].m_Name << " Score: "
			<< this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

void SpeechManager:: saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	//Put the winners data to file
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << ", " << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	//close file
	ofs.close();
	cout << "Record is saved!" << endl;

}

//Destructor
SpeechManager:: ~SpeechManager()
{

}
