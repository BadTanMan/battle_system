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
												-spell system doesn't reduce spell counter anymore
												-bomb option resets incorrect input counter properly   

update 08-04-2017 ver 0.05 by Danny Marshall	- fixed up classes to seperate information
												- changed from third person to second person
												- got rid of the playerName since it is now useless
												- made an enemyTurn method to reduce code
												- added freezeCounter and a forzen mechanic
*/

#include "stdafx.h"
#include "Encounter.h"
#include "windows.media.h" //enable music player
#pragma comment (lib, "winmm.lib") //enables music reader
#include <algorithm> //enables string transform() function 
																										
using namespace std;

//PLAYER SETTERS

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
	cout << "\t-attack\\hit" << endl;
	cout << "\t-block\\defend" << endl;
	cout << "\t-throw bomb" << endl;
	cout << "\t-spells\\cast spell" << endl;
	cout << "\t-help" << endl;
	cout << "\t-inventory\\i" << endl;
	cout << "\t-killself" << endl;
	cout << "\t-check enemy\\observe" << endl;
	cout << "\t-drink potion" << endl;
	cout << "\t-run away" << endl;
	cout << "\t-exit\\quit" << endl;
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
void ot(string user_s)
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
int potionCounter = 10;
int run;
int spellWait = 0;
int attackWait = 1;
int incorrect = 0;

//ENEMY TURN METHOD
void Enounter::enemyTurn()
{
	{
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
			cout << enemyName << " deals " << to_string(damage) << " damage to you." << endl;
			playerHP = playerHP - damage;
			PlaySoundA("claw_strike1.wav", NULL, SND_FILENAME);
		}
	}
}

