//BATTLE SYSTEM
//by Danny Marshall and Callum Buchanan
#include "stdafx.h"
#include "Encounter.h"
#include <string>
#include "windows.media.h" //enable music player
#pragma comment (lib, "winmm.lib") //enables music reader
#include <algorithm> //enables string transform() function 

/*
	created 05-04-2017 ver 0.01 by Danny Marshall
	update 06-04-2017 ver 0.02 by Callum Buchanan:	-added music playback	 
													-added block
													-added spell system	 
													-added wait system	
													-added bomb option
													-added menu's
													-added menu loop
													-added run option

	update 07-04-2017 ver 0.03 by Callum Buchanan:	-added menu ascii art	 
													-fixed player death check	
													-optimized audio playback	
													-added killself option		*/

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

void battleOver()
{
	cout << "=======================================================================" << endl;
	cout << endl;
	cout << endl;
	cout << "\t\tBATTLE" << endl;
	cout << endl;
	cout << "\t\t OVER" << endl;
	cout << endl;
	cout << endl;
	cout << "=======================================================================" << endl;
	cout << endl;
}

void battleWon()
{
	cout << "=======================================================================" << endl;
	cout << endl;
	cout << endl;
	PlaySoundA("ba_another.wav", NULL, SND_ASYNC);
	cout << "\t\tBATTLE" << endl;
	cout << endl;
	cout << "\t\t WON" << endl;
	cout << endl;
	cout << endl;
	cout << "=======================================================================" << endl;
	cout << endl;
}

void help()
{
	cout << "Input commands:" << endl;
	cout << endl;
	cout << "\t-attack" << endl;
	cout << "\t-block" << endl;
	cout << "\t-bomb" << endl;
	cout << "\t-cast" << endl;
	cout << "\t-help" << endl;
	cout << "\t-inventory\\i" << endl;
	cout << "\t-killself" << endl;
	cout << "\t-observe" << endl;
	cout << "\t-potion" << endl;
	cout << "\t-run" << endl;
	cout << "\t-_exit" << endl;
}

void intro()
{
	cout << endl;
	cout << "\tBATTLE SYSTEM\tver 0.3" << endl;
	cout << endl;
	cout << "by Danny Marshall and Callum Buchanan" << endl;
	cout << endl;
	cout << endl;
	cout << "-type 'help' for list of commands" << endl;
	cout << endl;
	cout << endl;
}


void ot(string user_s)
{
	cout << user_s << endl; //quicker output string
}

void ascii()
{
	cout << "=======================================================================" << endl;
}

void div()
{
	cout << endl;
}

bool quit;
bool dead;
string spell;
int potionCounter = 10;
int run;
int spellWait = 0;
int attackWait = 1;
bool win = false;

