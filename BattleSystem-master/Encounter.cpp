//BATTLE SYSTEM
//by Danny Marshall and Callum Buchanan
/*
created 05-04-2017 ver 0.1 by Danny Marshall
update 06-04-2017 ver 0.2 by Callum Buchanan:	-added music playback
												-added block
												-added spell system
												-added wait system
												-added bomb option
												-added menu's
												-added menu loop
												-added run option

update 07-04-2017 ver 0.3 by Callum Buchanan:	-added menu ascii art
												-fixed player death check
												-optimized audio playback
												-added killself option

update 07-04-2017 ver 0.4 by Callum Buchanan:	-input detects sentences and multiple words
												-spell system reduces spell counter properly
												-bomb option catches incorrect input counter correctly

update 08-04-2017 ver 0.05 by Danny Marshall	- fixed up classes to seperate information
												- changed from third person to second person
												- got rid of the playerName since it is now useless
												- made an enemyTurn method to reduce code
												- added freezeCounter and a forzen mechanic

update 15-04-2017 ver 0.6 by Callum Buchanan	-fixed class setters so class details can be implemented and manipulated in Encounter.cpp
												-fixed freeze spell displaying "Enemy Attacks" twice
												-added bombCounter
												-minor syntactical fixes
*/

#include "stdafx.h"
#include "Encounter.h"
#include "windows.media.h" //enables music player
#pragma comment (lib, "winmm.lib") //enables music reader
#include <algorithm> //enables string transform() function 
#include <ctime> // Needed to make random number generator "random"

using namespace std;

//BATTLE OVER TEXT
void battleOver()
{
	cout << "=========================================================================" << endl;
	cout << endl;
	cout << "\t\t\t\tBATTLE" << endl;
	cout << endl;
	cout << "\t\t\t\t OVER" << endl;
	cout << endl;
	cout << endl;
	cout << "=========================================================================" << endl;
	cout << endl;
}
//BATTLE WON TEXT
void battleWon()
{
	cout << "=========================================================================" << endl;
	cout << endl;
	PlaySoundA("ba_another.wav", NULL, SND_ASYNC);
	cout << "\t\t\t\tBATTLE" << endl;
	cout << endl;
	cout << "\t\t\t\t WON" << endl;
	cout << endl;
	cout << endl;
	cout << "=========================================================================" << endl;
	cout << endl;
}
//HELP TEXT
void help()
{
	cout << "Input commands:" << endl;
	cout << endl;
	cout << "\tattack\\hit" << endl;
	cout << "\tblock\\defend" << endl;
	cout << "\tthrow bomb\\bomb\\bombs" << endl;
	cout << "\tspells\\cast spell" << endl;
	cout << "\thelp" << endl;
	cout << "\tinventory\\i" << endl;
	cout << "\tkillself" << endl;
	cout << "\tcheck enemy\\observe" << endl;
	cout << "\tdrink potion\\potion" << endl;
	cout << "\trun away\\run" << endl;
	cout << "\texit\\quit" << endl;
}
//INTRO TEXT
void intro()
{
	cout << "\t\t\tBATTLE SYSTEM\tver 0.5" << endl;
	cout << endl;
	cout << "\t\tby Danny Marshall and Callum Buchanan" << endl;
	cout << endl;
	cout << endl;
	cout << "-type 'help' for list of commands" << endl;
	cout << endl;
	cout << endl;
}
//OUTPUT STRING
void ot(const string& user_s)
{
	cout << user_s << endl; //quicker output string
}
//ASCII ART
void ascii()
{
	cout << "=========================================================================" << endl;
}
//SINGLE ENDL
void div()
{
	cout << endl;
}
//DOUBLE ENDL
void dbldiv()
{
	cout << endl;
	cout << endl;
}
//VARIABLES
string spell;
string playerInput;
bool quit = false;
bool spellReady = false;
int damage;
int hit;
int run;
int spellWait = 0;
int attackWait = 1;
int incorrect = 0;
//ENEMY TURN METHOD
void Encounter::enemyTurn()
{
		ot((enemyName + " attacks!"));
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
			cout << enemyName << " deals " << to_string(damage) << " damage to you." << endl;
			playerHP = playerHP - damage;
			PlaySoundA("claw_strike1.wav", NULL, SND_FILENAME);
		}
}