//MAIN
void Enounter::battle()
{
	int freezeCounter = 0;
	ascii();
	div();
	ascii();
	intro();
	PlaySoundA("wait.wav", NULL, SND_FILENAME);
	ascii();
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
			cout << "Health: " << playerHP << endl;
		}
		else
		{
			if (spellWait <= 0)
			{
				spellWait = 0;
				ascii();
				cout << "Health: " << playerHP << "\t\tSpell Timer: " << spellWait << endl;
				ascii();
				PlaySoundA("wait2.wav", NULL, SND_FILENAME);
				cout << "You unleashes your energy!" << endl;
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				div();
			}
			else
			{
				ascii();
				cout << "Health: " << playerHP << "\t\tSpell Timer: " << spellWait << endl;
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
				cout << "You deal " + to_string(damage) + " damage to " + enemyName << endl;
				PlaySoundA("flameburst1.wav", NULL, SND_FILENAME);
				div();
				enemyHP = enemyHP - damage;
				if (enemyHP <= 0)
				{
					ascii();
					div();
					cout << enemyName << " has been slain!!" << endl;
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
				cout << "You cast freeze!" << endl;
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				div();
				cout << enemyName << " has frozen in place!" << endl;
				freezeCounter = 3;
				//CLEAR EQUIPPED SPELL
				spell = "";
				attackWait = 0;
				div();
				ascii();
				cout << "Health: " << playerHP << endl;
			}
			else if (spell == "SHIELD")
			{
				cout << "You are surrounded by a protective bubble!" << endl;
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				div();
				cout << enemyName << " attacks!" << endl;
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				hit = rand() % 6 + 1;
				//ENEMY HIT FAIL
				if (hit < 3)
				{
					cout << enemyName << " misses!" << endl;
					PlaySoundA("claw_miss2.wav", NULL, SND_FILENAME);
				}
				//ENEMT HIT SUCCESS
				else
				{
					damage = rand() % 3 + 1;
					cout << enemyName << " deals " << to_string(damage) << " damage to " << playerName << endl;
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
			if (attackWait > 0)
			{
				ot("Charging spell cannot attack!");
				spellWait++;
			}
			else
			{
				//PLAYER TURN
				cout << "You attack!\n";
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				hit = rand() % 6 + 1;

				//HIT PASS
				if (hit > 3)
				{
					damage = rand() % 10 + 1;
					cout << "You deal " << to_string(damage) << " damage to " << enemyName << endl;
					PlaySoundA("claw_strike1.wav", NULL, SND_FILENAME);
					enemyHP = enemyHP - damage;
					div();
					//ENEMY HEALTH CHECK
					if (enemyHP <= 0)
					{
						ascii();
						div();
						cout << enemyName << " has been slain!!" << endl;
						div();
						battleWon();
						//EXIT WHILE LOOP
						quit = true;
					}

					else if (freezeCounter != 0)
					{
						cout << enemyName << " is frozen solid and cannot act!!" << endl;
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
					cout << enemyName << " is frozen solid and cannot act!!" << endl;
					freezeCounter--;
				}

				else
				{
					//ENEMY TURN
					cout << "You miss!" << endl;
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
			cout << "You brace for impact!" << endl;
			PlaySoundA("wait.wav", NULL, SND_FILENAME);
			div();

			hit = rand() % 6 + 1;
			if (freezeCounter != 0)
			{
			cout << enemyName << " is frozen solid and cannot act!!" << endl;
			freezeCounter--;
			}
			else if (hit < 3)
			{
				cout << enemyName << " attacks!" << endl;
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				cout << enemyName << " misses!" << endl;
				PlaySoundA("claw_miss2.wav", NULL, SND_FILENAME);
			}
			else
			{
				cout << enemyName << " attacks!" << endl;
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				damage = rand() % 10 + 1;
				damage = damage / 2;
				cout << enemyName << " deals " << to_string(damage) << " damage to you." << endl;
				PlaySoundA("block.wav", NULL, SND_FILENAME);
				playerHP = playerHP - damage;

			}

			incorrect = 0;
		}

		//BOMB
		else if (playerInput == "THROW BOMB" || playerInput == "BOMB" || playerInput == "THROW BOMBS" || playerInput == "BOMBS" || playerInput == "THROW A BOMB")
		{
			if (attackWait <= 0)
			{
				damage = 4;
				cout <<"You throw a bomb!" << endl;
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				cout <<"You deal " << to_string(damage) << " damage to " << enemyName << endl;
				PlaySoundA("flameburst1.wav", NULL, SND_FILENAME);
				div();
				enemyHP = enemyHP - damage;
				if (enemyHP <= 0)
				{
					ascii();
					div();
					cout << enemyName << " has been slain!!" << endl;
					div();
					battleWon();
					//SET ITEM DISCOVERY AFTER DEATH
					/*win = true;*/
					//EXIT WHILE LOOP
					quit = true;
				}
				else if (freezeCounter != 0)
				{
					cout << enemyName << " is frozen solid and cannot act!!" << endl;
					freezeCounter--;
				}
				else
				{
					enemyTurn();
				}
				
			}
			else
			{
				cout << "Charging spell cannot attack!" << endl;
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
			cout << "\tPotions: " << potionCounter << endl;
			
			spellWait++;
			incorrect = 0;
		}
		
		//KILLSELF
		else if (playerInput == "KILLSELF" || playerInput == "SUICIDE" || playerInput == "COMMIT SUICIDE")
		{
			playerHP = 0;
			quit = true;
		}

		//OBSERVE
		else if (playerInput == "OBSERVE" || playerInput == "ENEMY HEALTH" || playerInput == "CHECK ENEMY")
		{
			cout << "\tEnemy Health: " << enemyHP << endl;
			div();
			ascii();
			PlaySoundA("wait.wav", NULL, SND_FILENAME);
			if (freezeCounter != 0)
			{
				cout << enemyName << " is frozen solid and cannot act!!" << endl;
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
					std::cout << "Health fully restored!" << endl;
					PlaySoundA("swingpsi1.wav", NULL, SND_FILENAME);	
				}
				else
				{	
					std::cout << "+6 Health restored!" << endl;
					PlaySoundA("swingpsi1.wav", NULL, SND_FILENAME);		
				}
				//ENEMY TURN AFTER PLAYER
				div();
				if (freezeCounter != 0)
				{
					cout << enemyName << " is frozen solid and cannot act!!" << endl;
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
			bool inputOk = false;
			while (!inputOk)
			{
				ot("\tFlare:\tCharge - 2 \tDamage - Does +5 damage to enemy");
				ot("\tShield:\tCharge - 2 \tEffect - Greatly reduces damage recieved");
				ot("\tFreeze:\tCharge - 3 \tEffect - Freezes enemy in place");
				div();
				ot("-enter BACK to quit spell menu-");
				div();
				cout << "Enter spell to cast: ";
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
					cout << "You start to focus";
					cout << ".";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					cout << ".";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					cout << "." << endl;
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					div();
					if (freezeCounter != 0)
					{
						cout << enemyName << " is frozen solid and cannot act!!" << endl;
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
					cout << playerName << " starts to focus";
					cout << ".";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					cout << ".";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					cout << "." << endl;
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					div();
					if (freezeCounter != 0)
					{
						cout << enemyName << " is frozen solid and cannot act!!" << endl;
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
					cout << playerName << " starts to focus";
					cout << ".";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					cout << ".";
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					cout << "." << endl;
					PlaySoundA("wait.wav", NULL, SND_FILENAME);
					div();
					if (freezeCounter != 0)
					{
						cout << enemyName << " is frozen solid and cannot act!!" << endl;
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
			run = rand() % 30 + 1;
			if (spell == "")
			{
				cout << "You try to flee";
				cout << ".";
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				cout << ".";
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				cout << "." << endl;
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				if (run < 10)
				{
					PlaySoundA("run.wav", NULL, SND_ASYNC);
					cout << "You fled from the battle!" << endl;
					div();
					battleOver();
					quit = true;
				}
				else
				{
					cout << "You failed to run away!" << endl;
					div();
					if (freezeCounter != 0)
					{
						cout << enemyName << " is frozen solid and cannot act!!" << endl;
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
				cout << "You stopped focusing!" << endl;
				spell = "";
				cout << "You try to flee";
				cout << ".";
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				cout << ".";
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				cout << "." << endl;
				PlaySoundA("wait.wav", NULL, SND_FILENAME);
				if (run < 10)
				{
					PlaySoundA("run.wav", NULL, SND_ASYNC);
					cout << "You fled from the battle!" << endl;
					battleOver();
					quit = true;
				}
				else
				{
					cout << "You failed to run away!" << endl;
					div();
					if (freezeCounter != 0)
					{
						cout << enemyName << " is frozen solid and cannot act!!" << endl;
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
			incorrect++;
			//DISPLAYS LIST OF COMMANDS UPON 3 INCORRECT ENTRIES
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
		cout << "You succumbs to your wounds and falls to the ground!" << endl;
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
} //END