void Enounter::battle()
{
	int incorrect = 0;
	quit = false;
	string playerInput;
	int damage;
	int hit;
	ascii();
	div();
	cout << "Enter Name: ";
	getline(cin, playerName);
	div();
	ascii();
	intro();
	PlaySoundA("wait.wav", NULL, SND_FILENAME);
	int wait;
	bool enemyWait = false;
	ascii();
	div();
	cout << "A wild " << enemyName << " appears!" << endl;
	//WHILE BATTLE WON OR PLAYER DEATH CONDITION NOT MET CONTINUE BATTLE
	while (!quit && playerHP > 0)
	{
		div();
		spellWait--;
		quit = false;
		//IF SPELL IS CHARGING
		if (spell == "")
		{
			spellWait = 0;
			ascii();
			div();
			cout << "Health: " << playerHP << endl;
		}
		else
		{
			if (spellWait <= 0)
			{
				spellWait = 0;
				ascii();
				cout << "Health: " << playerHP << endl;
				ascii();
				div();
				PlaySoundA("wait2.wav", NULL, SND_FILENAME);
				cout << playerName << " unleashes their energy!" << endl;
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				div();
			}
			else
			{
				ascii();
				div();
				cout << "Health: " << playerHP; cout << "\tSpell Timer: " << spellWait << endl;
			}
			
		}
		//IF SPELL COUNTER = 0
		if (spellWait <= 0)
		{
			if (spell == "FLARE")
			{
				damage = 5;
				cout << playerName << " casts Flare!" << endl;
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				cout << playerName + " deals " + to_string(damage) + " damage to " + enemyName << endl;
				PlaySoundA("flameburst1.wav", NULL, SND_FILENAME);
				div();
				enemyHP = enemyHP - damage;
				if (enemyHP <= 0)
				{
					ascii();
					div();
					cout << enemyName + " has been slain!!\n\n";
					battleWon();
					//SET ITEM DISCOVERY AFTER DEATH
					/*win = true;*/
					//EXIT WHILE LOOP
					quit = true;
					break;
				}
				else
				{
					cout << enemyName + " attacks!\n";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					hit = rand() % 6 + 1;
					//ENEMY HIT FAIL
					if (hit < 3)
					{
						cout << enemyName + " misses!" << endl;
						PlaySoundA("claw_miss2.wav", NULL, SND_FILENAME);
					}
					//ENEMT HIT SUCCESS
					else
					{
						damage = rand() % 10 + 1;
						cout << enemyName + " deals " + to_string(damage) + " damage to " + playerName << endl;
						PlaySoundA("claw_strike2.wav", NULL, SND_FILENAME);
						playerHP = playerHP - damage;
					}
				}
				//CLEAR EQUIPPED SPELL
				spell = "";
				attackWait = 0;
				div();
				ascii();
				cout << "Health: " << playerHP << endl;
			}
			else if (spell == "FREEZE")
			{
				cout << playerName << " casts freeze!" << endl;
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				div();
				wait = 3;
				cout << enemyName << " has frozen in place!" << endl;
				//CLEAR EQUIPPED SPELL
				spell = "";
				attackWait = 0;
				div();
				ascii();
				cout << "Health: " << playerHP << endl;
			}
			else if (spell == "SHIELD")
			{
				cout << playerName << " is surrounded by a protective bubble!" << endl;
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				div();
				cout << enemyName + " attacks!\n";
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				hit = rand() % 6 + 1;
				//ENEMY HIT FAIL
				if (hit < 3)
				{
					cout << enemyName + " misses!" << endl;
					PlaySoundA("claw_miss2.wav", NULL, SND_FILENAME);
				}
				//ENEMT HIT SUCCESS
				else
				{
					damage = rand() % 3 + 1;
					cout << enemyName + " deals " + to_string(damage) + " damage to " + playerName << endl;
					PlaySoundA("claw_strike3.wav", NULL, SND_FILENAME);
					playerHP = playerHP - damage;
				}
				//CLEAR EQUIPPED SPELL
				spell = "";
				attackWait = 0;
				div();
				ascii();
				cout << "Health: " << playerHP << endl;
			}
			else
			{
				attackWait = 0;
			}
		}	
		div();
		cout << playerName << "'s turn: ";
		PlaySoundA("in.wav", NULL, SND_ASYNC);
		getline(cin, playerInput);	

		//CONVERTS STRING TO UPPERCASE FOR SPELLING CATCH
		transform(playerInput.begin(), playerInput.end(), playerInput.begin(), ::toupper);
		div();
		ascii();
		div();
		//ATTACK
		if (playerInput == "ATTACK")
		{
			if (attackWait > 0)
			{
				cout << "Charging spell cannot attack!" << endl;
				spellWait++;
			}
			else
			{
				//PLAYER TURN
				cout << playerName + " attacks!\n";
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				hit = rand() % 6 + 1;

				//HIT PASS
				if (hit > 3)	
				{
					damage = rand() % 10 + 1;
					cout << playerName + " deals " + to_string(damage) + " damage to " + enemyName + "\n";
					PlaySoundA("claw_strike1.wav", NULL, SND_FILENAME);
					enemyHP = enemyHP - damage;
					div();
					//ENEMY HEALTH CHECK
					if (enemyHP <= 0) 
					{
						ascii();
						div();
						cout << enemyName + " has been slain!!\n\n";
						battleWon();
						//SET ITEM DISCOVERY AFTER DEATH
						win = true;
						//EXIT WHILE LOOP
						quit = true;
					}
					//ENEMY TURN
					else	
					{
						cout << enemyName + " attacks!\n";
						PlaySoundA("wait.wav", NULL, SND_FILENAME);
						hit = rand() % 6 + 1;
							
						//HIT FAIL
						if (hit < 3)
						{
							cout << enemyName + " misses!" << endl;
							PlaySoundA("claw_miss2.wav", NULL, SND_FILENAME);
						}
						//HIT PASS
						else
						{
							damage = rand() % 10 + 1;
							cout << enemyName + " deals " + to_string(damage) + " damage to " + playerName + "\n";
							PlaySoundA("claw_strike2.wav", NULL, SND_FILENAME);
							playerHP = playerHP - damage;
						}
					}
				}

				//HIT FAIL
				else
				{
					//ENEMY TURN
					cout << playerName << " misses!" << endl;
					PlaySoundA("claw_miss2.wav", NULL, SND_FILENAME);
					div();
					cout << enemyName + " attacks!" << endl;
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					hit = rand() % 6 + 1;

					//HIT FAIL
					if (hit < 3)
					{
						cout << enemyName + " misses!" << endl;
						PlaySoundA("claw_miss1.wav", NULL, SND_FILENAME);
					}
					//HIT PASS
					else
					{
						damage = rand() % 10 + 1;
						cout << enemyName << " deals " << to_string(damage) << " damage to " << playerName << endl;
						playerHP = playerHP - damage;
						PlaySoundA("claw_strike1.wav", NULL, SND_FILENAME);
					}
				}
				spellWait++;
			}
			incorrect = 0;
		}

		//BLOCK 
		else if (playerInput == "BLOCK")
		{
			cout << playerName + " braces for impact!" << endl;
			PlaySoundA("wait.wav", NULL, SND_FILENAME);
			div();

			hit = rand() % 6 + 1;
			if (hit < 3)
			{
				cout << enemyName + " attacks!\n";
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				cout << enemyName + " misses!" << endl;
				PlaySoundA("claw_miss2.wav", NULL, SND_FILENAME);
			}
			else
			{
				cout << enemyName + " attacks!\n";
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				damage = rand() % 10 + 1;
				damage = damage / 2;
				cout << enemyName << " deals " << to_string(damage) << " damage to " << playerName << endl;
				PlaySoundA("block.wav", NULL, SND_FILENAME);
				playerHP = playerHP - damage;

			}
			incorrect = 0;
		}

		//BOMB
		else if (playerInput == "BOMB")
		{
			if (attackWait <= 0)
			{
				damage = 4;
				cout << playerName << " throws a bomb!" << endl;
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				cout << playerName + " deals " + to_string(damage) + " damage to " + enemyName + "\n";
				PlaySoundA("flameburst1.wav", NULL, SND_FILENAME);
				div();
				enemyHP = enemyHP - damage;
				if (enemyHP <= 0)
				{
					ascii();
					div();
					cout << enemyName + " has been slain!!\n\n";
					battleWon();
					//SET ITEM DISCOVERY AFTER DEATH
					/*win = true;*/
					//EXIT WHILE LOOP
					quit = true;
				}
				else
				{
					cout << enemyName + " attacks!\n";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					hit = rand() % 6 + 1;
					//ENEMY HIT FAIL
					if (hit < 3)
					{
						cout << enemyName + " misses!" << endl;
						PlaySoundA("claw_miss2.wav", NULL, SND_FILENAME);
					}
					//ENEMT HIT SUCCESS
					else
					{
						damage = rand() % 10 + 1;
						cout << enemyName + " deals " + to_string(damage) + " damage to " + playerName + "\n";
						PlaySoundA("claw_strike2.wav", NULL, SND_FILENAME);
						playerHP = playerHP - damage;
					}
				}
			}
			else
			{
				cout << "Charging spell cannot attack!" << endl;
				spellWait++;
			}
		}

		//EXIT
		else if (playerInput == "_EXIT")
		{
			//EXIT WHILE LOOP
			win = true;
			quit = true;
		}

		//HELP
		else if (playerInput == "HELP")
		{
			help();
			incorrect = 0;
			spellWait++;
		}

		//INVENTORY
		else if (playerInput == "INVENTORY")
		{
			cout << "\tPotions: " << potionCounter << endl;
			spellWait++;
			incorrect = 0;

		}

		//INVENTORY
		else if (playerInput == "I")
		{
			cout << "\tPotions: " << potionCounter << endl;
			spellWait++;
			incorrect = 0;
		}

		//KILLSELF
		else if (playerInput == "KILLSELF")
		{
			playerHP = 0;
			quit = true;
		}

		//OBSERVE
		else if (playerInput == "OBSERVE")
		{
			cout << "\tEnemy Health: " << enemyHP << endl;
			div();
			ascii();
			div();
			PlaySoundA("wait.wav", NULL, SND_FILENAME);
			cout << enemyName + " starts to attack!\n";
			PlaySoundA("wait.wav", NULL, SND_FILENAME);
			hit = rand() % 6 + 1;
			//ENEMY HIT FAIL
			if (hit < 3)
			{
				cout << enemyName + " misses!" << endl;
				PlaySoundA("claw_miss2.wav", NULL, SND_FILENAME);
			}
			//ENEMT HIT SUCCESS
			else
			{
				damage = rand() % 10 + 1;
				cout << enemyName + " deals " << to_string(damage) << " damage to " << playerName << endl;
				PlaySoundA("claw_strike3.wav", NULL, SND_FILENAME);
				playerHP = playerHP - damage;
			}
			incorrect = 0;
		}

		//POTION 
		else if (playerInput == "POTION")
		{
			//CHECKS POTION COUNT
			if (potionCounter < 1)
			{
				ot("No More Potions!!");
			}
			else if (playerHP == 30)
			{
				ot("Already at full health!");
			}
			//HEAL PLAYER
			else
			{
				potionCounter--;
				playerHP = playerHP + 7;
				//CATCHES HEALTH EXCEEDING 10
					
				//ADD STANDARD HEALING TO HEALTH
				if (playerHP > 30)
				{
					playerHP = 25;
					cout << "Health fully restored!" << endl;
					PlaySoundA("swingpsi1.wav", NULL, SND_FILENAME);	
				}
				else
				{	
					cout << "+6 Health restored!" << endl;
					PlaySoundA("swingpsi1.wav", NULL, SND_FILENAME);		
				}
				//ENEMY TURN AFTER PLAYER
				div();
				cout << enemyName + " attacks!\n";
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				hit = rand() % 6 + 1;
				//ENEMY MISS
				if (hit < 3)
				{	
					cout << enemyName + " misses!" << endl;
					PlaySoundA("claw_miss2.wav", NULL, SND_FILENAME);
				}
				//ENEMY HIT
				else
				{
					damage = rand() % 10 + 1;
					cout << enemyName + " deals " + to_string(damage) + " damage to " + playerName + "\n";
					PlaySoundA("claw_strike2.wav", NULL, SND_FILENAME);
					playerHP = playerHP - damage;
				}
			}
			incorrect = 0;
		}

		//SPELLS
		else if (playerInput == "CAST")
		{
			bool inputOk = false;
			while (!inputOk)
			{
				ot("\tFlare:\tCharge - 2 \tDamage - 5");
				ot("\tShield:\tCharge - 1 \tDefence - 5");
				ot("\tFreeze:\tCharge - 3 \tEffect - 2");
				div();
				cout << "Enter Spell to Cast: ";
				PlaySoundA("in.wav", NULL, SND_ASYNC);
				getline(cin, playerInput);
				transform(playerInput.begin(), playerInput.end(), playerInput.begin(), ::toupper);
				div();
				ascii();
				div();
				//FLARE
				if (playerInput == "FLARE")
				{
					spell = "FLARE";
					inputOk = true;
					spellWait = 3;
					attackWait = 1;
					cout << playerName << " starts to focus";
					cout << ".";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					cout << ".";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					cout << "." << endl;
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					div();
					cout << enemyName << " attacks!" << endl;
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					hit = rand() % 6 + 1;

					//ENEMY HIT FAIL
					if (hit < 3)
					{		
						cout << enemyName + " misses!" << endl;
						PlaySoundA("claw_miss2.wav", NULL, SND_FILENAME);
					}
					//ENEMT HIT SUCCESS
					else
					{
						damage = rand() % 10 + 1;
						cout << enemyName + " deals " + to_string(damage) + " damage to " + playerName << endl;
						PlaySoundA("claw_strike3.wav", NULL, SND_FILENAME);
						playerHP = playerHP - damage;
					}
				}
				//SHIELD
				else if (playerInput == "SHIELD")
				{
					spell = "SHIELD";
					inputOk = true;
					spellWait = 3;
					attackWait = 1;
					cout << playerName + " starts to focus";
					cout << ".";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					cout << ".";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					cout << "." << endl;
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					div();
					cout << enemyName + " attacks!\n";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					hit = rand() % 6 + 1;
					//ENEMY HIT FAIL
					if (hit < 3)
					{
						cout << enemyName + " misses!" << endl;
						PlaySoundA("claw_miss1.wav", NULL, SND_FILENAME);
					}
					//ENEMT HIT SUCCESS
					else
					{
						damage = rand() % 10 + 1;
						cout << enemyName + " deals " + to_string(damage) + " damage to " + playerName + "\n";
						PlaySoundA("claw_strike3.wav", NULL, SND_FILENAME);
						playerHP = playerHP - damage;
					}
				}
				//FREEZE
				else if (playerInput == "FREEZE")
				{
					inputOk = true;
					spellWait = 4;
					attackWait = 1;
					spell = "FREEZE";
					cout << playerName + " starts to focus";
					cout << ".";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					cout << ".";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					cout << "." << endl;
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					div();
					cout << enemyName + " attacks!\n";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					hit = rand() % 6 + 1;
					//ENEMY HIT FAIL
					if (hit < 3)
					{
						cout << enemyName + " misses!" << endl;
						PlaySoundA("claw_miss1.wav", NULL, SND_FILENAME);
					}
					//ENEMT HIT SUCCESS
					else
					{
						damage = rand() % 10 + 1;
						cout << enemyName + " deals " + to_string(damage) + " damage to " + playerName + "\n";
						PlaySoundA("claw_strike1.wav", NULL, SND_FILENAME);
						playerHP = playerHP - damage;
					}
				}
				else if (playerInput == "BACK")
				{
					inputOk = true;
					spellWait++;
				}
				else
				{
					ot("I don't understand");
					div();
					inputOk = false;
					spellWait++;
				}
			}
			incorrect = 0;
		}

		//RUN 
		else if (playerInput == "RUN")
		{
			run = rand() % 30 + 1;
			if (spell == "")
			{
				cout << playerName << " tries to flee";
				cout << ".";
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				cout << ".";
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				cout << "." << endl;
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				if (run < 10)
				{
					div();
					PlaySoundA("run.wav", NULL, SND_ASYNC);
					cout << playerName + " fled the battle!" << endl;
					div();
					battleOver();
					quit = true;
				}
				else
				{
					cout << playerName + " failed to run away!" << endl;
					div();
					cout << enemyName + " attacks!\n";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					hit = rand() % 6 + 1;
					//ENEMY HIT FAIL
					if (hit < 3)
					{
						cout << enemyName + " misses!" << endl;
						PlaySoundA("claw_miss1.wav", NULL, SND_FILENAME);
							
					}
					//ENEMT HIT SUCCESS
					else
					{
						damage = rand() % 15 + 1;
						cout << enemyName + " deals " << to_string(damage) << " damage to " << playerName << endl;
						PlaySoundA("claw_strike3.wav", NULL, SND_FILENAME);
						playerHP = playerHP - damage;
					}
				}
			}
			else
			{
				cout << playerName << " stopped focusing!" << endl;
				spell = "";
				cout << playerName << " tries to flee" << endl;
				cout << ".";
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				cout << ".";
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				cout << "." << endl;
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				div();
				if (run < 10)
				{
					PlaySoundA("run.wav", NULL, SND_ASYNC);
					cout << playerName + " fled the battle!" << endl;
					battleOver();
					quit = true;
				}
				else
				{
					cout << playerName + " failed to run away!" << endl;
					cout << enemyName + " attacks!\n";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					hit = rand() % 6 + 1;
					//ENEMY HIT FAIL
					if (hit < 3)
					{
						cout << enemyName + " misses!" << endl;
						PlaySoundA("claw_miss2.wav", NULL, SND_FILENAME);
					}
					//ENEMT HIT SUCCESS
					else
					{
						damage = rand() % 15 + 1;
						cout << enemyName + " deals " << to_string(damage) << " damage to " << playerName << endl;
						PlaySoundA("claw_strike3.wav", NULL, SND_FILENAME);
						playerHP = playerHP - damage;
					}
				}
			}

			incorrect = 0;
		}

		//ERROR CATCH
		else
		{
			incorrect++;
			if (incorrect == 3)
			{
				cout << "I don't understand?" << endl;
				div();
				cout << "\t\tTRY THESE COMMMANDS" << endl;
				help();
				incorrect = 0;
			}
			else
			{
				cout << "I don't understand?" << endl;
			}
			spellWait++;
		}	//end ERROR CATCH

	}	//end menu while loop

	//PLAYERDEATH!
	if (playerHP <= 0)
	{
		cout << "Health: " << playerHP << endl;
		div();
		ascii();
		div();
		cout << playerName << " fell the the ground and died!" << endl;
		div();
		ascii();
		div();
		div();
		ot("\t\tG\tA\tM\tE");
		div();
		ot("\t\tO\tV\tE\tR");
		div();
		div();
		ascii();
		div();
		PlaySoundA("scream_far3.wav", NULL, SND_ASYNC);
	}

} //END
