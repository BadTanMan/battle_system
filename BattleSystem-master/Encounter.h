#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;
	class Enounter
	{
		string enemyName;
		int enemyHP = 0;
		int enemyAttack = 0;
		string playerName;
		int playerHP = 0;
		int potionCount = 0;

	public:
		void setPlayerDetails(string, int, int);
		void setEnemyDetails(string, int, int);
		void battle();
	};


