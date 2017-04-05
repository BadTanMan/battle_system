// EncounterTest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <string>
#include "Encounter.h"
using namespace std;

string halt;
int main()
{
	Enounter encount1;

	//set the enemy details
	encount1.setEnemyDetails("Crab", 25, 3);

	//set the player details
	encount1.setPlayerDetails("Danny", 25, 3);
	encount1.battle();
    return 0;
}

