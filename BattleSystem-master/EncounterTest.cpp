// EncounterTest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <string>
#include "Encounter.h"
#include "windows.media.h" //enable music player
#pragma comment (lib, "winmm.lib") //enables music reader

//update 06-04-2017 ver 0.02 by Callum Buchanan
//update 07-04-2017 ver 0.03 by Callum Buchanan

using namespace std;

int main()
{
	string exit_i;
	Enounter encount1;

	//set the enemy details
	encount1.setEnemyDetails("Crab", 25, 3);

	//set the player details
	encount1.setPlayerDetails("Danny", 30, 3);
	encount1.battle();
	system("pause");
    return 1;
}

