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
	Encounter encount1;	
	encount1.setPlayerDetails("Jack", 30, 10, 10);
	encount1.setEnemyDetails("Crab", 25, 10);
	encount1.battle();
	system("pause");
    return 1;
}

