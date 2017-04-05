
#include "stdafx.h"
#include "Encounter.h"
#include <string>
#include "windows.media.h" //enable music player
#pragma comment (lib, "winmm.lib") //enables music reader
#include <algorithm> //enables string transform() function 
using namespace std;


void Enounter::setPlayerDetails(string pName, int pHP, int potCount)
{
	playerName = pName;
	playerHP = pHP;
	potionCount = potCount;
}

void Enounter::setEnemyDetails(string eName, int eHP, int eAtt)
{
	enemyName = eName;
	enemyHP = eHP;
	enemyAttack = eAtt;
}

void help()
{
	cout << "Input commands:" << endl;
	cout << "\t-attack" << endl;
	cout << "\t-block" << endl;
	cout << "\t-inventory\\i" << endl;
	cout << "\t-observe" << endl;
	cout << "\t-potion" << endl;
	cout << "\t-run" << endl;
	cout << "\t-_exit" << endl;
	
}

void div()
{
	cout << endl;
}

bool quit;
bool dead;
int potionCounter = 3;
int run;

void Enounter::battle()
{
	//PlaySoundA(LPCSTR("yourLoveIsADrug.wav"), NULL, SND_LOOP | SND_ASYNC);		//music will start here
	quit = false;
	string playerInput;
	int damage;
	int hit;
	cout << "Enter Name: ";
	getline(cin, playerName);
	cout << endl;
	cout << "BATTLE SYSTEM \tVER:0.2\tby Callum Buchanan" << endl;
	cout << endl;
	cout << "-type 'help' for list of commands" << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "You see a crab!" << endl;

	//WHILE BATTLE WON OR PLAYER DEATH CONDITION NOT MET CONTINUE BATTLE
	while (!quit && playerHP > 0)
	{
		div();
	    quit = false;
		
		//CHECK ENEMY HEALTH FOR BATTLE VICTORY CONDITION
		if (enemyHP < 0)
		{
			cout << "Battle Won!" << endl;
			//EXIT WHILE LOOP
			quit = true;
		}
		else
		{
			cout << "What will " + playerName + " do?\t\tHealth: " << playerHP << endl;
			//GRABS ENTIRE INPUT LINE RATHER THAN WORD BY WORD TO AVOID UNWANTED MENU REPITITION 
			getline (cin, playerInput);
			div();
			//CONVERTS STRING TO UPPERCASE FOR SPELLING CATCH
			transform(playerInput.begin(), playerInput.end(), playerInput.begin(), ::toupper);
			//ATTACK OPTION
			if (playerInput == "ATTACK")
			{
				cout << playerName + " readies his weapon!\n";
				hit = rand() % 6 + 1;
				//HIT SUCCESS
				if (hit > 3)
				{
					damage = rand() % 10 + 1;
					cout << playerName + " deals " + to_string(damage) + " damage to " + enemyName + "\n";
					enemyHP = enemyHP - damage;
					
					if (enemyHP < 0)
					{
						cout << enemyName + " has been slain!!\n\n";
					}
					else
					{
						cout << enemyName + " begins to attack!\n";
						hit = rand() % 6 + 1;
						//ENEMY HIT FAIL
						if (hit < 3)
						{
							cout << enemyName + " misses!" << endl;
						}
						//ENEMT HIT SUCCESS
						else
						{
							damage = rand() % 10 + 1;
							cout << enemyName + " deals " + to_string(damage) + " damage to " + playerName + "\n";
							playerHP = playerHP - damage;
						}
					}
				}
				//HIT FAIL
				else
				{
					cout << playerName << " misses" << endl;
					cout << enemyName + " begins to attack!\n";
					hit = rand() % 6 + 1;
					//ENEMY HIT FAIL
					if (hit < 3)
					{
						cout << enemyName + " misses!" << endl;
					}
					//ENEMT HIT SUCCESS
					else
					{
						damage = rand() % 10 + 1;
						cout << enemyName + " deals " + to_string(damage) + " damage to " + playerName + "\n";
						playerHP = playerHP - damage;
					}
				}	
			}
			//EXIT OPTION
			else if (playerInput == "_EXIT")
			{
				//EXIT WHILE LOOP
				quit = true;
			}
			//DRINK POTION OPTION
			else if (playerInput == "POTION")
			{
				//CHECKS POTION COUNT
				if (potionCounter < 1)
				{
					cout << "No more potions!" << endl;
				}
			    //HEAL PLAYER
				else
				{
					potionCounter--;
					playerHP = playerHP + 6;
					//CATCHES HEALTH EXCEEDING 10
					if (playerHP == 25)
					{
						cout << playerName << " is already healthy!" << endl;
					}
					//ADD STANDARD HEALING TO HEALTH
					else if (playerHP > 25)
					{
						playerHP = 25;
						cout << "Health fully restored!" << endl;
					}
					else
					{
						cout << "+6 Health restored!" << endl;
					}
					//ENEMY TURN AFTER PLAYER
					div();
					cout << enemyName + " begins to attack!\n";
					hit = rand() % 6 + 1;
					if (hit < 3)
					{
						cout << enemyName + " misses!" << endl;
					}
					else
					{
						damage = rand() % 10 + 1;
						cout << enemyName + " deals " + to_string(damage) + " damage to " + playerName + "\n";
						playerHP = playerHP - damage;
					}
				}
			}

			//BLOCK OPTION
			else if (playerInput == "BLOCK")
			{
				cout << enemyName + " begins to attack!\n";
				cout << playerName + " braces for impact!" << endl;
				hit = rand() % 6 + 1;
				if (hit < 3)
				{
					cout << enemyName + " misses!" << endl;
				}
				else
				{
					damage = rand() % 10 + 1;
					damage = damage / 2;
					cout << enemyName << " deals " << to_string(damage) << " damage to " << playerName << endl;
					playerHP = playerHP - damage;
				}
			}
			//RUN OPTION
			else if (playerInput == "RUN")
			{
				run = rand() % 175 + 1;
				if (run < 10)
				{
					cout << playerName + " fled the battle" << endl;
					quit = true;
				}
				else
				{
					cout << playerName+ " failed to run away!" << endl;
					cout << enemyName + " begins to attack!\n";
					hit = rand() % 6 + 1;
					//ENEMY HIT FAIL
					if (hit < 3)
					{
						cout << enemyName + " misses!" << endl;
					}
					//ENEMT HIT SUCCESS
					else
					{
						damage = rand() % 15 + 1;
						cout << enemyName + " deals " << to_string(damage) << " damage to " << playerName << endl;
						playerHP = playerHP - damage;
					}
				}
			}
			//DISPLAYS INVENTORY
			else if (playerInput == "INVENTORY")
			{
				cout << "\tPotions: " << potionCounter <<"\tHealth: " << playerHP << endl;
			}
			//DISPLAYS INVENTORY
			else if (playerInput == "I")
			{
				cout << "\tPotions: " << potionCounter << "\tHealth: " << playerHP << endl;
			}
			//DISPLAYS ENEMY HEALTH
			else if (playerInput == "OBSERVE")
			{
				cout << "\tEnemy Health: " << enemyHP << endl;
				div();
				cout << enemyName + " starts to attack!\n";
				hit = rand() % 6 + 1;
				//ENEMY HIT FAIL
				if (hit < 3)
				{
					cout << enemyName + " misses!" << endl;
				}
				//ENEMT HIT SUCCESS
				else
				{
					damage = rand() % 10 + 1;
					cout << enemyName + " deals " << to_string(damage) << " damage to " << playerName << endl;
					playerHP = playerHP - damage;
				}
			}
			//DISPLAYS LIST OF INPUT COMMANDS
			else if (playerInput == "HELP")
			{
				help();
			}
			//ERROR CATCH
			else
			{
				cout << "I don't understand?" << endl;
			}
		}	
	}
	if (!quit)
	{
		cout << "Health: " << playerHP << endl;
		cout << playerName << " died!" << endl;
		div();
		cout << "\t\tG\tA\tM\tE" << endl;
		div();
		cout << "\t\tO\tV\tE\tR" << endl;
		div();
		div();
	}
}