//MAIN
void Encounter::battle()
{
	srand(time(0));
	int freezeCounter = 0;
	ascii();
	div();
	ascii();
	intro();
	PlaySoundA("wait.wav", NULL, SND_FILENAME);
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
			ot("Health: " + to_string(playerHP));
		}
		else
		{
			if (spellWait <= 0)
			{
				spellWait = 0;
				ascii();
				ot("Health: " + to_string(playerHP));
				ot("\t\tSpell Timer: " + to_string(spellWait));
				ascii();
				PlaySoundA("wait2.wav", NULL, SND_FILENAME);
				ot("You unleash your energy!");
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				div();
			}
			else
			{
				ascii();
				ot("Health: " + to_string(playerHP));
				ot("\t\tSpell Timer: " + to_string(spellWait));
				div();
			}
		}
		//IF SPELL COUNTER = 0
		if (spellWait <= 0)
		{
			if (spell == "FLARE")
			{
				damage = 5;
				cout << "You cast Flare!" << endl;
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				ot(("You deal " + to_string(damage) + " damage to " + enemyName));
				PlaySoundA("flameburst1.wav", NULL, SND_FILENAME);
				div();
				enemyHP = enemyHP - damage;
				if (enemyHP <= 0)
				{
					ascii();
					div();
					ot((enemyName + " has been slain!!"));
					div();
					battleWon();
					//SET ITEM DISCOVERY AFTER DEATH
					/*win = true;*/
					//EXIT WHILE LOOP
					quit = true;
					break;
				}
				else
				{
					enemyTurn();
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
				ot("You cast freeze!");
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				div();
				ot(enemyName + " has frozen in place!");
				freezeCounter = 3;
				//CLEAR EQUIPPED SPELL
				spell = "";
				attackWait = 0;
				div();
				ascii();
				ot("Health: " + to_string(playerHP));
			}
			else if (spell == "SHIELD")
			{
				ot("You are surrounded by a protective bubble!");
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				div();	
				enemyTurn();
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
		cout << "Your turn: ";
		PlaySoundA("in.wav", NULL, SND_ASYNC);
		//GRABS ENTIRE LINE
		getline(cin, playerInput);
		//CONVERTS STRING TO UPPERCASE FOR SPELLING CATCH
		transform(playerInput.begin(), playerInput.end(), playerInput.begin(), ::toupper);
		div();
		ascii();
		//ATTACK
		if (playerInput == "ATTACK" || playerInput == "STRIKE" || playerInput == "HIT")
		{
			div();
			if (attackWait > 0)
			{
				ot("Charging spell cannot attack!");
				spellWait++;
			}
			else
			{
				//PLAYER TURN
				ot("You attack!");
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				hit = rand() % 6 + 1;

				//HIT PASS
				if (hit > 3)
				{
					damage = rand() % 10 + 1;
					ot("You deal " + to_string(damage) + " damage to " + enemyName);
					PlaySoundA("claw_strike1.wav", NULL, SND_FILENAME);
					enemyHP = enemyHP - damage;
					div();
					//ENEMY HEALTH CHECK
					if (enemyHP <= 0)
					{
						ascii();
						div();
						ot(enemyName + " has been slain!!");
						div();
						battleWon();
						//EXIT WHILE LOOP
						quit = true;
					}

					else if (freezeCounter != 0)
					{
						ot(enemyName + " is frozen solid and cannot act!!");
						freezeCounter--;
					}
					//ENEMY TURN
					else
					{
						enemyTurn();
					}
				}

				//HIT FAIL
				else if (freezeCounter != 0)
				{
					ot("You miss!");
					ot(enemyName + " is frozen solid and cannot act!!");
					freezeCounter--;
				}

				else
				{
					//ENEMY TURN
					ot("You miss!");
					PlaySoundA("claw_miss2.wav", NULL, SND_FILENAME);
					div();
					enemyTurn();
				}
			}
			incorrect = 0;
		}

		//BLOCK 
		else if (playerInput == "DEFEND" || playerInput == "BLOCK")
		{
			div();
			ot("You brace for impact!");
			PlaySoundA("wait.wav", NULL, SND_FILENAME);
			div();

			hit = rand() % 6 + 1;
			if (freezeCounter != 0)
			{
				ot((enemyName + " is frozen solid and cannot act!!"));
				freezeCounter--;
			}
			else
			{
				enemyTurn();
			}

			incorrect = 0;
		}

		//BOMB
		else if (playerInput == "THROW BOMB" || playerInput == "BOMB" || playerInput == "THROW BOMBS" || playerInput == "BOMBS" || playerInput == "THROW A BOMB")
		{
			div();
			//CHECK SPELL COUNTER
			if (attackWait <= 0)
			{
				//CHECK BOMB COUNTER
				if (bombCount > 0)
				{
					damage = 4;
					ot("You throw a bomb!");
					bombCount--;
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					ot ("You deal " + to_string(damage) + " damage to " + enemyName);
					PlaySoundA("flameburst1.wav", NULL, SND_FILENAME);
					div();
					enemyHP = enemyHP - damage;
					//ENEMY HEALTH CHECK
					if (enemyHP <= 0)
					{
						ascii();
						div();
						ot((enemyName + " has been slain!!"));
						div();
						battleWon();
						quit = true;
					}
					//FREEZE SPELL CHECK
					else if (freezeCounter != 0)
					{
						ot(enemyName + " is frozen solid and cannot move!!");
						freezeCounter--;
					}
					else
					{
						enemyTurn();
					}
					
				}
				//NO BOMBS LEFT
				else	
				{
					ot("No more bombs left");
				}
			}
			else
			{
				ot("Charging spell cannot attack!");
				spellWait++;
			}

			incorrect = 0;
		}

		//EXIT
		else if (playerInput == "EXIT" || playerInput == "QUIT")
		{
			//EXIT WHILE LOOP
			quit = true;
		}

		//HELP
		else if (playerInput == "HELP")
		{
			help();

			spellWait++;
			incorrect = 0;
		}

		//INVENTORY
		else if (playerInput == "INVENTORY" || playerInput == "CHECK INVENTORY" || playerInput == "CHECK ITEMS" || playerInput == "I" || playerInput == "CHECK BAG" || playerInput == "CHECK SUPPLIES" || playerInput == "BAG")
		{
			div();
			ot("\tPotions: " + to_string(potionCount));
			ot("\tBombs: " + to_string(bombCount));
			spellWait++;
			incorrect = 0;
		}

		//KILLSELF
		else if (playerInput == "KILLSELF" || playerInput == "SUICIDE" || playerInput == "COMMIT SUICIDE")
		{
			div();
			playerHP = 0;
			quit = true;
		}

		//OBSERVE
		else if (playerInput == "OBSERVE" || playerInput == "ENEMY HEALTH" || playerInput == "CHECK ENEMY")
		{
			div();
			ot("\tEnemy Health: " + to_string(enemyHP));
			div();
			ascii();
			PlaySoundA("wait.wav", NULL, SND_FILENAME);
			if (freezeCounter != 0)
			{
				ot((enemyName + " is frozen solid and cannot act!!"));
				freezeCounter--;
			}
			else
			{
				enemyTurn();
			}

			incorrect = 0;
		}

		//POTION 
		else if (playerInput == "POTION" || playerInput == "DRINK POTION" || playerInput == "USE POTION")
		{
			div();
			//CHECKS POTION COUNT
			if (potionCount < 1)
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
				potionCount--;
				playerHP += 10;
				if (playerHP >= 30)
				{
					playerHP = 30;
					ot("Health fully restored!");
					PlaySoundA("swingpsi1.wav", NULL, SND_FILENAME);
				}
				else
				{
					ot("+10 Health restored!");
					PlaySoundA("swingpsi1.wav", NULL, SND_FILENAME);
				}
				//ENEMY TURN AFTER PLAYER
				div();
				if (freezeCounter != 0)
				{
					ot((enemyName + " is frozen solid and cannot act!!"));
					freezeCounter--;
				}
				else
				{
					enemyTurn();
				}
			}

			incorrect = 0;
		}

		//SPELLS
		else if (playerInput == "CAST" || playerInput == "SPELL" || playerInput == "CAST SPELL" || playerInput == "MAGIC" || playerInput == "SPELLS")
		{
			div();
			bool inputOk = false;
			while (!inputOk)
			{
				ot("\tFlare:\tCharge - 2 \tDamage - Does +5 damage to enemy");
				ot("\tShield:\tCharge - 2 \tEffect - Greatly reduces damage recieved");
				ot("\tFreeze:\tCharge - 2 \tEffect - Freezes enemy in place");
				div();
				ot("-enter BACK to quit spell menu-");
				div();
				ot("Enter spell to cast: ");
				PlaySoundA("in.wav", NULL, SND_ASYNC);
				getline(cin, playerInput);
				transform(playerInput.begin(), playerInput.end(), playerInput.begin(), ::toupper);
				div();
				ascii();
				//FLARE
				if (playerInput == "FLARE")
				{
					spell = "FLARE";
					inputOk = true;
					spellWait = 3;
					attackWait = 1;
					ot("You start to focus");
					cout << ".";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					cout << ".";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					cout << "." << endl;
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					div();
					if (freezeCounter != 0)
					{
						ot(( enemyName + " is frozen solid and cannot act!!"));
						freezeCounter--;
					}
					else
					{
						enemyTurn();
					}
				}
				//SHIELD
				else if (playerInput == "SHIELD")
				{
					spell = "SHIELD";
					inputOk = true;
					spellWait = 3;
					attackWait = 1;
					ot("You start to focus");
					cout << ".";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					cout << ".";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					cout << "." << endl;
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					div();
					if (freezeCounter != 0)
					{
						ot((enemyName + " is frozen solid and cannot act!!"));
						freezeCounter--;
					}
					else
					{
						enemyTurn();
					}
				}
				//FREEZE
				else if (playerInput == "FREEZE")
				{
					inputOk = true;
					spellWait = 4;
					attackWait = 1;
					spell = "FREEZE";
					ot("You start to focus");
					ot(".");
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					ot(".");
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					ot(".");
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					div();
					if (freezeCounter != 0)
					{
						ot((enemyName + " is frozen solid and cannot act!!"));
						freezeCounter--;
					}
					else
					{
						enemyTurn();
					}
				}
				//EXIT MENU
				else if (playerInput == "QUIT" || playerInput == "EXIT" || playerInput == "BACK" || playerInput == "CANCEL")
				{
					//EXIT WHILE LOOP
					inputOk = true;
					spellWait++;
				}
				//ERROR CATCH
				else
				{
					ot("I don't understand");
					div();
					inputOk = false;
				}
			}

			incorrect = 0;
		}

		//RUN 
		else if (playerInput == "RUN" || playerInput == "FLEE" || playerInput == "RETREAT" || playerInput == "RUN AWAY")
		{
			div();
			run = rand() % 30 + 1;
			if (spell == "")
			{
				ot("You try to flee");
				ot(".");
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				ot(".");
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				ot(".");
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				if (run < 10)
				{
					PlaySoundA("run.wav", NULL, SND_ASYNC);
					ot("You fled from the battle!");
					div();
					battleOver();
					quit = true;
				}
				else
				{
					ot("You failed to run away!");
					div();
					if (freezeCounter != 0)
					{
						ot((enemyName + " is frozen solid and cannot act!!"));
						freezeCounter--;
					}
					else
					{
						enemyTurn();
					}
				}
			}
			else
			{
				ot("You stopped focusing!");
				spell = "";
				ot("You try to flee");
				ot(".");
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				ot(".");
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				ot(".");
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				if (run < 10)
				{
					PlaySoundA("run.wav", NULL, SND_ASYNC);
					ot("You fled from the battle!");
					battleOver();
					quit = true;
				}
				else
				{
					ot("You failed to run away!");
					div();
					if (freezeCounter != 0)
					{
						ot((enemyName + " is frozen solid and cannot act!!"));
						freezeCounter--;
					}
					else
					{
						enemyTurn();
					}
				}
			}

			incorrect = 0;
		}

		//ERROR CATCH
		else
		{
			div();
			incorrect++;
			//DISPLAYS LIST OF COMMANDS UPON 3 INCORRECT ENTRIES
			if (incorrect == 3)
			{
				ot("I don't understand?");
				div();
				ot("\t\tTRY THESE COMMMANDS");
				help();
				incorrect = 0;
			}
			else
			{
				ot("I don't understand?");
			}
			spellWait++;
		}	//end ERROR CATCH

	}	//end menu while loop

	//PLAYERDEATH!	
	if (playerHP <= 0)		
	{
		div();
		ot(("Health: " + playerHP));
		div();
		ascii();
		ot(("You succumb to your wounds and fall to the ground!"));
		div();
		ascii();
		dbldiv();
		ot("\t\t\tG\tA\tM\tE");
		div();
		ot("\t\t\tO\tV\tE\tR");
		dbldiv();
		div();
		ascii();
		div();
		PlaySoundA("scream_far3.wav", NULL, SND_ASYNC);
	}
}	//END

