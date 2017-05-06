#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

class Player
{
public:
	void setPlayerDetails(string pName, int pHP, int potCount, int bCount)
	{
		playerName = pName;
		playerHP = pHP;
		potionCount = potCount;
		bombCount = bCount;
	}

protected:	string playerName;
			int playerHP = 0;
			int potionCount = 0;
			int bombCount = 0;
};

class Monsters
{
protected:	string enemyName;
			int enemyHP = 0;
			int enemyAttack = 0;
public:
	void setEnemyDetails(string eName, int eHP, int eAtt)
	{
		enemyName = eName;
		enemyHP = eHP;
		enemyAttack = eAtt;
	}
};

class Encounter : public Player, public Monsters
{
public:
	void battle();
	void enemyTurn();
};


